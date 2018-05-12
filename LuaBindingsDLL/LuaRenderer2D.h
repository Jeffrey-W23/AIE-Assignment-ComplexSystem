// #includes, using, etc
#pragma once

// declspec for exporting functions for use with dll
#ifdef LUABINDINGSDLL_EXPORTS  
	#define LUABINDINGS_API __declspec(dllexport)   
#else  
	#define LUABINDINGS_API __declspec(dllimport)   
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
	static void SetRenderer2D(aie::Renderer2D* pRenderer);

	//--------------------------------------------------------------------------------------
	// pointer to the renderer2d.
	//--------------------------------------------------------------------------------------
	static aie::Renderer2D* sm_pRenderer2D;
};

// extern c all of the lua functions.
#ifdef __cplusplus
extern "C"
{
#endif
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
	LUABINDINGS_API extern int l_GetRenderer2D(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_Begin: Lua bindings for the bootstrap renderer2d Begin function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_Begin(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_End: Lua bindings for the bootstrap renderer2d End function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_End(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetCameraPos: Lua bindings for the bootstrap renderer2d SetCameraPos function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_SetCameraPos(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetRenderColour: Lua bindings for the bootstrap renderer2d SetRenderColour function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_SetRenderColour(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_SetUVRect: Lua bindings for the bootstrap renderer2d SetUVRect function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_SetUVRect(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawSprite: Lua bindings for the bootstrap renderer2d DrawSprite function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_DrawSprite(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawLine: Lua bindings for the bootstrap renderer2d DrawLine function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_DrawLine(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawCircle: Lua bindings for the bootstrap renderer2d DrawCircle function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_DrawCircle(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawBox: Lua bindings for the bootstrap renderer2d DrawBox function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_DrawBox(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_DrawText: Lua bindings for the bootstrap renderer2d DrawText function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_DrawText(lua_State* pLuaState);
#ifdef __cplusplus
}
#endif