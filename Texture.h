#pragma once
#include <string>
#include "GL/glew.h"
#include "Dependencies/include/stb_image/stb_image.h"
class Texture
{
private:
	unsigned char* m_location;
	GLuint m_TextureID;
	int m_width;
	int m_hieght;
	int m_bpp;
public:
	Texture();
	~Texture();
	void bind(GLuint v_TextureID, unsigned int slot) const;
	void unbind() const;
	GLuint loadTexture(const std::string& filepath);
};

