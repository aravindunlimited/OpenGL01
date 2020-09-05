#pragma once

#include <GL/glew.h>
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"


class VertexArrayObject
{
public:
	VertexArrayObject();
	void addBuffer( VertexBuffer& vb,  VertexBufferLayout& layout) ;
	void bind();
	void unbind();
	~VertexArrayObject();
private:
	GLuint m_vbo;
};

