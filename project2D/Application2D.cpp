// #includes, using, etc
#include "Application2D.h"
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

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
Application2D::Application2D() 
{
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Application2D::~Application2D() 
{
}

//--------------------------------------------------------------------------------------
// startup: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
//--------------------------------------------------------------------------------------
bool Application2D::startup() 
{
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

	// set the renderer2d for lua
	m_pLuaRenderer2D->SetRenderer2D(m_2dRenderer);

	// load the lua file demo.lua
	LoadLuaFileToExecute("demo.lua");








	// PUT THIS IN A FUNCTION SO I DONT HAVE TO REPEAT

	//// get the global variable startup and pushes it to the top of the stack
	//lua_getglobal(m_pLuaState, "Startup");

	//// if there is something on the top of stack
	//if (lua_isfunction(m_pLuaState, -1))
	//{
	//	// call function
	//	if (lua_pcall(m_pLuaState, 0, 0, 0) != 0)
	//	{
	//		std::cout << "Function Error: " << lua_tostring(m_pLuaState, -1) << std::endl;

	//		lua_pop(m_pLuaState, 1);
	//	}
	//}
	//else
	//{
	//	// pop off the top of the stack
	//	lua_pop(m_pLuaState, -1);
	//}









	
	// return true for startup
	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void Application2D::shutdown() 
{
	// delete pointers
	delete m_2dRenderer;

	// get the global variable shutdown and pushes it to the top of the stack
	lua_getglobal(m_pLuaState, "Shutdown");

	// if there is something on the top of stack
	if (lua_isfunction(m_pLuaState, -1))
	{
		// call function
		if (lua_pcall(m_pLuaState, 0, 0, 0) != 0)
		{
			std::cout << "Function Error: " << lua_tostring(m_pLuaState, -1) << std::endl;

			lua_pop(m_pLuaState, 1);
		}
	}
	else
	{
		// pop off the top of the stack
		lua_pop(m_pLuaState, -1);
	}

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
void Application2D::update(float deltaTime) 
{
	// Get input instance
	aie::Input* input = aie::Input::getInstance();
	
	// if escape key close down application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// if the grave accent key is pressed
	if (input->wasKeyPressed(aie::INPUT_KEY_GRAVE_ACCENT))
	{
		// reload the demo.lua file
		LoadLuaFileToExecute("demo.lua");
	}

	// Set the aie input pointer for lua
	m_pLuaInput->SetInputPointer(input);

	// get the global variable update and pushes it to the top of the stack
	lua_getglobal(m_pLuaState, "Update");
	
	// if there is something on the top of stack
	if (lua_isfunction(m_pLuaState, -1))
	{
		// push deltatime onto the stack
		lua_pushnumber(m_pLuaState, deltaTime);

		// call function
		if (lua_pcall(m_pLuaState, 1, 1, 0) != 0)
		{
			std::cout << "Function Error: " << lua_tostring(m_pLuaState, -1) << std::endl;

			lua_pop(m_pLuaState, 1);
		}

		// new bool for if update is successful
		bool bSuccess = true;

		// Is the top of the stack a bool
		if (lua_isboolean(m_pLuaState, -1))
		{
			// put the success bool on the stack
			bSuccess = lua_toboolean(m_pLuaState, -1);
		}

		// pop 1 value of the stack
		lua_pop(m_pLuaState, 1);
	}
	else
	{
		// pop off the top of the stack
		lua_pop(m_pLuaState, -1);
	}
}

//--------------------------------------------------------------------------------------
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void Application2D::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// get the global variable draw and pushes it to the top of the stack
	lua_getglobal(m_pLuaState, "Draw");
	
	// if there is something on the top of stack
	if (lua_isfunction(m_pLuaState, -1))
	{
		// call function
		if (lua_pcall(m_pLuaState, 0, 0, 0) != 0)
		{
			std::cout << "Function Error: " << lua_tostring(m_pLuaState, -1) << std::endl;

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
void Application2D::LoadLuaFileToExecute(const char* kcFileName)
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
