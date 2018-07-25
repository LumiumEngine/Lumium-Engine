#pragma once
#include <glad/glad.h>
#include <LumiumEngine/Graphics/Vertex.hpp>
#include <vector>

namespace lumi
{
	namespace graphics
	{
		class Buffers
		{
		public:
			Buffers();
			~Buffers();
			void createVertexBuffers(std::vector<lumi::graphics::Vertex> data, int flags = GL_DYNAMIC_STORAGE_BIT);
			void createElementBuffer(std::vector<GLushort> indices, int flags = GL_DYNAMIC_STORAGE_BIT);
			void bindBuffers();
			void unbindBuffers();

		private:
			void createVao();
			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ebo;
		};
	}
}