#include"ContactBook.h"

void ContactBookTest()
{
	ContactBook cb;
	ContactBookInit(&cb);

	Contact ct = { "ÕÅ·É","12345678901", "Î÷²Æ",20 };
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



