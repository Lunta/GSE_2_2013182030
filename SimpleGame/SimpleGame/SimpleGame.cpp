/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Framework.h"
#include "GameTimer.h"

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.f);
	GameFramework.Render();
	glutSwapBuffers();
}

void Idle(void)
{
	if (Timer.GetTick())
	{
		GameFramework.Update(Timer.GetTimeElapsed());
		RenderScene();
	}
	else return;

	glutSetWindowTitle(GameFramework.GetTitleStr());
}

// 키보드 전반
void KeyInput(unsigned char key, int x, int y)
{
	GameFramework.Input_Key(key, x, y);
}

// 방향키, 쉬프트, 컨트롤
void SpecialKeyInput(int key, int x, int y)
{
	GameFramework.Input_SpecialKey(key, x, y);
}

// 마우스 클릭 및 클릭시 좌표
void MouseInput(int button, int state, int x, int y)
{
	GameFramework.Input_MouseButton(button, state, x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);//optional
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT); //optional
	glutCreateWindow(CLIENT_TITLE);
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

	GameFramework.Init(CLIENT_WIDTH, CLIENT_HEIGHT);

	glutMainLoop();

    return 0;
}

