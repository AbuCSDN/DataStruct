#include"ContactBook.h"

void ContactBookTest()
{
	ContactBook cb;
	ContactBookInit(&cb);

	Contact ct = { "�ŷ�","12345678901", "����",20 };
	ContactBookAdd(&cb, &ct1);
}

void Menu()
{

}

int main()
{
	Menu();
	ContactBookTest();

	return 0;
}



