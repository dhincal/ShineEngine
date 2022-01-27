#pragma once

#include <GLAD/glad.h>


#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

static void GL_ClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GL_LogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}


#define ASSERT(x) if(!(x)) __debugbreak();
#define GL_Call(x) GL_ClearError();\
	x;\
	ASSERT(GL_LogCall(#x,__FILE__,__LINE__))



