#include "IndexBuffer.h"

#include "Renderer.h"



IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count): m_count(count)
{

	glGenBuffers(1, &m_indexbuffer); GLerrorProcessing(__LINE__, __FUNCTION__);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbuffer); GLerrorProcessing(__LINE__, __FUNCTION__);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW); GLerrorProcessing(__LINE__, __FUNCTION__);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GLerrorProcessing(__LINE__, __FUNCTION__);
}

void IndexBuffer::bind()
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexbuffer); GLerrorProcessing(__LINE__, __FUNCTION__);

}

void IndexBuffer::unbind()
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GLerrorProcessing(__LINE__, __FUNCTION__);

}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_indexbuffer);
}

