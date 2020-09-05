#pragma once
#include <vector>
#include <GL/glew.h>

struct vbLayout
{
	unsigned int count;
	unsigned int type;
	unsigned char normalised;
};

class VertexBufferLayout
{
public:

	VertexBufferLayout();
	~VertexBufferLayout();
	void addLayout(vbLayout*);
	unsigned int size(unsigned int type);
	GLuint m_stride;
	std::vector<vbLayout> m_layoutElements;
	inline std::vector<vbLayout> getElements() { return m_layoutElements; }
	inline unsigned int getStride() { return m_stride; }

	template<typename T>
	void push(unsigned int)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_layoutElements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_stride += count  * size(GL_FLOAT);
	}
	
	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_layoutElements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		m_stride += count * size(GL_UNSIGNED_BYTE);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_layoutElements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_stride += count * size(GL_UNSIGNED_INT);
	}

private:

};

