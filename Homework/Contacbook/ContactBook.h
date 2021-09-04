#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 30
#define TEL_MAX 20
#define ADDR_MAX 100

#define CONTACT_BOOK_MAX 100//�ɴ�100����ϵ��

typedef struct Contact
{
	char name[NAME_MAX];
	char tel[TEL_MAX];
	char addrss[ADDR_MAX];
	int age;
	//
}Contact;

typedef struct ContactBook
{
	Contact array[CONTACT_BOOK_MAX];//�洢��ϵ�˵�����
	int size;						//ʵ�ʴ洢�˶�����ϵ��
}ContactBook;


void ContactBookInit(ContactBook* pcb);
void ContactBookAdd(ContactBook* pcb, Contact* pc);//���ṹ�������һ����ϵ��
