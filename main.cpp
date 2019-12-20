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
		{ 0, 0, 1, 1, 1, 0, 0, 0 },//0 �յ�
		{ 0, 0, 1, 3, 1, 0, 0, 0 },//1 ǽ
		{ 0, 0, 1, 0, 1, 1, 1, 1 },//3 Ŀ�ĵ�
		{ 1, 1, 1, 4, 0, 4, 3, 1 },//4 ����
		{ 1, 3, 0, 4, 5, 1, 1, 1 },//5 ��
		{ 1, 1, 1, 1, 4, 1, 0, 0 },//6 
		{ 0, 0, 0, 1, 3, 1, 0, 0 },//7 ���Ӻ�Ŀ�ĵ��غ�
		{ 0, 0, 0, 1, 1, 1, 0, 0 } //8 �˺�Ŀ�ĵ��غ�
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

void Start()//��ʼ����
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
			int tmp = NextMap();//������Ϸ�������棬��������ѡ��
			switch (tmp)
			{
			case 1:
				PlayGame();
				return 1;
				break;//��һ��
			case 2:
				return 2;
				break;//�˳���Ϸ
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
				printf("��");
				break;
			case 3:
				SetColor(11);
				printf("��");
				break;
			case 4:
				SetColor(2);
				printf("��");
				break;
			case 5:
				SetColor(12);
				printf("��");
				break;
			case 7:
				SetColor(9);
				printf("��");   //���Ӻ�Ŀ�ĵ�
				break;
			case 8:
				SetColor(12);
				printf("��");    //�˺�Ŀ�ĵ�
				break;
			default:
				break;
			}
		}
		printf("\n");//������õײ�
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
	int r, c;       //�˵�����
	ch = _getch();   //�����<conio.h>ͷ�ļ�,ֱ�ӽ����ַ�,���ð��س�
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
		if (AllMaps[KEY][i][j] == 5 || AllMaps[KEY][i][j] == 8)  //�ж�����Ŀ�ĵ�
			break;
	}
	switch (ch)
	{
	case'w':         //��
	case'W':
	case 72:        //��ֵ
		//�˵����� AllMaps[KEY][r][c], ����һ��λ�� AllMaps[KEY][r-1][c] �Ƿ�Ϊ�յ�0��Ŀ�ĵ�3,�Ǿͽ���ֵ
		if (AllMaps[KEY][r - 1][c] == 0 || AllMaps[KEY][r - 1][c] == 3)
		{
			AllMaps[KEY][r - 1][c] += 5;    //�������ƶ�
			AllMaps[KEY][r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
		}
		else if (AllMaps[KEY][r - 1][c] == 4 || AllMaps[KEY][r - 1][c] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
		{
			if (AllMaps[KEY][r - 2][c] == 0 || AllMaps[KEY][r - 2][c] == 3)   //����ǰ�� AllMaps[KEY][r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
			{
				AllMaps[KEY][r - 2][c] += 4;       //���������ƶ�
				AllMaps[KEY][r - 1][c] += 1;       //���ƶ���ԭ����λ��
				AllMaps[KEY][r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
			}
		}
		break;

	case's':         //��
	case'S':
	case 80:
		if (AllMaps[KEY][r + 1][c] == 0 || AllMaps[KEY][r + 1][c] == 3)
		{
			AllMaps[KEY][r + 1][c] += 5;    //�������ƶ�
			AllMaps[KEY][r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
		}
		else if (AllMaps[KEY][r + 1][c] == 4 || AllMaps[KEY][r + 1][c] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
		{
			if (AllMaps[KEY][r + 2][c] == 0 || AllMaps[KEY][r + 2][c] == 3)   //����ǰ�� AllMaps[KEY][r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
			{
				AllMaps[KEY][r + 2][c] += 4;       //���������ƶ�
				AllMaps[KEY][r + 1][c] += 1;       //���ƶ���ԭ����λ��
				AllMaps[KEY][r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
			}
		}

		break;


	case'a':         //��
	case'A':
	case 75:
		if (AllMaps[KEY][r][c - 1] == 0 || AllMaps[KEY][r][c - 1] == 3)
		{
			AllMaps[KEY][r][c - 1] += 5;    //�������ƶ�
			AllMaps[KEY][r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
		}
		else if (AllMaps[KEY][r][c - 1] == 4 || AllMaps[KEY][r][c - 1] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
		{
			if (AllMaps[KEY][r][c - 2] == 0 || AllMaps[KEY][r][c - 2] == 3)   //����ǰ�� AllMaps[KEY][r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
			{
				AllMaps[KEY][r][c - 2] += 4;       //���������ƶ�
				AllMaps[KEY][r][c - 1] += 1;       //���ƶ���ԭ����λ��
				AllMaps[KEY][r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
			}
		}
		break;

	case'd':         //��
	case'D':
	case 77:
		if (AllMaps[KEY][r][c + 1] == 0 || AllMaps[KEY][r][c + 1] == 3)
		{
			AllMaps[KEY][r][c + 1] += 5;    //�������ƶ�
			AllMaps[KEY][r][c] -= 5;        //ԭλ�ñ�ؿյ�0 
		}
		else if (AllMaps[KEY][r][c + 1] == 4 || AllMaps[KEY][r][c + 1] == 7)   //��5��ǰ��������4, ������4��Ŀ�ĵ�3�غ�Ϊ7λ��
		{
			if (AllMaps[KEY][r][c + 2] == 0 || AllMaps[KEY][r][c + 2] == 3)   //����ǰ�� AllMaps[KEY][r-2][c]�Ƿ�Ϊ�յػ�Ŀ�ĵ�
			{
				AllMaps[KEY][r][c + 2] += 4;       //���������ƶ�
				AllMaps[KEY][r][c + 1] += 1;       //���ƶ���ԭ����λ��
				AllMaps[KEY][r][c] -= 5;           //ԭ�ȵ���λ�ñ�Ϊ�յ�0
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
	/*������Ϸ��������*/
	Sleep(500);  //ͣ���룬��������ִ��
	SetColor(11);
	SetCursorPosition(10, 8);
	std::cout << "��������������������������������������������";
	Sleep(30);
	SetCursorPosition(9, 9);
	std::cout << " ��              ��ϲ��                      ��";
	Sleep(30);
	SetCursorPosition(9, 10);
	std::cout << " ��                                          ��";
	Sleep(30);
	SetCursorPosition(9, 11);
	std::cout << " ��   �Ƿ�ʼ��һ�أ�                       ��";
	Sleep(30);
	SetCursorPosition(9, 12);
	std::cout << " ��                                          ��";
	Sleep(30);
	SetCursorPosition(9, 13);
	std::cout << " ��    �ţ��õ�        ���ˣ�����ѧϰ����˼  ��";
	Sleep(30);
	SetCursorPosition(9, 14);
	std::cout << " ��                                          ��";
	Sleep(30);
	SetCursorPosition(10, 15);
	std::cout << "��������������������������������������������";

	Sleep(100);
	SetCursorPosition(12, 13);
	SetBackColor();
	std::cout << "�ţ��õ�";
	SetCursorPosition(0, 31);

	/*ѡ�񲿷�*/
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
				std::cout << "�ţ��õ�";
				SetCursorPosition(20, 13);
				SetColor(11);
				std::cout << "���ˣ�����ѧϰ����˼";
				--tmp_key;
			}
			break;

		case 77://RIGHT
			if (tmp_key < 2)
			{
				SetCursorPosition(20, 13);
				SetBackColor();
				std::cout << "���ˣ�����ѧϰ����˼";
				SetCursorPosition(12, 13);
				SetColor(11);
				std::cout << "�ţ��õ�";
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
		return 1;//������һ�ŵ�ͼ
	case 2:
		return 2;//�˳���Ϸ
	default:
		return 1;
	}
}

