#pragma once
#include "Commons.h"
#include "Device.h"

#include "RootParameter.h"

namespace Machi {

	namespace NativeGraphics {
		//root signature maximum size is 64 DWORDs
		// Root constants cost 1 DWORD each, since they are 32-bit values.
		// Root descriptors (64-bit GPU virtual addresses) cost 2 DWORDs each.
		// Descriptor tables cost 1 DWORD each.
		class RootSignature final {
		private:
			ComPtr<ID3D12RootSignature> m_rootsignature;




			void init(std::shared_ptr<Device> device, RootParameter& params);

			inline ID3D12RootSignature* Get() { return m_rootsignature.Get(); };


			friend class NativeGraphicsManager;
			friend class PipeLineState;
			friend class Device;





		};
	}

}