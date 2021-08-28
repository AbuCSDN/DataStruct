//#include"heap.h"
#include"bst.h"

void main()
{
	int ar[] = { 27, 15, 19, 18, 1, 28, 34, 65, 100, 49, 25, 37 };
	int n = sizeof(ar) / sizeof(ar[0]);

	BSTree bst;
	BstInit(&bst);

	for (int i = 0; i<n; ++i)
		BstInsert(&bst, ar[i]);

	printf("min = %d\n", BstMin(bst));
	printf("max = %d\n", BstMax(bst));

	BstSortPrint(bst);
	printf("\n");

	BSTNode *p = BstFind(bst, 37);
	BstErase(&bst, p);
	/*int v = (0 - 1) / 2;
	int ar[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	int n = sizeof(ar) / sizeof(ar[0]);
	MinHeap mhp;
	HeapInit(&mhp);
	for (int i = 0; i<n; ++i)
		HeapInsert(&mhp, ar[i]);
	HeapShow(&mhp);
	HeapInsert(&mhp, 17);
	HeapShow(&mhp);
	HeapErase(&mhp);
	HeapShow(&mhp);
	HeapSort(&mhp, ar, n);
	HeapShow(&mhp);*/
	system("pause");
}