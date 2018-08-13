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
			std::vector<Vertex> m_vertices;
			std::vector<GLushort> m_indices;
			glm::mat4 m_model;
		};
	}
}