#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

class Input
{
public:
	static Input* instance;
	static bool isKeyPressed(int key);
	static bool isKeyDown(int key);
	static bool isKeyReleased(int key);
	static void mousePos(double& x, double& y);

private:
	bool keysPressed[GLFW_KEY_LAST];
	bool keysReleased[GLFW_KEY_LAST];
	bool keysDown[GLFW_KEY_LAST];
	double mouseX;
	double mouseY;

public:
	Input();
	void update();
	void focus() { instance = this; };

private:
	bool keyPressed(int key);
	bool keyDown(int key);
	bool keyReleased(int key);
	~Input();
	friend void windowFocusChange(GLFWwindow* win, int focused);
	friend void windowKeyChange(GLFWwindow* win, int key, int scancode, int action, int mods);
	friend void mouseMoved(GLFWwindow* win, double x, double y);
	void setMouse(double x, double y);

};

