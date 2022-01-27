#include "stdafx.h"

#include "GLAD/glad.h"

#include "RenderContext.h"

#include <iostream>


void CheckErrorInShader(unsigned int shaderId);

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
		it_Element->vertexArray->Bind();
		it_Element->vertexBuffer->Bind();
		it_Element->indexBuffer->Bind();


		GL_Call(glDrawElements(GL_TRIANGLES, it_Element->indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));


		it_Element->vertexArray->Unbind();
		it_Element->vertexBuffer->Unbind();
		it_Element->indexBuffer->Unbind();
		
	}

}

void RenderContext::AddObject(VertexArray* va, VertexBuffer* vb, IndexBuffer* ib, Shader* shader)
{
	m_RenderObjects.push_front({ shader, va, ib, vb });

}


//void RenderContext::Setup_Triangle()
//{
//	float vertices[] = {
//	  -0.5f, -0.5f,  // sol alt
//	   0.5f, -0.5f,  // sag alt
//	   0.5f,  0.5f,  // sag ust
//	  -0.5f,  0.5f,  // sol ust
//	};
//
//	unsigned int indices[] = {
//		0,1,2,
//		2,3,0
//	};
//
//	
//	
//	// VAO
//	
//	VertexArray va;
//	VertexBuffer vb(vertices,sizeof(vertices));
//
//	VertexBufferLayout layout;
//	layout.Push<float>(2);
//	va.AddBuffer(vb,layout);
//
//
//	IndexBuffer ib(indices,6);
//
//	
//	
//
//	
//}
