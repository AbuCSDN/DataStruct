//#include"stack.h"
#include"queue.h"

void main()
{

	CycleSeqQueue Q;
	CycleSeqQueueInit(&Q);
	CycleSeqQueueEn(&Q, 1);
	CycleSeqQueueEn(&Q, 2);
	CycleSeqQueueEn(&Q, 3);
	CycleSeqQueueEn(&Q, 4);
	CycleSeqQueueEn(&Q, 5);
	CycleSeqQueueEn(&Q, 6);
	CycleSeqQueueEn(&Q, 7);
	CycleSeqQueueEn(&Q, 8);

	CycleSeqQueueEn(&Q, 9);
	CycleSeqQueueShow(&Q);

	CycleSeqQueueDe(&Q);
	CycleSeqQueueShow(&Q);
	CycleSeqQueueEn(&Q, 9);
	CycleSeqQueueShow(&Q);
	/*LinkQueue Q;
	LinkQueueInit(&Q);
	LinkQueueEn(&Q, 1);
	LinkQueueEn(&Q, 2);
	LinkQueueEn(&Q, 3);
	LinkQueueEn(&Q, 4);
	LinkQueueEn(&Q, 5);
	LinkQueueShow(&Q);

	int front_val;
	while (!LinkQueueEmpty(&Q))
	{
		front_val = LinkQueueFront(&Q);
		LinkQueueDe(&Q);
		printf("%d ³ö¶Ó.\n", front_val);
	}
	LinkQueueDestroy(&Q);*/

		/*LinkStack st;
		LinkStackInit(&st);
		LinkStackPush(&st, 1);
		LinkStackPush(&st, 2);
		LinkStackPush(&st, 3);
		LinkStackPush(&st, 4);
		LinkStackPush(&st, 5);
		LinkStackShow(&st);
		LinkStackPop(&st);
		LinkStackPop(&st);
		LinkStackShow(&st);
		printf("top = %d\n", LinkStackTop(&st));
		printf("size = %d\n", LinkStackSize(&st));
		LinkStackDestroy(&st);*/
	
	//SeqStack st;
	//SeqStackInit(&st);
	//SeqStackPush(&st, 1);
	//SeqStackPush(&st, 2);
	//SeqStackPush(&st, 3);
	//SeqStackPush(&st, 4);
	//SeqStackPush(&st, 5);
	//SeqStackShow(&st);
	//int top_val;
	//while (!SeqStackIsEmpty(&st))
	//{
	//	//top_val = SeqStackTop(&st);
	//	SeqStackTop(&st, &top_val);
	//	SeqStackPop(&st);
	//	printf("%d ³öÕ».\n", top_val);
	//}
	//SeqStackDestroy(&st);

	system("pause");
}