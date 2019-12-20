#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<iostream>
#include<Windows.h>
#include"tools.h"

#define MapNum 10
#define RPow 8
#define CPow 8

using namespace std;

int KEY = 0;
int AllMaps[MapNum][RPow][CPow] = {
	{
		{ 0, 0, 1, 1, 1, 0, 0, 0 },//0 空地
		{ 0, 0, 1, 3, 1, 0, 0, 0 },//1 墙
		{ 0, 0, 1, 0, 1, 1, 1, 1 },//3 目的地
		{ 1, 1, 1, 4, 0, 4, 3, 1 },//4 箱子
		{ 1, 3, 0, 4, 5, 1, 1, 1 },//5 人
		{ 1, 1, 1, 1, 4, 1, 0, 0 },//6 
		{ 0, 0, 0, 1, 3, 1, 0, 0 },//7 箱子和目的地重合
		{ 0, 0, 0, 1, 1, 1, 0, 0 } //8 人和目的地重合
	},
	{
		{ 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0 },
		{ 1, 3, 1, 4, 0, 1, 0, 0 },
		{ 1, 0, 1, 3, 0, 1, 1, 1 },
		{ 1, 3, 4, 0, 0, 4, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 5, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 }
	},
	{
		{ 0, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 3, 1, 1, 4, 0, 1 },
		{ 1, 0, 3, 3, 4, 0, 0, 1 },
		{ 1, 0, 0, 1, 4, 0, 0, 1 },
		{ 1, 0, 0, 5, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 3, 3, 1, 0, 0 },
		{ 0, 1, 1, 0, 3, 1, 1, 0 },
		{ 0, 1, 0, 0, 4, 3, 1, 0 },
		{ 1, 1, 0, 4, 0, 0, 1, 1 },
		{ 1, 0, 0, 1, 4, 4, 0, 1 },
		{ 1, 0, 0, 0, 0, 5, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 }
	}
};

void Start();
void DrawGame();
bool IsOver();
void Move();
int NextMap();
int PlayGame();

int main()
{
	while (1)
	{
		system("cls");
		Start();
		int tmp = PlayGame();
		if (tmp == 1)
		{
			system("cls");
			continue;
		}
		else
		{
			break;
		}
	}
	return 0;
}

void Start()//开始界面
{
	SetColor(10);
	SetCursorPosition(12, 10);
	std::cout << "Press any key to start";
	SetCursorPosition(12, 15);
	system("pause");
}

int PlayGame()
{
	while (true)
	{
		DrawGame();
		_getch();
		Move();
		if (IsOver())
		{
			DrawGame();
			Sleep(100);
			int tmp = NextMap();//绘制游戏结束界面，并返回所选项
			switch (tmp)
			{
			case 1:
				PlayGame();
				return 1;
				break;//下一关
			case 2:
				return 2;
				break;//退出游戏
			default:
				return 2;
				break;
			}
		}		
	}
	return 0;
}

void DrawGame()
{
	system("cls");
	for (int i = 0; i < RPow; ++i)
	{
		for (int j = 0; j < CPow; ++j)
		{
			switch (AllMaps[KEY][i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				SetColor(7);
				printf("■");
				break;
			case 3:
				SetColor(11);
				printf("☆");
				break;
			case 4:
				SetColor(2);
				printf("□");
				break;
			case 5:
				SetColor(12);
				printf("♀");
				break;
			case 7:
				SetColor(9);
				printf("★");   //箱子和目的地
				break;
			case 8:
				SetColor(12);
				printf("♀");    //人和目的地
				break;
			default:
				break;
			}
		}
		printf("\n");//光标下置底部
	}
}

bool IsOver()
{
	for (int i = 0; i < RPow; ++i)
	{
		for (int j = 0; j < CPow; ++j)
		{
			if (AllMaps[KEY][i][j] == 3 || AllMaps[KEY][i][j] == 8)
			{
				return false;
			}
		}
	}
	return true;
}

void Move() {
	char ch;
	int i, j;
	int r, c;       //人的坐标
	ch = _getch();   //需加载<conio.h>头文件,直接接收字符,不用按回车
	for (i = 0; i < RPow; ++i)
	{
		for (j = 0; j < CPow; ++j)
		{
			if (AllMaps[KEY][i][j] == 5 || AllMaps[KEY][i][j] == 8)
			{
				r = i;
				c = j;
			}
		}
		if (AllMaps[KEY][i][j] == 5 || AllMaps[KEY][i][j] == 8)  //判断人在目的地
			break;
	}
	switch (ch)
	{
	case'w':         //上
	case'W':
	case 72:        //键值
		//人的坐标 AllMaps[KEY][r][c], 人上一个位置 AllMaps[KEY][r-1][c] 是否为空地0或目的地3,是就交换值
		if (AllMaps[KEY][r - 1][c] == 0 || AllMaps[KEY][r - 1][c] == 3)
		{
			AllMaps[KEY][r - 1][c] += 5;    //人向上移动
			AllMaps[KEY][r][c] -= 5;        //原位置变回空地0 
		}
		else if (AllMaps[KEY][r - 1][c] == 4 || AllMaps[KEY][r - 1][c] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
		{
			if (AllMaps[KEY][r - 2][c] == 0 || AllMaps[KEY][r - 2][c] == 3)   //箱子前面 AllMaps[KEY][r-2][c]是否为空地或目的地
			{
				AllMaps[KEY][r - 2][c] += 4;       //箱子向上移动
				AllMaps[KEY][r - 1][c] += 1;       //人移动到原箱子位置
				AllMaps[KEY][r][c] -= 5;           //原先的人位置变为空地0
			}
		}
		break;

	case's':         //下
	case'S':
	case 80:
		if (AllMaps[KEY][r + 1][c] == 0 || AllMaps[KEY][r + 1][c] == 3)
		{
			AllMaps[KEY][r + 1][c] += 5;    //人向上移动
			AllMaps[KEY][r][c] -= 5;        //原位置变回空地0 
		}
		else if (AllMaps[KEY][r + 1][c] == 4 || AllMaps[KEY][r + 1][c] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
		{
			if (AllMaps[KEY][r + 2][c] == 0 || AllMaps[KEY][r + 2][c] == 3)   //箱子前面 AllMaps[KEY][r-2][c]是否为空地或目的地
			{
				AllMaps[KEY][r + 2][c] += 4;       //箱子向上移动
				AllMaps[KEY][r + 1][c] += 1;       //人移动到原箱子位置
				AllMaps[KEY][r][c] -= 5;           //原先的人位置变为空地0
			}
		}

		break;


	case'a':         //左
	case'A':
	case 75:
		if (AllMaps[KEY][r][c - 1] == 0 || AllMaps[KEY][r][c - 1] == 3)
		{
			AllMaps[KEY][r][c - 1] += 5;    //人向上移动
			AllMaps[KEY][r][c] -= 5;        //原位置变回空地0 
		}
		else if (AllMaps[KEY][r][c - 1] == 4 || AllMaps[KEY][r][c - 1] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
		{
			if (AllMaps[KEY][r][c - 2] == 0 || AllMaps[KEY][r][c - 2] == 3)   //箱子前面 AllMaps[KEY][r-2][c]是否为空地或目的地
			{
				AllMaps[KEY][r][c - 2] += 4;       //箱子向上移动
				AllMaps[KEY][r][c - 1] += 1;       //人移动到原箱子位置
				AllMaps[KEY][r][c] -= 5;           //原先的人位置变为空地0
			}
		}
		break;

	case'd':         //右
	case'D':
	case 77:
		if (AllMaps[KEY][r][c + 1] == 0 || AllMaps[KEY][r][c + 1] == 3)
		{
			AllMaps[KEY][r][c + 1] += 5;    //人向上移动
			AllMaps[KEY][r][c] -= 5;        //原位置变回空地0 
		}
		else if (AllMaps[KEY][r][c + 1] == 4 || AllMaps[KEY][r][c + 1] == 7)   //人5的前面是箱子4, 或箱子4与目的地3重合为7位置
		{
			if (AllMaps[KEY][r][c + 2] == 0 || AllMaps[KEY][r][c + 2] == 3)   //箱子前面 AllMaps[KEY][r-2][c]是否为空地或目的地
			{
				AllMaps[KEY][r][c + 2] += 4;       //箱子向上移动
				AllMaps[KEY][r][c + 1] += 1;       //人移动到原箱子位置
				AllMaps[KEY][r][c] -= 5;           //原先的人位置变为空地0
			}
		}
		break;
	case 27:
		NextMap();
		break;
	}
}

int NextMap()
{
	/*绘制游戏结束界面*/
	Sleep(500);  //停半秒，继续向下执行
	SetColor(11);
	SetCursorPosition(10, 8);
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━";
	Sleep(30);
	SetCursorPosition(9, 9);
	std::cout << " ┃              恭喜你                      ┃";
	Sleep(30);
	SetCursorPosition(9, 10);
	std::cout << " ┃                                          ┃";
	Sleep(30);
	SetCursorPosition(9, 11);
	std::cout << " ┃   是否开始下一关？                       ┃";
	Sleep(30);
	SetCursorPosition(9, 12);
	std::cout << " ┃                                          ┃";
	Sleep(30);
	SetCursorPosition(9, 13);
	std::cout << " ┃    嗯，好的        不了，还是学习有意思  ┃";
	Sleep(30);
	SetCursorPosition(9, 14);
	std::cout << " ┃                                          ┃";
	Sleep(30);
	SetCursorPosition(10, 15);
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━";

	Sleep(100);
	SetCursorPosition(12, 13);
	SetBackColor();
	std::cout << "嗯，好的";
	SetCursorPosition(0, 31);

	/*选择部分*/
	int ch;
	int tmp_key = 1;
	bool flag = false;
	while ((ch = _getch()))
	{
		switch (ch)
		{
		case 75://LEFT
			if (tmp_key > 1)
			{
				SetCursorPosition(12, 13);
				SetBackColor();
				std::cout << "嗯，好的";
				SetCursorPosition(20, 13);
				SetColor(11);
				std::cout << "不了，还是学习有意思";
				--tmp_key;
			}
			break;

		case 77://RIGHT
			if (tmp_key < 2)
			{
				SetCursorPosition(20, 13);
				SetBackColor();
				std::cout << "不了，还是学习有意思";
				SetCursorPosition(12, 13);
				SetColor(11);
				std::cout << "嗯，好的";
				++tmp_key;
			}
			break;

		case 13://Enter
			flag = true;
			break;

		default:
			break;
		}

		SetCursorPosition(0, 31);
		if (flag) {
			break;
		}
	}

	SetColor(11);
	switch (tmp_key)
	{
	case 1:
		KEY++;
		return 1;//进入下一张地图
	case 2:
		return 2;//退出游戏
	default:
		return 1;
	}
}

