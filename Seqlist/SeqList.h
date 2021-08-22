// SeqList.h
#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include"Common.h"
#define SEQLIST_DEFAULT_SIZE 8

//����˳���Ľṹ
typedef struct SeqList
{
	ElemType *base;
	size_t    capacity;
	size_t    size;
}SeqList;

void SeqListInit(SeqList *plist);
void SeqListDestroy(SeqList *plist);//
void SeqListPushBack(SeqList *plist, ElemType x);
void SeqListPushFront(SeqList *plist, ElemType x);
void SeqListShow(SeqList *plist);

void SeqListPopBack(SeqList *plist);
void SeqListPopFront(SeqList *plist);
void SeqListClear(SeqList *plist);
bool SeqListInsertByPos(SeqList *plist, int pos, ElemType x);
void SeqListInsertByVal(SeqList *plist, ElemType x);
void SeqListEraseByPos(SeqList *plist, int pos);
void SeqListEraseByVal(SeqList *plist, ElemType key);
void SeqListSort(SeqList *plist);

size_t SeqListLength(SeqList *plist);
size_t SeqListCapacity(SeqList *plist);

int SeqListFind(SeqList *plist, ElemType key);

void SeqListReverse(SeqList *plist);

/////////////////////////////////////////////////////////////////////////////////
void SeqListPopFront(SeqList *plist);


//////////////////////////////////////////////////////////////////////////////////
bool IsFull(SeqList *plist)
{
	assert(plist != NULL);
	return plist->size >= plist->capacity;
}

bool IsEmpty(SeqList *plist)
{
	assert(plist != NULL);
	return plist->size == 0;
}

void SeqListInit(SeqList *plist)
{
	assert(plist != NULL);
	plist->capacity = SEQLIST_DEFAULT_SIZE;
	plist->base = (ElemType*)malloc(sizeof(ElemType)*plist->capacity);
	plist->size = 0;
}

void SeqListDestroy(SeqList *plist)
{
	assert(plist != NULL);
	free(plist->base);
	plist->base = NULL;
	plist->capacity = plist->size = 0;
}

size_t SeqListLength(SeqList *plist)
{
	assert(plist != NULL);
	return plist->size;
}
size_t SeqListCapacity(SeqList *plist)
{
	assert(plist != NULL);
	return plist->capacity;
}

void SeqListPushBack(SeqList *plist, ElemType x)
{
	assert(plist != NULL);
	if (IsFull(plist))
	{
		printf("˳���������%d ����β������.\n", x);
		return;
	}
	plist->base[plist->size] = x;
	plist->size++;
}

void SeqListPushFront(SeqList *plist, ElemType x)
{
	assert(plist != NULL);
	if (IsFull(plist))
	{
		printf("˳���������%d ����ͷ������.\n", x);
		return;
	}
	for (size_t i = plist->size; i > 0; --i)
	{
		plist->base[i] = plist->base[i - 1];
	}
	plist->base[0] = x;
	plist->size++;
}

void SeqListShow(SeqList *plist)
{
	assert(plist != NULL);
	for (size_t i = 0; i < plist->size; ++i)
	{
		printf("%d ", plist->base[i]);
	}
	printf("\n");
}

void SeqListPopBack(SeqList *plist)
{
	assert(plist != NULL);
	if (IsEmpty(plist))
	{
		printf("˳����ѿգ����ܽ���β��ɾ��.\n");
		return;
	}
	plist->size--;
}
void SeqListPopFront(SeqList *plist)
{
	assert(plist != NULL);
	if (IsEmpty(plist))
	{
		printf("˳����ѿգ����ܽ���ͷ��ɾ��.\n");
		return;
	}
	for (size_t i = 0; i < plist->size; ++i)
	{
		plist->base[i] = plist->base[i + 1];
	}
	plist->size--;
}

bool SeqListInsertByPos(SeqList *plist, int pos, ElemType x)
{
	assert(plist != NULL);
	if (IsFull(plist))
	{
		printf("˳���������%d ���ܲ���.\n", x);
		return false;
	}
	if (pos<0 || pos>plist->size)
	{
		printf("Ҫ�����λ��[%d]�ǷǷ�λ��, %d ���ܲ���.\n", pos, x);
		return false;
	}
	for (size_t i = pos ; i < plist->size; ++i)
	{
		plist->base[pos + 1] = plist->base[pos];
	}

	plist->base[pos] = x;
	plist->size++;
	return true;
}

void SeqListInsertByVal(SeqList *plist, ElemType x)
{
	assert(plist != NULL);
	if (IsFull(plist))
	{
		printf("˳�������,%d ���ܲ���.\n", x);
		return false;
	}
	size_t i = 0;
	while (x>plist->base[i]){
		++i;
	}
	size_t pos = i;
	for (i = plist->size; i >pos; --i){
		plist->base[i] = plist->base[i - 1];
	}
	plist->base[pos] = x;
	plist->size++;
}

void SeqListEraseByPos(SeqList *plist, int pos)
{
	assert(plist != NULL);
	if (IsEmpty(plist))
	{
		printf("˳����ѿգ����ܽ���ɾ��.\n");
		return;
	}
	if (pos < 0 || pos >= plist->size){
		printf("�������λ�ò��Ϸ�����λ��������.\n");
		return;
	}
	for (size_t i = pos; i < plist->size; ++i){
		plist->base[i] = plist->base[i + 1];
	}
	plist->size--;
}

void SeqListEraseByVal(SeqList *plist, ElemType key)
{
	assert(plist != NULL);
	int pos = SeqListFind(plist, key);
	if (pos == -1)
		return;
	SeqListEraseByPos(plist, pos);

}

int SeqListFind(SeqList *plist, ElemType key)
{
	assert(plist != NULL);
	int pos = 0;
	while (pos < plist->size&&key != plist->base[pos]){
		pos++;
	}
	if (plist->size == pos ){
		pos = -1;
	}
	return pos;
}

void SeqListSort(SeqList *plist)
{
	assert(plist != NULL);
	for (size_t i = 0; i < plist->size - 1; i++)
	{
		for (size_t j = 0; j < plist->size - 1 - i; j++)
		{
			if (plist->base[j]>plist->base[j - +1])
			{
				Swap(&plist->base[j], &plist->base[j + 1]);
			}
		}
	}
}

void SeqListReverse(SeqList *plist)
{
	assert(plist != NULL);
	if (plist->size == 1)
		return;
	int start = 0;
	int end = plist->size - 1;
	while (start < end){
		Swap(&plist->base[start], &plist->base[end]);
		start++;
		end--;
	}
}

void SeqListClear(SeqList *plist)
{
	assert(plist != NULL);
	plist->size = 0;
}

#endif