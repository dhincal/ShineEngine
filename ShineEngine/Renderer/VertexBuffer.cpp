#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	//this->Delete();
}

// Binds the VBO
void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

// Unbinds the VBO
void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VertexBuffer::Delete() const
{
	//glDeleteBuffers(1, &m_RendererId);
}