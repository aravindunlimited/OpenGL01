#include "Texture.h"
#include "Renderer.h"


Texture::Texture() : m_TextureID(0), m_location(nullptr), m_width(0), m_hieght(0), m_bpp(0)
{
	
}
Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture::bind(GLuint v_TextureID, unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot); GLerrorProcessing(__LINE__, __FUNCTION__);
	glBindTexture(GL_TEXTURE_2D, v_TextureID); GLerrorProcessing(__LINE__, __FUNCTION__);
	//glActiveTexture(GL_TEXTURE0); GLerrorProcessing(__LINE__, __FUNCTION__);
	//glBindTextureUnit(GL_TEXTURE0 + slot, v_TextureID);

}

void Texture::unbind() const
{

	glBindTexture(GL_TEXTURE_2D, 0); GLerrorProcessing(__LINE__, __FUNCTION__);
}

GLuint Texture::loadTexture(const std::string& filepath) 
{
	glGenTextures(1, &m_TextureID); GLerrorProcessing(__LINE__, __FUNCTION__);
	glBindTexture(GL_TEXTURE_2D, m_TextureID); GLerrorProcessing(__LINE__, __FUNCTION__);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); GLerrorProcessing(__LINE__, __FUNCTION__); // Setting up texture parameter. 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GLerrorProcessing(__LINE__, __FUNCTION__);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); GLerrorProcessing(__LINE__, __FUNCTION__);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); GLerrorProcessing(__LINE__, __FUNCTION__);

	stbi_set_flip_vertically_on_load(1);
	m_location = stbi_load(filepath.c_str(), &m_width, &m_hieght, &m_bpp, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_hieght, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_location); GLerrorProcessing(__LINE__, __FUNCTION__);

	glGenerateMipmap(GL_TEXTURE_2D);

	if (m_location)
	{
		stbi_image_free(m_location);
	}

	glBindTexture(GL_TEXTURE_2D, 0); GLerrorProcessing(__LINE__, __FUNCTION__);

	return m_TextureID;

}