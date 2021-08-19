#include<stdio.h>
#include<windows.h>

#pragma warning(disable:4996)

int GreatestCommonDivisor1(int _x, int _y)
{
	int temp = _x > _y ? _y : _x;//取出偏小的那个值
	for (; temp > 2; temp--){    //从偏小的值由大到小找目标的最大公约数
		if (_x%temp == 0 && _y%temp == 0){
			return temp;
		}
	}
	return 1;      //最大公约数至少是1
}

int GreatestCommonDivisor2(int _x, int _y)
{
	while (1)     //辗转相减直到_x和_y相等；引用死循环
	{
		if (_x > _y)
		{
			_x = _x - _y;
		}
		else if (_y > _x)
		{
			_y = _y - _x;
		}
		else{
			break;  //相等时表明找到目标T，跳出循环
		}
	}
	return _x;      //任意返回_x或_y
}

int GreatestCommonDivisor3(int _x, int _y)
{
	while (_x*_y != 0)//1.保证被除数不为零
		              //2._x和_y不是互相的倍数，否则直接返回较小那一个
	{
		if (_x > _y)
		{
			_x %= _y;
		}
		else if (_x < _y)
		{
			_y %= _x;
		}
		else{
			break;
		}
	}
	return _x == 0 ? _y : _x;//最终一定有一个变为0，它的上一次循环返回的值就是T
}

//编写程序数一下 1到 100 的所有整数中出现多少个数字9
int CountNine()
{
	int count = 0;
	int i = 1;
	for (; i < 100; i++)
	{
		if (i % 10 == 9){
			count++;
		}
		if (i / 10 == 9){
			count++;
		}
	}
	return count;
}

//计算1 / 1 - 1 / 2 + 1 / 3 - 1 / 4 + 1 / 5 …… + 1 / 99 - 1 / 100 的值，打印出结果
float Cal()
{
	int flag = 1;
	float num = 0.0;
	int i = 1;
	for(; i <= 100; i++)
	{
		num += flag*(1.0f / i);
		flag = -flag;
	}
	return num;
}

int Max(int a[], int num)
{
	int i = 1;
	int max = a[0];
	for (; i < num; i++)
	{	
		if (max < a[i])
		{
			max = a[i];
		}
	}
	return max;
}

void Show()
{
	int i = 1;

	for (; i <= 9; i++)
	{
		int j = 1;
		for (; j <= i; j++)
		{
			printf("%d*%d=%d ", j, i, i*j);
		}
		printf("\n");
	}
	printf("\n");
}

int BinSearch(int a[],int num,int i)
{
	int start = 0;
	int end = num - 1;
	while (start<=end){
		int mid = (start + end) / 2;
		if (i > a[mid]){
			start = mid + 1;
		}
		else if (i < a[mid]){
			end = mid - 1;
		}
		else {
			return mid;
			break;
		}
	}

}
int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int num = sizeof(a) / sizeof(a[0]);
	printf("请输入你要找的数：");
	int i = 0;
	scanf("%d", &i);
	int ret = BinSearch(a, num, i);
	printf("他的下标为：%d\n", ret);
	//Show();

	/*int a[10] = { 0 };
	int i = 0;
	printf("请输入十个数据：");
	for (; i < 10; i++)
	{
		scanf("%d\n", &a[i]);
	}
	
	int max = Max(a, 10);
	printf("其中最大值为：%d\n", max);*/
	

	/*printf("%f\n", Cal());*/
	/*int num = CountNine();
	printf("%d\n", num);*/
	//printf("请输入两个数：");
	//int x = 0;
	//int y = 0;
	//scanf("%d %d", &x, &y);
	//int ret = GreatestCommonDivisor1(x, y);
	//printf("这两个数的最大公约数为：%d\n", ret);
	system("pause");
	return 0;
}

/*if (_x > _y)
{
int i = _y;
for (; i > 2; i--){
if (_x%i == 0 && _y%i == 0){
return i;
}
}
}
else if (_y > _x)
{
int i = _x;
for (; i > 2; i--){
if (_x%i == 0 && _y%i == 0){
return i;
}
}
}
else{
return _x;
}
return 1;*/
