#include <iostream>
#include "FirstPersonCamera.h"


FirstPersonCamera::FirstPersonCamera(glm::vec3 initPos, std::string projectionType) : cameraPos(initPos), mprojectionType(projectionType)
{
	if (mprojectionType == "PERSPECTIVE") {
		cameraProjection = glm::perspective(glm::radians(zoom), 1.33f, 0.1f, 1000.0f);
	}
	else
	{
		cameraProjection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -500.0f, 500.0f);
	}

	cameraFront = glm::normalize(cameraPos - glm::vec3(0,0,0)); // direction vector is the diff between origin and target
	cameraRight = glm::normalize(glm::cross(up, cameraFront));
	
	cameraUp = glm::cross(cameraFront, cameraRight);
	cameratTranView = glm::lookAt(glm::vec3(0,0,0), cameraFront, cameraUp);
	cameraRotView =  glm::rotate(glm::mat4(1.0f), cameraAngle, cameraFront);
	cameraView = glm::translate(glm::mat4(1), cameraPos) * cameraRotView * cameratTranView ;
	this->setInstance();
}

glm::mat4 FirstPersonCamera::getCameraProjection()
{
	return cameraProjection * cameraView;
}

glm::mat4 FirstPersonCamera::getCameraSpin()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(spin), cameraFront);
}

glm::vec3 FirstPersonCamera::getCameraPos()
{
	return cameraPos;
}

FirstPersonCamera::~FirstPersonCamera()
{
}



void FirstPersonCamera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	glm::vec3 direction;
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

}

void FirstPersonCamera::processInput(GLFWwindow * window)
{

	cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}

void FirstPersonCamera::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	zoom -= (float)yoffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}

glm::mat4 FirstPersonCamera::updateCamera(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPosCallback(window, FirstPersonCamera::mouse_callback_orig);

	glfwSetScrollCallback(window, FirstPersonCamera::scroll_callback_orig);
	processInput(window);

	cameraRight = glm::normalize(glm::cross(up, cameraFront)); 
	cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));
	cameraView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	

	if (mprojectionType == "PERSPECTIVE") {
		cameraProjection = glm::perspective(glm::radians(zoom), 1.33f, 0.1f, 1000.0f);
	}
	else
	{
		cameraProjection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -500.0f, 500.0f);
	}

	std::cout << "inCAMERA: " << cameraPos.x << ":" << cameraPos.y << ":" << cameraPos.z << std::endl;
	return(cameraProjection * cameraView );
}
