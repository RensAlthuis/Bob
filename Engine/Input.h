#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

namespace Engine
{
class Input
{
public:
	static Input *instance;
	static bool isKeyPressed(int key);
	static bool isKeyDown(int key);
	static bool isKeyReleased(int key);
	static double mouseX();
	static double mouseY();
	static double mouseDragX();
	static double mouseDragY();
	static bool mouseDragged();

private:
	bool keysPressed[GLFW_KEY_LAST];
	bool keysReleased[GLFW_KEY_LAST];
	bool keysDown[GLFW_KEY_LAST];
	double mPosX;
	double mPosY;
	double mDragX;
	double mDragY;
	double oldMouseX;
	double oldMouseY;
	bool isMouseDragged;

public:
	Input();
	~Input();
	void update();
	void focus() { instance = this; };

private:
	bool keyPressed(int key);
	bool keyDown(int key);
	bool keyReleased(int key);

	friend void windowFocusChange(GLFWwindow *win, int focused);
	friend void windowKeyChange(GLFWwindow *win, int key, int scancode, int action, int mods);
	friend void mouseMoved(GLFWwindow *win, double x, double y);
	void setMouse(double x, double y);
};
}; // namespace Engine