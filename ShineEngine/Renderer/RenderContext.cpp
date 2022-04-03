#include "../stdafx.h"

#include "GLAD/glad.h"

#include "RenderContext.h"

#include <iostream>


void RenderContext::Draw(IndexBuffer ib, VertexArray va)
{
	va.Bind();
	GL_Call(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	va.Unbind();
}

void RenderContext::DrawAll()
{

	std::list<RenderObject>::iterator it_Element;
	// Make iterate point to begining and incerement it one by one till it reaches the end of list.
	for (it_Element = m_RenderObjects.begin(); it_Element != m_RenderObjects.end(); it_Element++)
	{

		/*
			vao bind
			vbo bind
			ibo bind

			ABI FORMASYONU ile bind olup,unbind olunacak

			shaderin yerinin onemi yok (?)
		*/
		
		if (it_Element->shader)
			it_Element->shader->Bind();
		it_Element->vertexArray->Bind();
		it_Element->vertexBuffer->Bind();
		it_Element->indexBuffer->Bind();

		it_Element->shader->CallPreRender();
		GL_Call(glDrawElements(GL_TRIANGLES, it_Element->indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));


		if (it_Element->shader)
			it_Element->shader->Unbind();
		it_Element->vertexArray->Unbind();
		it_Element->vertexBuffer->Unbind();
		it_Element->indexBuffer->Unbind();
		
	}

}
void RenderContext::AddObject(VertexArray* va, VertexBuffer* vb, IndexBuffer* ib)
{
	m_RenderObjects.push_front({ nullptr, va, ib, vb });

	va->Unbind();
	vb->Unbind();
	ib->Unbind();
}
void RenderContext::AddObject(VertexArray* va, VertexBuffer* vb, IndexBuffer* ib, Shader* shader)
{
	m_RenderObjects.push_front({ shader, va, ib, vb });

	shader->Unbind();
	va->Unbind();
	vb->Unbind();
	ib->Unbind();
}
