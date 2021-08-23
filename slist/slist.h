#ifndef _SLIST_H_
#define _SLIST_H_
#include"common.h"
typedef struct SListNode
{
	ElemType data;
	struct SListNode *next;
}SListNode;

//不带头结点的单链表
typedef SListNode* SList;


void SListInit(SList *phead);
void SListPushBack(SList *phead, ElemType x);
void SListPushFront(SList *phead, ElemType x);
void SListPopBack(SList *phead);
void SListPopFront(SList *phead);
void SListShow(SList *phead);
size_t SListLength(SList *phead);

SListNode* SListFind(SList phead, ElemType key);
void SListEraseByVal(SList *phead, ElemType key);
void SListInsertByVal(SList *phead, ElemType key);
void SListSort(SList *phead);

ElemType SListFront(SList phead);
ElemType SListBack(SList phead);
void SListEraseAll(SList *phead, ElemType key); //删除所有
void SListClear(SList *phead);
void SListDestroy(SList *phead);
void SListReverse(SList *phead);
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
void SListInit(SList *phead)
{
	assert(phead != NULL);
	*phead = NULL;
}
void SListPushBack(SList *phead, ElemType x)
{
	assert(phead != NULL);
	SListNode *s = (SListNode *)malloc(sizeof(SListNode));
	assert(s != NULL);
	s->data = x;
	s->next = NULL;

	//链接节点
	SListNode *p = *phead;
	if (p == NULL){   //p为*phead的指针变量
		*phead = s;   //s赋值给解引用phead
	}
	else{
		while (p->next != NULL){  
			p = p->next;
		}
		p->next = s;     //此时p->next为空
	}
}
void SListPushFront(SList *phead, ElemType x)
{
	assert(phead != NULL);
	SListNode *s = (SListNode *)malloc(sizeof(SListNode));
	assert(s != NULL);
	s->data = x;
	s->next = NULL;

	s->next = *phead;
	*phead = s;
	//SListNode *p = *phead;
	//if (p == NULL){   //p为*phead的指针变量
	//	*phead = s;   //s赋值给解引用phead
	//}
	//else{
	//	s->next = p;
	//	*phead = s;
	//}
}
void SListPopBack(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = *phead;
	SListNode *prev = NULL;
	while (p != NULL && p->next != NULL)
	{
		prev = p;
		p = p->next;
	}
	prev->next = NULL;
	free(p);
}
void SListPopFront(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = *phead;
	if (p != NULL){
		*phead = p->next;
		free(p);
	}
	/**phead = (*phead)->next;
	p->next = NULL;
	free(p);*/
}
size_t SListLength(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = *phead;
	size_t num = 0;
	while (p != NULL)
	{
		p = p->next;
		num++;
	}
	return num;
}
SListNode* SListFind(SList phead, ElemType key)
{
	SListNode *p = phead;
	while (p->data != key)
	{
		p = p->next;
	}
	if (p->data = key){
		return p;
	}
	else{
		return NULL;
	}
}
void SListEraseByVal(SList *phead, ElemType key)
{
	assert(phead != NULL);
	SListNode *p = SListFind(*phead, key);
	if (p == NULL)
		return;

	SListNode *prev = *phead;
	while (prev != p && prev->next != p)
		prev = prev->next;
	if (prev == p)       //对，只会是第一个元素
		*phead = p->next;
	else
		prev->next = p->next;
	free(p);

}
	/*SListNode *prev = NULL;
	while (p != NULL)
	{
		if (p->data = key){   //有错误
			prev->next = p->next;
			free(p);
		}
		prev->next = p;
		p = p->next;
	}*/      
void SListInsertByVal(SList *phead, ElemType key)
{
	assert(phead != NULL);
	SListNode *p = *phead;
	SListNode *prev = NULL;

	while (p != NULL&&key > p->data){
		prev = p;
		p = p->next;
	}

	SListNode *s = (SListNode*)malloc(sizeof(SListNode));
	assert(s != NULL);
	s->data = key;

	if (prev == NULL){
		s->next = *phead;
		*phead = s;
	}
	else{
		s->next = prev->next;
		prev->next = s;
	}
}

void SListSort(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = (SListNode *)malloc(sizeof(SListNode));
	SListNode *q = (SListNode *)malloc(sizeof(SListNode));
	size_t tmp;
	for (p = *phead; p != NULL; p = p->next){
		for (q = p->next; q != NULL; q = q->next){
			if (p->data > q->data){
				tmp = q->data;
				q->data = p->data;
				p->data = tmp;
			}
		}
	}
}

void SListShow(SList phead)
{
	SListNode *p = phead;
	while (p != NULL){
		printf("%d->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}

#endif