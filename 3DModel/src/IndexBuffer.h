#pragma once
#include <glad/glad.h>
class IndexBuffer
{
private:
	unsigned int m_Id;
	unsigned int m_count;
public:
	IndexBuffer();
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void add(const unsigned int* data, unsigned int count);

	unsigned int GetCount();
};