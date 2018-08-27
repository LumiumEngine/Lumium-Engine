#include "Square.hpp"

lumi::graphics::Square::Square()
{
	m_model = glm::mat4(1);
	createSquare();
}

lumi::graphics::Square::~Square()
{
}

void lumi::graphics::Square::createSquare()
{
	std::vector<glm::vec3> positions =
	{
		glm::vec3(-1.0, -1.0,  1.0),
		glm::vec3(1.0, -1.0,  1.0),
		glm::vec3(1.0,  1.0,  1.0),
		glm::vec3(-1.0,  1.0,  1.0)
	};

	std::vector<glm::vec2> uvs =
	{
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
		0,  1,  2,		0,  2,  3,
	};
}