#include "Buffers.hpp"
#include <iostream>

lumi::graphics::Buffers::Buffers()
{
	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;
}

lumi::graphics::Buffers::~Buffers()
{
}

void lumi::graphics::Buffers::createVao()
{
	glCreateVertexArrays(1, &m_vao);
}

void lumi::graphics::Buffers::createVertexBuffers(std::vector<lumi::graphics::Vertex> data, int flags)
{
	if (m_vao == 0)
	{
		createVao();
	}
	glCreateBuffers(1, &m_vbo);	// vertex buffer
	glNamedBufferStorage(m_vbo, data.size() * sizeof(lumi::graphics::Vertex), data.data(), flags);

	glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(lumi::graphics::Vertex));
	glEnableVertexArrayAttrib(m_vao, 0); // vao, index
	glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(lumi::graphics::Vertex, Position));
	glVertexArrayAttribBinding(m_vao, 0, 0);
}

void lumi::graphics::Buffers::createElementBuffer(std::vector<GLushort> indices, int flags)
{
	if (m_vao == 0)
	{
		createVao();
	}
	glCreateBuffers(1, &m_ebo);
	glNamedBufferStorage(m_ebo, indices.size() * sizeof(GLushort), indices.data(), flags);

	glVertexArrayElementBuffer(m_vao, m_ebo);
}

void lumi::graphics::Buffers::bindBuffers()
{
	glBindVertexArray(m_vao);
}

void lumi::graphics::Buffers::unbindBuffers()
{
	glBindVertexArray(0);
}