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

//��ˮ�ɻ�������ָһ��nλ�������λ���ֵ�n�η�֮��ȷ�õ��ڸ�������\
    ��:153��1 ^ 3��5 ^ 3��3 ^ 3����153��һ����ˮ�ɻ�������
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

//��ӡ����
void show(int n)
{

}
//����ˮ��1ƿ��ˮ1Ԫ��2����ƿ���Ի�һƿ��ˮ����20Ԫ�����Զ�����ˮ�����ʵ�֣���
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
	//// ��������Ϊ�����д洢��Ԫ��������int���͵ģ����ֻҪ��һ��int��ָ�룬\
	//����ȡ���������е�ÿ��Ԫ�ؼ���
	//int* p = arr;  // ����������������Ԫ�صĵ�ַ
	//for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	//{
	//	printf("%d ", *p);   // *p: ȡ��p��ָ��λ�õ�Ԫ��
	//	++p;                 // ��ȡp����һ��λ��
	//}

	//int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//Print(&arr);
	system("pause");
	return 0;
}