#include<stdio.h>
#include<windows.h>
#include<assert.h>

size_t my_strlen(const char *string)
{
	int length = 0;
	while (*string++ != 0)
	{
		++length;
	}
	return length;
}
char* my_strcpy(char *str1, const char *str2)
{
	char *p = str1;
	const char *q = str2;

	while (*q != '\0')
	{
		*p++ = *q++;
	}
	*p = '\0';
	return str1;
}

char *my_strcat(char *str1, const char *str2)
{
	char *p = str1;
	const char *q = str2;
	assert(str1 != NULL);
	assert(str2 != NULL);

	while (*p != '\0')
	{
		++p;
	}

	while (*p = *q)
	{
		++p;
		++q;
	}
	*p = '\0';
	return str1;
}

char *my_strcmp(const char *string1, const char *string2)
{
	if (string1 == NULL&&string2 == NULL)
	{
		return 0;
	}
	const char *str1 = string1;
	const char *str2 = string2;

	while (1)
	{

	}
}

	
int main()
{
	char str1[] = "ABCDEFGH";
	char str2[] = "EFGHABCD";

	int len = strlen(str1);
	char *double_string = (char*) malloc(len * 2 + 1);

	strcpy(double_string, str1);
	strcat(double_string, str1);
	printf("double string : %s\n", double_string);

	if (strstr(double_string, str2) != NULL)
	{
		printf("Yes!\n");
	}
	else
		printf("No!n");

	free(double_string);
	system("pause");
	return 0;
}







//#include<stdio.h>
//#include<windows.h>
//#include<stdlib.h>
//
////void qsort(void*    base, size_t   num, size_t      size, int(*comper)(const void*, const void*))
//	         //排序起始地址   有效元素个数   每一个元素的大小   比较函数
//	
//int ComperInt (const void* vx, const void* vy)
//{
//	int *x = (int*)vx;
//	int *y = (int*)vy;//强制类型转换为自己想要的类型
//
//	//vx,vy代表任意两个元素的地址，*x,*y代表任何两个元素
//	if (*x > *y){
//		return 1;
//	}
//	else if (*x < *y){
//		return -1;
//	}
//	else
//		return 0;
//}
//int ComperFloat(const void* vx, const void* vy)
//{
//	float *x = (float*)vx;
//	float *y = (float*)vy;
//	if (*x > *y){
//		return 1;
//	}
//	else if (*x < *y){
//		return -1;
//	}
//	else
//		return 0;
//}
//void show(int* arr, int num)
//{
//	for (int i = 0; i < num; ++i)
//	{
//		printf("%d ", arr[i]);
//	}
//	printf("\n");
//}
//int main()
//{
//	int arr[] = { 4, 7, 2, 9, 12, 56, 84, 39 };
//	float arr1[] = { 1.2, 3.4, 7.1, 2.6, 3.5 };
//	int num = sizeof(arr) / sizeof(arr[0]);
//	int num1 = sizeof(arr1) / sizeof(arr1[0]);
//	//show(arr, num1);
//	qsort(arr, num, sizeof(int), ComperInt);
//	qsort(arr1, num1, sizeof(float), ComperFloat);
//	//show(arr, num1);
//	system("pause");
//	return 0;
//}

//#include<stdio.h>
//#include<windows.h>
//#include<assert.h>
//#include<stdlib.h>
//
////void qsort(void*    base, size_t   num, size_t      size, int(*comper)(const void*, const void*))
//            //排序起始地址   有效元素个数   每一个元素的大小   比较函数
//
//int ComperInt(const void* vx, const void* vy)
//{
//	int *x = (int*)vx;
//	int *y = (int*)vy;//强制类型转换为自己想要的类型
//
//	//vx,vy代表任意两个元素的地址，*x,*y代表任何两个元素
//	if (*x > *y){
//		return 1;
//	}
//	else if (*x < *y){
//		return -1;
//	}
//	else
//		return 0;
//}
//int ComperFloat(const void* vx, const void* vy)
//{
//	float *x = (float*)vx;
//	float *y = (float*)vy;
//	if (*x > *y){
//		return 1;
//	}
//	else if (*x < *y){
//		return -1;
//	}
//	else
//		return 0;
//}
//void show(int* arr, int num)
//{
//	for (int i = 0; i < num; ++i)
//	{
//		printf("%d ", arr[i]);
//	}
//	printf("\n");
//}
//void swap(char *x, char *y,int size)
//{
//	for (int i = 0; i < size; ++i)
//	{
//		*(x + i) ^= *(y + i);
//		*(y + i) ^= *(x + i);
//		*(x + i) ^= *(y + i);
//	}
//}
//void My_sort(void* base, int num, int size, int(*comp)(const void*,const void* ))
//{
//	assert(base);
//	assert(comp);
//	char *_base = (char *)base;//按照字节的方式进行操作
//	//冒泡
//	int flag = 0;
//	for (int i = 0; i < num - 1; ++i)
//	{
//		for (int j = 0; j < num - 1 - i; ++j)
//		{
//			if (comp(_base + size*j,_base + size*(j + 1)) > 0)
//			{
//				flag = 1;
//				swap(_base + size*j, _base + size*(j + 1),size);
//			}
//			/*if (base[j] > base[j + 1]){    //base[j] -> *(base+j), 不合理
//				swap(base + j, base + j + 1);
//			}*/
//
//		}
//		if (flag == 0){
//			break;
//		}
//	}
//}
//int main()
//{
//	int arr[] = { 4, 7, 2, 9, 12, 56, 84, 39 };
//	//float arr1[] = { 1.2, 3.4, 7.1, 2.6, 3.5 };
//	int num = sizeof(arr) / sizeof(arr[0]);
//	//int num1 = sizeof(arr1) / sizeof(arr1[0]);
//	show(arr, num);
//	My_sort(arr, num, sizeof(int), ComperInt);
//	//My_sort(arr1, num1, sizeof(float), ComperFloat);
//	show(arr, num);
//	system("pause");
//	return 0;
//}

