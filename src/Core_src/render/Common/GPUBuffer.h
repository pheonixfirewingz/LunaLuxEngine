#ifndef LUNALUXENGINE_GPUBUFFER_H
#define LUNALUXENGINE_GPUBUFFER_H
#include <LLESDK/types.h>
#include <any>
namespace LunaLuxEngine
{
	class GPUBuffer
	{
	private:
		std::any* vertexBuffer;
		std::any* IndicesBuffer;
		uint64 VertexCount, IndicesCount;
	public:

	};
}
#endif