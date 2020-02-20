#ifndef LUNALLUXENGINE_BUFFER
#define LUNALLUXENGINE_BUFFER
#ifdef WIN32
#include <d3d11.h>
#endif
#include "../utils/BufferUtil.h"
#include <LLESDK\types.h>
namespace LunaLuxEngine
{
	class BufferUtils
	{
	private:
#ifdef WIN32
		ID3D11Buffer* pVBuffer;
		ID3D11Buffer* pIBuffer;
		ID3D11Device* dev;
		ID3D11DeviceContext* devcon;
#endif
		int64 vercount = 0;
	public:
		inline static BufferUtils* get()
		{
			static BufferUtils* util_ = new BufferUtils();
			return util_;
		}
		inline void setVercount(int64 in_ver)
		{
			vercount =+ in_ver;
		}

		inline int64 getVerCont()
		{
			return vercount;
		}
		void createBuffer(VERTEX []);
#ifdef WIN32
		void giveInstance(ID3D11DeviceContext*, ID3D11Device*);
#endif
		void releaseBuffers();
	};
}
#endif