#pragma once
#include <string>

class Shader
{
private:
	unsigned int m_Id;
	//std::string vs, fs;
public:
	Shader();
	Shader(const std::string& vertex, const std::string& fragment);
	~Shader();
	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void SetUniform3f(const std::string & name, float f1, float f2, float f3);
	void SetUniformMatrix4fv(const std::string& name, unsigned int size, bool b, const float* data);
	unsigned int CreateShader(const std::string& vs, const std::string& fs);
	const std::string GetShader(const std::string& path);
private:
	unsigned int CompileShader(unsigned int type, const std::string& shader);
	int GetUniformLocation(const std::string& name);
};