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

#define member_size(type, member) sizeof(((type *)0)->member)

float PI = 180.0f;
int MAX_VERTEX = 1000;

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

	Vertex position[] = {
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

	glm::mat4 perspproj = glm::perspective(45.0f, 1.33f, 0.1f, 1000.0f);
	glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -500.0f, 500.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 model_tran = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 model_rot = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 model = model_rot * model_tran;
	glm::mat4 result = perspproj * view * model;


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
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // direction vector is the diff between origin and target
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glfwSetTime(0);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		openGl->Clear();

		glfwGetCursorPos(window, &xpos, &ypos);

		second = glfwGetTime();
		//movement = 50 * second ;
		//angle = movement * PI / (50 * 3.14f);

		/*state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		 if (state == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &xpos, &ypos);
			glfwSetTime(0);
			movement = 0;

		}
		else
		{ */
			second = glfwGetTime() ;
			movement = 0.5 * 9.80 * second * second;
			//ypos -= movement;
			angle = 0.5 * 9.80 * second * PI / (200 * 3.14f);
			//if (ypos < -500) {
			//	ypos = -500;
			//	angle = 90.0f;
			//}
		//}
		
	
		//view = glm::translate(glm::mat4(1), glm::vec3(xpos, 0, 0));
		//view = glm::lookAt(glm::vec3(0, 0 , 0), glm::vec3(xpos, ypos * -1, -50), glm::vec3(0, 1, 0));

		//model_tran = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.0f)); // +movement ));
		//model_rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1, 1, 1));
		//model = model_tran * model_rot;
			xpos -= 320;
			ypos -= 240;
			zpos = 0;
			ypos *= -1;
			if (xpos > 30) { xpos = 30; }
			if (xpos < -30) { xpos = -30; }
			if (ypos > 30) { ypos = 30; }
			if (ypos < -30) { ypos = -30; }
			float temp1 = 900 - (xpos * xpos);
			if (temp1 <= 0) {
				zpos = 0;
			}
			else {
				zpos = glm::sqrt(temp1);
			}
			float temp2 = zpos;
			temp1 = (zpos * zpos) - (ypos * ypos);

			if (temp1 <= 0) {
				zpos = temp2;
			}
			else {
				zpos = glm::sqrt(temp1);
			}

			//xpos = 80 * glm::sin(xpos * 180 / (20.0f * 3.14f));
			//zpos = 80 * glm::cos(xpos * 180 / (20.0f * 3.14f));
			float camX = sin(glfwGetTime()) * 50;
			float camZ = cos(glfwGetTime()) * 50;
			//ypos = 20 *  glm::sin(ypos * 180 / (zpos * 3.14f));
			//zpos = 20 * glm::cos(ypos * 180 / (zpos * 3.14f));
		   view = glm::lookAt(glm::vec3(xpos, ypos, zpos), glm::vec3(0, 0, 0.0f), glm::vec3(0, 1, 0));
			//view = glm::lookAt(glm::vec3(camX, 0, camZ), glm::vec3(0, 0, 0.0f), glm::vec3(0, 1, 0));
			


		shader.use();

		shader.setUniform1a("u_TexCoord", 2, texCoord);
		texture.bind(ContainerTexture, 0);
		texture.bind(WallTexture, 1);

		for (int i = -10; i < 10; i++)
		{
			for (int j = -10; j < 10; j++)
			{

				model_tran = glm::translate(glm::mat4(1.0f), glm::vec3(50 * i, 50 * j, ((i + j - 20) * 50) + movement));
				model_rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(i, i/3, i%3));
				model = model_tran * model_rot;
				result = perspproj * view * model;

				shader.setUniformMat4("u_projection", result);
				openGl->drawStuffs(vao, index, shader);
			}
		}


	//	buffer.dynamicVertex((float*)&position, sizeof(position));


		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}
	delete openGl;

	glfwTerminate();
	return 0;
}
