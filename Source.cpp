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
#include "FirstPersonCamera.h"

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
	Vec3f normal;
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
		-0.5f, -0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, -1.0f,//0  front
		 0.5f, -0.5f,  -0.5f,  5.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, -1.0f,//1
		 0.5f,  0.5f,  -0.5f,  5.0f, 5.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, -1.0f,//2
		-0.5f,  0.5f,  -0.5f,  0.0f, 5.0f, 1.0f, 2.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, -1.0f,//3

		-0.5f, -0.5f,   0.5f,  0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,//20 back
		 0.5f, -0.5f,   0.5f,  5.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,//21
		 0.5f,  0.5f,   0.5f,  5.0f, 5.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,//22
		-0.5f,  0.5f,   0.5f,  0.0f, 5.0f, 0.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,//23

		-0.5f,  0.5f,   0.5f,  5.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f,//10
		-0.5f,  0.5f,  -0.5f,  0.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f,//11
		-0.5f, -0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f,//8 left
		-0.5f, -0.5f,   0.5f,  5.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f,//9
			
		 0.5f,  0.5f,   0.5f,  0.0f, 5.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,//7
		 0.5f,  0.5f,  -0.5f,  5.0f, 5.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,//6
		 0.5f, -0.5f,  -0.5f,  5.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,//5
		 0.5f, -0.5f,   0.5f,  0.0f, 0.0f, 1.0f, 2.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,//4 right
		 
		-0.5f, -0.5f,  -0.5f,  0.0f, 5.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f, 0.0f, //15
		 0.5f, -0.5f,  -0.5f,  5.0f, 5.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f, 0.0f, //14
		 0.5f, -0.5f,   0.5f,  5.0f, 0.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f, 0.0f, //13
		-0.5f, -0.5f,   0.5f,  0.0f, 0.0f, 2.0f, 2.0f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f, 0.0f, //12 bottom
			 
		-0.5f,  0.5f,  -0.5f,  0.0f, 5.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, //19
		 0.5f,  0.5f,  -0.5f,  5.0f, 5.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, //18
		 0.5f,  0.5f,   0.5f,  5.0f, 0.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, //17
		-0.5f,  0.5f,   0.5f,  0.0f, 0.0f, 1.0f, 2.0f, 2.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f //16 top
		   
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
	glm::vec3(0.0f,  5.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 5.0f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 lightSource(0.0f, 0.0f, 25.0f);
	glm::vec3 initPos = glm::vec3(0.0f, 0.0f, 0.0f);
	float angleSpeed = 0.0f;
	//Camera firstPerson(initPos, "PERSPECTIVE");
	FirstPersonCamera firstPerson(initPos, "PERSPECTIVE");
	glm::mat4 cameraProjection = firstPerson.getCameraProjection();

	glm::mat4 model_tran = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(3.0f)), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 model_rot = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 model = model_rot * model_tran;
	glm::mat4 result = cameraProjection * model;
	glm::mat4 lightTran = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)), lightSource); 
	glm::mat4 lightRot =  glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec3 lightColor = glm::vec3(1.0f);

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
	layouts.push<float>(member_size(Vertex, normal) / sizeof(float));

	VertexBufferLayout lightLayouts;
	lightLayouts.push<float>(member_size(Vertex, position) / sizeof(float));
	lightLayouts.push<float>(member_size(Vertex, texCoord) / sizeof(float));
	lightLayouts.push<float>(member_size(Vertex, fragcolor) / sizeof(float));
	lightLayouts.push<float>(member_size(Vertex, texIndex) / sizeof(float));
	lightLayouts.push<float>(member_size(Vertex, normal) / sizeof(float));

	VertexArrayObject vao, lightVAO;
	vao.bind();
	lightVAO.bind();
	VertexBuffer buffer((float*)&position, MAX_VERTEX * sizeof(Vertex));
	VertexBuffer lightBuffer((float*)& position, MAX_VERTEX * sizeof(Vertex));
	vao.addBuffer(buffer, layouts);
	lightVAO.addBuffer(lightBuffer, layouts);
	IndexBuffer index(indices, sizeof(indices));
	index.bind();

	Shader shader("res/shader/basicShader.vs", "res/shader/basicShader.fs");
	Shader lightShader("res/shader/lightShader.vs", "res/shader/lightShader.fs");


	Texture texture;
	GLuint ContainerDiffuse = texture.loadTexture("res/images/container2.png");
	GLuint ContainerSpecular = texture.loadTexture("res/images/container2_specular.png");
	GLuint WallTexture = texture.loadTexture("res/images/wall.jpg");
	GLuint LightTexture = texture.loadTexture("res/images/jail.png");

	int texCoord[3] = { 0,1, 2 };

	vao.unbind();
	lightVAO.unbind();
	buffer.unbind();
	lightBuffer.unbind();
	index.unbind();

	double xpos = 0, ypos = 0, zpos = 0, prev_ypos = 0;
	float movement,angle = 0.0f;
	int counter = 0;
	double second = 0;
	int state = 0;
	glm::vec3 newLampPos, camPos;
	texture.bind(ContainerDiffuse, 0);
	texture.bind(ContainerSpecular, 1);
	texture.bind(LightTexture, 2);

	texture.unbind();

	glfwSetTime(0);
	/* Loop until the user closes the window */

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		openGl->Clear();
		cameraProjection = firstPerson.updateCamera(window);
		camPos = firstPerson.getCameraPos();
		angleSpeed += 0.5f;
		lightSource = glm::vec3(10 * glm::sin(glm::radians(angleSpeed)), 10 * glm::cos(glm::radians(angleSpeed)), 0.0f);
		std::cout << "LightSource: " << lightSource.x << ":" << lightSource.y << ":" << lightSource.z << std::endl;
		//for (int i = 0; i < 10; i++)
		//{

		    
			model_tran = glm::translate(glm::mat4(1.0f), cubePositions[0]);
			//model_tran = glm::translate(glm::mat4(1.0f), cubePositions[0]); 
			model = model_rot * model_tran;
			result = cameraProjection * model; 
			/*  lightColor.x = sin(glfwGetTime() * 2.0f);
			lightColor.y = sin(glfwGetTime() * 0.7f);
			lightColor.z = sin(glfwGetTime() * 1.3f); */ 

			glm::vec3 diffuseColor = glm::vec3(0.5f, 0.5f, 0.5f);
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

			shader.use();

			shader.setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
			//shader.setUniform1a("u_TexCoord", 2, texCoord);
			shader.setUniform3f("ulightSource", lightSource.x, lightSource.y, lightSource.z);
			shader.setUniform3f("ufColor", diffuseColor.x, diffuseColor.y, diffuseColor.z);
			shader.setUniform3f("uCameraPos", camPos.x, camPos.y, camPos.z);
			shader.setUniform1f("shininess", 32.0f);
			shader.setUniform3f("ambience", 0.2125f, 0.1275f, 0.054f);
			shader.setUniform1i("diffuser", 0);
			texture.bind(ContainerDiffuse, 0);
			shader.setUniform1i("specularity", 1);
			texture.bind(ContainerSpecular, 1);

			shader.setUniformMat4("u_projection", result);
			shader.setUniformMat4("u_model", model);
			buffer.dynamicVertex((float*)& position, sizeof(position));
			shader.use();
			openGl->drawStuffs(vao, index, shader);
			shader.Unuse();
		//}



			//lightRot = glm::rotate(glm::mat4(1), glm::radians(angleSpeed += 0.3f), glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
			//lightRot = glm::rotate(glm::mat4(1), glm::radians(0), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));
		
		lightTran = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.4f)), lightSource); 
		result = cameraProjection * lightTran ;
		lightShader.use();
		
		lightShader.setUniform3f("light.ambience", ambientColor.x, ambientColor.y, ambientColor.z);
		lightShader.setUniform3f("light.diffuser", diffuseColor.x, diffuseColor.y, diffuseColor.z);
		lightShader.setUniform3f("light.specularity", 1.0f, 1.0f, 1.0f);
		lightShader.setUniform1a("u_TexCoord", 3, texCoord);
		texture.bind(LightTexture, 2);
		lightShader.setUniformMat4("u_projection", result);
		lightBuffer.dynamicVertex((float*)& position, sizeof(position));
		openGl->drawStuffs(lightVAO, index, lightShader);
		lightShader.Unuse();
		


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}


	delete openGl;

	glfwTerminate();
	return 0;
}
