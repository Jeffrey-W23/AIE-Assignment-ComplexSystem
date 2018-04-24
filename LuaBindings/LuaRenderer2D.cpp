// #includes using etc.
#include "LuaRenderer2D.h"
#include "Lua.hpp"
#include "Renderer2D.h"

LuaRenderer2D::LuaRenderer2D()
{

}

LuaRenderer2D::~LuaRenderer2D()
{

}

void CreateRenderer2DLibrary(lua_State* pLuaState)
{
	static const struct luaL_reg s_kslRenderer2DLibrary[] = {
		{ "New", l_Renderer2DNew },
		{ NULL, NULL }
	};

	luaL_openlib(pLuaState, "Renderer2D", s_kslRenderer2DLibrary, 0);
}

int l_Renderer2DNew(lua_State* pLuaState)
{
	aie::Renderer2D* rRenderer2D = new aie::Renderer2D();
	lua_pushlightuserdata(pLuaState, rRenderer2D);

	return 1;
}

int l_Renderer2DDelete(lua_State* pLuaState)
{
	
}

int l_SetCameraPos(lua_State* pLuaState)
{
	
}

