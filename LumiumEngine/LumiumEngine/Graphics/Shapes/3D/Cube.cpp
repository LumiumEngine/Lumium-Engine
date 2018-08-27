#include "Cube.hpp"

lumi::graphics::Cube::Cube()
{
	m_model = glm::mat4(1);
	createCube();
}

lumi::graphics::Cube::~Cube()
{
}

void lumi::graphics::Cube::createCube()
{
	std::vector<glm::vec3> positions =
	{
		// Front face
		glm::vec3(-1.0, -1.0,  1.0),
		glm::vec3( 1.0, -1.0,  1.0),
		glm::vec3( 1.0,  1.0,  1.0),
		glm::vec3(-1.0,  1.0,  1.0),
		// Back face
		glm::vec3(-1.0, -1.0, -1.0),
		glm::vec3(-1.0,  1.0, -1.0),
		glm::vec3( 1.0,  1.0, -1.0),
		glm::vec3( 1.0, -1.0, -1.0),
		// Top face
		glm::vec3(-1.0,  1.0, -1.0),
		glm::vec3(-1.0,  1.0,  1.0),
		glm::vec3( 1.0,  1.0,  1.0),
		glm::vec3( 1.0,  1.0, -1.0),
		// Bottom face
		glm::vec3(-1.0, -1.0, -1.0),
		glm::vec3( 1.0, -1.0, -1.0),
		glm::vec3( 1.0, -1.0,  1.0),
		glm::vec3(-1.0, -1.0,  1.0),
		// Right face
		glm::vec3( 1.0, -1.0, -1.0),
		glm::vec3( 1.0,  1.0, -1.0),
		glm::vec3( 1.0,  1.0,  1.0),
		glm::vec3( 1.0, -1.0,  1.0),
		// Left face
		glm::vec3(-1.0, -1.0, -1.0),
		glm::vec3(-1.0, -1.0,  1.0),
		glm::vec3(-1.0,  1.0,  1.0),
		glm::vec3(-1.0,  1.0, -1.0),
	};

	std::vector<glm::vec2> uvs =
	{
		// Front
		glm::vec2(0.0,  0.0),
		glm::vec2(1.0,  0.0),
		glm::vec2(1.0,  1.0),
		glm::vec2(0.0,  1.0),
		// Back
		glm::vec2(0.0,  0.0),
		glm::vec2(1.0,  0.0),
		glm::vec2(1.0,  1.0),
		glm::vec2(0.0,  1.0),
		// Top
		glm::vec2(0.0,  0.0),
		glm::vec2(1.0,  0.0),
		glm::vec2(1.0,  1.0),
		glm::vec2(0.0,  1.0),
		// Bottom
		glm::vec2(0.0,  0.0),
		glm::vec2(1.0,  0.0),
		glm::vec2(1.0,  1.0),
		glm::vec2(0.0,  1.0),
		// Right
		glm::vec2(0.0,  0.0),
		glm::vec2(1.0,  0.0),
		glm::vec2(1.0,  1.0),
		glm::vec2(0.0,  1.0),
		// Left
		glm::vec2(0.0,  0.0),
		glm::vec2(1.0,  0.0),
		glm::vec2(1.0,  1.0),
		glm::vec2(0.0,  1.0)
	};

	for (int i = 0; i < positions.size(); i++)
	{
		Vertex vert;
		vert.Position = positions[i];
		vert.TexCoord = uvs[i];
		m_vertices.push_back(vert);
	}

	m_indices =
	{
		0,  1,  2,      0,  2,  3,    // front
		4,  5,  6,      4,  6,  7,    // back
		8,  9,  10,     8,  10, 11,   // top
		12, 13, 14,     12, 14, 15,   // bottom
		16, 17, 18,     16, 18, 19,   // right
		20, 21, 22,     20, 22, 23,   // left
	};
}