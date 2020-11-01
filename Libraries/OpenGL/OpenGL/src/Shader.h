#pragma once
#include <string_view>
class Shader
{
	unsigned int id;

	int GetUniformLocation(std::string_view name) const;
	static unsigned int CompileShader(unsigned int type, const std::string& source);
public:
	Shader(std::string_view vertexShaderFilepath, std::string_view fragmentShaderFilepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	/*set uniforms*/
	void SetUniform4f(std::string_view name, float v0, float v1, float v2, float v3);
};