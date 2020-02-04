#ifndef LUNALLUXENGINE
#define LUNALUXENGINE

#include <LunaLuxEnginePhysics.h>
#include <LLESDK/IGame.h>
#include <LLESDK/Common_Header.h>
#include "render/IRender.h"
#include "render/DirectX.h"
#include "render/Vulkan.h"
#include "window/Window.h"

#define LLE LunaLuxEngine::lunaLuxEngine::get();
namespace LunaLuxEngine
{
	class lunaLuxEngine
	{
	private:
		bool _2DOr3D_ = false;
		const static bool debug_level_0 = true;
		Game* m_game_main = nullptr;
	private:
		void initEngine();
		int8 updateEngine();
	protected:
		window_api::CrossWindow* window = new window_api::CrossWindow();
		Physics::LunaLuxEnginePhysics* Core_Physics_Controller = new Physics::LunaLuxEnginePhysics();
		IRender* render;
	public:
		static lunaLuxEngine* get()
		{
			static lunaLuxEngine* engine = new lunaLuxEngine();
			return  engine;
		}
		~lunaLuxEngine() { m_game_main = nullptr; };
		void runEngine(Game*);
		//used to control 3D or 2D mode
		void set3D();
	};
}
#endif