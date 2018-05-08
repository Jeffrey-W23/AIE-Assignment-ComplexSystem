// #includes, using, etc
#include "LuaApplication.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <lauxlib.h>
#include <lualib.h> 
#include "Lua.hpp"

#include "LuaRenderer2D.h"
#include "LuaTexture.h"
#include "LuaFont.h"
#include "LuaInput.h"

#include <iostream>

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



aie::Application* currentApp;

//--------------------------------------------------------------------------------------
// startup: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
//--------------------------------------------------------------------------------------
bool LuaApplication::startup()
{
	currentApp = this;
	// new pointer to renderer2d
	m_2dRenderer = new aie::Renderer2D();

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
	m_pLuaRenderer2D->SetRenderer2D(m_2dRenderer);

	// return true for startup
	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void LuaApplication::shutdown()
{
	// delete pointers
	delete m_2dRenderer;

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
		LoadLuaFileToExecute("demo.lua"); // needs to refresh the passed in files from application2d
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
//		kcFunction:
//		fParam:
//		fReturn:
//		fErrorfnc:
//		deltaTime:
//--------------------------------------------------------------------------------------
void LuaApplication::LoadLuaFunctionToExecute(const char* kcFunction, int fParam, int fReturn, int fErrorfnc, float deltaTime)
{
	// get the global variable update and pushes it to the top of the stack
	lua_getglobal(m_pLuaState, kcFunction);

	// if there is something on the top of stack
	if (lua_isfunction(m_pLuaState, -1))
	{
		// if there is a param // For now this is only used for the Update function
		if (fParam > 0)
		{
			// push deltatime onto the stack
			lua_pushnumber(m_pLuaState, deltaTime);
		}

		// call function
		if (lua_pcall(m_pLuaState, fParam, fReturn, fErrorfnc) != 0)
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
//--------------------------------------------------------------------------------------
extern int l_ClearScreen(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));

	// call the renderer2d clearScreen function
	currentApp->clearScreen();

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_Quit: Lua bindings for the bootstrap Application Quit function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
extern int l_Quit(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));

	// call the renderer2d quit function
	currentApp->quit();

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}