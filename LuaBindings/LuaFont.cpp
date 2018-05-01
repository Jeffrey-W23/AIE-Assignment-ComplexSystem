// #includes, using, etc
#include "LuaFont.h"
#include "Lua.hpp"
#include "Font.h"

// static member initialization of m_mfLoadedFonts.
std::map <std::string, aie::Font*> LuaFont::m_mfLoadedFonts;

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
LuaFont::LuaFont()
{
}

//--------------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------------
LuaFont::~LuaFont()
{
	// clean up textures
	CleanUpFontMap();
}

//--------------------------------------------------------------------------------------
// CreateFontLibrary: Create the lua library for the Font class.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
void LuaFont::CreateFontLibrary(lua_State* pLuaState)
{
	// Register lua functions from cpp
	static const struct luaL_reg s_kslFontLibrary[] = {
		{ "New", l_NewFont },
	{ NULL, NULL }
	};

	// Open library for lua
	luaL_openlib(pLuaState, "Font", s_kslFontLibrary, 0);
}

//--------------------------------------------------------------------------------------
// CleanUpFontMap: Delete all loaded fonts in the map.
//--------------------------------------------------------------------------------------
void LuaFont::CleanUpFontMap()
{
	// loop through map
	for (auto i : m_mfLoadedFonts)
	{
		// delete textures
		delete i.second;
		i.second = nullptr;
	}
}

//--------------------------------------------------------------------------------------
// l_NewFont: Lua bindings for the bootstrap Font constructor.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaFont::l_NewFont(lua_State* pLuaState)
{
	// if the stack isnt 2
	if (lua_gettop(pLuaState) != 2)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaFont::NewFont requires exactly 2 arguments (FileName, Size)");

		// return 2 values
		return 2;
	}

	// if there is no first argument
	if (lua_isstring(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaFont::NewFont argument 1 should be a string (FileName)");

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
		lua_pushstring(pLuaState, "LuaFont::NewFont argument 2 should be a number (Size)");

		// return 2 values
		return 2;
	}

	// get 2 value from lua and store
	const char* kcFileName = (char*)lua_tostring(pLuaState, 1);
	unsigned short usiFontSize = (short)lua_tonumber(pLuaState, 2);

	// pop values off the stack
	lua_pop(pLuaState, 2);

	// push error checking bool
	lua_pushboolean(pLuaState, true);

	// search the map for the font by the filename
	auto search = m_mfLoadedFonts.find(kcFileName);

	// if the result is already in the map
	if (search != m_mfLoadedFonts.end())
	{
		// return a pointer to lua
		lua_pushlightuserdata(pLuaState, search->second);
	}

	// if the result is not already in the map
	else
	{
		// assign a new font pointer
		aie::Font* pFont = new aie::Font(kcFileName, usiFontSize);

		// insert the font into the map
		m_mfLoadedFonts.emplace(std::string(kcFileName), pFont);

		// return a pointer to lua
		lua_pushlightuserdata(pLuaState, pFont);
	}

	// return 2 values.
	return 2;
}