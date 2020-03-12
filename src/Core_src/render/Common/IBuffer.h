#ifndef LUNALUXENGINE_IBUFFER_H
#define LUNALUXENGINE_IBUFFER_H
namespace LunaLuxEngine
{
	class IVertexBuffer
	{
	public:
		virtual void create(float[]) = 0;
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual void destory() = 0;
	};

	class IIndexBuffer
	{
	public:
		virtual void create(int[]) = 0;
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual void destory() = 0;
	};
}
#endif
