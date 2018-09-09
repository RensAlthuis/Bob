#pragma once
#include <iostream>
#include <GLFW\glfw3.h>

class Input
{
public:
	static Input* instance;
	static bool isKeyPressed(int key);
	static bool isKeyDown(int key);
	static bool isKeyReleased(int key);

private:
	bool keysPressed[GLFW_KEY_LAST];
	bool keysReleased[GLFW_KEY_LAST];
	bool keysDown[GLFW_KEY_LAST];

public:
	Input();

	void focus() { instance = this; };
	void press(int key);
	void release(int key);
	void repeat(int key);
	void update();

private:
	bool keyPressed(int key);
	bool keyDown(int key);
	bool keyReleased(int key);
	~Input();

};

