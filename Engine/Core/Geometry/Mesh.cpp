#include "Mesh.h"
using namespace Machi::Geometry;

bool simple_alloc_function(void** ptr, MSIZE_T* cur_size, MSIZE_T desired_size) {
	if (desired_size <= 0)
		return false;


	if (*ptr == NULL) {
		*ptr = new MUCHAR[desired_size];
		*cur_size = desired_size;
	}
	else {
		if (*cur_size< desired_size) {

			void* tmp = new MUCHAR[desired_size];
			memcpy_s(tmp, desired_size, *ptr, *cur_size);
			delete[] *ptr;
			*ptr = tmp;
			*cur_size = desired_size;
		}
		// else do noting
	}

	return true;
}

MUINT Machi::Geometry::Mesh::get_bytes() {

	return this->get_elem_size(element_type::VERTEX) * this->get_elem_type_size(element_type::VERTEX)
		+ this->get_elem_size(element_type::TEX_COORDINATE) * this->get_elem_type_size(element_type::TEX_COORDINATE)
		+ this->get_elem_size(element_type::NORMAL) * this->get_elem_type_size(element_type::NORMAL)
		+ this->get_elem_size(element_type::FACE) * this->get_elem_type_size(element_type::FACE);



}
void Machi::Geometry::Mesh::allocate(element_type type, MSIZE_T size)
{

	switch (type)
	{
	case Machi::Geometry::Mesh::element_type::VERTEX:
	{
		//if (m_vertice == NULL) {
		//	m_vertice = new MDOUBLE[size];
		//	attr.m_vertice_size = size;

		//}
		//else {
		//	if (attr.m_vertice_size < size) {

		//		void* tmp = new MDOUBLE[size];
		//		memcpy_s(tmp, size, m_vertice, attr.m_vertice_size);
		//		delete[] m_vertice;
		//		m_vertice = tmp;
		//		attr.m_vertice_size = size;
		//	}
		//	// else do noting
		//}

		simple_alloc_function(&m_vertice, &(attr.m_vertice_size), sizeof(MDOUBLE) * size * 3);
	}
		break;
	case Machi::Geometry::Mesh::element_type::FACE:
	{
		if (m_is_all_face_size_same && *reinterpret_cast<MSIZE_T*>(m_face_elem_nums)) {
			simple_alloc_function(&m_faces, &(attr.m_face_size), sizeof(MUINT) * size* (*reinterpret_cast<MSIZE_T*>(m_face_elem_nums)) );
		}
		else {
			simple_alloc_function(&m_faces, &(attr.m_face_size), sizeof(MUINT) * size );
		}
	}
		break;
	case Machi::Geometry::Mesh::element_type::NORMAL:
	{
		simple_alloc_function(&m_normals, &(attr.m_normal_size), sizeof(MDOUBLE) * size*3);
	}
		break;
	case Machi::Geometry::Mesh::element_type::TEX_COORDINATE:
	{
		simple_alloc_function(&m_tex_coord, &(attr.m_texcoord_size), sizeof(MDOUBLE) * size*2);
	}
		break;
	default:
		break;
	}
}

bool Mesh::set_face_nums(MSIZE_T size)
{
	if (m_face_elem_nums == NULL)
		m_face_elem_nums = new MSIZE_T;
	if (size > 0)
		*reinterpret_cast<MSIZE_T*>(m_face_elem_nums) = size;
	m_face_elem_nums_size = 1;
	m_is_all_face_size_same = true;
	return true;
}

bool Mesh::set_face_nums(const std::vector<MSIZE_T>& sizes) {

	const int size = sizes.size();
	if (m_face_elem_nums == NULL)
		m_face_elem_nums = new MSIZE_T[size];
	else {
		if (size > m_face_elem_nums_size) {
			delete [] m_face_elem_nums;
			m_face_elem_nums = new MSIZE_T[size];
		}
	}
	
	memcpy_s(m_face_elem_nums, sizeof(MSIZE_T)*size, sizes.data(), sizeof(MSIZE_T)*size);
	m_is_all_face_size_same = false;
	return true;
}



bool Mesh::set_face_nums(const std::vector<MUCHAR>& sizes) {

	std::vector<MSIZE_T> tmp(sizes.begin(), sizes.end());
	return set_face_nums(sizes);
}

MUINT Machi::Geometry::Mesh::get_elem_size(element_type type)
{



	switch (type)
	{
	case Machi::Geometry::Mesh::element_type::VERTEX:
	{
		return attr.m_vertice_size;
	}
	break;
	case Machi::Geometry::Mesh::element_type::FACE:
	{
		return attr.m_face_size;
	}
	break;
	case Machi::Geometry::Mesh::element_type::NORMAL:
	{
		return attr.m_normal_size;
	}
	break;
	case Machi::Geometry::Mesh::element_type::TEX_COORDINATE:
	{
		return attr.m_texcoord_size;
	}
	break;
	}
	return 0;
}

MUINT Machi::Geometry::Mesh::get_elem_type_size(element_type type)
{



	switch (type)
	{
	case Machi::Geometry::Mesh::element_type::VERTEX:
	{
		return attr.m_vertice_size;
	}
	break;
	case Machi::Geometry::Mesh::element_type::FACE:
	{
		return attr.m_face_size;
	}
	break;
	case Machi::Geometry::Mesh::element_type::NORMAL:
	{
		return attr.m_normal_size;
	}
	break;
	case Machi::Geometry::Mesh::element_type::TEX_COORDINATE:
	{
		return attr.m_texcoord_size;
	}
	break;
	}
	return 0;
}