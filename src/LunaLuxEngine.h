#ifndef LUNALLUXENGINE
#define LUNALUXENGINE

class Window;

#include "utils/IGame.h"
#include "Common_Header.h"
#include "render/IRender.h"
#include "window/Window.h"

namespace LunaLuxEngine
{
	class lunaLuxEngine
	{
	protected:
		bool _is_paused_ = false;
		bool _2DOr3D_ = false;

		IRender* render = new IRender();
		window_api::Window* window = new window_api::Window();
		void initEngine();
		int8 updateEngine();
	public:
		Game* m_game_main = nullptr;
		static lunaLuxEngine* get()
		{
			static lunaLuxEngine* engine = new lunaLuxEngine();
			return  engine;
		}
		~lunaLuxEngine() { m_game_main = nullptr; };
		void runEngine();
		//used to pause the game
		bool isGamePaused();
		//used to control 3D or 2D mode
		void set3D();
	};
}
#endif 