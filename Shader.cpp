#include "Shader.h"
#include "Renderer.h"


std::string Shader::loadShader(const std::string& filepath) 
{
	std::ifstream stream(filepath);
	std::cout << filepath << std::endl;
	std::string line;
	std::stringstream shadersrc;
	while (std::getline(stream, line))
	{
		shadersrc << line << "\n";
	}

	return(shadersrc.str());
}
unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	std::cout << source.c_str() << std::endl;
	glShaderSource(shader, 1, &src, nullptr); GLerrorProcessing(__LINE__, __FUNCTION__);
	glCompileShader(shader); GLerrorProcessing(__LINE__, __FUNCTION__);
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length); GLerrorProcessing(__LINE__, __FUNCTION__);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message); GLerrorProcessing(__LINE__, __FUNCTION__);
		std::cout << "Error compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

unsigned int Shader::CreateShader(const std::string& vertexshader, const std::string& fragmentshader)
{

	std::string vssource = loadShader(vertexshader);
	std::string fssource = loadShader(fragmentshader);
	unsigned int program = glCreateProgram(); GLerrorProcessing(__LINE__, __FUNCTION__);
	unsigned int vs = CompileShader(vssource, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fssource, GL_FRAGMENT_SHADER);
	glAttachShader(program, vs); GLerrorProcessing(__LINE__, __FUNCTION__);
	glAttachShader(program, fs); GLerrorProcessing(__LINE__, __FUNCTION__);
	glLinkProgram(program); GLerrorProcessing(__LINE__, __FUNCTION__);
	glValidateProgram(program); GLerrorProcessing(__LINE__, __FUNCTION__);
	glDeleteShader(vs); GLerrorProcessing(__LINE__, __FUNCTION__);
	glDeleteShader(fs); GLerrorProcessing(__LINE__, __FUNCTION__);
	return program;
}

Shader::Shader(const std::string& vertexshader, const std::string& fragmentshader) : m_location(0), m_shader(CreateShader(vertexshader, fragmentshader))
{
	use();
	//setColor("ufColor", 1.0f, 2.0f, 0.0f, 1.0f);
}

void Shader::use() 
{

	glUseProgram(m_shader); GLerrorProcessing(__LINE__, __FUNCTION__);

	
}

void Shader::setColor(const GLchar* uniformCode, float x, float y, float z, float alpha)  
{
	int location = getUniform("ufColor"); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform4f(location, x, y, z, alpha); GLerrorProcessing(__LINE__, __FUNCTION__);
}

int Shader::getUniform(const GLchar* uniformCode) 
{
	auto val = m_locatonMap.find(uniformCode);
	if (val != m_locatonMap.end()) return val->second;
	int location = glGetUniformLocation(m_shader, uniformCode);
	if (location == -1) {	
		GLerrorProcessing(__LINE__, __FUNCTION__);
	}
	m_locatonMap.insert({ uniformCode, location });
	return location;
}


void Shader::setUniform2f(const GLchar* uniformCode, float x, float y)  
{	
	use();
	int location = getUniform(uniformCode); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform2f(location, x, y); GLerrorProcessing(__LINE__, __FUNCTION__);
}


void Shader::setUniform3f(const GLchar* uniformCode, float x, float y, float z) 
{
	int location = getUniform(uniformCode); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform3f(location, x, y, z); GLerrorProcessing(__LINE__, __FUNCTION__);
	
}

void Shader::setUniform1f(const GLchar* uniformCode, float x) 
{
	int location = getUniform(uniformCode); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform1f(location, x); GLerrorProcessing(__LINE__, __FUNCTION__);
}

void Shader::setUniform1i(const GLchar* uniformCode, int x) 
{
	int location = getUniform(uniformCode); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform1i(location, x); GLerrorProcessing(__LINE__, __FUNCTION__);
}

void Shader::setUniform1a(const GLchar* uniformCode, int count, int* x) 
{
	int location = getUniform(uniformCode); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform1iv(location, count, x); GLerrorProcessing(__LINE__, __FUNCTION__);
}

void Shader::setUniform4f(const GLchar* uniformCode, float x, float y, float z, float alpha) 
{
	int location = getUniform(uniformCode); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform4f(location, x, y, z, alpha); GLerrorProcessing(__LINE__, __FUNCTION__);
}

void Shader::setUniformMat4(const GLchar* uniformCode, glm::mat4 matrix) 
{
	int location = getUniform(uniformCode); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniformMatrix4fv(location,1, GL_FALSE, &matrix[0][0] ); GLerrorProcessing(__LINE__, __FUNCTION__);
}

void Shader::move(float xpos, float ypos, float zpos)
{   
	
	m_location = getUniform("movepos"); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform3f(m_location, xpos, ypos,zpos); GLerrorProcessing(__LINE__, __FUNCTION__);

}



void Shader::scale(float xpos, float ypos, float zpos)
{

	m_location = glGetUniformLocation(m_shader, "scale"); GLerrorProcessing(__LINE__, __FUNCTION__);
	glUniform3f(m_location, xpos, ypos, zpos); GLerrorProcessing(__LINE__, __FUNCTION__);

}
//void Shader::rotate()

void Shader::Unuse()
{
	glUseProgram(0); GLerrorProcessing(__LINE__, __FUNCTION__);

}
Shader::~Shader()
{
	glDeleteProgram(m_shader);
}
