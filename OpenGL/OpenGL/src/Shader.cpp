#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>



unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	auto id = glCreateShader(type);
	auto src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		auto length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::string message(length, 0);
		glGetShaderInfoLog(id, length, &length, &(*message.begin()));
		std::cout << message << '\n';
	}
	return id;
}

static std::string GetSource(std::string_view filepath)
{
	std::ifstream file(filepath.data());
	if (!file.is_open())
	{
		std::cerr << "Failed to get source from: " << filepath << "\n";
		terminate();
	}
	return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

Shader::Shader(std::string_view vertexShaderFilepath, std::string_view fragmentShaderFilepath):id(glCreateProgram())
{

	std::string vertexShaderSource_string{ GetSource(vertexShaderFilepath) };
	std::string fragmentShaderSource_string{ GetSource(fragmentShaderFilepath) };
	auto vertexShaderid = CompileShader(GL_VERTEX_SHADER, vertexShaderSource_string);
	auto fragmentShaderid = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource_string);

	/*DEBUG*/
	std::cout << vertexShaderSource_string << "\n\n" << fragmentShaderSource_string;

	glAttachShader(id, vertexShaderid);
	glAttachShader(id, fragmentShaderid);
	glLinkProgram(id);
	glValidateProgram(id);
	
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::Bind() const
{
	glUseProgram(id);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(std::string_view name) const
{
	return glGetUniformLocation(id, name.data());
}

void Shader::SetUniform4f(std::string_view name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
