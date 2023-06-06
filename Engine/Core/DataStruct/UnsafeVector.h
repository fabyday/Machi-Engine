#include <Platform/types.h>
#include <memory>
#include <cassert>
namespace Machi {

	namespace DataStructure {
		
		template<typename T>
		class Array {
			T* m_data;
			MUINT m_capacity;
			MUINT m_size;



			void resize(MUINT size) {
				assert(size > 0 && "size is not signed.");
				if (m_capacity < size) {
					m_capacity = size;
					T* tmp = new T[size];
					memcpy_s(tmp, size, m_Data, m_size);
				}
				else {

					m_capacity
				}
			}



		};


	}
}