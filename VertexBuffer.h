#pragma once

#include <GL/glew.h>
class VertexBuffer
{
public:
	VertexBuffer(float* position, GLsizeiptr size);
	void bind();
	void unbind();
	~VertexBuffer();
	void dynamicVertex(float* position, GLsizeiptr size);
private:
	GLuint m_buffer;
};

