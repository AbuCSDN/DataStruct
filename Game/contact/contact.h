#ifndef _CONTACT_H_
#define _CONTACT_H_

#pragma warning(disable:4996)

#include<stdio.h>
#include<assert.h>
#include<windows.h>

//person内部元素的大小
#define NAME_SIZE 32
#define SEX_SIZE 8
#define TELPHONE_SIZE 16
#define ADDRESS_SIZE 128

//通讯里的初始信息
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
	int cap;    //容量信息
	int size;   //当前有效好友信息
	person_t friends[0]; //柔性数组
}contact_t;

void InitContact(contact_t **ct);//初始化通讯录
void AddFriend(contact_t **ct);//添加好友信息
void DelFriend(contact_t* ct);
void SearchFriend(contact_t* ct);
void ModifyContact(contact_t* ct);
void ShowContact(contact_t *ct);
void ClearContact(contact_t *ct);
void SortContact(contact_t* ct);


#endif