#include"contact.h"

void InitContact(contact_t **ct)
{
	*ct = (contact_t* )malloc(sizeof(contact_t)+INIT_NUM*sizeof(person_t));
	if (ct == NULL)
	{
		perror("malloc");
		exit(1);
	}
	(*ct)->size = 0;
	(*ct)->cap = INIT_NUM;
}

int IsExist(contact_t *ct, person_t *p)
{
	assert(ct);
	assert(p);

	int i = 0;
	for (; i < ct->size; ++i)
	{
		if (strcmp(ct->friends[i].name, p->name) == 0) {
			return 1;
		}
	}
	return 0;
}
static int IsFull(contact_t *ct)
{
	return ct->cap == ct->size;
}
static int IsEmpty(contact_t *ct)
{
	return ct->size == 0;
}
static int Inc(contact_t **ct)
{
	assert(ct);

	contact_t* ct_temp = (contact_t*)realloc(*ct, sizeof(contact_t)+((*ct)->cap + INC_SIZE)*sizeof(person_t));
	if (ct_temp == NULL)
	{
		return 0;
	}
	*ct = ct_temp;
	(*ct)->cap += INC_SIZE;

	printf("自动扩容成功!\n");
	return 1;
}
void AddFriend(contact_t **ct)
{
	assert(ct);
	//通讯录满了，自动扩容
	if (!IsFull(*ct) || Inc(ct))//没有满，执行第一个条件之后不需要扩容，若已满，则执行第二个扩容条件
	{
		//1.没有满
		//2.扩容成功
		person_t p;
		printf("请输入新增用户的姓名->");
		scanf("%s", p.name);  //name是一个数组，数组名代表首元素地址
		printf("请输入新增用户的性别->");
		scanf("%s", p.sex);
		printf("请输入新增用户的年纪->");
		scanf("%d", &(p.age));
		printf("请输入新增用户的电话->");
		scanf("%s", p.telphone);
		printf("请输入新增用户的地址->");
		scanf("%s", p.address);

		//判断用户是否已经存在
		if (IsExist(*ct, &p))
		{
			printf("%s 已经存在，请不要重复插入！\n", p.name);
			return;
		}
		//(*ct)->friends[(*ct)->size] = p;
		memcpy((*ct)->friends + (*ct)->size, &p, sizeof(p));
		(*ct)->size += 1;
		printf("新增用户 %s 成功！\n", p.name);

	}
	else
	{
		perror("扩容失败！\n");
	}
}
static int SearchCore(contact_t* ct, const char* name)
{
	assert(ct);
	assert(name);
	int i = 0;
	for (; i < ct->size; ++i)
	{
		person_t* p = ct->friends + i;
		if (strcmp(name, p->name) == 0)
		{
			return i;
		}
	}
}
void DelFriend(contact_t* ct)
{
	assert(ct);
	printf("请输入你要删除的人的姓名->");
	char name[NAME_SIZE];
	scanf("%s", name);
	int i = SearchCore(ct, name);
	if (i >= 0)
	{
		//将最后一个用户的信息直接覆盖到当前位置
		ct->friends[i] = ct->friends[ct->size - 1];
		ct->size -= 1;
	}
	else
	{
		printf("你要删除的人不存在!\n");
	}

}

void SearchFriend(contact_t* ct)
{
	assert(ct);
	printf("请输入你要查找的人的姓名->");
	char name[NAME_SIZE];
	scanf("%s", name);
	int i = SearchCore(ct, name);
	if (i >= 0)
	{
		person_t* p = ct->friends + i;
		printf("|%-10s|%-10s|%-10d|%s|%-10s|\n", p->name, p->sex, p->age, p->telphone, p->address);
	}
	else
	{
		printf("%s 用户不存在!\n");
	}
	return;
}
static int FindByName(contact_t* ct, char name[])
{
	int i = 0;
	assert(ct);
	for (i = 0; i<ct->size; i++)
	{
		if (0 == strcmp(ct->friends[i].name, name))
		{
			return i;
		}
	}
	//找不到
	return -1;
}
void ModifyContact(contact_t* ct)
{
	int i = 0;
	char name[NAME_SIZE] = { 0 };
	int pos = 0;
	assert(ct);

	if (ct->size == 0)
	{
		printf("通讯录已空，无法查找信息\n");
		return;
	}
	//修改
	printf("请输入要修改条目的姓名:>");
	scanf("%s", name);
	//查找（修改之前需要先查找）
	pos = FindByName(ct, name);
	if (pos == -1)
	{
		printf("要修改的条目不存在\n");
		return;
	}
	//询问要改什么
	printf("请输入要修改什么信息（1-名字，2-年龄，3-性别，4-电话，5-住址）:>");
	int msg;
	scanf("%d", &msg);
	switch (msg)
	{
	case 1:
		printf("请输入新的姓名:>");
		scanf("%s", ct->friends[pos].name);
		break;
	case 2:
		printf("请输入新的年龄:>");
		scanf("%d", &ct->friends[pos].age);
		break;
	case 3:
		printf("请输入新的性别:>");
		scanf("%s", ct->friends[pos].sex);
		break;
	case 4:
		printf("请输入新的电话:>");
		scanf("%s", ct->friends[pos].telphone);
		break;
	case 5:
		printf("请输入新的地址:>");
		scanf("%s", ct->friends[pos].address);
		break;
	default:
		printf("输入有误，修改失败\n");
		return;
	}
	printf("修改成功\n");
}
void ShowContact(contact_t *ct)
{
	assert(ct);
	int i = 0;
	printf("\n|cap:d     |size:d    |\n\n", ct->cap, ct->size);
	printf("|%-10s|%-10s|%-10s|%-10s|%-10s|\n", "姓名","性别","年纪","电话","地址");
	for (; i < ct->size; ++i)
	{
		person_t *p = ct->friends + i;
		printf("|%-10s|%-10s|%-10d|%s|%-10s|\n", p->name, p->sex, p->age, p->telphone, p->address);
	}
	printf("\n");
}
void ClearContact(contact_t *ct)
{
	assert(ct);
	ct->size = 0;
}
static int CmpPerson(const void* p1, const void* p2)
{
	assert(p1);
	assert(p2);
	person_t* _p1 = (person_t*)p1;
	person_t* _p2 = (person_t*)p2;

	return strcmp(_p1->name, _p2->name);
}
void SortContact(contact_t* ct)
{
	assert(ct);
	if (!IsEmpty(ct))
	{
		qsort(ct->friends, ct->size, sizeof(person_t), CmpPerson);
	}
}