#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <list>

struct RenderObject
{
	Shader* shader;
	VertexArray* vertexArray;
	IndexBuffer* indexBuffer;
	VertexBuffer* vertexBuffer;
};

class RenderContext
{
private:
	std::list<RenderObject> m_RenderObjects;

public:
	void Draw(IndexBuffer ib, VertexArray va);
	void DrawAll();
	void AddObject(VertexArray* va,  VertexBuffer* vb,IndexBuffer* ib,Shader* shader);
	void AddObject(VertexArray* va,  VertexBuffer* vb,IndexBuffer* ib);


};

