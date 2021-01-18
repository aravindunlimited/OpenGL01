#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include  "glm/gtx/quaternion.hpp"
#include "CallBack.h"

struct quart
{
	float x;
	float y;
	float z;
	float w;
};

class FirstPersonCamera : public CallBack
{
public:
	glm::vec3 cameraPos;
	glm::mat4 cameraProjection, cameraView, cameratTranView, cameraRotView, cameraYawview, cameraTranslate;
	FirstPersonCamera(glm::vec3 initPos, std::string projectionType);
	glm::mat4 getCameraProjection();
	glm::mat4 getCameraSpin();
	glm::vec3 getCameraPos();
	~FirstPersonCamera();
	glm::mat4 updateCamera(GLFWwindow* window);
private:
	float cameraSpeed = 0.0f; // adjust accordingly
	bool firstMouse = true;
	glm::mat4 spinRot, yawRot;
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront, cameraUp, cameraRight;
	float zoom = 45.0f;
	float cameraAngle = 0.0f;
	float yaw = 0.0f, pitch = -90.0f, spin = 90.0f;
	double xpos, ypos;
	float lastX = 400, lastY = 300;
	const float sensitivity = 0.1f;
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	virtual void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	virtual void processInput(GLFWwindow* window);
	std::string mprojectionType;

};

