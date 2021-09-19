#ifndef _CONTACT_H_
#define _CONTACT_H_

#pragma warning(disable:4996)

#include<stdio.h>
#include<assert.h>
#include<windows.h>

//person�ڲ�Ԫ�صĴ�С
#define NAME_SIZE 32
#define SEX_SIZE 8
#define TELPHONE_SIZE 16
#define ADDRESS_SIZE 128

//ͨѶ��ĳ�ʼ��Ϣ
#define INIT_NUM 1000
#define INC_SIZE 5

typedef struct person{
	char name[NAME_SIZE];
	char sex[SEX_SIZE];
	int age;
	char telphone[TELPHONE_SIZE];
	char address[ADDRESS_SIZE];
}person_t;

typedef struct contact{
	int cap;    //������Ϣ
	int size;   //��ǰ��Ч������Ϣ
	person_t friends[0]; //��������
}contact_t;

void InitContact(contact_t **ct);//��ʼ��ͨѶ¼
void AddFriend(contact_t **ct);//��Ӻ�����Ϣ
void DelFriend(contact_t* ct);
void SearchFriend(contact_t* ct);
void ModifyContact(contact_t* ct);
void ShowContact(contact_t *ct);
void ClearContact(contact_t *ct);
void SortContact(contact_t* ct);


#endif