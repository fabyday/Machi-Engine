
#pragma once 

#include "IResource.h"


namespace Machi {


	namespace Graphics {


		class Texture : public IResource {

			std::vector<char> m_data;
			MUINT m_row;
			MUINT m_col;
			MUINT m_color;





		public:
			virtual void set_native_pointer(void* p, MUINT size);
			virtual void commit_data_to_gpu();
			virtual void initialize(MUINT size);

			inline Texture& set_row_size(MUINT row) { m_row = row; return *this; }
			inline Texture& set_col_size(MUINT col) { m_col = col; return *this; }
			inline Texture& set_color_size(MUINT color) { m_color = color; return *this; }
			virtual void set_data(std::vector<char>& src);
			virtual void set_data(void* t, MUINT size);
			inline MUINT row_size() { return m_row; };
			inline MUINT col_size() { return m_col; };
			inline MUINT color_size() { return m_color; };
			virtual MUINT size();

			virtual const std::vector<char>& as_vector();
			inline void initialize_buffer(MUINT row, MUINT col = -1, MUINT color = -1) {
				m_row = row;
				m_col = col;
				m_color = color;
				this->initialize(row * (col < 0 ? 1 : col) * (color < 0 ? 1 : color));
			}
		};
	}

}