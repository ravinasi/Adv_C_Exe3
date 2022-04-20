#include <stdio.h>
#include "Queue.h"

void newPlace(Queue* q, unsigned int num);
void printQueue(Queue* q);
/***************** Queue ADT Implementation *****************/

void initQueue(Queue* q)
{
	q->head = NULL;
	q->tail = NULL;
}

void destroyQueue(Queue* q)
{
	intNode* temp = q->head;
	intNode* next = NULL;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	q->head = q->tail = NULL;// לבדוק אם צריך
}

void enqueue(Queue* q, unsigned int data)
{
	intNode* newnode = (intNode*)malloc(sizeof(intNode));
	if (!newnode)
	{
		printf("allocation failed");
		exit(1);
	}
	newnode->data = data;
	newnode->next = NULL;
	if (isEmptyQueue(q))
	{
		q->head = q->tail = newnode;
		return;
	}
	q->tail->next = newnode;
	q->tail = newnode;	
}

unsigned int dequeue(Queue* q)
{
	if (isEmptyQueue(q))
	{
		printf("the queue is empty\n");
		return;
	}
	unsigned int temp = q->head->data;
	intNode* tempptr = q->head;
	if (q->head->next == NULL)
	{
		q->head = q->tail = NULL;
	}
	else q->head = q->head->next;
	free(tempptr);
	return temp;
}

int isEmptyQueue(const Queue* q)
{
	if (q->head == NULL)
		return 1;
	else return 0;
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)
{
	if (isEmptyQueue(q))
	{
		printf("the queue is empty\n");
		return;
	}
	if (q->head == q->tail)
		return;
	intNode* newhead = q->tail;
	Queue* temp = q;
	Queue* prev = NULL;
	Queue* next = q->head->next;
	while (next != NULL)
	{
		prev = q;
		temp->head = temp->head->next;
		next = next->head->next;
	}
	q->tail = prev;
	newhead->next = q->head;
	q->head = newhead;
}

void cutAndReplace(Queue* q)
{
	if (isEmptyQueue(q))// if the queue is empty
	{
		printf("the queue is empty\n");
		return;
	}
	int size = 0;
	Queue* temp = q;
	while (temp != NULL)// check the size of queue
	{
		size++;
		temp = temp->head->next;
	}
	if (size % 2 == 1)// if the size is odd 
	{
		int sum = 0;
		unsigned int ave;
		while (temp != NULL)// sum all the nodes
		{
			sum += temp->head->data;
			temp->head = temp->head->next;
		}
		ave = sum / size;
		enqueue(q, ave); // add ave to the tail
		size += 1;
	}
	Queue* newhead = (Queue*)malloc(sizeof(Queue));
	if (!newhead)
	{
		printf("allocation failled\n");
		exit(1);
	}
	initQueue(newhead);
	Queue* newtail = (Queue*)malloc(sizeof(Queue));
	if (!newtail)
	{
		printf("allocation failled\n");
		exit(1);
	}
	initQueue(newtail);
	Queue* temphead = (Queue*)malloc(sizeof(Queue));
	if (!newhead)
	{
		printf("allocation failled\n");
		exit(1);
	}
	initQueue(temphead);
	for (int i = 0; i < size/2; i++)// add to newtail
	{
		unsigned int num = dequeue(q);
		enqueue(newtail, num);
	}
	for (int i = 0; i < size/2; i++)// add to newhead
	{
		unsigned int num = dequeue(q);
		enqueue(newhead, num);
	}
	while (newhead != NULL)// rotate newhead
	{
		unsigned int num = dequeue(newhead);
		enqueue(temphead, num);
	}
	while (newtail != NULL)// put new tail into original q
	{
		unsigned int num = dequeue(newtail);
		enqueue(q, num);
	}
	while (temphead != NULL)//put new head (rotated) into original q
	{
		unsigned int num = dequeue(temphead);
		enqueue(q, num);
	}
	free(newhead);
	free(newtail);
	free(temphead);
}

void sortKidsFirst(Queue* q)
{
	if (isEmptyQueue(q))
	{
		printf("the queue is empty\n");
		return;
	} 
	if (q->head = q->tail)// if there one node
		return;
	Queue* temp = q;
	while (temp != NULL)
	{
		if (temp->head->data < temp->head->next->data)
		{
			temp->head = temp->head->next;
		}
		else {
			unsigned int num = dequeue(q);
			Queue* next = q;
			Queue* newplace = NULL;
			while (num < next->head->data)//קטן בהתחלה
			{
				newplace = next;
				next = next->head->next;
			}
			newPlace(newplace, num);
			temp->head = temp->head->next;
		}
	}
}

void newPlace(Queue* q, unsigned int num)// put in the first place
{
	intNode* newnode = (intNode*)malloc(sizeof(intNode));
	if (!newnode)
	{
		printf("allocation failed");
		exit(1);
	}
	newnode->data = num;
	newnode->next = q->head;
	q->head = newnode;
}

void printQueue(Queue* q)
{
	printf("the queue is:\n");
	Queue* temp = q;
	while (temp != NULL)
	{
		printf(" %u", temp->head->data);
		temp->head = temp->head->next;
	}
}