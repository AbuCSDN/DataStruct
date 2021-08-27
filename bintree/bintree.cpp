#include"bintree.h"

void main()
{

	const char *vlr = "ABCDEFGH";
	const char *lvr = "CBEDFAGH";
	const char *lrv = "CEFDBHGA";

	BinTree bt;
	BinTreeInit(&bt);
	BinTreeCreate(&bt);

	bt = BinTreeCreate_3(vlr, lvr, strlen(vlr));

	/*const char *str = "ABC##DE##F##G#H##";
	BinTree bt;
	BinTreeInit(&bt);
	int index = 0;
	bt = BinTreeCreate_2(str, &index);*/
	//�������
	printf("VLR: ");
	BinTreeVLR_Nor(bt);
	printf("\n");
	//�������
	printf("LVR: ");
	BinTreeLVR_Nor(bt);
	printf("\n");
	//�������
	printf("LRV: ");
	BinTreeLRV_Nor(bt);
	printf("\n");

	//const char *str = "ABC##DE##F##G#H##";
	//BinTree bt;
	//BinTreeInit(&bt);
	////BinTreeCreate(&bt);
	////bt = BinTreeCreate_1();
	//int index = 0;
	//bt = BinTreeCreate_2(str, &index);
	////BinTree bt1 = BinTreeClone(bt);

	////�������
	//printf("VLR: ");
	//BinTreeVLR(bt);
	//printf("\n");
	////�������
	//printf("LVR: ");
	//BinTreeLVR(bt);
	//printf("\n");
	////�������
	//printf("LRV: ");
	//BinTreeLRV(bt);
	//printf("\n");
	////��α���
	//printf("Level: ");
	//BinTreeLevel(bt);
	//printf("\n");
	//printf("size = %d\n", Size(bt));
	//printf("height = %d\n", Height(bt));
	//char key = 'A';
	//BinTreeNode *p = BinTreeFind(bt, key);
	//BinTreeNode *pr = BinTreeParent(bt, p);

	system("pause");
}