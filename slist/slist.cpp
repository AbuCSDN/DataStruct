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
		printf("��ѡ��:>");
		scanf("%d", &select);
		if (0 == select){
			break;
		}
		switch (select){
		case 1:
			printf("������Ҫ���������<��-1����>:");
			while (scanf("%d", &item), item != -1)
			{
				SListPushBack(&list, item);
				//SeqListPushFront(&list, item);
			}
			printf("β���������ݳɹ�......\n");
			break;
		case 2:
			printf("������Ҫ���������<��-1����>:");
			while (scanf("%d", &item), item != -1)
			{
				SListPushFront(&list, item);
				//SeqListPushBack(&list, item);
			}
			printf("ͷ���������ݳɹ�......\n");
			break;
		case 3:
			SListShow(list);
			break;
		case 4:
			SListPopBack(&list);
			printf("β��ɾ�����ݳɹ�......\n");
			break;
		case 5:
			SListPopFront(&list);
			printf("ͷ��ɾ�����ݳɹ�......\n");
			break;
		case 7:
			printf("������Ҫ�����Ԫ��:>");
			scanf("%d", &item);
			SListInsertByVal(&list, item);
			printf("�������ݳɹ�.......\n");
			break;
		case 9:
			printf("������Ҫɾ����Ԫ��:>");
			scanf("%d", &item);
			SListEraseByVal(&list, item);
			printf("ɾ�����ݳɹ�.......\n");
			break;
		case 10:
			printf("��������Ҫ���ҵ�Ԫ�أ�");
			scanf("%d", &item);
			key = SListFind(list, item);
			if (key == NULL)
				printf("���ݲ���ʧ��.\n");
			else
				printf("���ݲ��ҳɹ�.\n");
			break;
		case 11:
			printf("SList Length = %d\n", SListLength(&list));
			break;
		case 13:
			SListSort(&list);
			printf("�������......\n");
			break;

		}
	}
	system("pause");

	
	return 0;
}