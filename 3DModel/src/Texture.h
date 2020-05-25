#pragma once
#include <glad/glad.h>
#include<GL/glut.h>
#include<string>

class Texture 
{
private:
	unsigned int m_id;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture();
	~Texture();

	void add(std::string& path);
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};