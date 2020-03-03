#include "Buffer.h"

namespace LunaLuxEngine
{

	void BufferUtils::createVBufAndAddToArray(VERTEX vers[], int64 vertexcount)
	{
#ifdef WIN32
		ID3D11Buffer* pVBuffer{};
		D3D11_BUFFER_DESC vertexBufferDesc{};
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VERTEX) * vertexcount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertexData{};
		vertexData.pSysMem = vers;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		dev->CreateBuffer(&vertexBufferDesc, &vertexData, &pVBuffer);
		VBarray[currentVBAsize] = pVBuffer;
		currentVBAsize++;
#endif
	}

	void LunaLuxEngine::BufferUtils::createIBufAndAddToArray(int ind[], int64 indicescount)
	{
		addIndicesToGlobalIndices(indicescount);
		ID3D11Buffer* pIBuffer{};
		D3D11_BUFFER_DESC indexBufferDesc{};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(int) * indicescount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indexData{};
		indexData.pSysMem = ind;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		dev->CreateBuffer(&indexBufferDesc, &indexData, &pIBuffer);
		IBarray[currentIBAsize] = pIBuffer;
		currentIBAsize++;
	}

	void BufferUtils::releaseBuffers()
	{
#ifdef WIN32
		for (int i = 0; i < currentVBAsize; i++) if (IBarray[i] != nullptr) VBarray[i]->Release();

		for (int i = 0; i < currentIBAsize; i++) if (IBarray[i] != nullptr) IBarray[i]->Release();
#endif
	}
}