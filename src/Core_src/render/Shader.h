#ifndef LUNALUXENGINE_READER_H
#define LUNALUXENGINE_READER_H
#include <LLESDK/types.h>
#include <D3D11.h>
#pragma comment ( lib, "D3d11.lib" )
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include <vector>
namespace LunaLuxEngine
{

	class Shaders
	{
	private:
		LLEbool NativeMode;
		ID3D11Device* device;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext* devicecon;           // the pointer to our Direct3D device context
		ID3D11InputLayout* pLayout;            // the pointer to the input layout
		ID3D11VertexShader* pVS;               // the pointer to the vertex shader
		ID3D11PixelShader* pPS;                // the pointer to the pixel shader
	public:
		static inline Shaders* get()
		{
			static Shaders* shaders = new Shaders();
			return shaders;
		}
		inline void toggleNativeCompiler()
		{
			if (NativeMode) 
				NativeMode = LLEfalse
			else 
				NativeMode = LLEtrue
		}
		void compileShader(LPCWSTR);
		void giveDevice(ID3D11Device*);
		void giveContext(ID3D11DeviceContext*);

		inline void clearShaders()
		{
			pLayout->Release();
			pVS->Release();
			pPS->Release();
		}
	};
}
#endif