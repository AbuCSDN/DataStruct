#include<stdio.h>
#include<windows.h>

#define rs 4
#define cs 4

//��һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳�����������һ��
//����������������һ����ά�����һ���������ж��������Ƿ��и�������ʱ�临�Ӷ� O(row + col)
bool Find(int *matrix, int rows, int columns, int number)
{
	bool found = false;

	if (matrix != NULL && rows > 0 && columns > 0)
	{
		int row = 0;
		int column = columns - 1;
		while (row < rows && column >= 0)
		{
			if (matrix[row*columns+column] == number)
			{
				found = true;
				break;
			}
			else if (matrix[row*columns + column] > number)
			{
				--column;
			}
			else
				++row;
		}
	}
	return found;
}

void ReplaceBlank(char string[], int length)
{
	if (string == NULL || length <= 0)
		return;

	int originalLength = 0;
	int numberOfBlank = 0;
	int i = 0;
	while (string[i] != '\0')  //�ַ�������
	{
		++originalLength;

		if (string[i] == ' ')  //�ո����
			++numberOfBlank;

		++i;
	}

	int newLength = originalLength + numberOfBlank * 2;
	if (newLength > length)
		return;

	int indexOfOriginal = originalLength;  //ԭʼ�ַ������һ��λ��
	int indexOfNew = newLength;            //���ݺ��ַ������һ��λ��
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
	{
		if (string[indexOfOriginal] == ' ')
		{
			string[indexOfNew--] = '0';
			string[indexOfNew--] = '2';
			string[indexOfNew--] = '%';
		}
		else
		{
			string[indexOfNew--] = string[indexOfOriginal];
		}

		--indexOfOriginal;
	}
}
long long fib(unsigned n)
{
	int result[2] = { 0, 1 };
	if (n < 2)
		return result[n];

	long long fibOne = 1;
	long long fibTwo = 0;
	long long fibN = 0;
	for (unsigned int i = 2; i <= n; ++i)
	{
		fibN = fibOne + fibTwo;

		fibTwo = fibOne;
		fibOne = fibN;
	}

	return fibN;
}

int CountOne(int number)
{
	int count = 0;
	while (number)
	{
		++count;
		number = number&(number - 1);
	}
	return count;
}
void test1() {

	int a[rs * cs] = { 1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15 };

	int count = Find(a, rs, cs, 7);

	if (count)
		printf("sucess!\n");
	else
		printf("not find!\n");
}
void Func(char str_arg[2])
{
	int m = sizeof(str_arg);
	int n = strlen(str_arg);
	printf("%d\n", m);
	printf("%d\n", n);
}
char FindFirstRepeat(char *c, int n)
{
	char word[500];
	int i, j;
	word[0] = *c;
	for (i = 1; i < n; ++i)
	{
		for (j = 0; j < i; ++j)
		{
			if (*(c + i) == word[j])
			{
				printf("%c", *(c + i));
				return 1;
			}
			else
				word[i] = *(c + i);
		}
	}
}
char* replace(char *str, int more)
{
	char *ptr = str;         //�����м�֮���
	while (*str != ' ')
	{
		char *m;
		if (*str == '\0')
		{
			m = str - more - 1; //���δ�ո�
			*m = *str;
			break;
		}
		else    //������
		{
			m = str - more;     
			*m = *str;
			str++;
		}

	}

	if (*str != '/0')

	{
		char *tem = str - more;
		*tem = *str;
		str;
	}
	return str;
}
char* formatString(char *sourceString) {
	char *str = sourceString;   //�����ַ���

	while (*str == ' ')   //�׿ո�
	{
		str++;

	}
	sourceString = str;    //���׿ո�ȡ�����
	int more = 0;          //
	while (*str != '\0')
	{

		if (*str == ' ')
		{
			str++;
			while (*str == ' ')
			{
				more++;       //�м�ո���
				str++;       
				if (*str != ' ')
					break;
			}
			str = replace(str, more);
		}
		else
			str++;
	}
	return sourceString;
}


int main()
{
	char str[] = "  I   love you   ";
	printf("%s\n", str);
	char* temp = formatString(str);
	printf("%s", temp);

	/*char c[] = "qywyer23tdd";
	int n = 0;
	n = sizeof(c) / sizeof(c[0]);
	FindFirstRepeat(c, n);
	getchar();*/
	/*char str[] = "Hello";
	Func(str);*/
	/*long long index = fib(45);
	printf("%u", index);*/
	/*char arr[100] = "We are happy.";
	printf("%s\n", arr);
	ReplaceBlank(arr, 100);
	printf("%s\n", arr);
*/


	system("pause");
	return 0;
}
