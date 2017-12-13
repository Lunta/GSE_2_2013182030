#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <list>

#include <filesystem>
using namespace std::experimental::filesystem;

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#define CLIENT_WIDTH	500
#define CLIENT_HEIGHT	800
#define CLIENT_TITLE	"Game Software Engineering KPU"

#ifdef _DEBUG
#define MAX_FPS 1.0 / 500
#else
#define MAX_FPS 1.0 / 144.0
#endif
/* Font Type
#define  GLUT_STROKE_ROMAN
#define  GLUT_STROKE_MONO_ROMAN
#define  GLUT_BITMAP_9_BY_15   
#define  GLUT_BITMAP_8_BY_13
#define  GLUT_BITMAP_TIMES_ROMAN_10
#define  GLUT_BITMAP_TIMES_ROMAN_24
#define  GLUT_BITMAP_HELVETICA_10
#define  GLUT_BITMAP_HELVETICA_12
#define  GLUT_BITMAP_HELVETICA_18
*/

#define KEY_TAB			9
#define KEY_BACKSPACE	8
#define KEY_SPACE		32
#define KEY_ENTER		13

#define SPECIAL_KEY_SHIFT	112
#define SPECIAL_KEY_CTRL	114
#define SPECIAL_KEY_ALT		116
#define SPECIAL_KEY_LEFT	100
#define SPECIAL_KEY_UP		101
#define SPECIAL_KEY_RIGHT	102
#define SPECIAL_KEY_DOWN	103

#define MOUSE_LEFT_BUTTON	0
#define MOUSE_WHEEL_BUTTON	1
#define MOUSE_RIGHT_BUTTON	2
#define MOUSE_WHEEL_UP		3
#define MOUSE_WHEEL_DOWN	4

#define MOUSE_BUTTON_UP		1
#define MOUSE_BUTTON_DOWN	0

#define LEVEL_GOD 0.0f
#define LEVEL_SKY 0.1f
#define LEVEL_GROUND 0.2f
#define LEVEL_UNDERGROUND 0.3f
#define LEVEL_PROJECTILE 0.4f
#define LEVEL_PARTICLE 0.5f
#define LEVEL_UNIT 0.6f
#define LEVEL_BUILDING 0.7f
#define LEVEL_BACKGROUND 0.8f

#define OBJECT_GAUGE_WIDTH_FACTOR	1.0f
#define OBJECT_GAUGE_HEIGHT_FACTOR	0.1f

template<typename Enum>
inline constexpr auto GetEnumValueByType(Enum enumerator) noexcept
{
	return static_cast<std::underlying_type_t<Enum>>(enumerator);
}

#include "Vector.h"
