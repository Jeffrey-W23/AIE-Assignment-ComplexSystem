// #includes, using, etc
#pragma once
#include <map>
#include <string>

// Preprogramming to check and then switch between if the program is a dll libary or static.
//#ifdef STATIC_LIB
//	#define LUA_DLL
//#else
//	#ifdef DLL_EXPORT
//		#define LUA_DLL __declspec(dllexport)
//	#else
//		#define LUA_DLL __declspec(dllimport)
//	#endif
//#endif

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
	//--------------------------------------------------------------------------------------
	static int l_NewFont(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// An Associative Array where the key is the file name, value is the loaded font.
	//--------------------------------------------------------------------------------------
	static std::map <std::string, aie::Font*> m_mfLoadedFonts;
};