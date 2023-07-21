#include <Platform/types.h>
#include <memory>
#include <cassert>


namespace Machi {

	namespace DataStructure {


		


		template <typename T>
		class MMatrix {
			
			void* m_data;
			MSIZE_T m_row, m_col, m_elem;
			bool m_is_initialized;

		public :
			MMatrix() :m_is_initialized(false){
			
			
			};
			
			/*MMatrix(MMatrix<T>& data) {
				m_data = data.m_data;
				m_col = data.col;
				m_row = data.m_row;
				m_elem = data.m_elem;
				m_is_initialized = true;

			}*/


			MMatrix(int row, int col):MMatrix(row, col, 1){};
			MMatrix(int row, int col, int elem)
				: m_row(row), m_col(col), m_elem(elem){ 
				create();
			};
			~MMatrix() {
				delete[] static_cast<T>(m_data);
			
			};


			void create() {
				m_data = new double[m_row * m_col * m_elem];
				m_is_initialized =true;
			}
			void release();
			MSIZE_T rows() { return m_row; };
			MSIZE_T cols() { return m_col; };
			MSIZE_T elems() { return m_elem; };
			MSIZE_T size() {
				return m_row * m_col * m_elem;
			}

			
			struct matrix_data_insert_operation {
				T* const m_data;
				MSIZE_T m_index;
				MSIZE_T m_size;
				matrix_data_insert_operation(T* ptr, MSIZE_T size): m_data(ptr), m_size(size), m_index(0){};
				matrix_data_insert_operation& operator ,(T data) {
					m_data[m_index] = data;
					m_index++;
					return *this;
				}
			};

			matrix_data_insert_operation operator <<(T data) {
				return matrix_data_insert_operation(m_data, size());
			}

		};




		typedef MMatrix<MDOUBLE> MatrixD;// default predefined matrix is runtime dynamic matrix.
		typedef MMatrix<MFLOAT> MatrixF;// default predefined matrix is runtime dynamic matrix.


	}
}
