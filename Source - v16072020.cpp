#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
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


float PI = 180.0f;

int main(void)
{
	GLFWwindow* window;

	float position[] = {
		-50.0f, -50.0f, 100.0f,  0.0f, 0.0f,  //0
		 50.0f, -50.0f, 100.0f,  5.0f, 0.0f,  //1
		 50.0f,  50.0f, 100.0f,  5.0f, 5.0f,  //2
		-50.0f,  50.0f, 100.0f,  0.0f, 5.0f,  //3
		-50.0f, -50.0f, -100.0f, 0.0f, 0.0f,  //4
	   	 50.0f, -50.0f, -100.0f, 5.0f, 0.0f,  //5
		 50.0f,  50.0f, -100.0f, 5.0f, 5.0f,  //6
		-50.0f,  50.0f, -100.0f, 0.0f, 5.0f  //7
	};


	float increment = 0.0f;
	unsigned int indices[] = {
		0 , 1 , 2,
		2, 3 , 0,
		1, 5, 6,
		6, 2, 1,
		5 ,4 , 6,
		4 , 7 , 6,
		4, 0 ,  7,
		0, 3 , 7,
		1, 5 , 4,
		4 , 0 , 1,
		2,  6 ,7,
		7, 3 , 2

	};

	glm::mat4 perspproj = glm::perspective((PI / 4), 1.33f, 0.1f, -500.0f);
	glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -500.0f, 500.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 model_tran = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -400.0f));
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
	layouts.push<float>(3);
	layouts.push<float>(2);

	VertexArrayObject vao;
	vao.bind();
	VertexBuffer buffer(position, 8 * 5 * sizeof(float));
	vao.addBuffer(buffer, layouts);
	IndexBuffer index(indices, 36);
	index.bind();

	Shader shader("res/shader/basicShader.vs", "res/shader/basicShader.fs");
	Texture ghost("res/images/container.jpg");
	ghost.bind(0);

	shader.use();
	shader.setUniform1i("u_TexCoord", 0);
	shader.setUniformMat4("u_projection", result);
	
	//shader.setUniform4f("ufColor", 1.0f, 0.0f, 0.0f, 1.0f);

	//shader.Unuse();
	vao.unbind();
	buffer.unbind();
	index.unbind();

	double xpos = 0, ypos = 0;
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

		glfwGetCursorPos(window, &xpos, &ypos);

		//state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		/* if (state == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &xpos, &ypos);
			glfwSetTime(0);
			movement = 0;

		}
		else
		{
			second = glfwGetTime() ;
			movement = 0.5 * 9.80 * second * second;
			ypos -= movement;
			angle = movement * PI / (50 * 3.14f);
			if (ypos < -500) {
				ypos = -500;
				angle = 90.0f;
			}
		}
		*/
	
		std::cout << "x = " << xpos << "y = " << 480 - ypos << std::endl;

		view = glm::translate(glm::mat4(1), glm::vec3(glm::vec2((xpos + 320) * -1 ,(ypos - 240) ), 0));

		for (int i = -10; i < 10; i++)
		{
			model_tran = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f * i / 2, 200.0f * (i % 2), -400.0f));
			model = model_tran * model_rot;
			result = perspproj * view * model;

			shader.use();
			shader.setUniformMat4("u_projection", result);
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
