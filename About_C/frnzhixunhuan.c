#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#pragma warning(disable:4996)

//void Menu()
//{
//	printf("#######################\n");
//	printf("##1.Guess      2.Quit##\n");
//	printf("#######################\n");
//	printf("Please Select>");
//}
//void Game()
//{
//
//	printf("..........��Ϸ��ʼ..........\n");
//	srand((unsigned int)time(NULL));//ͨ��srand()����������һ��������ӣ��������������
//		                            //����ʱ��ÿʱÿ�̶��Ǳ仯�ģ�������time()ʱ�亯�����������ӡ�
//	int data = rand() % 100 + 1;//ͨ������rand()���������������Ϊ�˱��ڲ²⣬�趨���ִ�С��ΧΪ[1,100]
//	printf("����: ��������������[1,100]֮������֣���Ҫ�ܲų����������԰�!\n");
//	for (;;){
//		printf("Guess: ");
//		int x = 0;
//		scanf("%d", &x);
//
//		if (x > data){
//			printf("��´��ˣ�\n");
//		}
//		else if (x < data){
//			printf("���С�ˣ�\n");
//		}
//		else{
//			printf("��ϲ�㣬�¶��ˣ������ǣ�%d\n", data);
//			break;
//		}
//	}
//	printf("..........��Ϸ����..........\n");
//	
//
//}
//int main()
//{
//	int quit = 0;
//	while (!quit)
//	{
//		Menu();
//		int select = 0;
//		scanf("%d", &select);
//		switch (select){
//		case 1:
//			Game();
//			printf("Ҫ��Ҫ����һ�֣�\n");
//			break;
//		case 2:
//			quit = 1;
//			printf("Game End!\n");
//			break;
//		default:
//			printf("��������������������룡\n");
//			break;
//		}
//	}
//	system("pause");
//	return 0;
//}








int isOdd(_data)
{
	if (_data % 2 == 1)
	{
		return 1;
	}
	else{
		return 0;
	}
}

//int Sort(int _x, int _y, int _z)//������ʱ��
//{
//	int temp = 0;
//	if (_x < _y)
//	{
//		temp = _y;
//		_y = _x;
//		_x = temp;
//		if (_x < _z)
//		{
//			temp = _z;
//			_z = _x;
//			_z = temp;
//			if (_y < _z)
//			{
//				temp = _z;
//				_z = _y;
//				_z = temp;
//			}
//		}
//	}
//	else if (_x > _y)
//	{
//		if (_x < _z)
//		{
//			temp = _z;
//			_z = _x;
//			_z = temp;
//
//			temp = _z;
//			_z = _y;
//			_z = temp;
//
//		}
//		else if (_x > _z)
//		{
//			if (_y < _z)
//			{
//				temp = _z;
//				_z = _y;
//				_z = temp;
//			}
//			else
//			{
//				return 1;
//			}
//
//		}
//	}
//}

int isThree(int _x)
{
	return _x % 3 == 0;
}

//��ӡ����
int isRun(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return 1;
	}
	else{
		return 0;
	}
}
//���Լ��
int GreatestCommonDivisor(int x, int y)
{
	int top = x > y ? y : x;
	int i = top;
	for (; i >= 2; i--)
	{
		if ((x%i == 0) && (y%i == 0))
		{
			return i;
		}
	}
	return 1;
}
//��ӡ����
int isSu(int _x)
{
	int i = 2;
	for (; i < _x; i++)
	{
		if (_x % i == 0){
			break;
		}
		/*else{
			return 1;
		}*/
	}
	if (i < _x){
		return 0;
	}
	return 1;
}
int main()
{
	printf("��������������>");
	int x = 0;
	int y = 0;
	scanf("%d %d", &x, &y);
	int ret = GreatestCommonDivisor(x, y);
	printf("���Լ��Ϊ��>%d\n", ret);
	/*int x = 1;
	for (; x < 100; x++)
	{
		if (isSu(x) == 1){
			printf("%d ", x);
		}
	
	}*/

	/*int x = 1000;
	for (; x <= 2000; x++)
	{
		if (isRun(x) == 1){
			printf("%d ", x);
		}
	}*/

	
	/*int i = 1;
	for (; i < 100; i++)
	{
		if (isThree(i))
		printf("%d ", i);
	}
	printf("\n");*/
	/*printf("Please Enter Three Data:");  
	//�Ե�
	int a = 2;
	int b = 3;
	int c = 1;
	scanf("%d %d %d", &a, &b, &c);
	if (a<b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
	if (a<c)
	{
		int tmp = a;
		a = c;
		c = tmp;
	}
	if (b<c)
	{
		int tmp = b;
		b = c;
		c = tmp;
	}
	printf("a=%d b=%d c=%d\n", a, b, c);*/
	/*printf("Please Enter Your ��Χ��");
		int start;
		int end;
		
		scanf("%d %d", &start,&end);
		
		for (; start <= end; start++)
		{
			if (isOdd(start))
			{
				printf("%d ", start);
			}
			else{}
		}
		printf("\n");
*/
		system("pause");
		return 0;
}