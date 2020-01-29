#ifndef LUNALLUXENGINE
#define LUNALUXENGINE

#include "utils/IGame.h"
#include "Common_Header.h"
#include "render/IRender.h"
#include "window/Window.h"
namespace LunaLuxEngine
{
	class lunaLuxEngine
	{
	protected:
		bool _is_paused_ = false, _2DOr3D_ = false;
		const static bool debug_level_0 = false;
		window_api::CrossWindow* window = new window_api::CrossWindow();
		IRender* render = new IRender();
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