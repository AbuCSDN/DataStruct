#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 30
#define TEL_MAX 20
#define ADDR_MAX 100

#define CONTACT_BOOK_MAX 100//可存100个联系人

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
	Contact array[CONTACT_BOOK_MAX];//存储联系人的数组
	int size;						//实际存储了多少联系人
}ContactBook;


void ContactBookInit(ContactBook* pcb);
void ContactBookAdd(ContactBook* pcb, Contact* pc);//往结构体里添加一个联系人
