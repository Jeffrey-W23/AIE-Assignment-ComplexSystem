// #includes, using, etc
#pragma once
#include "Application.h"

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
class LuaRenderer2D;
class LuaTexture;
class LuaFont;
class LuaInput;
struct lua_State;

// aie forward declares
namespace aie
{
	class Renderer2D;
	class Input;
	class Application;
}

//--------------------------------------------------------------------------------------
// LuaApplication object.
//--------------------------------------------------------------------------------------
class LuaApplication : public aie::Application
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	LuaApplication();

	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	virtual ~LuaApplication();

	//--------------------------------------------------------------------------------------
	// startup: Initialize the game.
	//
	// Returns:
	//		bool: Returns a true or false for if the startup is sucessful.
	//--------------------------------------------------------------------------------------
	virtual bool startup();

	//--------------------------------------------------------------------------------------
	// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
	//--------------------------------------------------------------------------------------
	virtual void shutdown();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	virtual void update(float deltaTime);

	//--------------------------------------------------------------------------------------
	// Draw: A virtual function to render (or "draw") objects to the screen.
	//--------------------------------------------------------------------------------------
	virtual void draw();

	// --------------------------------------------------------------------------------------
	// LoadLuaFileToExecute: Load and excute a lua file by the passed in filename.
	//
	// Param:
	//		kcFileName: const char pointer for the filename of the lua file to load.
	//--------------------------------------------------------------------------------------
	void LoadLuaFileToExecute(const char* kcFileName);

protected:

	static aie::Application* currentApp;

	//--------------------------------------------------------------------------------------
	// CreateApplicationLibrary: Create the lua library for the Application class.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static void CreateApplicationLibrary(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_ClearScreen: Lua bindings for the bootstrap Application ClearScreen function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_ClearScreen(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_Quit: Lua bindings for the bootstrap Application Quit function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static int l_Quit(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// LoadLuaFunctionToExecute: Load and excute a lua function by passed in function name.
	//
	// Param:
	//		kcFunction:
	//		fParam:
	//		fReturn:
	//		fErrorfnc:
	//		deltaTime:
	//--------------------------------------------------------------------------------------
	void LoadLuaFunctionToExecute(const char* kcFunction, int fParam, int fReturn, int fErrorfnc, float deltaTime = 0);

	//--------------------------------------------------------------------------------------
	// A pointer to lua_State.
	//--------------------------------------------------------------------------------------
	lua_State* m_pLuaState;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaRenderer2D.
	//--------------------------------------------------------------------------------------
	LuaRenderer2D* m_pLuaRenderer2D;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaTexture.
	//--------------------------------------------------------------------------------------
	LuaTexture* m_pLuaTexture;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaFont.
	//--------------------------------------------------------------------------------------
	LuaFont* m_pLuaFont;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaInput.
	//--------------------------------------------------------------------------------------
	LuaInput* m_pLuaInput;

	//--------------------------------------------------------------------------------------
	// A pointer to Renderer2D.
	//--------------------------------------------------------------------------------------
	aie::Renderer2D* m_2dRenderer;
};

//#ifdef __cplusplus
//extern "C"
//{
//	//--------------------------------------------------------------------------------------
//	// l_ClearScreen: Lua bindings for the bootstrap Application ClearScreen function.
//	//
//	// Param:
//	//		pLuaState: pointer to the lua_State.
//	//--------------------------------------------------------------------------------------
//	LUA_DLL extern int l_ClearScreen(lua_State* pLuaState);
//
//	//--------------------------------------------------------------------------------------
//	// l_Quit: Lua bindings for the bootstrap Application Quit function.
//	//
//	// Param:
//	//		pLuaState: pointer to the lua_State.
//	//--------------------------------------------------------------------------------------
//	LUA_DLL extern int l_Quit(lua_State* pLuaState);
//#endif // __cplusplus
//
//}