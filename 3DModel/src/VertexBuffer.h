#pragma once
#include <glad/glad.h>
class VertexBuffer
{
private:
	unsigned int m_Id;
public:
	VertexBuffer();
	~VertexBuffer();

	void add(unsigned int size, const void* data);
	void ChangeData(unsigned int size, const void * data);
	void Bind() const;
	void Unbind() const;
};