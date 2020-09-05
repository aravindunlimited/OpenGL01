#include "GLFW/glfw3.h"
#pragma once
class CallBack
{
public:
	virtual void mouse_callback(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) = 0;
	virtual void processInput(GLFWwindow* window) = 0;

	static CallBack* callback_event;

	inline virtual void setInstance() { callback_event = this; }

	inline static void mouse_callback_orig(GLFWwindow* window, double xpos, double ypos)
	{
		if (callback_event) { callback_event->mouse_callback(window, xpos, ypos); }
	}

	inline static void scroll_callback_orig(GLFWwindow* window, double xoffset, double yoffset)
	{
		if (callback_event) { callback_event->scroll_callback(window, xoffset, yoffset); }
	}

	inline static void processInput_orig(GLFWwindow* window)
	{
		if (callback_event) { callback_event->processInput(window); }
	}

};

