#include <Platform/types.h>
#include <memory>
#include <cassert>
namespace Machi {

	namespace DataStructure {
		


		template<typename T>
		class PredefArrayView {
			T * m_data;
			const MUINT m_size;

		public:
			PredefArrayView(T* data, MUINT size) : m_data(data) , m_size(size) {};
			//PredefArrayView(T* data, MUINT size) { m_data = data; m_size = size; };

			//PredefArrayView(PredefArrayView&& other) = delete;
			//PredefArrayView(const PredefArrayView& other) = delete;
			//PredefArrayView() :m_size(10) { };
			PredefArrayView() = delete;
			MUINT size() {
				return m_size;
			}
			T& operator[](MUINT index) {
				if (index >= m_size || index < 0) {
					throw std::out_of_range("array out of range...");
				}
				return reinterpret_cast<T*>(m_data)[index];
			}
		};



		class ArrayView {
			void* m_data;
			MUINT m_size;
			

			ArrayView(void* data, MUINT size) :m_size(size), m_data(data) {};
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