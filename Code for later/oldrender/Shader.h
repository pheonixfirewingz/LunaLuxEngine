#ifndef LUNALUXENGINE_READER_H
#define LUNALUXENGINE_READER_H
#include <LLESDK/types.h>
#ifdef WIN32
#include <D3D11.h>
#pragma comment ( lib, "D3d11.lib" )
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#endif
namespace LunaLuxEngine
{

	class Shaders
	{
	private:
#ifdef WIN32
		ID3D11InputLayout* pLayout = nullptr;            // the pointer to the input layout
		ID3D11VertexShader* pVS = nullptr;               // the pointer to the vertex shader
		ID3D11PixelShader* pPS = nullptr;                // the pointer to the pixel shader

		Shaders() {}
	public:
		~Shaders()
		{
			delete& pLayout;
			delete& pVS;
			delete& pPS;
		}
#endif
		static inline Shaders* get()
		{
			static Shaders* shaders = new Shaders();
			return shaders;
		}
		void compileShader(LPCWSTR);

		inline void clearShaders()
		{
#ifdef WIN32
			pLayout->Release();
			pVS->Release();
			pPS->Release();
#endif
		}
	};
}
#endif