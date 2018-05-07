// #includes, using, etc
#pragma once

// forward declares
class LuaRenderer2D;
class LuaTexture;
class LuaFont;
class LuaInput;
struct lua_State;

// aie forward declares
namespace aie
{
	class Input;
	class Renderer2D;
	class Texture;
	class Font;
}

//--------------------------------------------------------------------------------------
// LuaInitialize object.
//--------------------------------------------------------------------------------------
class LuaInitialize
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	LuaInitialize();
	
	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~LuaInitialize();

	//--------------------------------------------------------------------------------------
	// Startup: Initialize the game.
	//
	// Returns:
	//		bool: Returns a true or false for if the startup is sucessful.
	//--------------------------------------------------------------------------------------
	static bool Startup(aie::Renderer2D* Renderer2D);

	//--------------------------------------------------------------------------------------
	// Shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
	//--------------------------------------------------------------------------------------
	static void Shutdown();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	static void Update(float deltaTime, aie::Input* Input);

	//--------------------------------------------------------------------------------------
	// Draw: A virtual function to render (or "draw") objects to the screen.
	//--------------------------------------------------------------------------------------
	static void Draw();

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
	static void LoadLuaFunctionToExecute(const char* kcFunction, int fParam, int fReturn, int fErrorfnc, float deltaTime);
	
	// --------------------------------------------------------------------------------------
	// LoadLuaFileToExecute: Load and excute a lua file by the passed in filename.
	//
	// Param:
	//		kcFileName: const char pointer for the filename of the lua file to load.
	//--------------------------------------------------------------------------------------
	static void LoadLuaFileToExecute(const char* kcFileName);

	//--------------------------------------------------------------------------------------
	// A pointer to lua_State.
	//--------------------------------------------------------------------------------------
	static lua_State* m_pLuaState;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaRenderer2D.
	//--------------------------------------------------------------------------------------
	static LuaRenderer2D* m_pLuaRenderer2D;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaTexture.
	//--------------------------------------------------------------------------------------
	static LuaTexture* m_pLuaTexture;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaFont.
	//--------------------------------------------------------------------------------------
	static LuaFont* m_pLuaFont;

	//--------------------------------------------------------------------------------------
	// A pointer to LuaInput.
	//--------------------------------------------------------------------------------------
	static LuaInput* m_pLuaInput;
};

