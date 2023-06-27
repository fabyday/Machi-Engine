#include "ObjReader.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include <tiny_obj_loader.h>
#include <iostream>
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
	meshes = new Machi::Geometry::Mesh[shapes.size()];
	for (int i = 0; i < shapes.size(); i++) {
		meshes[i].allocate(Geometry::Mesh::element_type::VERTEX_ALLOCATE, sizeof(tinyobj::real_t)*attrib.vertices.size());
		meshes

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




}

bool OBJReader::write_mesh(MSTRING& name, Machi::Geometry::Mesh* mesh)
{
	return false;
}
