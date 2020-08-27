#ifndef LUNALLUXENGINE
#define LUNALLUXENGINE

#include <LLESDK/types.h>
#include <LLESDK/IGame.h>
#include <chrono>

namespace LunaLuxEngine
{
    class lunaLuxEngine
    {
    private:
        Game *m_game_main = nullptr;

        void initEngine(bool &);

        int8 updateEngine(bool &);
    public:
        static lunaLuxEngine *get()
        {
            static auto *engine = new lunaLuxEngine();
            return engine;
        }

        void runEngine(Game *, bool);
    };
}
#endif