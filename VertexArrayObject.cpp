#include "VertexArrayObject.h"
#include "Renderer.h"


VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_vbo);		GLerrorProcessing(__LINE__, __FUNCTION__); 
}
GLuint spacings;

void VertexArrayObject::addBuffer( VertexBuffer& vb,  VertexBufferLayout& layout) 
{
	bind();
	vb.bind();
	unsigned int spacings = 0;
	const auto &elements = layout.getElements();
	for (unsigned int i = 0 ; i< elements.size() ; i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i); GLerrorProcessing(__LINE__, __FUNCTION__);
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (const void*)spacings); GLerrorProcessing(__LINE__, __FUNCTION__);
		std::cout << "pointer: " << i << "," << element.count << "," << element.type << "," << element.normalised << "," << layout.getStride() << "," << spacings << std::endl;
 		spacings += element.count * layout.size(element.type);
	}
}

void VertexArrayObject::bind()
{

	glBindVertexArray(m_vbo); GLerrorProcessing(__LINE__, __FUNCTION__);

}

void VertexArrayObject::unbind()
{

	glBindVertexArray(0); GLerrorProcessing(__LINE__, __FUNCTION__);

}
VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_vbo);		GLerrorProcessing(__LINE__, __FUNCTION__);
	
}

