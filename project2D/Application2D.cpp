// #includes, using, etc
#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
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
	// Run the lua application startup
	bool bSuccessful = LuaApplication::startup();

	// if the startup is successful
	if (bSuccessful)
	{
		// load the lua file demo.lua
		LoadLuaFileToExecute("demo.lua");
	}

	// return successful
	return bSuccessful;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void Application2D::shutdown() 
{
	// Run the lua application shutdown
	LuaApplication::shutdown();
}

//--------------------------------------------------------------------------------------
// Update: A virtual function to update objects.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void Application2D::update(float deltaTime) 
{
	// Run the lua application update
	LuaApplication::update(deltaTime);
}

//--------------------------------------------------------------------------------------
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void Application2D::draw() 
{
	// Run the lua application draw
	LuaApplication::draw();
}
