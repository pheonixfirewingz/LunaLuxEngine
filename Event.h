#ifndef LUNALLUXENGINE_EVENT
#define LUNALLUXENGINE_EVENT
namespace LunaLuxEngine
{
	enum TYPE
	{
		RENDER
	};
	class Event
	{
	private:
		TYPE type;
	public:
		Event(TYPE _type_)
		{
			type = _type_;
		}
		~Event()
		{

		}

		void fire();
	};
}
#endif
