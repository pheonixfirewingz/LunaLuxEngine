#ifndef LUNALLUXENGINE
#define LUNALLUXENGINE

//#include <LunaLuxEnginePhysics.h>
#include <LLESDK/types.h>
#include <LLESDK/IGame.h>
#include <LLESDK/Input.h>
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
		Game* m_game_main = nullptr;
	private:
		void initEngine();
		int8 updateEngine();
	protected:
		//Physics::LunaLuxEnginePhysics* Core_Physics_Controller = new Physics::LunaLuxEnginePhysics();
		IRender* render{};
	public:
		static lunaLuxEngine* get()
		{
			static auto* engine = new lunaLuxEngine();
			return  engine;
		}
		~lunaLuxEngine() { m_game_main = nullptr; };
		void runEngine(Game*);
	};
}
#endif