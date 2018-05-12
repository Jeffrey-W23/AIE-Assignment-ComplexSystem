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
	class Input;
}

//--------------------------------------------------------------------------------------
// LuaInput object.
//--------------------------------------------------------------------------------------
class LuaInput
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	LuaInput();
	
	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	~LuaInput();

	//--------------------------------------------------------------------------------------
	// CreateInputLibrary: Create the lua library for the Input class.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static void CreateInputLibrary(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// SetInputPointer: Set the aie input pointer for the lua bindings.
	//
	// Param:
	//		pInput: pointer to the aie input.
	//--------------------------------------------------------------------------------------
	static void SetInputPointer(aie::Input * pInput);

	//--------------------------------------------------------------------------------------
	// pointer to the aie input.
	//--------------------------------------------------------------------------------------
	static aie::Input* sm_pInput;
};

// extern c all of the lua functions.
#ifdef __cplusplus
extern "C"
{
#endif
	//--------------------------------------------------------------------------------------
	// l_GetInstance: Lua bindings for the bootstrap Input GetInstance singleton function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_GetInputPointer(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_IsKeyDown: Lua bindings for the bootstrap Input IsKeyDown function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_IsKeyDown(lua_State* pLuaState);
#ifdef __cplusplus
}
#endif