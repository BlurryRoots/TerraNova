#ifndef TerraNova_Mesh_h
#define TerraNova_Mesh_h

#include <vector>

#include <tiny_obj_loader.h>

// GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3

namespace terranova { namespace model {

struct Mesh {

	Mesh (void)
	: shapes ()
	, materials ()
	, vertex_array_object (0)
	, vertex_buffer (0)
	, index_buffer (0)
	, uv_buffer (0)
	, normal_buffer (0)
	, color_buffer (0) {
		//
	}

	Mesh (
		std::vector<tinyobj::shape_t> shapes,
		std::vector<tinyobj::material_t> materials
	)
	: shapes (shapes)
	, materials (materials)
	, vertex_array_object (0)
	, vertex_buffer (0)
	, index_buffer (0)
	, uv_buffer (0)
	, normal_buffer (0)
	, color_buffer (0) {
		//
	}

	Mesh (const Mesh &other)
	: shapes (other.shapes)
	, materials (other.materials)
	, vertex_array_object (other.vertex_array_object)
	, vertex_buffer (other.vertex_buffer)
	, index_buffer (other.index_buffer)
	, uv_buffer (other.uv_buffer)
	, normal_buffer (other.normal_buffer)
	, color_buffer (other.color_buffer) {
		//
	}

	virtual
	~Mesh (void) {
		//
	}

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::vector<glm::vec3> dimensions;

	GLuint vertex_array_object;

	GLuint vertex_buffer;
	GLuint index_buffer;
	GLuint uv_buffer;
	GLuint normal_buffer;
	GLuint color_buffer;

};

}}

#endif