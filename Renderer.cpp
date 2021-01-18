#pragma once
#include "Renderer.h"


int Renderer::initialise()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialisation failed" << std::endl;
		return 0;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	return 1;
}

void GLerrorProcessing(const int line, const std::string& func) 
{
	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		std::cout << "OpenGL error: " << result << ". function: " << func << ", Line no:" << line << " in source file " << __FILE__ << std::endl;
	// 	std::cout << "Message: " << <std:string>gluErrorString(result) << std::endl;
	}

}

void Renderer::Clear()
{

	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawStuffs( VertexArrayObject& vao,  IndexBuffer& ib,  Shader& shader) const
{
	glActiveTexture(GL_TEXTURE0); GLerrorProcessing(__LINE__, __FUNCTION__);
	vao.bind();
	ib.bind();
	//shader.use();
	
	glDrawElements(GL_TRIANGLES, ib.getIndexSize(), GL_UNSIGNED_INT, nullptr);	GLerrorProcessing(__LINE__, __FUNCTION__);

}

