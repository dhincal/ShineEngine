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
public:
    static RenderContext& getInstance()
    {
        static RenderContext instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    void Draw(IndexBuffer ib, VertexArray va);
    void DrawAll();
    void AddObject(VertexArray* va, VertexBuffer* vb, IndexBuffer* ib, Shader* shader);
    void AddObject(VertexArray* va, VertexBuffer* vb, IndexBuffer* ib);
private:
    RenderContext() {}                    // Constructor? (the {} brackets) are needed here.
    std::list<RenderObject> m_RenderObjects;

public:
    RenderContext(RenderContext const&) = delete;
    void operator=(RenderContext const&) = delete;
};
