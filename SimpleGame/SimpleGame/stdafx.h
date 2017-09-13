#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <chrono>
#include <string>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#define CLIENT_WIDTH 500
#define CLIENT_HEIGHT 500

#define CLIENT_TITLE "Game Software Engineering KPU"

#ifdef _DEBUG
#define MAX_FPS 0.0
#else
#define MAX_FPS 1.0 / 60.0
#endif

#define MOUSE_LEFT_BUTTON 0
#define MOUSE_RIGHT_BUTTON 2
#define MOUSE_BUTTON_DOWN 0
#define MOUSE_BUTTON_UP 1
#define MOUSE_WHEEL_UP 3
#define MOUSE_WHEEL_DOWN 4

#define KEY_TAB 9
#define KEY_BACKSPACE 8
#define KEY_SPACE 32
#define KEY_ENTER 13

#define SPECIAL_KEY_SHIFT 112
#define SPECIAL_KEY_CTRL 114
#define SPECIAL_KEY_ALT 116
#define SPECIAL_KEY_LEFT 100
#define SPECIAL_KEY_UP 101
#define SPECIAL_KEY_RIGHT 102
#define SPECIAL_KEY_DOWN 103