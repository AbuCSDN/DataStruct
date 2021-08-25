#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "common.h"

//typedef struct LinkQueueNode
//{
//	ElemType data;
//	struct LinkQueueNode *link;
//}LinkQueueNode;
//
//typedef struct LinkQueue
//{
//	LinkQueueNode *head;//对头指针
//	LinkQueueNode *tail;//队尾指针
//}LinkQueue;
//
//void LinkQueueInit(LinkQueue *pq);
//void LinkQueueEn(LinkQueue *pq, ElemType x);
//void LinkQueueDe(LinkQueue *pq);
//ElemType LinkQueueFront(LinkQueue *pq);
//int LinkQueueSize(LinkQueue *pq);
//bool LinkQueueEmpty(LinkQueue *pq);
//void LinkQueueShow(LinkQueue *pq);
//void LinkQueueDestroy(LinkQueue *pq);
///////////////////////////////////////////////////////
//void LinkQueueInit(LinkQueue *pq)
//{
//	assert(pq != NULL);
//	pq->head = pq->tail = NULL;
//}
//void LinkQueueEn(LinkQueue *pq, ElemType x)
//{
//	assert(pq != NULL);
//	LinkQueueNode *node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
//	assert(node != NULL);
//	node->data = x;
//	node->link = NULL;
//	if (pq->head = NULL){
//		pq->head = pq->tail = node;
//	}
//	else{
//		pq->tail->link = node;
//		pq->tail = node;
//	}
//}
//void LinkQueueDe(LinkQueue *pq)
//{
//	assert(pq != NULL);
//	if (pq->head != NULL){
//		LinkQueueNode *p = pq->head;
//		if (pq->head == pq->tail){
//			pq->head = pq->tail = NULL;
//		}
//		else{
//			pq->head = p->link;
//		}
//		free(p);
//	}
//		/*return;
//	}
//	else{
//		LinkQueueNode *p = pq->tail;
//		pq->tail
//	}*/
//}
//ElemType LinkQueueFront(LinkQueue *pq)
//{
//	assert(pq != NULL);
//	assert(pq->head != NULL);
//	/*if (pq->head = NULL){
//		return;
//	}*/
//	LinkQueueNode *p = pq->head;
//	return p->data;  //pq->head->data   //pq->tail->data
//}
//int LinkQueueSize(LinkQueue *pq)
//{
//	assert(pq != NULL);
//	int size = 0;
//	LinkQueueNode *p = pq->head;
//	while (p != NULL)
//	{
//		size++;
//		p = p->link;
//	}
//	return size;
//}
//bool LinkQueueEmpty(LinkQueue *pq)
//{
//	assert(pq != NULL);
//	return pq->head == NULL;
//}
//void LinkQueueShow(LinkQueue *pq)
//{
//	assert(pq != NULL);
//	LinkQueueNode *p = pq->head;
//	while (p != NULL)
//	{
//		printf("%d ", p->data);
//		p = p->link;
//	}
//	printf("\n");
//}
//void LinkQueueDestroy(LinkQueue *pq)
//{
//	assert(pq != NULL);
//	LinkQueueNode *p = pq->head;
//	while (p != NULL)
//	{
//		pq->head = p->link;
//		free(p);
//		p = pq->head;
//	}
//}


//循环队列

#define QUEUE_DEFAULT_SIZE 8

typedef struct CycleSeqQueue
{
	ElemType *base;
	int      capacity;
	int      front;
	int      rear;
}CycleSeqQueue;

void CycleSeqQueueInit(CycleSeqQueue *pcq, int sz = QUEUE_DEFAULT_SIZE);
void CycleSeqQueueEn(CycleSeqQueue *pcq, ElemType x);
void CycleSeqQueueDe(CycleSeqQueue *pcq);
ElemType CycleSeqQueueFront(CycleSeqQueue *pcq);
int CycleSeqQueueSize(CycleSeqQueue *pcq);
bool CycleSeqQueueEmpty(CycleSeqQueue *pcq);
void CycleSeqQueueShow(CycleSeqQueue *pcq);
void CycleSeqQueueDestroy(CycleSeqQueue *pcq);
//////////////////////////////////////////////////
bool IsFull(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	return (pcq->rear + 1) % (pcq->capacity + 1) == pcq->front;
}
bool IsEmpty(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	return pcq->front == pcq->rear;
}
void CycleSeqQueueInit(CycleSeqQueue *pcq,int sz)
{
	assert(pcq != NULL);
	pcq->capacity = sz > QUEUE_DEFAULT_SIZE ? sz : QUEUE_DEFAULT_SIZE;
	pcq->base = (ElemType *)malloc(sizeof(ElemType)*(pcq->capacity + 1));
	pcq->front = pcq->rear = 0;
}
void CycleSeqQueueEn(CycleSeqQueue *pcq, ElemType x)
{
	assert(pcq != NULL);
	if (IsFull(pcq))
	{
		printf("队列已满， %d 不能入队.\n");
		return;
	}
	pcq->base[pcq->rear] = x;
	pcq->rear = (pcq->rear + 1) % (pcq->capacity + 1);
}
void CycleSeqQueueDe(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	if (IsEmpty(pcq))
	{
		printf("队列已空，不能出队.\n");
		return;
	}
	pcq->front = (pcq->front + 1) % (pcq->capacity + 1);
}
ElemType CycleSeqQueueFront(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	assert(!IsEmpty(pcq));
	return pcq->base[pcq->front];
}
int CycleSeqQueueSize(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	int size = 0;
	for (int i = pcq->front; i != pcq->rear;)
	{
		size++;
		i = (i + 1) % (pcq->capacity + 1);
	}
	return size;
}
bool CycleSeqQueueEmpty(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	return IsEmpty;
}
void CycleSeqQueueShow(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	for (int i = pcq->front; i != pcq->rear;)
	{
		printf("%d ", pcq->base[i]);
		i = (i + 1) % (pcq->capacity + 1);
	}
	printf("\n");
}
void CycleSeqQueueDestroy(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	free(pcq->base);
	pcq->capacity = pcq->front = pcq->rear = 0;
}


#endif