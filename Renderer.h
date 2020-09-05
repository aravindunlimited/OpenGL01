#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VertexArrayObject.h"
#include "Shader.h"
#include "IndexBuffer.h"

void GLerrorProcessing(const int line, const std::string& func);

class Renderer
{
public:
	bool init_failed;
	int initialise();
	void Clear();
	void drawStuffs( VertexArrayObject& vao,  IndexBuffer& ib,  Shader& shader) const;

};

