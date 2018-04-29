// #includes using etc.
#include "LuaRenderer2D.h"
#include "Lua.hpp"
#include "Renderer2D.h"

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
LuaRenderer2D::LuaRenderer2D()
{

}

//--------------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------------
LuaRenderer2D::~LuaRenderer2D()
{

}

//--------------------------------------------------------------------------------------
// CreateRenderer2DLibrary: Create the lua library for the Renderer2D class.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
void LuaRenderer2D::CreateRenderer2DLibrary(lua_State* pLuaState)
{
	// Register lua functions from cpp
	static const struct luaL_reg s_kslRenderer2DLibrary[] = {
		{ "New", l_Renderer2DNew },
		{ "Delete", l_Renderer2DDelete },
		{ "Begin", l_Begin },
		{ "End", l_End },
		{ "SetCameraPos", l_SetCameraPos },
		{ "SetRenderColour", l_SetRenderColour },
		{ "SetUVRect", l_SetUVRect },
		{ "DrawSprite", l_DrawSprite },
		{ "DrawLine", l_DrawLine },
		{ "DrawCircle", l_DrawCircle },
		{ "DrawBox", l_DrawBox },
		{ "DrawText", l_DrawText },
		{ NULL, NULL }
	};

	// Open library for lua
	luaL_openlib(pLuaState, "Renderer2D", s_kslRenderer2DLibrary, 0);
}

//--------------------------------------------------------------------------------------
// l_Renderer2DNew: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_Renderer2DNew(lua_State* pLuaState)
{
	aie::Renderer2D* rRenderer2D = new aie::Renderer2D();
	lua_pushlightuserdata(pLuaState, rRenderer2D);

	return 1;
}

//--------------------------------------------------------------------------------------
// l_Renderer2DDelete: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_Renderer2DDelete(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...

	return 0; // returning 0 result
}

//--------------------------------------------------------------------------------------
// l_Begin: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_Begin(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_End: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_End(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_SetCameraPos: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_SetCameraPos(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_SetRenderColour: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_SetRenderColour(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_SetUVRect: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_SetUVRect(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_DrawSprite: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_DrawSprite(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_DrawLine: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_DrawLine(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_DrawCircle: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_DrawCircle(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_DrawBox: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_DrawBox(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}

//--------------------------------------------------------------------------------------
// l_DrawText: 
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaRenderer2D::l_DrawText(lua_State* pLuaState)
{
	// get function argument
	// calling C++ function with this argument...
	// nothing to return!

	return 0;
}


// https://eliasdaler.wordpress.com/2013/11/30/lua_and_cpp_pt3/