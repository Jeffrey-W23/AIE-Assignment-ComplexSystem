// #includes, using, etc
#include "LuaTexture.h"
#include "Lua.hpp"
#include "Texture.h"

// static member initialization of m_mtLoadedTextures.
std::map <std::string, aie::Texture*> LuaTexture::m_mtLoadedTextures;

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
LuaTexture::LuaTexture()
{
}

//--------------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------------
LuaTexture::~LuaTexture()
{
	// clean up textures
	CleanUpTextureMap();
}

//--------------------------------------------------------------------------------------
// CreateTextureLibrary: Create the lua library for the Texture class.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
void LuaTexture::CreateTextureLibrary(lua_State* pLuaState)
{
	// Register lua functions from cpp
	static const struct luaL_reg s_kslTextureLibrary[] = {
		{ "New", l_NewTexture },
		{ NULL, NULL }
	};

	// Open library for lua
	luaL_openlib(pLuaState, "Texture", s_kslTextureLibrary, 0);
}

//--------------------------------------------------------------------------------------
// CleanUpTextureMap: Delete all loaded textures in the map.
//--------------------------------------------------------------------------------------
void LuaTexture::CleanUpTextureMap()
{
	// loop through map
	for (auto i : m_mtLoadedTextures)
	{
		// delete textures
		delete i.second;
		i.second = nullptr;
	}
}

// --------------------------------------------------------------------------------------
// l_NewTexture: Lua bindings for the bootstrap Texture constructor.
//
// Param:
//		pLuaState: pointer to the lua_State.
//--------------------------------------------------------------------------------------
int LuaTexture::l_NewTexture(lua_State* pLuaState)
{
	// if there is no first argument
	if (lua_isstring(pLuaState, 1) == 0)
	{
		// pop all values off the stack
		lua_pop(pLuaState, lua_gettop(pLuaState));

		// push false bool for failure and error message
		lua_pushboolean(pLuaState, false);
		lua_pushstring(pLuaState, "LuaTexture::NewTexture argument 1 should be a string (FileName)");

		// return 2 values
		return 2;
	}

	// get 1 value from lua and store
	const char* kcFileName = (char*)lua_tostring(pLuaState, 1);

	// pop values off the stack
	lua_pop(pLuaState, 1);

	// push error checking bool
	lua_pushboolean(pLuaState, true);

	// search the map for the texture by the filename
	auto search = m_mtLoadedTextures.find(kcFileName);

	// if the result is already in the map
	if (search != m_mtLoadedTextures.end())
	{
		// return a pointer to lua
		lua_pushlightuserdata(pLuaState, search->second);
	}

	// if the result is not already in the map
	else
	{
		// assign a new texture pointer
		aie::Texture* pTexture = new aie::Texture(kcFileName);

		// insert the texture into the map
		m_mtLoadedTextures.emplace(std::string(kcFileName), pTexture);

		// return a pointer to lua
		lua_pushlightuserdata(pLuaState, pTexture);
	}

	// return 2 values.
	return 2;
}