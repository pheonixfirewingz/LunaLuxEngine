#include "Shader.h"

namespace LunaLuxEngine
{
	void Shaders::compileShader(LPCWSTR file)
	{
		// load and compile the two shaders
		ID3D10Blob* VS, * PS, * ER;
		memset(&VS, 0, 0);
		memset(&PS, 0, 0);
		HRESULT hr;

		hr = D3DCompileFromFile(file, 0, 0, "VMain", "vs_4_0", 0, 0, &VS, &ER);
		if (FAILED(hr))
		{
			if (ER)
			{
				OutputDebugStringA((char*)ER->GetBufferPointer());
				printf("failed to vertex compile shader check if is in exeacutable localtion\n");
				ER->Release();
				exit(-1);
			}
		}

		hr = D3DCompileFromFile(file, 0, 0, "PMain", "ps_4_0", 0, 0, &PS, &ER);
		if (FAILED(hr))
		{
			if (ER)
			{
				OutputDebugStringA((char*)ER->GetBufferPointer());
				printf("failed to pixel compile shader check if is in exeacutable localtion\n");
				ER->Release();
				exit(-1);
			}
		}

		// encapsulate both shaders into shader objects
		device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// create the input layout object
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);

		devicecon->IASetInputLayout(pLayout);

		// set the shader objects
		devicecon->VSSetShader(pVS, 0, 0);
		devicecon->PSSetShader(pPS, 0, 0);
	}
	void Shaders::giveDevice(ID3D11Device* dev)
	{
		device = dev;
	}
	void Shaders::giveContext(ID3D11DeviceContext* context)
	{
		devicecon = context;
	}
}