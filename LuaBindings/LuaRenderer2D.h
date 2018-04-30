// #includes, using, etc
#pragma once

// forward declares
struct lua_State;

namespace aie
{
	class Renderer2D;
}

//--------------------------------------------------------------------------------------
// LuaRenderer2D object.
//--------------------------------------------------------------------------------------
class LuaRenderer2D
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	LuaRenderer2D();

	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	~LuaRenderer2D();

	//--------------------------------------------------------------------------------------
	// CreateRenderer2DLibrary: Create the lua library for the Renderer2D class.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	void CreateRenderer2DLibrary(lua_State* pLuaState);

private:

	//--------------------------------------------------------------------------------------
	// SetRenderer2D: 
	//
	// Param:
	//		pRenderer: 
	//--------------------------------------------------------------------------------------
	static void SetRenderer2D(aie::Renderer2D* renderer);

	//--------------------------------------------------------------------------------------
	// l_GetRenderer2D: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_GetRenderer2D(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_Begin: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_Begin(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_End: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_End(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetCameraPos: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_SetCameraPos(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetRenderColour: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_SetRenderColour(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetUVRect: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_SetUVRect(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawSprite: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_DrawSprite(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawLine: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_DrawLine(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawCircle: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_DrawCircle(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawBox: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_DrawBox(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawText: 
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_DrawText(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// pointer to the renderer2d.
	//--------------------------------------------------------------------------------------
	static aie::Renderer2D* m_pRenderer2D;
};