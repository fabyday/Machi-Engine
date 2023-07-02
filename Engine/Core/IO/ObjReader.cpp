#include "ObjReader.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include <tiny_obj_loader.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
using namespace Machi::IO;

void extract_data_from_tinyobjloader();


bool OBJReader::read_mesh(const MSTRING& name, Machi::Geometry::Mesh** meshes1, int& read_mesh_num) {
	using namespace Machi;
	
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	std::string warn;


	std::string one_b_string(name.begin(), name.end());
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, one_b_string.c_str());


	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		throw std::exception("return error.");
	}

	Machi::Geometry::Mesh* meshes = NULL ;
	// init and alloc meshes memories.
	meshes = new Machi::Geometry::Mesh[shapes.size()];
	std::set<int> test;
	
	
	for (int i = 0; i < shapes.size(); i++) {
		std::set<int> v_size_checker;
		std::for_each(shapes[i].mesh.indices.begin(), shapes[i].mesh.indices.end(),
			[&v_size_checker](struct tinyobj::index_t t) {v_size_checker.insert(t.vertex_index); });
		const MSIZE_T size = v_size_checker.size();
		meshes[i].allocate(Geometry::Mesh::element_type::FACE, shapes[i].mesh.indices.size());
		meshes[i].allocate(Geometry::Mesh::element_type::VERTEX, size);
		meshes[i].allocate(Geometry::Mesh::element_type::NORMAL, size);
		meshes[i].allocate(Geometry::Mesh::element_type::TEX_COORDINATE, size);
	}





	std::map<int, int> v_idx_converter;
	std::map<int, int> f_idx_helper;
	std::cout << v_idx_converter.max_size() << std::endl;
	for (int i = 0; i < shapes.size(); i++) {
		using namespace Machi::Geometry;
		using namespace Machi::DataStructure;
		
		MUINT count_f = std::count(shapes[i].mesh.num_face_vertices.begin(), shapes[i].mesh.num_face_vertices.end(), *(shapes[i].mesh.num_face_vertices.begin()) );
		if (count_f == shapes[i].mesh.num_face_vertices.size()) { // if size is same.
			meshes[i].set_face_nums(count_f);
		}
		else { // size is diff
			meshes[i].set_face_nums(shapes[i].mesh.num_face_vertices);
		}

		MSIZE_T index_offset = 0; // tiny obj face index;
		MSIZE_T max_v_idx = 0;
		MSIZE_T v_idx = 0;
		MSIZE_T face_idx = 0; // for dstination face index;
		for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++) {
			MINT f_th_face_size = shapes[i].mesh.num_face_vertices[f];
			PredefArrayView<UINT> face = meshes[i].get_elem_view<Mesh::element_type::FACE>(face_idx);
			for (size_t fi = 0; fi < f_th_face_size; fi++) {// fi := face index
				tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + fi];

				//vertex
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

				std::map<int, int>::iterator iter = v_idx_converter.find(idx.vertex_index);
				if (iter == v_idx_converter.end()) {
					v_idx = max_v_idx++;
					v_idx_converter.insert({ idx.vertex_index , v_idx });
				}
				else {
					v_idx = iter->second;
				}

				PredefArrayView<MDOUBLE> vertex = meshes[i].get_elem_view<Mesh::element_type::VERTEX>(v_idx);
				//vertex[0] = vx; vertex[1] = vy; vertex[2] = vz;

				if (idx.normal_index != -1) {// if normal data existed
					tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
					PredefArrayView<MDOUBLE> normal = meshes[i].get_elem_view<Mesh::element_type::NORMAL>(v_idx);
				}

				if (idx.texcoord_index != -1) { //if texcoord data existed
					tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
					PredefArrayView<MDOUBLE> texcoord = meshes[i].get_elem_view<Mesh::element_type::TEX_COORDINATE>(v_idx);
					texcoord[0] = tx; texcoord[1] = ty;
				}
				face[fi] = v_idx;
			}
			index_offset += f_th_face_size;
		}

	}


	*meshes1 = meshes;
return true;


}

bool OBJReader::write_mesh(MSTRING& name, Machi::Geometry::Mesh* mesh)
{
	return false;
}
