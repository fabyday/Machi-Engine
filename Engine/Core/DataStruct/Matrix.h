#include <Platform/types.h>
#include <memory>
#include <cassert>


namespace Machi {

	namespace DataStructure {


		template <typename T, int R, int C>
		class Matrix {
			void* m_data;



		public :
			Matrix(int row, int col) {};
			~Matrix() {};
			void create();
			void release();
			MSIZE_T rows();
			MSIZE_T cols();

		};

	}
}