#pragma once
#include "Commons.h"
#include "Device.h"
namespace Machi {


	namespace NativeGraphics {
		class Sampler {


			Sampler() {};
			D3D12_SAMPLER_DESC t;
			D3D12_STATIC_SAMPLER_DESC m_desc;
			D3D12_CPU_DESCRIPTOR_HANDLE m_cpu_handle;

			Sampler& init(Device& device) {

				device->CreateSampler(m_desc, m_cpu_handle);
				return Sampler;
			}

			D3D12_SAMPLER_DESC* Get() {
				return nullptr;
			}
		};

		class StaticSampler {


			D3D12_STATIC_SAMPLER_DESC m_desc;
			D3D12_CPU_DESCRIPTOR_HANDLE m_cpu_handle;


			Sampler& init(Device& device) {
				device->CreateSampler(m_desc, m_cpu_handle);

			}


			D3D12_STATIC_SAMPLER_DESC* Get() {
				return nullptr;
			}
		};
	};
}