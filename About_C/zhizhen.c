#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<math.h>

#pragma warning(disable:4996)

//int Print(int *arr)
//{
//	int i = 0;
//	{
//		for (; i < 10; i++)
//		{
//			*arr = &arr[i];
//			printf("%d ", arr);
//		}
//	}
//}

void CharacterStringInversion(char *s)
{
	char *head = s;
	char *end = s + strlen(s) - 1;
	while (head < end){
		char temp = *head;
		*head = *end;
		*end = temp;
		++head;
		--end;
	}
}

//“水仙花数”是指一个n位数，其各位数字的n次方之和确好等于该数本身，\
    如:153＝1 ^ 3＋5 ^ 3＋3 ^ 3，则153是一个“水仙花数”。
int Count(int x)
{
	int count = 0; 
	while (x)
	{
		x /= 10;
		count++;
	}
	return count;
}

int NarcissusCount(int a )
{
	int old_data = a;
	int count = Count(a);
	int sum = 0;
	while (a)
	{
		int temp = a % 10;
		sum += (int)pow(temp, count);
		a /= 10;
	}
	return sum == old_data;
}

//打印菱形
void show(int n)
{

}
//喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，给20元，可以多少汽水（编程实现）。
int main()
{
	int a = 20;
	int sum = 0;
	for (; a > 0; a /= 2)
	{
		sum += a;
	}
	printf("%d\n", sum);

	/*int i = 100;
	for (; i < 100000; i++)
	{
		if (NarcissusCount(i))
		{
			printf("%d ", i);
		}
	}
	printf("\n");*/

	/*int sn = 2;
	int sum = 0;
	int i = 0;
	for (; i < 5; i++)
	{
		sn = sn * 10 + 2;
		sum += sn;
	}
	printf("2+22+222+2222+22222=%d\n", sum);*/

	/*char str[] = "hello bit.";
	CharacterStringInversion(str);
	printf("%s\n", str);*/

	/*int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int i = 0;
	int *p = arr;
	for (; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", *p);
		++p;
	}*/
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//// 分析：因为数组中存储的元素类型是int类型的，因此只要给一个int的指针，\
	//依次取索引数组中的每个元素即可
	//int* p = arr;  // 数组名代表数组首元素的地址
	//for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	//{
	//	printf("%d ", *p);   // *p: 取到p所指向位置的元素
	//	++p;                 // 获取p的下一个位置
	//}

	//int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//Print(&arr);
	system("pause");
	return 0;
}