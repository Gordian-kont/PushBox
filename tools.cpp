#include "tools.h"
#include <windows.h>
#include <stdio.h>   //使用sprintf()
#include<cstddef>

void SetColor(int colorID)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);//控制台颜色属性
}

void SetCursorPosition(const int x, const int y)
{
	COORD position;
	position.X = x * 2;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);//控制台光标位置
}

void SetBackColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}