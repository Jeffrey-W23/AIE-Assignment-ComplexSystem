// #includes, using, etc
#pragma once
#include <map>
#include <string>

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
	void CreateTextureLibrary(lua_State* pLuaState);

private:

	//--------------------------------------------------------------------------------------
	// CleanUpTextureMap: Delete all loaded textures in the map.
	//--------------------------------------------------------------------------------------
	void CleanUpTextureMap();

	//--------------------------------------------------------------------------------------
	// l_NewTexture: Lua bindings for the bootstrap Texture constructor.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_NewTexture(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// An Associative Array where the key is the file name, value is the loaded texture.
	//--------------------------------------------------------------------------------------
	static std::map <std::string, aie::Texture*> m_mtLoadedTextures;
};