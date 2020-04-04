#ifndef LUNALLUXENGINE
#define LUNALLUXENGINE

#include <LLESDK/types.h>
#include <LLESDK/IGame.h>
#include <vector>
#define LLE LunaLuxEngine::lunaLuxEngine::get();

namespace LunaLuxEngine
{
	class lunaLuxEngine
	{
	private:
		Game* m_game_main = nullptr;
		void initEngine();
		int8 updateEngine();
	public:
		int currentAPItype = 0;
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