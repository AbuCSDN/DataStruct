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
//	printf("..........游戏开始..........\n");
//	srand((unsigned int)time(NULL));//通过srand()函数，种下一个随机种子，来产生随机数。
//		                            //根据时间每时每刻都是变化的，可以用time()时间函数来产生种子。
//	int data = rand() % 100 + 1;//通过调用rand()函数产生随机数，为了便于猜测，设定数字大小范围为[1,100]
//	printf("规则: 计算机会随机生成[1,100]之间的数字，你要能才出来，快试试吧!\n");
//	for (;;){
//		printf("Guess: ");
//		int x = 0;
//		scanf("%d", &x);
//
//		if (x > data){
//			printf("你猜大了！\n");
//		}
//		else if (x < data){
//			printf("你猜小了！\n");
//		}
//		else{
//			printf("恭喜你，猜对了，数字是：%d\n", data);
//			break;
//		}
//	}
//	printf("..........游戏结束..........\n");
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
//			printf("要不要再玩一局？\n");
//			break;
//		case 2:
//			quit = 1;
//			printf("Game End!\n");
//			break;
//		default:
//			printf("你的输入有误，请重新输入！\n");
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

//int Sort(int _x, int _y, int _z)//犯错，花时间
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

//打印闰年
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
//最大公约数
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
//打印素数
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
	printf("请输入两个数：>");
	int x = 0;
	int y = 0;
	scanf("%d %d", &x, &y);
	int ret = GreatestCommonDivisor(x, y);
	printf("最大公约数为：>%d\n", ret);
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
	//对的
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
	/*printf("Please Enter Your 范围：");
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