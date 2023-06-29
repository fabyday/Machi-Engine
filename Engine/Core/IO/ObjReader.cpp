#include "ObjReader.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include <tiny_obj_loader.h>
#include <iostream>
#include <map>
using namespace Machi::IO;

bool OBJReader::read_mesh(const MSTRING& name, Machi::Geometry::Mesh* meshes, int& read_mesh_num) {
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


	// init and alloc meshes memories.
	meshes = new Machi::Geometry::Mesh[shapes.size()];
	for (int i = 0; i < shapes.size(); i++) {
		meshes[i].allocate(Geometry::Mesh::element_type::VERTEX, sizeof(MDOUBLE)*shapes[i].points.indices.size());
		meshes[i].allocate(Geometry::Mesh::element_type::FACE, sizeof(MDOUBLE)*shapes[i].mesh.indices.size());
		meshes[i].allocate(Geometry::Mesh::element_type::NORMAL, sizeof(MDOUBLE)*shapes[i].points.indices.size());
		meshes[i].allocate(Geometry::Mesh::element_type::TEX_COORDINATE, sizeof(MDOUBLE)*shapes[i].points.indices.size());
	}
	std::map<int, int> v_idx_converter;
	std::map<int, int> f_idx_helper;
	for (int i = 0; i < shapes.size(); i++) {
		using namespace Machi::Geometry;
		MSIZE_T index_offset = 0;
		MSIZE_T max_v_idx = 0;
		MSIZE_T v_idx = 0;
		for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++) {
			MINT f_th_face_size = shapes[i].mesh.num_face_vertices[f];


			for (size_t fi = 0; fi < f_th_face_size; fi++) {// fi := face index
				tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + fi];
				
				meshes[i].get_elem_view<Mesh::element_type::FACE>(index_offset);


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
				//meshes[i].get_elem_view< Mesh::element_type::VERTEX>(v_idx);
			}
			index_offset += f_th_face_size;
		}



	}



	for (int s = 0; s < shapes.size(); s++) {
		MSIZE_T index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			MINT fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
				tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
				tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
				// Optional: vertex colors
				// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
				// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
				// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

return false;


}

bool OBJReader::write_mesh(MSTRING& name, Machi::Geometry::Mesh* mesh)
{
	return false;
}
