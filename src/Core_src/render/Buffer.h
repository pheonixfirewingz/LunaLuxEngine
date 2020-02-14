#ifndef LUNALLUXENGINE_BUFFER
#define LUNALLUXENGINE_BUFFER
#include <vector>
#include <d3d11.h>
#include "../utils//BufferUtil.h"
namespace LunaLuxEngine
{
	class BufferUtils
	{
	private:
		std::vector<VERTEX> data;
		ID3D11Buffer* pVBuffer;
		ID3D11Buffer* pIBuffer;
		ID3D11Device* dev;
		ID3D11DeviceContext* devcon;
	public:
		inline static BufferUtils* get()
		{
			static BufferUtils* util_ = new BufferUtils();
			return util_;
		}
		void createBuffer(VERTEX []);
		void giveInstance(ID3D11DeviceContext*, ID3D11Device*);
		void releaseBuffers();
	};
}
#endif