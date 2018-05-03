// #includes, using, etc
#pragma once

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
	//		pRenderer: pointer to the aie input.
	//--------------------------------------------------------------------------------------
	static void SetInputPointer(aie::Input * pInput);

private:

	//--------------------------------------------------------------------------------------
	// l_GetInstance: Lua bindings for the bootstrap Input GetInstance singleton function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_GetInputPointer(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_IsKeyDown: Lua bindings for the bootstrap Input IsKeyDown function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_IsKeyDown(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// pointer to the aie input.
	//--------------------------------------------------------------------------------------
	static aie::Input* sm_pInput;
};