#include <iostream>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Camera.h"

#define member_size(type, member) sizeof(((type *)0)->member)

float PI = 180.0f;
int MAX_VERTEX = 1000;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float currentFrame = 0.0f;

struct Vec2f {
	float data[2];
	float x()
	{
		return data[0];
	};

	float y()
	{
		return data[1];
	};

	
};

struct Vec3f {
	float data[3];
	float x()
	{
		return data[0];
	};

	float y()
	{
		return data[1];
	};

	float z()
	{
		return data[2];
	};
};

struct Vec4f {
	float data[4];
	float x()
	{
		return data[0];
	};

	float y()
	{
		return data[1];
	};

	float z()
	{
		return data[2];
	};


	float alpha()
	{
		return data[3];
	};
};

struct Vertex
{
	Vec3f position;
	Vec2f texCoord;
	Vec4f fragcolor;
	float texIndex;
};



int main(void)
{
	GLFWwindow* window;

	Vertex oldposition[] = {
	-10.0f, -10.0f,  10.0f,  0.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//0  front
	 10.0f, -10.0f,  10.0f,  5.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//1
	 10.0f,  10.0f,  10.0f,  5.0f, 5.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//2
	-10.0f,  10.0f,  10.0f,  0.0f, 5.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//3

	 10.0f, -10.0f, -10.0f,  0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//4 right
	 10.0f, -10.0f,  10.0f,  5.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//5
	 10.0f,  10.0f,  10.0f,  5.0f, 5.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//6
	 10.0f,  10.0f, -10.0f,  0.0f, 5.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//7

	-10.0f, -10.0f,  10.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//8 left
	-10.0f, -10.0f, -10.0f,  5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//9
	-10.0f,  10.0f, -10.0f,  5.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//10
	-10.0f,  10.0f,  10.0f,  0.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//11

	-10.0f, -10.0f, -10.0f,  0.0f, 0.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//12 bottom
	 10.0f, -10.0f, -10.0f,  5.0f, 0.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//13
	 10.0f, -10.0f,  10.0f,  5.0f, 5.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//14
	-10.0f, -10.0f,  10.0f,  0.0f, 5.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//15

	-10.0f,  10.0f, -10.0f,  0.0f, 0.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //16 top
	 10.0f,  10.0f, -10.0f,  5.0f, 0.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //17
	 10.0f,  10.0f,  10.0f,  5.0f, 5.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //18
	-10.0f,  10.0f,  10.0f,  0.0f, 5.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //19

	-10.0f, -10.0f, -10.0f,  0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f,//20 back
	 10.0f, -10.0f, -10.0f,  5.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, //21
	 10.0f,  10.0f, -10.0f,  5.0f, 5.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, //22
	-10.0f,  10.0f, -10.0f,  0.0f, 5.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f//23
	};

	Vertex position[] = {
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//0  front
		 0.5f, -0.5f,  0.5f,  5.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//1
		 0.5f,  0.5f,  0.5f,  5.0f, 5.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//2
		-0.5f,  0.5f,  0.5f,  0.0f, 5.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f,//3
		   
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//4 right
		 0.5f, -0.5f,  0.5f,  5.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//5
		 0.5f,  0.5f,  0.5f,  5.0f, 5.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//6
		 0.5f,  0.5f, -0.5f,  0.0f, 5.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f,//7
		  
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//8 left
		-0.5f, -0.5f, -0.5f,  5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//9
		-0.5f,  0.5f, -0.5f,  5.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//10
		-0.5f,  0.5f,  0.5f,  0.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f,//11
		  
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//12 bottom
		 0.5f, -0.5f, -0.5f,  5.0f, 0.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//13
		 0.5f, -0.5f,  0.5f,  5.0f, 5.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//14
		-0.5f, -0.5f,  0.5f,  0.0f, 5.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f,//15
			 
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //16 top
		 0.5f,  0.5f, -0.5f,  5.0f, 0.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //17
		 0.5f,  0.5f,  0.5f,  5.0f, 5.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //18
		-0.5f,  0.5f,  0.5f,  0.0f, 5.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, //19
		   
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f,//20 back
		 0.5f, -0.5f, -0.5f,  5.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, //21
		 0.5f,  0.5f, -0.5f,  5.0f, 5.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, //22
		-0.5f,  0.5f, -0.5f,  0.0f, 5.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f//23
	};


	float increment = 0.0f;
	unsigned int indices[] = {
		0 , 1 , 2,
		2, 3 , 0,
		4, 5 , 6,
		6 , 7 , 4, 
		8 , 9 , 10,
		10, 11, 8,
		12 , 13 , 14,
		14, 15 , 12,
		16, 17, 18, 
		18, 19, 16,
		20 , 21, 22,
		22,  23,  20


	};
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 initPos = glm::vec3(0.0f, 0.0f, 0.0f);
	Camera thirdPerson(initPos, "PERSPECTIVE");
	glm::mat4 cameraProjection = thirdPerson.getCameraProjection();

	glm::mat4 model_tran = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 model_rot = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 model = model_rot * model_tran;
	glm::mat4 result = cameraProjection * model;


	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "GLFW initialisation failed" << std::endl;
		return -1;
	}

	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	Renderer* openGl = new Renderer();

	if (!openGl->initialise())
	{
		std::cout << "Error in Renderer" << std::endl;
	}



	VertexBufferLayout layouts;
	layouts.push<float>(member_size(Vertex, position) /sizeof(float));
	layouts.push<float>(member_size(Vertex, texCoord) / sizeof(float));
	layouts.push<float>(member_size(Vertex, fragcolor) / sizeof(float));
	layouts.push<float>(member_size(Vertex, texIndex) / sizeof(float));

	VertexArrayObject vao;
	vao.bind();
	VertexBuffer buffer((float*)&position, MAX_VERTEX * sizeof(Vertex));
	vao.addBuffer(buffer, layouts);
	IndexBuffer index(indices, sizeof(indices));
	index.bind();

	Shader shader("res/shader/basicShader.vs", "res/shader/basicShader.fs");


	Texture texture;
	GLuint ContainerTexture = texture.loadTexture("res/images/wall.jpg");
	GLuint WallTexture = texture.loadTexture("res/images/wall.jpg");

	int texCoord[2] = { 0,1 };
	shader.use();
	shader.setUniformMat4("u_projection", result);
	
	//shader.setUniform4f("ufColor", 1.0f, 0.0f, 0.0f, 1.0f);

	shader.Unuse();
	vao.unbind();
	buffer.unbind();
	index.unbind();
	texture.unbind();

	double xpos = 0, ypos = 0, zpos = 0, prev_ypos = 0;
	float movement,angle = 0.0f;
	int counter = 0;
	double second = 0;
	int state = 0;

	glfwSetTime(0);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		openGl->Clear();
		cameraProjection = thirdPerson.updateCamera(window);
		shader.use();

		shader.setUniform1a("u_TexCoord", 2, texCoord);
		texture.bind(ContainerTexture, 0);
		texture.bind(WallTexture, 1);

		for (int i = 0; i < 10; i++)
		{
			model_tran = glm::translate(glm::mat4(1.0f), cubePositions[i]); 
		    model = model_rot * model_tran;
			result = cameraProjection * model;
			shader.setUniformMat4("u_projection", result);
			buffer.dynamicVertex((float*)& position, sizeof(position));

			openGl->drawStuffs(vao, index, shader);
		}
  

		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}
	delete openGl;

	glfwTerminate();
	return 0;
}
