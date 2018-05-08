// #includes, using, etc
#pragma once

// Preprogramming to check and then switch between if the program is a dll libary or static.
#ifdef STATIC_LIB
	#define LUA_DLL
#else
	#ifdef DLL_EXPORT
		#define LUA_DLL __declspec(dllexport)
	#else
		#define LUA_DLL __declspec(dllimport)
	#endif
#endif

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
	static void CreateRenderer2DLibrary(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// SetRenderer2D: Set the renderer2d for the lua bindings.
	//
	// Param:
	//		pRenderer: pointer to the renderer2d.
	//--------------------------------------------------------------------------------------
	static void SetRenderer2D(aie::Renderer2D* renderer);

private:

	//--------------------------------------------------------------------------------------
	// l_GetRenderer2D: Lua bindings for getting an instance of the bootstrap renderer2d
	// pointer in lua.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_GetRenderer2D(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_Begin: Lua bindings for the bootstrap renderer2d Begin function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_Begin(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_End: Lua bindings for the bootstrap renderer2d End function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_End(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetCameraPos: Lua bindings for the bootstrap renderer2d SetCameraPos function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_SetCameraPos(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetRenderColour: Lua bindings for the bootstrap renderer2d SetRenderColour function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_SetRenderColour(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetUVRect: Lua bindings for the bootstrap renderer2d SetUVRect function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_SetUVRect(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawSprite: Lua bindings for the bootstrap renderer2d DrawSprite function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_DrawSprite(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawLine: Lua bindings for the bootstrap renderer2d DrawLine function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_DrawLine(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawCircle: Lua bindings for the bootstrap renderer2d DrawCircle function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_DrawCircle(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawBox: Lua bindings for the bootstrap renderer2d DrawBox function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_DrawBox(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawText: Lua bindings for the bootstrap renderer2d DrawText function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_DrawText(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// pointer to the renderer2d.
	//--------------------------------------------------------------------------------------
	LUA_DLL static aie::Renderer2D* sm_pRenderer2D;
};