#include <Platform/types.h>
#include <memory>
#include <cassert>
namespace Machi {

	namespace DataStructure {
		
		class ArrayView {
			void* m_data;
			MUINT m_size;
			

			ArrayView(T* data, MUINT size) :m_size(size), m_data(data) {};
			ArrayView(ArrayView&& other) {
				m_data = other.m_data;
				m_size = other.m_size;
			}
			template<typename T>
			T& operator[](MUINT index) {
				MUINT max_index = m_size/sizeof(T);
				if(index >= max_index)
					throw std::exception("array out of range...")
				return *reinterpret_cast<T>(m_data)[index];
			}

		};


	}
}