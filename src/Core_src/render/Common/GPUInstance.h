#ifndef LUNALUXENGINE_GPUINSTANCE_H
#define LUNALUXENGINE_GPUINSTANCE_H
#include <LLESDK/types.h>
#include <d3d11.h>
namespace LunaLuxEngine
{
	class GPUInstance
	{
	private:
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
	public:
		void createDX11GPUInstance(ID3D11Device* device_in, ID3D11DeviceContext* deviceContext_in)
		{
			device = device_in;
			deviceContext = deviceContext_in;
		}

		ID3D11Device* getGPUDevice()
		{
			return device;
		}

		ID3D11DeviceContext* getGPUDeviceContext()
		{
			return deviceContext;
		}

		void Release()
		{
			device->Release();
			deviceContext->Release();
		}
	};
}
#endif