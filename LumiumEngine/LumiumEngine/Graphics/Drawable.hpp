#pragma once
#include "Vertex.hpp"
#include <vector>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace lumi
{
	namespace graphics
	{
		class Drawable
		{
		public:
			Drawable() { m_model = glm::mat4(1); };
			virtual ~Drawable() {};
			virtual std::vector<Vertex> getVertices() { return m_vertices; }
			virtual std::vector<GLushort> getIndices() { return m_indices; }
			virtual glm::mat4& getModel() { return m_model; }
			std::vector<Vertex> m_vertices;
			std::vector<GLushort> m_indices;
			glm::mat4 m_model;

		};
	}
}