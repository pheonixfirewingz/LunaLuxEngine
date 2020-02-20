#include "Buffer.h"

namespace LunaLuxEngine
{
	void BufferUtils::createBuffer(VERTEX vers[])
	{
#ifdef WIN32
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * 4;             // size is the VERTEX struct
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

		dev->CreateBuffer(&bd, nullptr, &pVBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;
		devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, vers, sizeof(vers));
		devcon->Unmap(pVBuffer, NULL);

		UINT stride = sizeof(vers);
		UINT offset = 0;
		devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
#endif
		//TODO: create buffers that actuly Fucking render grrrrrrrrr
	}

	void BufferUtils::releaseBuffers()
	{
#ifdef WIN32
		if (pVBuffer != nullptr)
			pVBuffer->Release();
		if (pIBuffer != nullptr)
			pIBuffer->Release();
#endif
	}
#ifdef WIN32
    void BufferUtils::giveInstance(ID3D11DeviceContext* in_con, ID3D11Device* in_dev)
    {
        dev = in_dev;
        devcon = in_con;
    }
#endif
}