#ifndef _BINTREE_H_
#define _BINTREE_H_

#include"common.h"

///////////////////////////////////////////////////////////////////////////////////

struct BinTreeNode;
typedef BinTreeNode* LinkQueueElemType;

typedef struct LinkQueueNode
{
	LinkQueueElemType data;
	struct LinkQueueNode *link;
}LinkQueueNode;

typedef struct LinkQueue
{
	LinkQueueNode *head; // 队头指针
	LinkQueueNode *tail; // 队尾指针
}LinkQueue;

void LinkQueueInit(LinkQueue *pq);
void LinkQueueEn(LinkQueue *pq, LinkQueueElemType x);
void LinkQueueDe(LinkQueue *pq);
LinkQueueElemType LinkQueueFront(LinkQueue *pq);
int LinkQueueSize(LinkQueue *pq);
bool LinkQueueEmpty(LinkQueue *pq);
void LinkQueueDestroy(LinkQueue *pq);
/////////////////////////////////////////////////////
void LinkQueueInit(LinkQueue *pq)
{
	assert(pq != NULL);
	pq->head = pq->tail = NULL;
}

void LinkQueueEn(LinkQueue *pq, LinkQueueElemType x)
{
	assert(pq != NULL);
	LinkQueueNode *node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	assert(node != NULL);
	node->data = x;
	node->link = NULL;
	if (pq->head == NULL)
		pq->head = pq->tail = node;
	else
	{
		pq->tail->link = node;
		pq->tail = node;
	}
}
void LinkQueueDe(LinkQueue *pq)
{
	assert(pq != NULL);
	if (pq->head != NULL)
	{
		LinkQueueNode *p = pq->head;
		if (pq->head == pq->tail)
			pq->head = pq->tail = NULL;
		else
			pq->head = p->link;
		free(p);
	}
}
LinkQueueElemType LinkQueueFront(LinkQueue *pq)
{
	assert(pq != NULL);
	assert(pq->head != NULL);
	return pq->head->data;  //return pq->tail->data
}
int LinkQueueSize(LinkQueue *pq)
{
	assert(pq != NULL);
	int size = 0;
	LinkQueueNode *p = pq->head;
	while (p != NULL)
	{
		size++;
		p = p->link;
	}
	return size;
}
bool LinkQueueEmpty(LinkQueue *pq)
{
	assert(pq != NULL);
	return pq->head == NULL;
}

void LinkQueueDestroy(LinkQueue *pq)
{
	assert(pq != NULL);
	LinkQueueNode *p = pq->head;
	while (p != NULL)
	{
		pq->head = p->link;
		free(p);
		p = pq->head;
	}
}



///////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
//链栈
typedef BinTreeNode* LinkSstackElemType;
typedef struct LinkStackNode
{
	LinkSstackElemType data;
	struct LinkStackNode *link;
}LinkStackNode;

typedef LinkStackNode* LinkStack;
void LinkStackInit(LinkStack *pst);
void LinkStackPush(LinkStack *pst, LinkSstackElemType x);
void LinkStackPop(LinkStack *pst);
LinkSstackElemType LinkStackTop(LinkStack *pst);
void LinkStackShow(LinkStack *pst);
int LinkStackSize(LinkStack *pst);
void LinkStackDestroy(LinkStack *pst);
bool LinkStackEmpty(LinkStack *pst);
/////////////////////////////////////////////////////

void LinkStackInit(LinkStack *pst)
{
	assert(pst != NULL);
	*pst = NULL;
}

void LinkStackPush(LinkStack *pst, LinkSstackElemType x)
{
	assert(pst != NULL);
	LinkStackNode *node = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	assert(node != NULL);
	node->data = x;

	node->link = *pst;
	*pst = node;
}
void LinkStackPop(LinkStack *pst)
{
	assert(pst != NULL);
	if (*pst != NULL)
	{
		LinkStackNode *p = *pst;
		*pst = p->link;
		free(p);
	}
}
LinkSstackElemType LinkStackTop(LinkStack *pst)
{
	assert(pst != NULL && *pst != NULL);
	return (*pst)->data;
}
void LinkStackShow(LinkStack *pst)
{
	assert(pst != NULL);
	LinkStackNode *p = *pst;
	while (p != NULL)
	{
		printf("| %d |\n", p->data);
		p = p->link;
	}
	printf(" --  \n");
}
int LinkStackSize(LinkStack *pst)
{
	assert(pst != NULL);
	int size = 0;
	LinkStackNode *p = *pst;
	while (p != NULL)
	{
		size++;
		p = p->link;
	}
	return size;
}

void LinkStackDestroy(LinkStack *pst)
{
	assert(pst != NULL);
	LinkStackNode *p = *pst;
	while (p != NULL)
	{
		*pst = p->link;
		free(p);
		p = *pst;
	}
}

bool LinkStackEmpty(LinkStack *pst)
{
	assert(pst != NULL);
	return *pst == NULL;
}

///////////////////////////////////////////////////////////////////////////////////

typedef char BinTreeElemType;
typedef struct BinTreeNode
{
	BinTreeElemType data;
	struct BinTreeNode *leftChild;
	struct BinTreeNode *rightChild;
}BinTreeNode;
typedef BinTreeNode* BinTree;
//二叉树的创建
void BinTreeInit(BinTree *t);
void BinTreeCreate(BinTree *t);
BinTree BinTreeCreate_1();
BinTree BinTreeCreate_2(const char *s, int *i);
BinTree BinTreeCreate_3(const char *vlr, const char *lvr, int n);
BinTree BinTreeCreate_4(const char *lvr, const char *lrv, int n);

//二叉树的遍历
void BinTreeVLR(BinTree t);
void BinTreeLVR(BinTree t);
void BinTreeLRV(BinTree t);
void BinTreeLevel(BinTree t);

//二叉树的非递归遍历
void BinTreeVLR_Nor(BinTree t);
void BinTreeLVR_Nor(BinTree t);
void BinTreeLRV_Nor(BinTree t);

//二叉树的算法
int Size(BinTree t);
int Height(BinTree t);
BinTreeNode* Left(BinTreeNode *p);
BinTreeNode* Right(BinTreeNode *p);
BinTreeNode* BinTreeFind(BinTree t, BinTreeElemType key);
BinTreeNode* BinTreeParent(BinTree t, BinTreeNode *p);
BinTreeNode* BinTreeCopy(BinTree t);
BinTreeNode* BinTreeClone(BinTree t);
bool         Equal(BinTree t1, BinTree t2);
////////////////////////////////////////////////////////////////////

void BinTreeInit(BinTree *t)  //BinTreeNode **t
{
	*t = NULL;               //初始化根节点为空
}
void BinTreeCreate(BinTree *t)  //创建二叉树
{
	assert(t != NULL);
	BinTreeElemType item;      //申请二叉树节点
	scanf("%c", &item);
	if (item == '#')           
		*t = NULL;
	else
	{
		*t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(*t != NULL);
		(*t)->data = item;
		BinTreeCreate(&(*t)->leftChild);
		BinTreeCreate(&(*t)->rightChild);
	}
}
BinTree BinTreeCreate_1()
{
	BinTreeElemType item;
	scanf("%c", &item);
	if (item == '#')
		return NULL;
	else
	{
		BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data = item;
		t->leftChild = BinTreeCreate_1();
		t->rightChild = BinTreeCreate_1();
		return t;
	}
}
BinTree BinTreeCreate_2(const char *s, int *i)
{
	assert(s != NULL);
	if (s[*i] == '\0' || s[*i] == '#')
		return NULL;
	else
	{
		BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data = s[*i];
		(*i)++;
		t->leftChild = BinTreeCreate_2(s, i);
		(*i)++;
		t->rightChild = BinTreeCreate_2(s, i);
		return t;
	}
}
//BinTree BinTreeCreate_3(const char *vlr, const char *lvr, int n)
//{
//	if (n == 0)
//		return NULL;
//	int k = 0;
//	while (vlr[0] != lvr[k])  //在中序里找到根节点位置
//		k++;
//
//	BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
//	t->data = lvr[k];//vlr[0]
//	t->leftChild = BinTreeCreate_3(vlr+1, lvr, k);
//	t->rightChild = BinTreeCreate_3(vlr+k+1, lvr+k+1, n-k-1);
//	return t;
//}
BinTree BinTreeCreate_3(const char *vlr, const char *lvr, int n)
{
	if (n == 0)
		return NULL;
	int k = 0;
	while (vlr[0] != lvr[k])  //在中序里找到根节点位置
		k++;

	BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	t->data = lvr[k];//vlr[0]
	t->leftChild = BinTreeCreate_3(vlr + 1, lvr, k);
	t->rightChild = BinTreeCreate_3(vlr + k + 1, lvr + k + 1, n - k - 1);
	return t;
}

void BinTreeVLR(BinTree t)  //先序遍历,递归
{
	if (t != NULL)
	{
		printf("%c", t->data);
		BinTreeVLR(t->leftChild);
		BinTreeVLR(t->rightChild);
	}
}
void BinTreeLVR(BinTree t)  //中序遍历,递归
{
	if (t != NULL)
	{
		BinTreeVLR(t->leftChild);
		printf("%c", t->data);
		BinTreeVLR(t->rightChild);
	}
}
void BinTreeLRV(BinTree t)  //后序遍历,递归
{
	if (t != NULL)
	{
		BinTreeVLR(t->leftChild);
		BinTreeVLR(t->rightChild);
		printf("%c", t->data);
	}
}
void BinTreeVLR_Nor(BinTree t)
{
	if (t != NULL)
	{
		LinkStack st;
		LinkStackInit(&st);

		LinkStackPush(&st, t);
		while (!LinkStackEmpty(&st))
		{
			BinTreeNode *p = LinkStackTop(&st);
			LinkStackPop(&st);
			printf("%c ", p->data);
			if (p->rightChild != NULL)
				LinkStackPush(&st, p->rightChild);
			if (p->leftChild != NULL)
				LinkStackPush(&st, p->leftChild);
		}
	}
}
void BinTreeLVR_Nor(BinTree t)
{
	if (t != NULL)
	{
		LinkStack st;
		LinkStackInit(&st);

		do{
			while (t != NULL)
			{
				LinkStackPush(&st, t);
				t = t->leftChild;
			}

			BinTreeNode *p = LinkStackTop(&st);
			LinkStackPop(&st);
			printf("%c ", p->data);
			if (p->rightChild != NULL)
				t = p->rightChild;

		} while (!LinkStackEmpty(&st) || t != NULL);
	}
}
void BinTreeLRV_Nor(BinTree t)
{
	if (t != NULL)
	{
		LinkStack st;
		LinkStackInit(&st);

		BinTreeNode *pre = NULL;
		do{
			while (t != NULL)
			{
				LinkStackPush(&st, t);
				t = t->leftChild;
			}

			BinTreeNode *p = LinkStackTop(&st);
			if (p->rightChild == NULL || p->rightChild == pre)
			{
				LinkStackPop(&st);
				printf("%c ", p->data);
				pre = p;
			}
			else
				t = p->rightChild;
		} while (!LinkStackEmpty(&st));
	}
}

void BinTreeLevel(BinTree t)
{
	if (t != NULL)
	{
		LinkQueue Q;  //申请一个队列
		LinkQueueInit(&Q);  //初始化队列

		LinkQueueEn(&Q, t);  //根节点入队
		while (!LinkQueueEmpty(&Q))      //一层一层入队出队
		{
			BinTreeNode* p = LinkQueueFront(&Q);
			LinkQueueDe(&Q);
			printf("%c", p->data);
			if (p->leftChild != NULL)
				LinkQueueEn(&Q, p->leftChild);
			if (p->rightChild != NULL)
				LinkQueueEn(&Q, p->rightChild);
		}
		LinkQueueDestroy(&Q);
	}
}
int Size(BinTree t)
{
	if (t == NULL)
		return 0;
	else
		return Size(t->leftChild) + Size(t->rightChild) + 1;
}
int Height(BinTree t)
{
	if (t == NULL)
		return 0;
	else
	{
		int left_h = Height(t->leftChild);
		int right_h = Height(t->rightChild);
		return (left_h > right_h ? left_h : right_h) + 1;
	}
}
BinTreeNode* Left(BinTreeNode *p)
{
	assert(p != NULL);
	return p->leftChild;
}
BinTreeNode* Right(BinTreeNode *p)
{
	assert(p != NULL);
	return p->rightChild;
}
BinTreeNode* BinTreeFind(BinTree t, BinTreeElemType key)
{
	if (t == NULL || t->data == key)
		return t;
	BinTreeNode *p = BinTreeFind(t->leftChild, key);
	if (p != NULL)
		return p;
	return BinTreeFind(t->rightChild, key);
}
BinTreeNode* BinTreeParent(BinTree t, BinTreeNode *p)
{
	if (t == NULL || p == NULL || t == p)
		return NULL;
	/*if (t == NULL || t->leftChild == NULL || t->rightChild == NULL)
		return NULL;
	if (t == p)
		return NULL;*/
	if (t->leftChild == p || t->rightChild == p)
		return t;
	BinTreeNode *pr = BinTreeParent(t->leftChild, p);
	if (pr != NULL)
		return pr;
	return BinTreeParent(t->rightChild, p);
}
BinTreeNode* BinTreeClone(BinTree t)
{
	if (t == NULL)
		return NULL;
	else
	{
		BinTreeNode *bt = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(bt != NULL);
		bt->data = t->data;
		bt->leftChild = BinTreeClone(t->leftChild);
		bt->rightChild = BinTreeClone(t->rightChild);
		return bt;
	}
}
bool         Equal(BinTree t1, BinTree t2)
{
	if (t1 == NULL && t2 == NULL)
		return true;
	if (t1 == NULL || t2 == NULL)
		return false;
	return (t1->data == t2->data
		&& Equal(t1->leftChild ,t2->rightChild)
		&& Equal(t1->rightChild ,t2->rightChild));
}

#endif