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

	printf("�Զ����ݳɹ�!\n");
	return 1;
}
void AddFriend(contact_t **ct)
{
	assert(ct);
	//ͨѶ¼���ˣ��Զ�����
	if (!IsFull(*ct) || Inc(ct))//û������ִ�е�һ������֮����Ҫ���ݣ�����������ִ�еڶ�����������
	{
		//1.û����
		//2.���ݳɹ�
		person_t p;
		printf("�����������û�������->");
		scanf("%s", p.name);  //name��һ�����飬������������Ԫ�ص�ַ
		printf("�����������û����Ա�->");
		scanf("%s", p.sex);
		printf("�����������û������->");
		scanf("%d", &(p.age));
		printf("�����������û��ĵ绰->");
		scanf("%s", p.telphone);
		printf("�����������û��ĵ�ַ->");
		scanf("%s", p.address);

		//�ж��û��Ƿ��Ѿ�����
		if (IsExist(*ct, &p))
		{
			printf("%s �Ѿ����ڣ��벻Ҫ�ظ����룡\n", p.name);
			return;
		}
		//(*ct)->friends[(*ct)->size] = p;
		memcpy((*ct)->friends + (*ct)->size, &p, sizeof(p));
		(*ct)->size += 1;
		printf("�����û� %s �ɹ���\n", p.name);

	}
	else
	{
		perror("����ʧ�ܣ�\n");
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
	printf("��������Ҫɾ�����˵�����->");
	char name[NAME_SIZE];
	scanf("%s", name);
	int i = SearchCore(ct, name);
	if (i >= 0)
	{
		//�����һ���û�����Ϣֱ�Ӹ��ǵ���ǰλ��
		ct->friends[i] = ct->friends[ct->size - 1];
		ct->size -= 1;
	}
	else
	{
		printf("��Ҫɾ�����˲�����!\n");
	}

}

void SearchFriend(contact_t* ct)
{
	assert(ct);
	printf("��������Ҫ���ҵ��˵�����->");
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
		printf("%s �û�������!\n");
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
	//�Ҳ���
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
		printf("ͨѶ¼�ѿգ��޷�������Ϣ\n");
		return;
	}
	//�޸�
	printf("������Ҫ�޸���Ŀ������:>");
	scanf("%s", name);
	//���ң��޸�֮ǰ��Ҫ�Ȳ��ң�
	pos = FindByName(ct, name);
	if (pos == -1)
	{
		printf("Ҫ�޸ĵ���Ŀ������\n");
		return;
	}
	//ѯ��Ҫ��ʲô
	printf("������Ҫ�޸�ʲô��Ϣ��1-���֣�2-���䣬3-�Ա�4-�绰��5-סַ��:>");
	int msg;
	scanf("%d", &msg);
	switch (msg)
	{
	case 1:
		printf("�������µ�����:>");
		scanf("%s", ct->friends[pos].name);
		break;
	case 2:
		printf("�������µ�����:>");
		scanf("%d", &ct->friends[pos].age);
		break;
	case 3:
		printf("�������µ��Ա�:>");
		scanf("%s", ct->friends[pos].sex);
		break;
	case 4:
		printf("�������µĵ绰:>");
		scanf("%s", ct->friends[pos].telphone);
		break;
	case 5:
		printf("�������µĵ�ַ:>");
		scanf("%s", ct->friends[pos].address);
		break;
	default:
		printf("���������޸�ʧ��\n");
		return;
	}
	printf("�޸ĳɹ�\n");
}
void ShowContact(contact_t *ct)
{
	assert(ct);
	int i = 0;
	printf("\n|cap:d     |size:d    |\n\n", ct->cap, ct->size);
	printf("|%-10s|%-10s|%-10s|%-10s|%-10s|\n", "����","�Ա�","���","�绰","��ַ");
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