// #includes, using, etc
#pragma once
#include <map>
#include <string>

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
	class Texture;
}

//--------------------------------------------------------------------------------------
// LuaTexture object.
//--------------------------------------------------------------------------------------
class LuaTexture
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	LuaTexture();
	
	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	~LuaTexture();

	//--------------------------------------------------------------------------------------
	// CreateTextureLibrary: Create the lua library for the Texture class.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static void CreateTextureLibrary(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// CleanUpTextureMap: Delete all loaded textures in the map.
	//--------------------------------------------------------------------------------------
	static void CleanUpTextureMap();

private:

	//--------------------------------------------------------------------------------------
	// l_NewTexture: Lua bindings for the bootstrap Texture constructor.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	LUA_DLL static int l_NewTexture(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// An Associative Array where the key is the file name, value is the loaded texture.
	//--------------------------------------------------------------------------------------
	static std::map <std::string, aie::Texture*> m_mtLoadedTextures;
};