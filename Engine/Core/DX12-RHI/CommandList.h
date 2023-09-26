#include "Common.h"
#include "Device.h"
#include "CommandAllocator.h"

#include "RootSignature.h"
#include "Viewport.h"
namespace Machi {
	namespace NativeGraphics {
		class CommandList final {




		public:
			void initialize(std::shared_ptr<Device> device, );
			void close();

			CommandList* set_graphics_rootsignature(std::shared_ptr<Rootsignature> root);
			CommandList* set_viewport(std::shared_ptr<Viewport>);
			CommandList* set_scissorrects(std::shared_ptr<Viewport>);
			CommandList* set_render_target(std::shared_ptr<Viewport>);

			CommandList* clear_render_target();
			CommandList* set_primitive_topology();
			CommandList* set_vertex_buffer();
			CommandList* draw_instance();
			CommandList* set_resource_barrier(/*current_state present_state*/);
			CommandList* unset_resource_barrier(/*current_state present_state*/);

			CommandList* reset();
			void execute();

			

		};
	}
}
