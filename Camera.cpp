#include <iostream>
#include "Camera.h"


Camera::Camera(glm::vec3 initPos, std::string projectionType) : cameraPos(initPos), mprojectionType(projectionType)
{
	if (mprojectionType == "PERSPECTIVE") {
		cameraProjection = glm::perspective(glm::radians(zoom), 1.33f, 0.1f, 1000.0f);
	}
	else
	{
		cameraProjection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -500.0f, 500.0f);
	}

	cameraFront = glm::normalize(cameraPos - glm::vec3(0,0,0)); // direction vector is the diff between origin and target
	cameraAxis = cameraFront;
	cameraRight = glm::normalize(glm::cross(up, cameraFront));
	cameraUp = glm::cross(cameraFront, cameraRight);
	cameratTranView = glm::lookAt(glm::vec3(0,0,0), cameraFront, cameraUp);
	cameraRotView =  glm::rotate(glm::mat4(1.0f), cameraAngle, cameraFront);
	cameraView = glm::translate(glm::mat4(1), cameraPos) * cameraRotView * cameratTranView ;
	this->setInstance();
}

glm::mat4 Camera::getCameraProjection()
{
	return cameraProjection * cameraView;
}

glm::mat4 Camera::getCameraSpin()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(spin), cameraFront);
}

Camera::~Camera()
{
}



void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	glm::vec3 direction;
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
	std::cout << "direction:" << cameraFront.x << ":" << cameraFront.y << cameraFront.z << std::endl;
	
}

void Camera::processInput(GLFWwindow * window)
{

	//currentFrame = glfwGetTime();
	//deltaTime = currentFrame = lastFrame;
	//lastFrame = currentFrame;
	//deltaTime = 1.0f;


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		//rotate the camera around the cameraFront direction
	{
		//cameraAngle += 1.0f;
		spin += 0.1f;
		//quarternion(0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	{
		//cameraAngle -= 1.0f;
		//quarternion(-0.1f);
		spin -= 0.1f;
	}
}

void Camera::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	zoom -= (float)yoffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}

glm::mat4 Camera::updateCamera(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwSetCursorPosCallback(window, Camera::mouse_callback_orig);

	glfwSetScrollCallback(window, Camera::scroll_callback_orig);
	cameraRight = glm::normalize(glm::cross(up, cameraFront));
	cameraUp = glm::cross(cameraFront, cameraRight);
	processInput(window);
	glm::mat4 cameraPosM = glm::translate(glm::mat4(1), cameraPos);
	glm::mat4 cameraPosMT = glm::inverse(cameraPosM);
	cameraRotView = cameraPosM * glm::rotate(glm::mat4(1), glm::radians(spin), cameraFront) * cameraPosMT;
	cameratTranView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	
	cameraView = cameratTranView;
	glm::mat4 rot = glm::translate(glm::mat4(1), cameraPos)  * glm::rotate(glm::mat4(1), glm::radians(spin), glm::vec3(0, 0, 1));
	//cameraView = glm::rotate(cameratTranView, glm::radians(spin), glm::vec3(0,0,1));
	//cameraView = cameratTranView;
	if (mprojectionType == "PERSPECTIVE") {
		cameraProjection = glm::perspective(glm::radians(zoom), 1.33f, 0.1f, 1000.0f);
	}
	else
	{
		cameraProjection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -500.0f, 500.0f);
	}

	return(cameraProjection * cameraView);
}
