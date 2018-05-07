// #includes, using, etc
#include "LuaInitialize.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Lua.hpp"
#include <lauxlib.h>
#include <lualib.h> 
#include "LuaRenderer2D.h"
#include "LuaTexture.h"
#include "LuaFont.h"
#include "LuaInput.h"
#include <iostream>





// static member initialization of m_pRenderer2D.
lua_State* LuaInitialize::m_pLuaState;
LuaRenderer2D* LuaInitialize::m_pLuaRenderer2D;
LuaTexture* LuaInitialize::m_pLuaTexture;
LuaFont* LuaInitialize::m_pLuaFont;
LuaInput* LuaInitialize::m_pLuaInput;






//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
LuaInitialize::LuaInitialize()
{
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
LuaInitialize::~LuaInitialize()
{
}

//--------------------------------------------------------------------------------------
// startup: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
//--------------------------------------------------------------------------------------
bool LuaInitialize::Startup(aie::Renderer2D* Renderer2D)
{
	// Create a new lua state and open libs.
	m_pLuaState = luaL_newstate();
	luaL_openlibs(m_pLuaState);

	// Create each of the lua libaray functions
	m_pLuaRenderer2D->CreateRenderer2DLibrary(m_pLuaState);
	m_pLuaTexture->CreateTextureLibrary(m_pLuaState);
	m_pLuaFont->CreateFontLibrary(m_pLuaState);
	m_pLuaInput->CreateInputLibrary(m_pLuaState);

	// set the renderer2d for lua
	m_pLuaRenderer2D->SetRenderer2D(Renderer2D);

	// load the lua file demo.lua
	LoadLuaFileToExecute("demo.lua");

	// return true for startup
	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void LuaInitialize::Shutdown()
{
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
void LuaInitialize::Update(float deltaTime, aie::Input* Input)
{
	// if the grave accent key is pressed
	if (Input->wasKeyPressed(aie::INPUT_KEY_GRAVE_ACCENT))
	{
		// reload the demo.lua file
		LoadLuaFileToExecute("demo.lua");
	}

	// Set the aie input pointer for lua
	m_pLuaInput->SetInputPointer(Input);

	// Load the lua function
	LoadLuaFunctionToExecute("Update", 1, 1, 0, deltaTime);
}

//--------------------------------------------------------------------------------------
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void LuaInitialize::Draw()
{
	// Load the lua function
	LoadLuaFunctionToExecute("Draw", 0 ,0 ,0, 0);
}

//--------------------------------------------------------------------------------------
// LoadLuaFunctionToExecute: Load and excute a lua function by passed in function name.
//
// Param:
//		kcFunction:
//		fParam:
//		fReturn:
//		fErrorfnc:
//		deltaTime:
//--------------------------------------------------------------------------------------
void LuaInitialize::LoadLuaFunctionToExecute(const char* kcFunction, int fParam, int fReturn, int fErrorfnc, float deltaTime)
{
	// get the global variable update and pushes it to the top of the stack
	lua_getglobal(m_pLuaState, kcFunction);

	// if there is something on the top of stack
	if (lua_isfunction(m_pLuaState, -1))
	{
		// push deltatime onto the stack
		lua_pushnumber(m_pLuaState, deltaTime);

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
void LuaInitialize::LoadLuaFileToExecute(const char* kcFileName)
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
