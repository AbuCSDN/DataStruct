#include"common.h"
#include"slist.h"

#pragma warning(disable:4996)

int main()
{

	SList list;
	SListInit(&list);

	ElemType item;
	int pos;
	SListNode *key;
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
		printf("请选择:>");
		scanf("%d", &select);
		if (0 == select){
			break;
		}
		switch (select){
		case 1:
			printf("请输入要插入的数据<以-1结束>:");
			while (scanf("%d", &item), item != -1)
			{
				SListPushBack(&list, item);
				//SeqListPushFront(&list, item);
			}
			printf("尾部插入数据成功......\n");
			break;
		case 2:
			printf("请输入要插入的数据<以-1结束>:");
			while (scanf("%d", &item), item != -1)
			{
				SListPushFront(&list, item);
				//SeqListPushBack(&list, item);
			}
			printf("头部插入数据成功......\n");
			break;
		case 3:
			SListShow(list);
			break;
		case 4:
			SListPopBack(&list);
			printf("尾部删除数据成功......\n");
			break;
		case 5:
			SListPopFront(&list);
			printf("头部删除数据成功......\n");
			break;
		case 7:
			printf("请输入要插入的元素:>");
			scanf("%d", &item);
			SListInsertByVal(&list, item);
			printf("插入数据成功.......\n");
			break;
		case 9:
			printf("请输入要删除的元素:>");
			scanf("%d", &item);
			SListEraseByVal(&list, item);
			printf("删除数据成功.......\n");
			break;
		case 10:
			printf("请输入你要查找的元素：");
			scanf("%d", &item);
			key = SListFind(list, item);
			if (key == NULL)
				printf("数据查找失败.\n");
			else
				printf("数据查找成功.\n");
			break;
		case 11:
			printf("SList Length = %d\n", SListLength(&list));
			break;
		case 13:
			SListSort(&list);
			printf("排序完成......\n");
			break;

		}
	}
	system("pause");

	
	return 0;
}