// #includes using etc.
#include "LuaRenderer2D.h"
#include "Lua.hpp"

#include "Renderer2D.h"
#include "Texture.h"
#include "Font.h"
#include <assert.h>

// static member initialization of m_pRenderer2D.
aie::Renderer2D* LuaRenderer2D::sm_pRenderer2D;

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
		{ "Get", l_GetRenderer2D },
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
// SetRenderer2D: Set the renderer2d for the lua bindings.
//
// Param:
//		pRenderer: pointer to the renderer2d.
//--------------------------------------------------------------------------------------
void LuaRenderer2D::SetRenderer2D(aie::Renderer2D* pRenderer)
{
	// set the renderer2d
	sm_pRenderer2D = pRenderer;
}

//--------------------------------------------------------------------------------------
// l_GetRenderer2D: Lua bindings for getting an instance of the bootstrap renderer2d
// pointer in lua.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_GetRenderer2D(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));
	
	// push the renderer2d
	lua_pushlightuserdata(pLuaState, (void*)LuaRenderer2D::sm_pRenderer2D);

	// returning 1 value
	return 1;
}

//--------------------------------------------------------------------------------------
// l_Begin: Lua bindings for the bootstrap renderer2d Begin function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_Begin(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));

	// call the renderer2d begin function
	LuaRenderer2D::sm_pRenderer2D->begin();

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_End: Lua bindings for the bootstrap renderer2d End function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_End(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));

	// call the renderer2d end function
	LuaRenderer2D::sm_pRenderer2D->end();

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_SetCameraPos: Lua bindings for the bootstrap renderer2d SetCameraPos function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_SetCameraPos(lua_State* pLuaState)
{
	// if the stack isnt 2
	if (lua_gettop(pLuaState) != 2)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));
		
		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetCameraPos requires exactly 2 arguments (xPos, yPos)");
		
		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isnumber(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetCameraPos argument 1 should be a number (xPos)");
		
		// return 2 values
		return 2;
	
	}

	// if there is no second argument
	if (lua_isnumber(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetCameraPos argument 2 should be a number (yPos)");
		
		// return 2 values
		return 2;
	}

	// get 2 float values from lua and store
	float fX = (float)lua_tonumber(pLuaState, 1);
	float fY = (float)lua_tonumber(pLuaState, 2);
	
	// pop values off the stack
	lua_pop(pLuaState, 2);

	// call the renderer2d setCameraPos function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->setCameraPos(fX, fY);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_SetRenderColour: Lua bindings for the bootstrap renderer2d SetRenderColour function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_SetRenderColour(lua_State* pLuaState)
{
	// if the stack isnt 4
	if (lua_gettop(pLuaState) != 4)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetRenderColour requires exactly 4 arguments (R, G, B, A)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isnumber(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetRenderColour argument 1 should be a number (R)");

		// return 2 values
		return 2;

	}

	// if there is no second argument
	if (lua_isnumber(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetRenderColour argument 2 should be a number (G)");

		// return 2 values
		return 2;
	}

	// if there is no third argument
	if (lua_isnumber(pLuaState, 3) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetRenderColour argument 3 should be a number (B)");

		// return 2 values
		return 2;
	}

	// if there is no fourth argument
	if (lua_isnumber(pLuaState, 4) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetRenderColour argument 4 should be a number (A)");

		// return 2 values
		return 2;
	}

	// get 4 float values from lua and store
	float fR = (float)lua_tonumber(pLuaState, 1);
	float fG = (float)lua_tonumber(pLuaState, 2);
	float fB = (float)lua_tonumber(pLuaState, 3);
	float fA = (float)lua_tonumber(pLuaState, 4);

	// pop values off the stack
	lua_pop(pLuaState, 4);

	// call the renderer2d setRenderColour function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->setRenderColour(fR, fG, fB, fA);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_SetUVRect: Lua bindings for the bootstrap renderer2d SetUVRect function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_SetUVRect(lua_State* pLuaState)
{
	// if the stack isnt 4
	if (lua_gettop(pLuaState) != 4)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetUVRect requires exactly 4 arguments (uvX, uvY, uvW, uvH)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isnumber(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetUVRect argument 1 should be a number (uvX)");

		// return 2 values
		return 2;

	}

	// if there is no second argument
	if (lua_isnumber(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetUVRect argument 2 should be a number (uvY)");

		// return 2 values
		return 2;
	}

	// if there is no third argument
	if (lua_isnumber(pLuaState, 3) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetUVRect argument 3 should be a number (uvW)");

		// return 2 values
		return 2;
	}

	// if there is no fourth argument
	if (lua_isnumber(pLuaState, 4) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::SetUVRect argument 4 should be a number (uvH)");

		// return 2 values
		return 2;
	}

	// get 4 float values from lua and store
	float fUVx = (float)lua_tonumber(pLuaState, 1);
	float fUVy = (float)lua_tonumber(pLuaState, 2);
	float fUVw = (float)lua_tonumber(pLuaState, 3);
	float fUVh = (float)lua_tonumber(pLuaState, 4);

	// pop values off the stack
	lua_pop(pLuaState, 4);

	// call the renderer2d setUVRect function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->setUVRect(fUVx, fUVy, fUVw, fUVh);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_DrawSprite: Lua bindings for the bootstrap renderer2d DrawSprite function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_DrawSprite(lua_State* pLuaState)
{
	// if the stack isnt 9
	if (lua_gettop(pLuaState) != 9)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite requires exactly 9 arguments (Texture, X, Y, Width, Height, Rotation, Depth, OriginX, OriginY)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isnil(pLuaState, 1) == 0 && lua_isuserdata(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 1 should be a userdate or nil (Texture)");

		// return 2 values
		return 2;
	}

	// if there is no second argument
	if (lua_isnumber(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 2 should be a number (X)");

		// return 2 values
		return 2;
	}

	// if there is no third argument
	if (lua_isnumber(pLuaState, 3) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 3 should be a number (Y)");

		// return 2 values
		return 2;
	}

	// if there is no fourth argument
	if (lua_isnumber(pLuaState, 4) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 4 should be a number (Width)");

		// return 2 values
		return 2;
	}

	// if there is no fifth argument
	if (lua_isnumber(pLuaState, 5) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 5 should be a number (Height)");

		// return 2 values
		return 2;
	}

	// if there is no sixth argument
	if (lua_isnumber(pLuaState, 6) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 6 should be a number (Rotation)");

		// return 2 values
		return 2;
	}

	// if there is no seventh argument
	if (lua_isnumber(pLuaState, 7) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 7 should be a number (Depth)");

		// return 2 values
		return 2;
	}

	// if there is no eighth argument
	if (lua_isnumber(pLuaState, 8) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 8 should be a number (OriginX)");

		// return 2 values
		return 2;
	}

	// if there is no ninth argument
	if (lua_isnumber(pLuaState, 9) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawSprite argument 9 should be a number (OriginY)");

		// return 2 values
		return 2;
	}

	// get 9 values from lua and store
	aie::Texture* pTexture = (aie::Texture*)lua_touserdata(pLuaState, 1);
	float fX = (float)lua_tonumber(pLuaState, 2);
	float fY = (float)lua_tonumber(pLuaState, 3);
	float fWidth = (float)lua_tonumber(pLuaState, 4);
	float fHeight = (float)lua_tonumber(pLuaState, 5);
	float fRotation = (float)lua_tonumber(pLuaState, 6);
	float fDepth = (float)lua_tonumber(pLuaState, 7);
	float fOriginX = (float)lua_tonumber(pLuaState, 8);
	float fOriginY = (float)lua_tonumber(pLuaState, 9);

	// pop values off the stack
	lua_pop(pLuaState, 9);

	// call the renderer2d drawSprite function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->drawSprite(pTexture, fX, fY, fWidth, fHeight, fRotation, fDepth, fOriginX, fOriginY);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_DrawLine: Lua bindings for the bootstrap renderer2d DrawLine function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_DrawLine(lua_State* pLuaState)
{
	// if the stack isnt 6
	if (lua_gettop(pLuaState) != 6)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawLine requires exactly 6 arguments (X1, Y1, X2, Y2, Thickness, Depth)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isnumber(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawLine argument 1 should be a number (X1)");

		// return 2 values
		return 2;
	}

	// if there is no second argument
	if (lua_isnumber(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawLine argument 2 should be a number (Y1)");

		// return 2 values
		return 2;
	}

	// if there is no third argument
	if (lua_isnumber(pLuaState, 3) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawLine argument 3 should be a number (X2)");

		// return 2 values
		return 2;
	}

	// if there is no fourth argument
	if (lua_isnumber(pLuaState, 4) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawLine argument 4 should be a number (Y2)");

		// return 2 values
		return 2;
	}

	// if there is no fifth argument
	if (lua_isnumber(pLuaState, 5) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawLine argument 5 should be a number (Thickness)");

		// return 2 values
		return 2;
	}

	// if there is no sixth argument
	if (lua_isnumber(pLuaState, 6) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawLine argument 6 should be a number (Depth)");

		// return 2 values
		return 2;
	}

	// get 6 values from lua and store
	float fX1 = (float)lua_tonumber(pLuaState, 1);
	float fY1 = (float)lua_tonumber(pLuaState, 2);
	float fX2 = (float)lua_tonumber(pLuaState, 3);
	float fY2 = (float)lua_tonumber(pLuaState, 4);
	float fThickness = (float)lua_tonumber(pLuaState, 5);
	float fDepth = (float)lua_tonumber(pLuaState, 6);

	// pop values off the stack
	lua_pop(pLuaState, 6);

	// call the renderer2d drawLine function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->drawLine(fX1, fY1, fX2, fY2, fThickness, fDepth);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_DrawCircle: Lua bindings for the bootstrap renderer2d DrawCircle function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_DrawCircle(lua_State* pLuaState)
{
	// if the stack isnt 4
	if (lua_gettop(pLuaState) != 4)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawCircle requires exactly 4 arguments (X, Y, Radius, Depth)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isnumber(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawCircle argument 1 should be a number (X)");

		// return 2 values
		return 2;
	}

	// if there is no second argument
	if (lua_isnumber(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawCircle argument 2 should be a number (Y)");

		// return 2 values
		return 2;
	}

	// if there is no third argument
	if (lua_isnumber(pLuaState, 3) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawCircle argument 3 should be a number (Radius)");

		// return 2 values
		return 2;
	}

	// if there is no fourth argument
	if (lua_isnumber(pLuaState, 4) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawCircle argument 4 should be a number (Depth)");

		// return 2 values
		return 2;
	}

	// get 4 values from lua and store
	float fX = (float)lua_tonumber(pLuaState, 1);
	float fY = (float)lua_tonumber(pLuaState, 2);
	float fRadius = (float)lua_tonumber(pLuaState, 3);
	float fDepth = (float)lua_tonumber(pLuaState, 4);

	// pop values off the stack
	lua_pop(pLuaState, 4);

	// call the renderer2d drawCircle function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->drawCircle(fX, fY, fRadius, fDepth);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_DrawBox: Lua bindings for the bootstrap renderer2d DrawBox function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_DrawBox(lua_State* pLuaState)
{
	// if the stack isnt 6
	if (lua_gettop(pLuaState) != 6)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawBox requires exactly 6 arguments (X, Y, Width, Height, Rotation, Depth)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isnumber(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawBox argument 1 should be a number (X)");

		// return 2 values
		return 2;

	}

	// if there is no second argument
	if (lua_isnumber(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawBox argument 2 should be a number (Y)");

		// return 2 values
		return 2;
	}

	// if there is no third argument
	if (lua_isnumber(pLuaState, 3) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawBox argument 3 should be a number (Width)");

		// return 2 values
		return 2;
	}

	// if there is no fourth argument
	if (lua_isnumber(pLuaState, 4) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawBox argument 4 should be a number (Height)");

		// return 2 values
		return 2;
	}

	// if there is no fifth argument
	if (lua_isnumber(pLuaState, 5) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawBox argument 5 should be a number (Rotation)");

		// return 2 values
		return 2;
	}

	// if there is no sixth argument
	if (lua_isnumber(pLuaState, 6) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawBox argument 6 should be a number (Depth)");

		// return 2 values
		return 2;
	}

	// get 6 float values from lua and store
	float fX = (float)lua_tonumber(pLuaState, 1);
	float fY = (float)lua_tonumber(pLuaState, 2);
	float fWidth = (float)lua_tonumber(pLuaState, 3);
	float fHeight = (float)lua_tonumber(pLuaState, 4);
	float fRotation = (float)lua_tonumber(pLuaState, 5);
	float fDepth = (float)lua_tonumber(pLuaState, 6);

	// pop values off the stack
	lua_pop(pLuaState, 6);

	// call the renderer2d drawBox function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->drawBox(fX, fY, fWidth, fHeight, fRotation, fDepth);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}

//--------------------------------------------------------------------------------------
// l_DrawText: Lua bindings for the bootstrap renderer2d DrawText function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//
// Return:
//		int: How many values are being returned.
//--------------------------------------------------------------------------------------
extern int l_DrawText(lua_State* pLuaState)
{
	// if the stack isnt 5
	if (lua_gettop(pLuaState) != 5)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawText requires exactly 5 arguments (Font, Text, X, Y, Depth)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isuserdata(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawText argument 1 should be a user data (Font)");

		// return 2 values
		return 2;

	}

	// if there is no second argument
	if (lua_isstring(pLuaState, 2) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawText argument 2 should be a string (Text)");

		// return 2 values
		return 2;

	}

	// if there is no third argument
	if (lua_isnumber(pLuaState, 3) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawText argument 3 should be a number (X)");

		// return 2 values
		return 2;

	}

	// if there is no fourth argument
	if (lua_isnumber(pLuaState, 4) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawText argument 4 should be a number (Y)");

		// return 2 values
		return 2;

	}

	// if there is no fifth argument
	if (lua_isnumber(pLuaState, 5) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaRenderer2D::DrawText argument 5 should be a number (Depth)");

		// return 2 values
		return 2;

	}

	// get 5 float values from lua and store
	aie::Font* pFont = (aie::Font*)lua_touserdata(pLuaState, 1);
	const char* kcpText = (char*)lua_tostring(pLuaState, 2);
	float fX = (float)lua_tonumber(pLuaState, 3);
	float fY = (float)lua_tonumber(pLuaState, 4);
	float fDepth = (float)lua_tonumber(pLuaState, 5);

	// pop values off the stack
	lua_pop(pLuaState, 5);

	// call the renderer2d drawText function and pass on lua values
	LuaRenderer2D::sm_pRenderer2D->drawText(pFont, kcpText, fX, fY, fDepth);

	// push true and returns 1 value
	lua_pushboolean(pLuaState, true);
	return 1;
}