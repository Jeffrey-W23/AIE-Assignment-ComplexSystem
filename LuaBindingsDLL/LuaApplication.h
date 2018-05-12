// #includes, using, etc
#pragma once
#include "Application.h"

// declspec for exporting functions for use with dll 
#ifdef LUABINDINGSDLL_EXPORTS  
#define LUABINDINGS_API __declspec(dllexport)   
#else  
#define LUABINDINGS_API __declspec(dllimport)   
#endif  

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
// LuaApplication object. Inherits from Application.
//--------------------------------------------------------------------------------------
class LuaApplication : public aie::Application
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API LuaApplication();

	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API virtual ~LuaApplication();

	//--------------------------------------------------------------------------------------
	// startup: Initialize the game.
	//
	// Returns:
	//		bool: Returns a true or false for if the startup is sucessful.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API virtual bool startup();

	//--------------------------------------------------------------------------------------
	// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API virtual void shutdown();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API virtual void update(float deltaTime);

	//--------------------------------------------------------------------------------------
	// Draw: A virtual function to render (or "draw") objects to the screen.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API virtual void draw();

	// --------------------------------------------------------------------------------------
	// LoadLuaFileToExecute: Load and excute a lua file by the passed in filename.
	//
	// Param:
	//		kcFileName: const char pointer for the filename of the lua file to load.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API void LoadLuaFileToExecute(const char* kcFileName);

	//--------------------------------------------------------------------------------------
	// A pointer to Application.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API static aie::Application* sm_pCurrentApp;

protected:

	//--------------------------------------------------------------------------------------
	// CreateApplicationLibrary: Create the lua library for the Application class.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//--------------------------------------------------------------------------------------
	static void CreateApplicationLibrary(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// LoadLuaFunctionToExecute: Load and excute a lua function by passed in function name.
	//
	// TODO: Make this function a templated function so that if a lua functions has a param 
	// the param can be passed in regardless of type. 
	//
	// Param:
	//		kcFunction: const char pointer for function name that you want to call.
	//		nParam: How many param does this function have.
	//		nReturn: How many returns does this function have.
	//		nErrorfnc: How many error functions does this function have.
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API void LoadLuaFunctionToExecute(const char* kcFunction, int nParam, int nReturn, int nErrorfnc, float deltaTime = 0);

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
	LUABINDINGS_API static aie::Renderer2D* sm_pRenderer2D;

	//--------------------------------------------------------------------------------------
	// A constant char pointer for lua filename.
	//--------------------------------------------------------------------------------------
	const char* m_kcFileName;
};

// extern c all of the lua functions.
#ifdef __cplusplus
extern "C"
{
#endif
	//--------------------------------------------------------------------------------------
	// l_ClearScreen: Lua bindings for the bootstrap Application ClearScreen function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int  l_ClearScreen(lua_State* pLuaState);

	//--------------------------------------------------------------------------------------
	// l_Quit: Lua bindings for the bootstrap Application Quit function.
	//
	// Param:
	//		pLuaState: pointer to the lua_State.
	//
	// Return:
	//		int: How many values are being returned.
	//--------------------------------------------------------------------------------------
	LUABINDINGS_API extern int l_Quit(lua_State* pLuaState);
#ifdef __cplusplus
}
#endif