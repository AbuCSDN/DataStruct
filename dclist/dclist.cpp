#include"dclist.h"

int main()
{

	DCList list;    //DCListNode *list
	DCListInit(&list);
	DCListNode *p = NULL;

	ElemType item;
	int pos;
	bool flag;
	int select = 1;
	while (select)
	{
		printf("*********************************************\n");
		printf("*  [1] push_back           [2] push_front   *\n");
		printf("*  [3] show_list           [0] quit_system  *\n");
		printf("*  [4] pop_back            [5] pop_front    *\n");
		printf("*  [6] insert_pos          [7] insert_val   *\n");
		printf("*  [8] erase_pos           [9] erase_val    *\n");
		printf("*  [10] find               [11] length      *\n");
		printf("*  [12] capacity           [13] sort        *\n");
		printf("*  [14] reverse            [15] clear       *\n");
		printf("*  [16] front              [17] back        *\n");
		printf("*  [18] binary_find        [19] erase_all   *\n");
		printf("*********************************************\n");
		printf("��ѡ��:>");
		scanf("%d", &select);
		if (select == 0)
			break;
		switch (select)
		{
		case 1:
			printf("������Ҫ���������<��-1����>:");
			while (scanf("%d", &item), item != -1)
			{
				DCListPushBack(&list, item);
			}
			printf("β���������ݳɹ�......\n");
			break;
		case 2:
			printf("������Ҫ���������<��-1����>:");
			while (scanf("%d", &item), item != -1)
			{
				DCListPushFront(&list, item);
			}
			printf("ͷ���������ݳɹ�......\n");
			break;
		case 3:
			DCListShow(list);
			break;

			return 0;
		}


	}
}