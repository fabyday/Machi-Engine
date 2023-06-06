#pragma once

#include <vector>
#include "IResource.h"
namespace Machi {


	namespace Graphics {



		class Buffer : public IResource{

			std::vector<char> m_data;
		public:
			virtual MUINT size();
			virtual void set_native_pointer(void* p, MUINT size);
			virtual void set_data(std::vector<char>& src);
			virtual void set_data(void* t, MUINT size);
			virtual const std::vector<char>& as_vector();
			virtual void commit_data_to_gpu();

			virtual void initialize(MUINT size) = 0;


		};
	}
}