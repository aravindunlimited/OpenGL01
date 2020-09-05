#pragma once

#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	void bind();
	void unbind();
	inline unsigned int getIndexSize() { return m_count; }
	~IndexBuffer();
private:
	GLuint m_indexbuffer;
	unsigned  int m_count;
};

