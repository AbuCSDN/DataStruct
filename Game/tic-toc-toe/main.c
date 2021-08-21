#include"chess.h"
void Menu()
{
	printf("##############################\n");
	printf("##  欢迎来到我的三子棋世界  ##\n");
	printf("##############################\n");
	printf("##  1.Play          2.Exit  ##\n");
	printf("##############################\n");
	printf("Please Enter Select:>\n");
}

int main()
{
	int quit = 0;
	while (!quit){
		int select = 0;
		Menu();
		scanf("%d", &select);

		switch (select){
		case 1:
			Game();
			break;
		case 2:
			quit = 1;
			break;
		default:
			printf("Enter Error!\n");
			break;
		}
	}


	system("pause");
	return 0;
}