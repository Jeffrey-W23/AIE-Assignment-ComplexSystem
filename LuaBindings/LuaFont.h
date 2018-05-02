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
	void CreateFontLibrary(lua_State* pLuaState);

private:

	//--------------------------------------------------------------------------------------
	// CleanUpFontMap: Delete all loaded fonts in the map.
	//--------------------------------------------------------------------------------------
	void CleanUpFontMap();

	//--------------------------------------------------------------------------------------
	// l_NewFont: Lua bindings for the bootstrap Font constructor.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_NewFont(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// An Associative Array where the key is the file name, value is the loaded font.
	//--------------------------------------------------------------------------------------
	static std::map <std::string, aie::Font*> m_mfLoadedFonts;
};