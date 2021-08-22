#include"Common.h"
#include"SeqList.h"

#pragma warning(disable:4996)

int main()
{
	SeqList list;
	SeqListInit(&list);
	//SeqList list;
	//SeqListInit(&list);


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
		printf("请选择:>");
		scanf("%d", &select);
		if (0 == select){
			break;
		}
		switch (select){
		case 1:
			printf("请输入你要尾部插入的数据<以-1结束>：>");
			while (scanf("%d", &item), item != -1)
			{
				SeqListPushBack(&list, item);
			}
			printf("尾部插入数据成功......\n");
			break;
		case 2:
			printf("请输入你要头部插入的数据<以-1结束>：>");
			while (scanf("%d", &item), item != -1)
			{
				SeqListPushFront(&list, item);
			}
			printf("头部插入数据成功......\n");
			break;
		case 3:
			SeqListShow(&list);
			break;
		case 4:
			SeqListPopBack(&list);
			printf("尾部删除数据成功......\n");
			break;
		case 5:
			SeqListPopFront(&list);
			printf("头部删除数据成功......\n");
			break;
		case 6:
			printf("请输入你要插入的位置：");
			scanf("%d", &pos);
			printf("请输入你要插入的数据：");
			scanf("%d", &item);
			flag = SeqListInsertByPos(&list, pos, item);
			if (flag)
				printf("插入数据成功.......\n");
			else
				printf("插入数据失败.......\n");
			break;
		case 7:
			printf("请输入要插入的元素:>");
			scanf("%d", &item);
			SeqListSort(&list);
			SeqListInsertByVal(&list, item);
			printf("插入数据成功.......\n");
			break;
		case 8:
			printf("请输入你要删除的位置：");
			scanf("%d", &pos);
			SeqListEraseByPos(&list, pos);
			printf("删除数据成功......\n");
			break;
		case 9:
			printf("请输入你要删除的元素：");
			scanf("%d", &item);
			SeqListEraseByVal(&list, item);
			printf("删除数据成功......\n");
			break;
		case 10:
			printf("请输入你要查找的元素：");
			scanf("%d", &item);
			pos = SeqListFind(&list, item);
			if (pos == -1)
				printf("数据查找失败.\n");
			else
			printf("找到了，%d 在下标为 %d 的位置\n", item, pos);
			break;
		case 11:
			printf("Length:%d\n",SeqListLength(&list));
			break;
		case 12:
			printf("Capacity:%d\n", SeqListCapacity(&list));
			break;
		case 13:
			SeqListSort(&list);
			printf("顺序表排序成功......\n");
			break;
		case 14:
			SeqListReverse(&list);
			printf("转置完成.\n");
			break;
		case 15:
			SeqListClear(&list);
			printf("数据清除完成......\n");
			break;
		default:
			printf("命令出错,请重新输入......\n");
			break;
		}

	}

	system("pause");
	
	SeqListDestroy(&list);
	return 0;
}