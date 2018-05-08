// #includes, using, etc
#pragma once
#include "LuaApplication.h"

//--------------------------------------------------------------------------------------
// Application2D object. Inherits from Application.
//--------------------------------------------------------------------------------------
class Application2D : public LuaApplication
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Application2D();

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	virtual ~Application2D();

	//--------------------------------------------------------------------------------------
	// startup: Initialize the game.
	//
	// Returns:
	//		bool: Returns a true or false for if the startup is sucessful.
	//--------------------------------------------------------------------------------------
	virtual bool startup();

	//--------------------------------------------------------------------------------------
	// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
	//--------------------------------------------------------------------------------------
	virtual void shutdown();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	virtual void update(float deltaTime);

	//--------------------------------------------------------------------------------------
	// Draw: A virtual function to render (or "draw") objects to the screen.
	//--------------------------------------------------------------------------------------
	virtual void draw();
};