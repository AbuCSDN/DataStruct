#include<stdio.h>
#include<windows.h>

#pragma warning(disable:4996)

int GreatestCommonDivisor1(int _x, int _y)
{
	int temp = _x > _y ? _y : _x;//ȡ��ƫС���Ǹ�ֵ
	for (; temp > 2; temp--){    //��ƫС��ֵ�ɴ�С��Ŀ������Լ��
		if (_x%temp == 0 && _y%temp == 0){
			return temp;
		}
	}
	return 1;      //���Լ��������1
}

int GreatestCommonDivisor2(int _x, int _y)
{
	while (1)     //շת���ֱ��_x��_y��ȣ�������ѭ��
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
			break;  //���ʱ�����ҵ�Ŀ��T������ѭ��
		}
	}
	return _x;      //���ⷵ��_x��_y
}

int GreatestCommonDivisor3(int _x, int _y)
{
	while (_x*_y != 0)//1.��֤��������Ϊ��
		              //2._x��_y���ǻ���ı���������ֱ�ӷ��ؽ�С��һ��
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
	return _x == 0 ? _y : _x;//����һ����һ����Ϊ0��������һ��ѭ�����ص�ֵ����T
}

//��д������һ�� 1�� 100 �����������г��ֶ��ٸ�����9
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

//����1 / 1 - 1 / 2 + 1 / 3 - 1 / 4 + 1 / 5 ���� + 1 / 99 - 1 / 100 ��ֵ����ӡ�����
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
	printf("��������Ҫ�ҵ�����");
	int i = 0;
	scanf("%d", &i);
	int ret = BinSearch(a, num, i);
	printf("�����±�Ϊ��%d\n", ret);
	//Show();

	/*int a[10] = { 0 };
	int i = 0;
	printf("������ʮ�����ݣ�");
	for (; i < 10; i++)
	{
		scanf("%d\n", &a[i]);
	}
	
	int max = Max(a, 10);
	printf("�������ֵΪ��%d\n", max);*/
	

	/*printf("%f\n", Cal());*/
	/*int num = CountNine();
	printf("%d\n", num);*/
	//printf("��������������");
	//int x = 0;
	//int y = 0;
	//scanf("%d %d", &x, &y);
	//int ret = GreatestCommonDivisor1(x, y);
	//printf("�������������Լ��Ϊ��%d\n", ret);
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
