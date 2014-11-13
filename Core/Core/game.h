#pragma once

class Game
{
	public:
		Game() {};
		virtual ~Game() {};
		virtual void input() {};
		virtual void update() {};
		virtual void render() {};
};

