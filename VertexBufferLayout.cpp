#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexBufferLayout::VertexBufferLayout()
{
	m_stride = 0;


}


VertexBufferLayout::~VertexBufferLayout()
{

	m_layoutElements.~vector();

}

void VertexBufferLayout::addLayout(vbLayout* layout)
{
	m_layoutElements.push_back(*layout);
}

unsigned int VertexBufferLayout::size(unsigned int type)
{
	switch (type)
	{
	case(GL_FLOAT): return 4;
	case(GL_UNSIGNED_INT): return 4;
	case(GL_UNSIGNED_BYTE): return 1;
	
	}
	return 0;
}