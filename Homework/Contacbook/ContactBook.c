#include"ContactBook.h"

void ContactBookInit(ContactBook* pcb)
{
	pcb->size = 0;
	memset(pcb->array, 0, sizeof(Contact)*CONTACT_BOOK_MAX);
}

void ContactBookAdd(ContactBook* pcb, Contact* pc)
{
	assert(pcb);
	assert(pc);

	if (pcb->size == CONTACT_BOOK_MAX);
	{
		printf("Í¨Ñ¶Â¼ÒÑÂú...\n");
		return;
	}

	strcpy(pcb->array[pcb->])
}