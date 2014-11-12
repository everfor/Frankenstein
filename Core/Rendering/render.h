#pragma once

class Render
{
	public:
		static void ClearScreen();
		static void InitGraphics();
		static void SetTextures(bool enabled);
	private:
		Render();
		~Render();
};