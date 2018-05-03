// #includes, using, etc
#include "LuaInput.h"
#include "Lua.hpp"
#include "Input.h"

// static member initialization of m_pInput.
aie::Input* LuaInput::sm_pInput;

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
LuaInput::LuaInput()
{
}

//--------------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------------
LuaInput::~LuaInput()
{
}

//--------------------------------------------------------------------------------------
// CreateInputLibrary: Create the lua library for the Input class.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
void LuaInput::CreateInputLibrary(lua_State* pLuaState)
{
	// Register lua functions from cpp
	static const struct luaL_reg s_kslInputLibrary[] = {
		{ "GetInstance", l_GetInputPointer },
		{"IsKeyDown", l_IsKeyDown },
		{ NULL, NULL }
	};

	// Open library for lua
	luaL_openlib(pLuaState, "Input", s_kslInputLibrary, 0);
}

//--------------------------------------------------------------------------------------
// SetInputPointer: Set the aie input pointer for the lua bindings.
//
// Param:
//		pRenderer: pointer to the aie input.
//--------------------------------------------------------------------------------------
void LuaInput::SetInputPointer(aie::Input * pInput)
{
	// set the input pointer
	sm_pInput = pInput;
}

//--------------------------------------------------------------------------------------
// l_GetInstance: Lua bindings for the bootstrap Input GetInstance singleton function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaInput::l_GetInputPointer(lua_State* pLuaState)
{
	// make sure there are no values on the stack
	lua_pop(pLuaState, lua_gettop(pLuaState));

	// push error checking bool
	lua_pushboolean(pLuaState, true);

	// return a pointer to lua
	lua_pushlightuserdata(pLuaState, sm_pInput);

	// return 2 values.
	return 2;
}

//--------------------------------------------------------------------------------------
// l_IsKeyDown: Lua bindings for the bootstrap Input IsKeyDown function.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaInput::l_IsKeyDown(lua_State* pLuaState)
{
	// if there is no second argument
	if (lua_isnumber(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaInput::IsKeyDown argument 1 should be a number or input code (InputKeyID)");

		// return 2 values
		return 2;
	}

	// push error checking bool
	lua_pushboolean(pLuaState, true);

	// get int values from lua and store
	int nInputKeyID = (int)lua_tonumber(pLuaState, 1);

	// pop values off the stack
	lua_pop(pLuaState, 1);

	// call the renderer2d setCameraPos function and pass on lua values
	lua_pushboolean(pLuaState, sm_pInput->isKeyDown(nInputKeyID));

	// return 2 values
	return 2;
}