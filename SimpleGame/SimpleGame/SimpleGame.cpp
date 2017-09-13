/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"

std::string title = CLIENT_TITLE;
std::string fps_string;

std::chrono::system_clock::time_point current_time;
std::chrono::duration<double> timeElapsed; // 시간이 얼마나 지났나
double fps;

void Init()
{
	current_time = std::chrono::system_clock::now();
	fps = 0.0;
}

void Update(double TimeElapsed)
{

}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	glutSwapBuffers();
}

void Idle(void)
{
	// Get tick
	timeElapsed = std::chrono::system_clock::now() - current_time;
	if (timeElapsed.count() > MAX_FPS)
	{
		current_time = std::chrono::system_clock::now();

		if (timeElapsed.count() > 0.0f)
			fps = 1.0f / timeElapsed.count();
	}
	// 최대 FPS 미만의 시간이 경과하면 진행 생략
	else return;

	Update(timeElapsed.count());
	RenderScene();

	int ifps = (int)fps;
	fps_string = title + " (FPS "+ std::to_string(ifps) + ")";
	glutSetWindowTitle(fps_string.data());
}

// 키보드 전반
void KeyInput(unsigned char key, int x, int y)
{
	std::cout << "KeyInput Key: "<< key << " X: " << x << " Y: " << y << std::endl;
}

// 방향키, 쉬프트, 컨트롤
void SpecialKeyInput(int key, int x, int y)
{
	std::cout << "Special Key Input Key: " << key << " X: " << x << " Y: " << y << std::endl;
}

// 마우스 클릭 및 클릭시 좌표
void MouseInput(int LRButton, int BottonUp, int x, int y)
{
	std::cout << "Mouse Input LRButton: " << LRButton 
		<< " BottonUp: " << BottonUp << " X: " << x << " Y: " << y << std::endl;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);//optional
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT); //optional
	glutCreateWindow(title.data());
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);
	glutMouseFunc(MouseInput);

	Init();

	glutMainLoop();

    return 0;
}

