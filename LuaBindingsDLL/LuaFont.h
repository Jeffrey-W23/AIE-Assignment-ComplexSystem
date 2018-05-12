// #includes, using, etc
#pragma once
#include <map>
#include <string>

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

	//--------------------------------------------------------------------------------------
	// An Associative Array where the key is the file name, value is the loaded font.
	//--------------------------------------------------------------------------------------
	static std::map <std::string, aie::Font*> sm_mfLoadedFonts;
};

// extern c all of the lua functions.
#ifdef __cplusplus
extern "C"
{
#endif
	//--------------------------------------------------------------------------------------
	// l_NewFont: Lua bindings for the bootstrap Font constructor.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_NewFont(lua_State* pLuaState);
#ifdef __cplusplus
}
#endif