#include "Input.h"

Input* Input::instance;

Input::Input()
{
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		keysPressed[i] = false;
		keysDown[i] = false;
		keysReleased[i] = false;
	}
	instance = this;
}

void Input::press(int key)
{
	keysPressed[key] = true;
	keysDown[key] = true;
}
void Input::release(int key)
{
	keysReleased[key] = true;
	keysDown[key] = false;
}

void Input::repeat(int key)
{
	// std::cout << "repeat: " << key << std::endl;
	// keysPressed[key] = true;
}

void Input::update()
{

	for(int i = 0; i < GLFW_KEY_LAST; i++)
	{
		keysReleased[i] = false;
		keysPressed[i] = false;
	}

}

bool Input::keyPressed(int key)
{
	return keysPressed[key];
}

bool Input::keyDown(int key)
{
	return keysDown[key];
}

bool Input::keyReleased(int key)
{
	return keysReleased[key];
}

//STATIC FUNCTIONS
bool Input::isKeyPressed(int key){
	return Input::instance->keyPressed(key);
}

bool Input::isKeyDown(int key){
	return Input::instance->keyDown(key);
}

bool Input::isKeyReleased(int key){
	return Input::instance->keyReleased(key);
}

Input::~Input()
{
}
