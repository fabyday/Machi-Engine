#include "Commons.h"
#include "Graphics/graphics_defined.h"
#include "native_format_converter.h"

namespace Machi {

	class Texture {


		D3D12_RESOURCE_DESC m_desc;

		ComPtr<ID3D12Resource> m_texture;



		struct {
			bool m_desc = false;
		}m_is_ready;
		

		Buffer& set_width(MUINT width) { 
			m_desc.Width = width; 
		};
		Buffer& set_height(MUINT height) { m_desc.Height = height; };
		Buffer& set_align(MUINT align_size) { m_desc.Alignment = align_size; };
		Buffer& set_mip_level(MUINT mip_level) { m_desc.MipLevels = mip_level; };
		Buffer& set_format(ResourceFormat format) { 
			m_desc.Format = resource_format_convert(format); 
		};
		Buffer& set_sample_property(MUINT sample_count, MUINT sample_quality) {
			m_desc.SampleDesc.Count = sample_count; m_desc.SampleDesc.Quality = sample_quality; 
		};

		Buffer& set_simple_texture_property(TextureType texture_type, ResourceFormat format, MUINT width, MUINT height, MUINT depth) {
			m_is_ready.m_desc = true;
			switch (texture_type) {
			case MACHI_TEXTURE_1D:
				m_desc = CD3DX12_RESOURCE_DESC::Tex1D(resource_format_convert(format), width);
				break;
			case MACHI_TEXTURE_2D:
				m_desc = CD3DX12_RESOURCE_DESC::Tex2D(resource_format_convert(format), width, height);
				break;
			case MACHI_TEXTURE_3D:
				m_desc = CD3DX12_RESOURCE_DESC::Tex3D(resource_format_convert(format), width, height, depth);
				break;
			default:
				m_is_ready.m_desc = false;
			}


		}

		bool init(Device& device) {

			D3D12_HEAP_PROPERTIES heap_prop_desc;

			if (m_is_ready.m_desc) {
				HRESULT hr = device->CreateCommittedResource(
					&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
					D3D12_HEAP_FLAG_NONE,
					&m_desc,
					D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
					IID_PPV_ARGS(&m_texture));
			}
			else {
				/*D3D12_RESOURCE_DESC depthStencilDesc;
				m_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				m_desc.Alignment = 0;
				m_desc.Width = mClientWidth;
				m_desc.Height = mClientHeight;
				m_desc.DepthOrArraySize = 1;
				m_desc.MipLevels = 1;
				m_desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
				m_desc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
				m_desc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
				m_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
				m_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

				m_texture->*/
				return false;
			}

			return true;
			
		};

		virtual bool connect_to_heap(Device& device, D3D12_CPU_DESCRIPTOR_HANDLE handle) {
			D3D12_SHADER_RESOURCE_VIEW_DESC desc;
			desc.Format = m_desc.Format;
			desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipLevels = 1;
			device->CreateShaderResourceView(m_texture.Get(), &desc, handle);
		};


	};

}