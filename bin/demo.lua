-- requires
local InputKeys = require("AIEInputKeyValues")

---- NEW LOCAL VARS ----
-- assign camera postion vars
local m_cameraX = 0
local m_cameraY = 0
	
-- assign timer var to be updated by delta time
local m_timer = 0

-- Create 2 new textures
local m_texture = Texture.New("./textures/numbered_grid.tga");
local m_shipTexture = Texture.New("./textures/ship.png");
	
-- Create new font
local m_font = Font.New("./font/consolas.ttf", 32);
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
	m_timer = m_timer + deltaTime;
	
	-- Move camera up
	if (Input.IsKeyDown(InputKeys.INPUT_KEY_UP)) then
		m_cameraY = m_cameraY + 500 * deltaTime;
	end

	-- Move camera down
	if (Input.IsKeyDown(InputKeys.INPUT_KEY_DOWN)) then
		m_cameraY = m_cameraY - 500 * deltaTime;
	end
		
	-- Move camera left
	if (Input.IsKeyDown(InputKeys.INPUT_KEY_LEFT)) then
		m_cameraX = m_cameraX - 500 * deltaTime;
	end
	
	-- Move camera right	
	if (Input.IsKeyDown(InputKeys.INPUT_KEY_RIGHT))then
		m_cameraX = m_cameraX + 500 * deltaTime;
	end	
end

----------------------------------------------------------------------------------------
-- Draw: A function to render (or "draw") objects to the screen.
----------------------------------------------------------------------------------------
function Draw()

	-- set the camera position before we begin rendering
	Renderer2D.SetCameraPos(m_cameraX, m_cameraY);

	-- begin drawing sprites
	Renderer2D.Begin();

	-- demonstrate animation
	Renderer2D.SetUVRect((m_timer % 8) / 8, 0, 1 / 8, 1 / 8);
	Renderer2D.DrawSprite(m_texture, 200, 200, 100, 100);

	-- demonstrate spinning sprite
	Renderer2D.SetUVRect(0, 0, 1, 1);
	Renderer2D.DrawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	-- draw a thin line
	Renderer2D.DrawLine(300, 300, 600, 400, 2, 1);

	-- draw a moving purple circle
	Renderer2D.SetRenderColour(1, 0, 1, 1);
	Renderer2D.DrawCircle(math.sin(m_timer) * 100 + 600, 150, 50);

	-- draw a rotating red box
	Renderer2D.SetRenderColour(1, 0, 0, 1);
	Renderer2D.DrawBox(600, 500, 60, 20, m_timer);

	-- draw a slightly rotated sprite with no texture, coloured yellow
	Renderer2D.SetRenderColour(1, 1, 0, 1);
	Renderer2D.DrawSprite(nullptr, 400, 400, 50, 50, 3.14159 * 0.25, 1);

	-- output some text, uses the last used colour
	--char fps[32];
	--sprintf_s(fps, 32, "FPS: %i", getFPS());
	--Renderer2D.DrawText(m_font, fps, 0, 720 - 32);
	Renderer2D.DrawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	-- done drawing sprites
	Renderer2D.End();
end

-- Print Loaded Successfully to show that lua is actually loading.
print("Loaded Successfully")