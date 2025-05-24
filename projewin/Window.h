#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class CWindow
{
public:
	CWindow();
	~CWindow();
	void Initialize();
	void Terminate();

	bool IsActive();
	void Update();
	void SwapBuffers() const;
	// todo: staticな関数はコンストラクタの上に書く
	static void Resize(GLFWwindow* const aWindow, const int aWidth, const int aHeight);
	static void Wheel(GLFWwindow* const aWindow, double aX, double aY);
	GLfloat Correct(const GLfloat aScale, GLfloat aMin, GLfloat aMax);
	GLfloat GetAspect() const;
	const GLfloat* GetSize() const;
	GLfloat GetScale() const;
	const GLfloat* GetLocation() const;

private:
	GLFWwindow* mWindow;
	GLfloat mAspect;
	GLfloat mSize[2]; // std::array
	GLfloat mScale;
	GLfloat mLocation[2];
};
