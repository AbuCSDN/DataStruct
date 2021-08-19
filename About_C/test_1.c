#include<stdio.h>
#include<windows.h>

#pragma warning(disable:4996)


void Print(unsigned int i)
{
	if (i > 9){
		Print(i / 10);
	}
	printf("%d ", i % 10);
}

long long Mul(int _n)
{
	if (_n == 1)
	{
		return 1;
	}
	else{
		return _n * Mul(_n - 1);
	}
	
}

int Mul2(int _n)
{
	if (_n > 1)
	{
		for (int i = _n; i > 1; i--)
		{
			_n *= i;
		}
		return _n;
	}
	else{
		return 1;
	}
}

int my_strlen(char *p)
{
	if ('\0' == *p){
		return 0;
	}
	return 1 + my_strlen(p + 1);
}
int my_strlen2(char *p)
{
	int count = 0;
	while (*p != '\0')
	{
		p++, count++;
	}
	return count;
}

void reverse_string(char* arr)
{
	char *left = arr;
	char *right = arr + strlen(arr) - 1;


	while (left<right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;


		left++;
		right--;
	}
}

void Reverse_string(char * str)
{
	char *start = str;
	char *end = str + strlen(str) - 1;
	char temp = *start;
	*start = *end;
	*end = '\0';
	if (strlen(str + 1) >= 2){
		Reverse_string(str + 1);
	}
	*end = temp;
}

int DigitSum(int n)
{
	if (n <= 9){
		return n;
	}
	else{
		return n % 10 + DigitSum(n / 10);
	}
}

int Pow(int n, int k)
{
	if (k == 0)
		return 1;
	else if (k >= 1)
	{
		return n*Pow(n, k - 1);
	}
}

void BubbleSort(int *arr, int num)
{
	int i = 0;
	for (; i < num - 1; i++)
	{
		int j = 0;
		int flag = 1;
		for (; j < num - 1 - i; j++)
		{
			if (arr[j]>arr[j + 1]){
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = 0;
			}
		}
		if (1 == flag){
			break;
		}
	}
	return;
}

void Show(int arr[], int num)
{
	int i = 0;
	for (; i < num; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void Init(int arr[], int sz, int set)
{
	int i = 0;
	for (i = 0; i<sz; i++)
	{
		arr[i] = set;
	}
}


void Print1(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i<sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


void Reverse(int arr[], int sz)
{
	int left = 0;
	int right = sz - 1;


	while (left<right)
	{
		int tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;
		left++;
		right--;
	}
}

int main()
{
	int arr1[10] = { 0 };
	int arr2[10] = { 0 };
	int i = 0;


	printf("请输入10个数字:>");
	for (i = 0; i<10; i++)
	{
		scanf("%d", &arr1[i]);
	}
	printf("请输入10个数字:>");
	for (i = 0; i<10; i++)
	{
		scanf("%d", &arr2[i]);
	}
	//交换
	for (i = 0; i<10; i++)
	{
		int tmp = arr1[i];
		arr1[i] = arr2[i];
		arr2[i] = tmp;
	}

	/*int arr[] = { 1, 8, 0, 3, 5, 1, 2, 4, 6 };
	int num = sizeof(arr) / sizeof(arr[0]);
	Show(arr, num);
	BubbleSort(arr, num);
	Show(arr, num);*/

	/*int n = 2345;
	int index = DigitSum(n);
	printf("%d\n", index);*/

	/*char str[] = "abcd1234";
	Reverse_string(str);
	printf("%s\n", str);*/

	/*char *p = "asdfghj";
	int index = my_strlen2(p);
	printf("%d\n", index);*/
	/*int n = 0;
	printf("请输入你要求的阶乘：");
	scanf("%d", &n);
	int index = Mul2(n);
	printf("结果为：%d\n", index);*/
	//Print(100);

	system("pause");
	return 0;
}