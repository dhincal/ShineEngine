//for dummy use
#include "stdafx.h"
#include "../stdafx.h"

#include "Shader.h"

#include <GLAD/glad.h>




Shader::Shader(const std::string& filePath) :m_FilePath(filePath), m_RendererId(0)
{
	ShaderProgramSource source = ParseShader(filePath);

	// if there is no source for at least one of them
	if (source.VertexSource == "" || source.FragmentSource == "")
	{
		std::cout << "No Vertex Source Or Fragment Source !! \n Maybe file isn't found or loaded properly. \n\n";
		ASSERT(true);
	}

	
	
	m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
	std::string vertexSrc;
	std::string fragmentSrc;
	LoadShaderFile(vertexFile, vertexSrc);
	LoadShaderFile(fragmentFile, fragmentSrc);

	m_RendererId = CreateShader(vertexSrc, fragmentSrc);
}

Shader::~Shader()
{
	GL_Call(glDeleteProgram(m_RendererId));
}

void Shader::Bind() const
{
	GL_Call(glUseProgram(m_RendererId));
}

void Shader::Unbind() const
{
	GL_Call(glUseProgram(0));
}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{

	GL_Call(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GL_Call(glAttachShader(program, vs));
	GL_Call(glAttachShader(program, fs));
	GL_Call(glLinkProgram(program));
	GL_Call(glValidateProgram(program));

	GL_Call(glDeleteShader(vs));
	GL_Call(glDeleteShader(fs));

	return program;

}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{

	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
			else
			{
				std::cout << "Invalid Shader Type";
				__debugbreak();
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str() , ss[1].str() };

}

const std::string& Shader::LoadShaderFile(const std::string& filePath)
{


	std::ifstream stream(filePath);


	std::string line;
	std::stringstream ss;

	if (!stream)
		std::cout << "Could not open file. \n FilePath : " << filePath << "\n";

	while (std::getline(stream, line))
	{
		ss << line << "\n";
	}

	return ss.str();
}



void Shader::LoadShaderFile(const std::string& filePath, std::string& srcVar)
{


	std::ifstream stream(filePath);


	std::string line;
	std::stringstream ss;

	if (!stream)
		std::cout << "Could not open file. \n FilePath : " << filePath << "\n";

	while (std::getline(stream, line))
	{
		ss << line << "\n";
	}

	srcVar = ss.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GL_Call(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GL_Call(glShaderSource(id, 1, &src, nullptr));
	GL_Call(glCompileShader(id));

	int result;
	GL_Call(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		GL_Call(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GL_Call(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << std::endl;
		std::cout << message << std::endl;


		GL_Call(glDeleteShader(id));
		return 0;
	}
	return id;
}


void Shader::SetUniform1f(const std::string& name, float v0)
{
	GL_Call(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GL_Call(glUniform3f(GetUniformLocation(name), v0,v1,v2));
}

void Shader::SetUniformMat4x4(const std::string& name,const float* ptr,int count,bool transpose)
{
	GL_Call(glUniformMatrix4fv(GetUniformLocation(name), count, transpose?GL_TRUE:GL_FALSE,ptr));
}


unsigned int Shader::GetUniformLocation(const std::string& name)
{
	GL_Call(int location = glGetUniformLocation(m_RendererId, name.c_str()));

	if (location == -1)
	{
		std::cout << "Warning:  `" << name << "` named uniform doesn't exist. \n\n";
		ASSERT(false);
	}
	return (unsigned int)location;
}

