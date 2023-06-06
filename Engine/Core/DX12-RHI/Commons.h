#pragma once
#include "d3d12.h"
#include "d3dx12.h"
#ifdef DX12_INNER_ONLY_INCLUDE
//#include "dxhelper.h"
#endif
#include <wrl.h> // ComPtr header
#include <shellapi.h>

#include <directxmath.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>

#include <d3d12sdklayers.h> // for debugging



#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")



namespace Machi {
	namespace NativeGraphics {
		template <typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
		using namespace DirectX;
	}

}

#include <Graphics/graphics_defined.h>
#include <Platform/types.h>
