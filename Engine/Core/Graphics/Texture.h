
#pragma once 

#include "IResource.h"


namespace Machi {


	namespace Graphics {


		class Texture : public IResource {

			std::vector<char> m_data;
			MUINT m_row;
			MUINT m_col;
			MUINT m_color;





			inline MUINT row_size() { return m_row; };
			inline MUINT col_size() { return m_col; };
			inline MUINT color_size() { return m_color; };
			virtual MUINT size();
			virtual void set_native_pointer(void* p, MUINT size);
			virtual void set_data(std::vector<char>& src);
			virtual void set_data(void* t, MUINT size);
			virtual const std::vector<char>& as_vector();
			virtual void commit_data_to_gpu();

			virtual void initialize(MUINT size);

			inline void initialize(MUINT row, MUINT col = -1, MUINT color = -1) {
				m_row = row;
				m_col = col;
				m_color = color;
				initialize(row * (col < 0 ? 1 : col) * (color < 0 ? 1 : color));
			}
		};
	}

}