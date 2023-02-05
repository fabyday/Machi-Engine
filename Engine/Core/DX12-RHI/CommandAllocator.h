#include "Commons.h"
#include "Device.h"
namespace Machi {





	class Device;
	class CommandAllocator final {
		friend class NativeGraphicsManager;
		enum CommandListType {
			MACHI_COMMAND_LIST_TYPE_DIRECT = 0,
			MACHI_COMMAND_LIST_TYPE_BUNDLE = 1,
			MACHI_COMMAND_LIST_TYPE_COMPUTE = 2,
			MACHI_COMMAND_LIST_TYPE_COPY = 3,
			MACHI_COMMAND_LIST_TYPE_VIDEO_DECODE = 4,
			MACHI_COMMAND_LIST_TYPE_VIDEO_PROCESS = 5,
			MACHI_COMMAND_LIST_TYPE_VIDEO_ENCODE = 6
		};

		ComPtr<ID3D12CommandAllocator> m_command_allocator;
		CommandListType m_type;
		CommandAllocator() :m_type(MACHI_COMMAND_LIST_TYPE_DIRECT) {};
		CommandAllocator(CommandListType type ) :m_type(type) {};

		bool create(Device& device);
		ID3D12CommandAllocator* operator->() { return m_command_allocator.Get(); }



	};
};

