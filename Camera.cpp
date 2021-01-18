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
	referenceUp = up;
	cameraRight = glm::normalize(glm::cross(referenceUp, cameraFront));
	
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

	glm::vec3 direction;
	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);
		cameraRight = cameraRightOriginal;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;
	//yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;


	cameraFront = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), glm::radians(yoffset *  -1), cameraRight) * glm::vec4(cameraFront, 0.0f)));


}

void Camera::processInput(GLFWwindow * window)
{

	cameraSpeed = 0.05f;
	immspin = 0.0f;
	immyaw = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraFront = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), glm::radians(0.1f), cameraRight) * glm::vec4(cameraFront, 0.0f)));
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraFront = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), glm::radians(-0.1f), cameraRight) * glm::vec4(cameraFront, 0.0f)));
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		immspin = 0.5f; 
		cameraFront = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), glm::radians(-0.05f), cameraRight) * glm::vec4(cameraFront, 0.0f)));
		referenceUp = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), glm::radians(immspin), cameraFront) * glm::vec4(referenceUp, 0.0f)));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		immspin = -0.5f; 
		cameraFront = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), glm::radians(-0.05f), cameraRight) * glm::vec4(cameraFront, 0.0f)));
		referenceUp = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), glm::radians(immspin), cameraFront) * glm::vec4(referenceUp, 0.0f)));
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

	if (firstMouse)
	{
		glfwGetCursorPos(window, &xpos, &ypos);
		//glfwSetCursorPosCallback(window, Camera::mouse_callback_orig);
		mouse_callback(window, xpos, ypos);

	}
	glfwSetScrollCallback(window, Camera::scroll_callback_orig);
	processInput(window);

	cameraRight = glm::normalize(glm::cross(referenceUp, cameraFront)); 
	cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));
	cameraView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	

	if (mprojectionType == "PERSPECTIVE") {
		cameraProjection = glm::perspective(glm::radians(zoom), 1.33f, 0.1f, 1000.0f);
	}
	else
	{
		cameraProjection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -500.0f, 500.0f);
	}

	return(cameraProjection * cameraView );
}
