#include "Shader.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <glad/glad.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	:m_Id(0)
{
	CreateShader(vertexPath, fragmentPath);
}

Shader::Shader()
	:m_Id(0)
{
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

const std::string Shader::GetShader(const std::string& path)
{
	std::string shader;
	std::stringstream ss;
	std::fstream file;
	file.open(path, std::fstream::in);
	if (!file.is_open())
		std::cout << "Error opening file..\n";
	ss << file.rdbuf();
	shader = ss.str();
	return shader;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shader)
{
	unsigned int id = glCreateShader(type);
	const char* src = shader.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int  success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") <<
			"::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vs = GetShader(vertexPath);
	std::string fs = GetShader(fragmentPath);
	m_Id = glCreateProgram();
	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vs);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fs);

	glAttachShader(m_Id, vertex);
	glAttachShader(m_Id, fragment);
	glLinkProgram(m_Id);
	glValidateProgram(m_Id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return m_Id;
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string & name, float f1, float f2, float f3, float f4)
{
	glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}
void Shader::SetUniform3f(const std::string & name, float f1, float f2, float f3)
{
	glUniform3f(GetUniformLocation(name), f1, f2, f3);
}

void Shader::SetUniformMatrix4fv(const std::string & name, unsigned int size, bool b, const float * data)
{
	glUniformMatrix4fv(GetUniformLocation(name), size, b, data);
}

int Shader::GetUniformLocation(const std::string & name)
{
	int location = glGetUniformLocation(m_Id, name.c_str());
	if (location == -1)
		std::cout << "Uniform " << name << " doesn't exist\n";
	return location;
}

void Shader::Bind() const
{
	glUseProgram(m_Id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

