#include "Commons.h"
#include "Device.h"



namespace Machi {



	class RootSignature final {
	private:
		ComPtr<ID3D12RootSignature> m_rootsignature;



		void add_constant_buffer(Machi::RootSignature, MUINT size);
		void init(Device& device);
		friend class NativeGraphicsManager;
	public:


	};


}