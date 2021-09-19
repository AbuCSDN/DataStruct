#include"contact.h"

void ShowMenu()
{
	printf("#######################################\n");
	printf("#  1.Add        2.Del        3.Search #\n");
	printf("#  4.Mod        5.Show       6.Clear  #\n");
	printf("#  7.Sort                    0.Exit   #\n");
	printf("#######################################\n");
	printf("Please Select->");
}

int main()
{
	contact_t *ct = NULL; 
	InitContact(&ct);
	while (1)
	{
		int select = 0;
		ShowMenu();
		scanf("%d", &select);

		switch (select)
		{
		case 1:  //Add
			AddFriend(&ct); //添加用户是唯一一个要进行自动扩容的
			break;
		case 2:  //Del
			DelFriend(ct);
			break;
		case 3:  //Search
			SearchFriend(ct);
			break;
		case 4:  //Mod
			ModifyContact(ct);
			break;
		case 5:  //Show
			ShowContact(ct);
			break;
		case 6:  //Clear
			ClearContact(ct);
			break;
		case 7:  //Sort
			SortContact(ct);
			break;
		case 0:  //Exit
			return;
		default:  //do nothing!
			break;
		}
	}

	system("pause");
	return 0;
}