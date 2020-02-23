#ifndef LUNALLUXENGINE_BUFFER
#define LUNALLUXENGINE_BUFFER
#ifdef WIN32
#include <d3d11.h>
#endif
#include "../utils/BufferUtil.h"
#include <LLESDK\types.h>
#include <vector>
namespace LunaLuxEngine
{
	class BufferUtils
	{
	private:
#ifdef WIN32
		std::vector<ID3D11Buffer*> VBarray{};
		std::vector <ID3D11Buffer*> IBarray{};
		ID3D11Device* dev{};
		~BufferUtils()
		{
			delete& VBarray;
			delete& IBarray;
			delete& dev;
		}
#endif
		int64 currentVBAsize = 0, currentIBAsize = 0;
		BufferUtils() {}
	public:
		inline static BufferUtils* get()
		{
			static BufferUtils* util_ = new BufferUtils();
			return util_;
		}
#ifdef WIN32
		inline ID3D11Buffer** getVbuff(int64 index)
		{
			return &VBarray[index];
		}

		inline ID3D11Buffer* getIBuff(int64 index)
		{
			return IBarray[index];
		}

		inline int getBufferCount()
		{
			return currentIBAsize;
		}
#endif
		void createVBufAndAddToArray(VERTEX[], int64 vertexcount);
		void createIBufAndAddToArray(int[], int64 vertexcount);
#ifdef WIN32
		inline void giveInstance(ID3D11Device* in_dev)
		{
			dev = in_dev;
			VBarray.resize((sizeof(int8)));
			IBarray.resize((sizeof(int8)));
		}
#endif
		void releaseBuffers();
	};
}
#endif