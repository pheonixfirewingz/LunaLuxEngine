#include "Shader.h"
#include "../render/Renderer.h"
namespace LunaLuxEngine
{
	void Shaders::compileShader(LPCWSTR file)
	{
#ifdef WIN32
		ID3D10Blob* VS, * PS;
		ZeroMemory(&VS, sizeof(VS));
		ZeroMemory(&PS, sizeof(PS));

		if (FAILED(D3DCompileFromFile(file, 0, 0, "VMain", "vs_4_0", 0, 0, &VS, nullptr)))
			FOURCE_STOP("failed to vertex compile shader check if is in exeacutable localtion\n")
			if (FAILED(D3DCompileFromFile(file, 0, 0, "PMain", "ps_4_0", 0, 0, &PS, nullptr)))
				FOURCE_STOP("failed to pixel compile shader check if is in exeacutable localtion\n")

				Renderer::get()->getInst()->getGPUDevice()->dx11_device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		Renderer::get()->getInst()->getGPUDevice()->dx11_device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		Renderer::get()->getInst()->getGPUDevice()->dx11_device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		Renderer::get()->getInst()->getGPUDeviceContext()->dx11_deviceContext->IASetInputLayout(pLayout);

		Renderer::get()->getInst()->getGPUDeviceContext()->dx11_deviceContext->VSSetShader(pVS, 0, 0);
		Renderer::get()->getInst()->getGPUDeviceContext()->dx11_deviceContext->PSSetShader(pPS, 0, 0);
#endif
	}
}