-- requires
local InputKeys = require("AIEInputKeyValues")

----------------------------------------------------------------------------------------
-- ErrorCheck: Error check a functon and return its data if successful.
----------------------------------------------------------------------------------------
function ErrorCheck(successful, data)
	
	-- if the function being checked is not successful
	if not successful then
		print("Error running function: " .. data)
		return nil
	
	-- return the data of the function 
	else
		return data
	end
end

---- NEW LOCAL VARS ----
-- assign camera postion vars
local m_cameraX = 0
local m_cameraY = 0
	
-- assign timer var to be updated by delta time
local m_timer = 0

-- Create 2 new textures
local m_texture = ErrorCheck(Texture.New("./textures/numbered_grid.tga"))
local m_shipTexture = ErrorCheck(Texture.New("./textures/ship.png"))
	
-- Create new font
local m_font = ErrorCheck(Font.New("./font/consolas.ttf", 32))
---- NEW LOCAL VARS ----

----------------------------------------------------------------------------------------
-- shutdown: Called on application shutdown and does all the cleaning up
--			(eg. Deleteing pointers.)
----------------------------------------------------------------------------------------
function Shutdown()
end

----------------------------------------------------------------------------------------
-- Update: A function to update objects.
--
-- Param:
--		deltaTime: Pass in deltaTime. A number that updates per second.
----------------------------------------------------------------------------------------
function Update( deltaTime )

	-- Update the timer by deltaTime
	m_timer = m_timer + deltaTime
	
	-- if escape key then close down application
	if (ErrorCheck(Input.IsKeyDown(InputKeys.INPUT_KEY_ESCAPE))) then
		Application.Quit()
	end
	
	-- Move camera up
	if (ErrorCheck(Input.IsKeyDown(InputKeys.INPUT_KEY_UP))) then
		m_cameraY = m_cameraY + 500 * deltaTime
	end

	-- Move camera down
	if (ErrorCheck(Input.IsKeyDown(InputKeys.INPUT_KEY_DOWN))) then
		m_cameraY = m_cameraY - 500 * deltaTime
	end
		
	-- Move camera left
	if (ErrorCheck(Input.IsKeyDown(InputKeys.INPUT_KEY_LEFT))) then
		m_cameraX = m_cameraX - 500 * deltaTime
	end
	
	-- Move camera right	
	if (ErrorCheck(Input.IsKeyDown(InputKeys.INPUT_KEY_RIGHT)))then
		m_cameraX = m_cameraX + 500 * deltaTime
	end	
end

----------------------------------------------------------------------------------------
-- Draw: A function to render (or "draw") objects to the screen.
----------------------------------------------------------------------------------------
function Draw()

	-- wipe the screen to the background colour
	Application.ClearScreen();

	-- set the camera position before we begin rendering
	Renderer2D.SetCameraPos(m_cameraX, m_cameraY)

	-- begin drawing sprites
	Renderer2D.Begin()

	-- demonstrate animation
	Renderer2D.SetUVRect(math.floor(m_timer) % 8 / 8.0, 0, 1.0 / 8, 1.0 / 8)
	Renderer2D.DrawSprite(m_texture, 200, 200, 100, 100, 0, 0, 0.5, 0.5)

	-- demonstrate spinning sprite
	Renderer2D.SetUVRect(0, 0, 1, 1)
	Renderer2D.DrawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1, 0.5, 0.47)
	
	-- draw a thin line
	Renderer2D.DrawLine(300, 300, 600, 400, 2, 1)

	-- draw a moving purple circle
	Renderer2D.SetRenderColour(1, 0, 1, 1)
	Renderer2D.DrawCircle(math.sin(m_timer) * 100 + 600, 150, 50, 0)

	-- draw a rotating red box
	Renderer2D.SetRenderColour(1, 0, 0, 1)
	Renderer2D.DrawBox(600, 500, 60, 20, m_timer, 0)

	-- draw a slightly rotated sprite with no texture, coloured yellow
	Renderer2D.SetRenderColour(1, 1, 0, 1)
	Renderer2D.DrawSprite(nil, 400, 400, 50, 50, 3.14159 * 0.25, 1 ,0.25, 0.25)

	-- output some text, uses the last used colour
	Renderer2D.DrawText(m_font, fps, 0, 720 - 32)
	Renderer2D.DrawText(m_font, "Press ESC to quit!", 0, 720 - 64, 0)
	Renderer2D.DrawText(m_font, "Press ~ to Refresh lua code!", 0, 690, 0)

	-- done drawing sprites
	Renderer2D.End()
end

-- Print Loaded Successfully to show that lua is actually loading.
print("Loaded Successfully")