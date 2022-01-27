#include "stdafx.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):
	m_Count(count)
{
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	this->Delete();
}

// Binds the VBO
void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

// Unbinds the VBO
void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void IndexBuffer::Delete()
{
	glDeleteBuffers(1, &m_RendererId);
}