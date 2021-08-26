#ifndef _DCLIST_H_
#define _DCLIST_H_
#include"common.h"

//带头结点的双向循环链表
//定义节点
typedef struct DCListNode
{
	ElemType data;
	DCListNode *next;
	DCListNode *prev;
}DCListNode;

typedef DCListNode* DCList;

void DCListInit(DCList *phead);
void DCListPushBack(DCList *phead, ElemType x);
void DCListPushFront(DCList *phead, ElemType x);
void DCListShow(DCList phead);
void DCListPopBack(DCList *phead);
void DCListPopFront(DCList *phead);
size_t DCListLength(DCList phead);
ElemType DCListFront(DCList phead);
ElemType DCListBack(DCList phead);
void DCListClear(DCList *phead);
void DCListDestroy(DCList *phead);
DCListNode* DCListFind(DCList phead, ElemType key);
void DCListEraseByVal(DCList phead, ElemType key);
void DCListSort(DCList phead);
void DCListInsertByVal(DCList phead, ElemType x);
void DCListReverse(DCList phead);
void DCListEraseAll(DCList phead, ElemType key);
/////////////////////////////////////////////////////////////////////
DCListNode* _Buynode(ElemType v = ElemType())//申请一个随机结点，ElemType()默认为0
{
	DCListNode *_S = (DCListNode *)malloc(sizeof(DCListNode));
	assert(_S != NULL);
	_S->data = v;
	_S->next = _S->prev = _S;
	return _S;
}
void DCListInit(DCList *phead)
{
	assert(phead != NULL);
	*phead = _Buynode();
}
void DCListPushBack(DCList *phead, ElemType x)
{
	assert(phead != NULL);
	DCListNode *s = _Buynode(x);
	DCListNode *head = *phead;

	s->prev = head->prev;
	s->next = head;
	s->prev->next = s;  //head->prev->next=s
	head->prev = s;
}
void DCListPushFront(DCList *phead, ElemType x)
{
	assert(phead != NULL);
	DCListNode *s = _Buynode(x);
	DCListNode *head = *phead;

	s->prev = head;
	s->next = head->next;
	head->next->prev = s;
	head->next = s;
}
void DCListShow(DCList phead)
{
	DCListNode *p = phead->next;
	while (p != phead)
	{
		printf("%d->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}


#endif