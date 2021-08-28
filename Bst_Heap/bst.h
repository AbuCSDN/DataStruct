#ifndef _BST_H_
#define _BST_H_

#include"common.h"

typedef int BstElemType;
typedef struct BSTNode
{
	BstElemType data;
	struct BSTNode *leftChild;
	struct BSTNode *rightChild;
}BSTNode;

typedef BSTNode* BSTree;

void BstInit(BSTree *bst);
bool BstInsert(BSTree *t, BstElemType x);

BstElemType BstMin(BSTree t);
BstElemType BstMax(BSTree t);
void BstSortPrint(BSTree t);
BSTNode* BstFind(BSTree t, BstElemType key);

bool BstErase(BSTree *t, BSTNode *p);

////////////////////////////////////////////////////////////
void BstInit(BSTree *bst)
{
	*bst = NULL;
}
bool BstInsert(BSTree *t, BstElemType x)
{
	if (*t == NULL)
	{
		*t = (BSTNode *)malloc(sizeof(BSTNode));
		assert(*t != NULL);
		(*t)->data = x;
		(*t)->leftChild = (*t)->rightChild = NULL;
		return true;
	}
	
	if (x < (*t)->data)
		return BstInsert(&(*t)->leftChild, x);
	else if (x >(*t)->data)
		return BstInsert(&(*t)->rightChild, x);
	else
		return false;
}
BstElemType BstMin(BSTree t)
{
	assert(t != NULL);
	while (t->leftChild != NULL)
		t = t->leftChild;
	return t->data;
}
BstElemType BstMax(BSTree t)
{
	assert(t != NULL);
	while (t->rightChild != NULL)
		t = t->rightChild;
	return t->data;
}
void BstSortPrint(BSTree t)
{
	if (t != NULL)
	{
		BstSortPrint(t->leftChild);
		printf("%d ", t->data);
		BstSortPrint(t->rightChild);
	}
}
BSTNode* BstFind(BSTree t, BstElemType key)
{
	if (t == NULL)
		return NULL;
	if (t->data == key)
		return t;

	if (t->data < key)
		return BstFind(t->rightChild, key);
	else
		return BstFind(t->leftChild, key);
}

bool BstErase(BSTree *t, BSTNode *p)
{
	if (*t != NULL)
	{
		if (p->data < (*t)->data)
			BstErase(&(*t)->leftChild, p);
		else if (p->data>(*t)->data)
			BstErase(&(*t)->rightChild, p);
		else
		{
			if (p->leftChild != NULL&&p->rightChild != NULL)
			{
				//×óÓÒ×ÓÊ÷¶¼´æÔÚ
				BSTNode *s = p->leftChild;
				while (s->rightChild != NULL)
					s = s->rightChild;
				p->data = s->data;
				BstErase(&p->leftChild, s);
			}
			else
			{
				if (p->leftChild != NULL)
					*t = p->leftChild;
				else
					*t = p->rightChild;
			}
			return true;
		}
	}
	return false;
}

#endif