// #includes, using, etc
#pragma once
#include <map>
#include <string>

// forward declares
struct lua_State;

namespace aie
{
	class Font;
}

//--------------------------------------------------------------------------------------
// LuaFont object.
//--------------------------------------------------------------------------------------
class LuaFont
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	LuaFont();

	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	~LuaFont();

	//--------------------------------------------------------------------------------------
	// CreateFontLibrary: Create the lua library for the Font class.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static void CreateFontLibrary(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// CleanUpFontMap: Delete all loaded fonts in the map.
	//--------------------------------------------------------------------------------------
	static void CleanUpFontMap();

private:

	//--------------------------------------------------------------------------------------
	// l_NewFont: Lua bindings for the bootstrap Font constructor.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	static int l_NewFont(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// An Associative Array where the key is the file name, value is the loaded font.
	//--------------------------------------------------------------------------------------
	static std::map <std::string, aie::Font*> sm_mfLoadedFonts;
};