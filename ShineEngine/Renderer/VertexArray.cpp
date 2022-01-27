#include "stdafx.h"

#include <iostream>

#include "VertexArray.h"


VertexArray::VertexArray()
{
	GL_Call(glGenVertexArrays(1, &m_RendererId));
}


VertexArray::~VertexArray()
{

	GL_Call(glDeleteVertexArrays(1, &m_RendererId));

}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();

	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		GL_Call(glEnableVertexAttribArray(i));
		GL_Call(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}


}


void  VertexArray::Bind() const
{
	GL_Call(glBindVertexArray(m_RendererId));
}
void VertexArray::Unbind()const
{
	GL_Call(glBindVertexArray(0));
}