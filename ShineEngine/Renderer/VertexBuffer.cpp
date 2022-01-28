#include "stdafx.h"
#include "VertexBuffer.h"


/// <summary>
/// Creates VertexBuffer object with given data and size(in bytes)
/// </summary>
/// <param name="data">The vertices data it self</param>
/// <param name="size">data's size in bytes</param>
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	this->Delete();
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete() const
{
	glDeleteBuffers(1, &m_RendererId);
}