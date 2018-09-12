#include "Input.h"

Input* Input::instance;

Input::Input():
	mouseX(0),
	mouseY(0)
{
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		keysPressed[i] = false;
		keysDown[i] = false;
		keysReleased[i] = false;
	}
	instance = this;
}

void Input::setMouse(double x, double y)
{
	mouseX = x;
	mouseY = y;
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

void Input::mousePos(double& x, double& y){
	x = Input::instance->mouseX;
	y = Input::instance->mouseY;
}

Input::~Input()
{
}
