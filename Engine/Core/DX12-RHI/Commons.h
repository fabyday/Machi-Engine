#pragma once

#include "d3d12.h"
#include "d3dx12.h"
#include "dxhelper.h"
#include <wrl.h> // ComPtr header
#include <shellapi.h>

#include <directxmath.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>

#include <d3d12sdklayers.h> // for debugging


#include <Graphics/graphics_defined.h>
#include <Platform/types.h>

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
using namespace DirectX;
