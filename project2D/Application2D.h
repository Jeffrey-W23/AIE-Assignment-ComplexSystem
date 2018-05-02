#pragma once

#include "Application.h"
#include "Renderer2D.h"

class LuaRenderer2D;
class LuaTexture;
class LuaFont;
class LuaInput;
struct lua_State;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	
	lua_State*			m_pLuaState;
	LuaRenderer2D*		m_pLuaRenderer2D;
	LuaTexture*			m_pLuaTexture;
	LuaFont*			m_pLuaFont;
	LuaInput*			m_pLuaInput;

	float m_cameraX, m_cameraY;
	float m_timer;
};