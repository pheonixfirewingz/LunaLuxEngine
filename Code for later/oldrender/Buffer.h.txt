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

		BufferUtils()
		{
			VBarray.resize((sizeof(int8)));
			IBarray.resize((sizeof(int8)));
		}
	public:
		~BufferUtils()
		{
			delete& VBarray;
			delete& IBarray;
		}
	private:
#endif
		int64 currentVBAsize = 0, currentIBAsize = 0, global_indices_count = 0;

		inline void addIndicesToGlobalIndices(int indices_count)
		{
			global_indices_count = +indices_count;
		}
	public:
		inline static BufferUtils* get()
		{
			static BufferUtils* util_ = new BufferUtils();
			return util_;
		}

		inline int64 getGlobalIndicesCount()
		{
			return  global_indices_count;
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
		void createIBufAndAddToArray(int[], int64 indicescount);
		void Release();
	};
}
#endif