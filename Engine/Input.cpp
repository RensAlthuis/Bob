#include "Input.h"

Input *Input::instance;

Input::Input() : mPosX(0),
				 mPosY(0),
				 mDragX(0),
				 mDragY(0),
				 oldMouseX(0),
				 oldMouseY(0)
{
	for (int i = 0; i < GLFW_KEY_LAST; i++)
	{
		keysPressed[i] = false;
		keysDown[i] = false;
		keysReleased[i] = false;
	}
	instance = this;
}

void Input::setMouse(double x, double y)
{
	mPosX = x;
	mPosY = y;
}

void Input::update()
{

	mDragX = mPosX - oldMouseX;
	mDragY = -(mPosY - oldMouseY);
	isMouseDragged = (int)mDragX != 0 || (int)mDragY != 0;
	for (int i = 0; i < GLFW_KEY_LAST; i++)
	{
		keysReleased[i] = false;
		keysPressed[i] = false;
	}
	oldMouseX = mPosX;
	oldMouseY = mPosY;
}

bool Input::mouseDragged()
{
	return Input::instance->isMouseDragged;
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
bool Input::isKeyPressed(int key)
{
	return Input::instance->keyPressed(key);
}

bool Input::isKeyDown(int key)
{
	return Input::instance->keyDown(key);
}

bool Input::isKeyReleased(int key)
{
	return Input::instance->keyReleased(key);
}

double Input::mouseX()
{
	return Input::instance->mPosX;
}

double Input::mouseY()
{
	return Input::instance->mPosY;
}

double Input::mouseDragX()
{
	return Input::instance->mDragX;
}
double Input::mouseDragY()
{
	return Input::instance->mDragY;
}

Input::~Input()
{
}
