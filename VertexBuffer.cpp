#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(float* position, GLsizeiptr size)
{

	glGenBuffers(1, &m_buffer);									GLerrorProcessing(__LINE__, __FUNCTION__);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);		               GLerrorProcessing(__LINE__, __FUNCTION__);
	//glBufferData(GL_ARRAY_BUFFER, size, position, GL_DYNAMIC_DRAW);  GLerrorProcessing(__LINE__, __FUNCTION__);
	glBufferData(GL_ARRAY_BUFFER, size, position, GL_STATIC_DRAW);  GLerrorProcessing(__LINE__, __FUNCTION__);
}

void VertexBuffer::bind()
{

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);		               GLerrorProcessing(__LINE__, __FUNCTION__);

}

void VertexBuffer::unbind()
{

	glBindBuffer(GL_ARRAY_BUFFER, 0);		               GLerrorProcessing(__LINE__, __FUNCTION__);

}
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}

void VertexBuffer::dynamicVertex(float* position, GLsizeiptr size)
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, position);
}

