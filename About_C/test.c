#include<stdio.h>
#include<windows.h>

#pragma warning(disable:4996);

#define DOUBLE(x) x*x

int get_max(int x, int y)
{
	int max = x > y ? x : y;
	return max;
	/*printf("��������������>");
	scanf("%d %d", &x, &y);
	if (x > y)
	{
		printf("�������нϴ����Ϊ��>");
		return x;
	}
	else if (y > x)
	{
		printf("�������нϴ����Ϊ��>");
		return y;
	}*/
}
int main()
{

	printf("%d\n", 10*DOUBLE(10+1));
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	//int num = sizeof(arr) / sizeof(arr[0]);//������Ԫ�صĸ���

	//int total = 0;
	//int i = 0;
	//for (; i < num; i++)//������ӡ
	//{
	//	printf("arr[%d]:%d\n", i, arr[i]);
	//	total = total + arr[i];//�ۼ����
	//}
	//printf("total:%d\n", total);


	/*int x = 0;
	int y = 0;
	int z = get_max(x,y);
	printf("%d\n", z);*/

	/*printf("���������ѡ��<1 or 2>");
	int select = 0;
	scanf("%d", &select);
	if (1 == select)
	{
		printf("offer\n");
	}
	else if (2 == select)
	{
		printf("����\n");
	}*/
	/*printf("\v \v \v \v \v \v \v \v \v \v \v \v \v \v \n");
	printf("\v \v \v \v \v \v \v \v \v \v \v \v \v \v \n");
	printf("\v \v \v \v \v \v \v \v \v \v \v \v \v \v \n");
	printf("\v \v \v \v \v \v \v \v \v \v \v \v \v \v \n");*/
	/*char arr1[] = "bit";
	char arr2[] = { 'b', 'i', 't' };
	char arr3[] = { 'b', 'i', 't', '\0' };

	printf("%s\n", arr1);
	printf("%s\n", arr2);
	printf("%s\n", arr3);*/

	/*int x = 0;
	int y = 0;
	printf("�������Ӧ�����ݣ�>");
	scanf("%d %d", &x, &y);
	printf("%d\n", x + y);*/
	//char c = 'A';
	//for (; c <= 'Z'; c++)
	//{
	//	printf("%c ", c);
	//}
	//printf("\n");
	system("pause");
	return 0;
}