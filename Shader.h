#pragma once
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <GL/glew.h>
#include "glm/glm.hpp"

class Shader
{
public:

	Shader(const std::string& vertexshader, const std::string& fragmentshader);
	void use();
	void setColor(const GLchar* uniformCode, float x, float y, float z, float alpha);
	int getUniform(const GLchar* uniformCode);
	void setUniform2f(const GLchar* uniformCode, float x, float y);
	void setUniform3f(const GLchar* uniformCode, float x, float y, float z);
	void setUniform1f(const GLchar* uniformCode, float x);
	void setUniform1i(const GLchar* uniformCode, int x);
	void setUniform1a(const GLchar* uniformCode, int count, int* x);
	void setUniform4f(const GLchar* uniformCode, float x, float y, float z, float alpha);
	void setUniformMat4(const GLchar* uniformCode, glm::mat4 matrix);
	void move(float xpos, float ypos,float zpos);
	void scale(float xpos, float ypos, float zpos);
	void Unuse();
	~Shader();
private:
	int m_location;
	unsigned int m_shader;
	static std::string loadShader(const std::string& filepath);
	static unsigned int CompileShader(const std::string& source, unsigned int type);
	static unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
	std::unordered_map<std::string, int> m_locatonMap;
};

