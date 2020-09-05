#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "CallBack.h"

class Camera : public CallBack
{
public:
	glm::vec3 cameraPos;
	glm::mat4 cameraProjection, cameraView, cameratTranView, cameraRotView;
	glm::vec3 cameraFront, cameraUp, cameraRight;
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera(glm::vec3 initPos, std::string projectionType);
	glm::mat4 getCameraProjection();
	~Camera();
	glm::mat4 updateCamera(GLFWwindow* window);
private:
	const float cameraSpeed = 0.05f; // adjust accordingly
	bool firstMouse = true;
	float zoom = 45.0f;
	float cameraAngle = 0.0f;
	float lastX = 400, lastY = 300;
	const float sensitivity = 0.1f;
	float yaw = -90.0f, pitch = -90.0f;
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	virtual void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	virtual void processInput(GLFWwindow* window);
	std::string mprojectionType;

};
