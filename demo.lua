	Renderer2D.begin();
	
	local successful, error = Renderer2D.SetCameraPos(5, "This will break");
	if not successful then 
		print(error)
	end
	
	Renderer2D.end();