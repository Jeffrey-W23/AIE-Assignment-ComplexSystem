// #includes, using, etc
#include "LuaApplication.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Lua.hpp"
#include "LuaRenderer2D.h"
#include "LuaTexture.h"
#include "LuaFont.h"
#include "LuaInput.h"
#include <iostream>

// static member initialization of m_pCurrentApp and m_pRenderer2D.
aie::Application* LuaApplication::sm_pCurrentApp;
aie::Renderer2D* LuaApplication::sm_pRenderer2D;

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
LuaApplication::LuaApplication()
{
}

//--------------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------------
LuaApplication::~LuaApplication()
{
}

//--------------------------------------------------------------------------------------
// startup: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
//--------------------------------------------------------------------------------------
bool LuaApplication::startup()
{
	// assign currentapp pointer
	sm_pCurrentApp = this;
	
	// new pointer to renderer2d
	sm_pRenderer2D = new aie::Renderer2D();

	// Create a new lua state and open libs.
	m_pLuaState = luaL_newstate();
	luaL_openlibs(m_pLuaState);

	// Create each of the lua libaray functions
	m_pLuaRenderer2D->CreateRenderer2DLibrary(m_pLuaState);
	m_pLuaTexture->CreateTextureLibrary(m_pLuaState);
	m_pLuaFont->CreateFontLibrary(m_pLuaState);
	m_pLuaInput->CreateInputLibrary(m_pLuaState);
	CreateApplicationLibrary(m_pLuaState);

	// set the renderer2d for lua
	m_pLuaRenderer2D->SetRenderer2D(sm_pRenderer2D);

	// return true for startup
	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void LuaApplication::shutdown()
{
	// delete pointers
	delete sm_pRenderer2D;

	// Load the lua function
	LoadLuaFunctionToExecute("Shutdown", 0, 0, 0, 0);

	// clean up the textures and the fonts being used in lua.
	m_pLuaTexture->CleanUpTextureMap();
	m_pLuaFont->CleanUpFontMap();

	// close the lua state
	lua_close(m_pLuaState);
}

//--------------------------------------------------------------------------------------
// Update: A virtual function to update objects.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void LuaApplication::update(float deltaTime)
{
	// Get input instance
	aie::Input* input = aie::Input::getInstance();

	// if the grave accent key is pressed
	if (input->wasKeyPressed(aie::INPUT_KEY_GRAVE_ACCENT))
	{
		// reload the demo.lua file
		LoadLuaFileToExecute(m_kcFileName);
	}

	// Set the aie input pointer for lua
	m_pLuaInput->SetInputPointer(input);

	// Load the lua function
	LoadLuaFunctionToExecute("Update", 1, 0, 0, deltaTime);
}

//--------------------------------------------------------------------------------------
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void LuaApplication::draw()
{
	// Load the lua function
	LoadLuaFunctionToExecute("Draw", 0, 0, 0, 0);
}

//--------------------------------------------------------------------------------------
// LoadLuaFunctionToExecute: Load and excute a lua function by passed in function name.
//
// TODO: Make this function a templated function so that if a lua functions has a param 
// the param can be passed in regardless of type. 
//
// Param:
//		kcFunction: const char pointer for function name that you want to call.
//		nParam: How many param does this function have.
//		nReturn: How many returns does this function have.
//		nErrorfnc: How many error functions does this function have.
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void LuaApplication::LoadLuaFunctionToExecute(const char* kcFunction, int nParam, int nReturn, int nErrorfnc, float deltaTime)
{
	// get the global variable update and pushes it to the top of the stack
	lua_getglobal(m_pLuaState, kcFunction);

	// if there is something on the top of stack
	if (lua_isfunction(m_pLuaState, -1))
	{
		// if there is a param // For now this is only used for the Update function
		if (nParam > 0)
		{
			// push deltatime onto the stack
			lua_pushnumber(m_pLuaState, deltaTime);
		}

		// call function
		if (lua_pcall(m_pLuaState, nParam, nReturn, nErrorfnc) != 0)
		{
			// print any errors
			std::cout << "Function Error: " << lua_tostring(m_pLuaState, -1) << std::endl;

			// pop off the of the stack
			lua_pop(m_pLuaState, 1);
		}
	}
	else
	{
		// pop off the top of the stack
		lua_pop(m_pLuaState, -1);
	}
}

// --------------------------------------------------------------------------------------
// LoadLuaFileToExecute: Load and excute a lua file by the passed in filename.
//
// Param:
//		kcFileName: const char pointer for the filename of the lua file to load.
//--------------------------------------------------------------------------------------
void LuaApplication::LoadLuaFileToExecute(const char* kcFileName)
{
	// Load and excute file.
	int nError = luaL_dofile(m_pLuaState, kcFileName);

	// if there is an error.
	if (nError != 0)
	{
		// print error to the console.
		std::cout << "Failed to load the file 'demo.lua'" << std::endl;
		std::cout << "Lua Error: " << lua_tostring(m_pLuaState, -1) << std::endl;

		// pop anything that might be on the stack.
		lua_pop(m_pLuaState, 1);

		// pause the application.
		system("pause");
	}

	// if no error
	if (nError == 0)
	{
		// assign file to memeber var
		m_kcFileName = kcFileName;
	}
}

//--------------------------------------------------------------------------------------
// CreateApplicationLibrary: Create the lua library for the Application class.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
void LuaApplication::CreateApplicationLibrary(lua_State* pLuaState)
{
	// Register lua functions from cpp
	static const struct luaL_reg s_kslApplicationLibrary[] = {
		{ "ClearScreen", l_ClearScreen }, // functions need to be static??
		{ "Quit", l_Quit },
	{ NULL, NULL }
	};

	// Open library for lua
	luaL_openlib(pLuaState, "Application", s_kslApplicationLibrary, 0);
}

//--------------------------------------------------------------------------------------
// l_ClearScreen: Lua bindings for the bootstrap Application ClearScreen function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_ClearScreen(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));

	// call the renderer2d clearScreen function
	LuaApplication::sm_pCurrentApp->clearScreen();

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_Quit: Lua bindings for the bootstrap Application Quit function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_Quit(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));

	// call the renderer2d quit function
	LuaApplication::sm_pCurrentApp->quit();

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}