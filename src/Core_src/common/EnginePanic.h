#ifndef LUNALUXENGINE_PANIC_H
#define LUNALUXENGINE_PANIC_H
#include<fstream>
#include<sstream>
#include<string>
namespace LunaLuxEngine
{
	class EnginePanic
	{
	private:
	public:
		inline static EnginePanic* get()
		{
			static EnginePanic* ep = new EnginePanic();
			return ep;
		}
		void panic(std::string);
	};
}
#endif
