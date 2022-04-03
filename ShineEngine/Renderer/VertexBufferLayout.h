#pragma once
#include <vector>
#include "GLAD/glad.h"

struct  VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:          return 4;
		case GL_UNSIGNED_INT:   return 4;

		default:
			return 0;
			break;
		}
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout():m_Stride(0){}

	template<typename T>
	void Push(unsigned int count)
	{
	//	static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,false });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}


	inline const std::vector<VertexBufferElement> GetElements()const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

};

