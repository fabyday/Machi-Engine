#pragma once 

#include <vector>
#include <Platform/types.h>
namespace Machi {
	namespace Graphics {



		class IResource abstract {
		public:
			virtual MUINT size() = 0;
			virtual void set_native_pointer(void* p, MUINT size) = 0;
			virtual void set_data(std::vector<char>& src) = 0;
			virtual void set_data(void* t, MUINT size) = 0;
			virtual const std::vector<char>& as_vector() = 0;
			virtual void commit_data_to_gpu() = 0;
			virtual void initialize(MUINT size_t) = 0;

			
		};
	}
}