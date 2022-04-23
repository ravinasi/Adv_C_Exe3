#include <stdio.h>
#include "Stack.h"

Stack* intervesionWord(Stack* s);
void printStack(Stack* s);
/***************** Stack ADT Implementation *****************/

void initStack(Stack* s)                         
{
	s->head = NULL;
}

void destroyStack(Stack* s)
{
	while (s->head != NULL)
		pop(s);
}

void push(Stack* s, char data)
{
	charNode* newnode = (charNode*)malloc(sizeof(charNode));
	if (!newnode)
	{
		printf("push: allocation faild\n");
		return;
	}
	newnode->data = data;
	s->head = addToHead(s->head, newnode);
}

charNode* addToHead(charNode *head, charNode *toadd)
{
	toadd->next = head;
	head = toadd;
	return head;
}

char pop(Stack* s)
{
	char res = s->head->data;
	charNode* temp = s->head;
	s->head = s->head->next;
	free(temp);
	return res;
}

int isEmptyStack(const Stack* s)
{
	if (s->head == NULL)
		return 1;
	return 0;
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
	int i = 0, hashAmount = 0;
	Stack* tempstack = (Stack*)malloc(sizeof(Stack));
	if (!tempstack)
	{
		printf("\nallocation failed");
		exit(1);
	}
	initStack(tempstack);
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if (!s)
	{
		printf("\nallocation failed");
		exit(1);
	}
	initStack(s);
	if (sentence == NULL)
	{
		printf("the string is empty");
		return;
	}
	while (sentence[i] != NULL)// put into stack
	{
		push(tempstack, sentence[i++]);
	}
	charNode* temp = tempstack->head;
	while (temp != NULL)// flip and count hashes
	{
		push(s, temp->data);
		if (temp->data == '#')
			hashAmount++;
		temp = temp->next;
	}
	destroyStack(tempstack);
	if (hashAmount % 2 == 1) // odd number of hashes
	{
		printf("odd number of hashes");
		destroyStack(s);
		return;
	}
	printf("the sentnce is:\n");
	while (s->head != NULL)
	{
		if (s->head->data == '#')
		{
			s->head = intervesionWord(s);// flip and print func
		}
		else
		{
			printf("%c", s->head->data);
			pop(s);
		}
	}
	destroyStack(s);
}

Stack* intervesionWord(Stack* s)
{
	s->head = s->head->next;
	Stack* newstack = (Stack*)malloc(sizeof(Stack));
	initStack(newstack);
	if (!newstack)
	{
		printf("\nallocation failed");
		exit(1);
	}
	while (s->head->data != '#')
	{
		push(newstack, s->head->data);
		pop(s);
	}
	while (newstack->head != NULL)
	{
		printf("%c", newstack->head->data);
		pop(newstack);
	}
	free(newstack);
	return s->head->next;
}

int isPalindrome(Stack* s)
{
	if (s == NULL)// s is nullptr
	{
		printf("stack need init");
		return 0;
	}
	if (s->head == NULL)// empty stack
		return 1;
	charNode* temp = s->head;
	Stack* smallstack = (Stack*)malloc(sizeof(Stack));
	if (!smallstack)
	{
		printf("allocation error");
		return;
	}
	initStack(smallstack);
	int count = 0;
	while (temp != NULL)// check stack size
	{
		count++;
		temp = temp->next;
	}
	if (count == 1)// if there is one char in the sentence
		return 1;
	temp = s->head;
	for (int i = 0; i < count / 2; i++)// push into small stack
	{
		push(smallstack, temp->data);
		temp = temp->next;
	}
	if (count % 2 == 1) // odd size of stack
	{
		temp = temp->next;
	}
	charNode* smalltemp = smallstack->head;
	for (int i = 0; i < count / 2; i++)// equal test between the stacks
	{
		if (smalltemp->data != temp->data)
			return 0;
		smalltemp = smalltemp->next;
		temp = temp->next;
	}
	free(smallstack);
	return 1;
}

void rotateStack(Stack* s, int n)
{
	if (s == NULL)// nullptr
	{
		printf("stack is nullptr\n");
		return;
	}
	if (s->head == NULL)// empty stack
	{
		printf("the stack is empty\n");
		return;
	}
	if (n <= 0)// if n is negetiv
	{
		printf("can't rotate - negetiv number\n");
		return;
	}
	charNode* temp = s->head;
	int size = 0;
	while (temp != NULL)// check stack size
	{
		size++;
		temp = temp->next;

	}
	if (n > size)
	{
		printf("your number is smaller than the sentence\n");
		return;
	}
	if (n == size)
	{
		printStack(s);
		return;
	}
	Stack* Newtop = (Stack*)malloc(sizeof(Stack));
	if (!Newtop)
	{
		printf("allocation error");
		return;
	}
	initStack(Newtop);
	Stack* Newtail = (Stack*)malloc(sizeof(Stack));
	if (!Newtail)
	{
		printf("allocation error");
		return;
	}
	initStack(Newtail);
	for (int i = 0; i < size - n; i++)// get new tail to a new stack
	{
		char c = pop(s);
		push(Newtail, c);
	}
	for (int i = 0; i < n; i++)// get new head to new list
	{
		char c = pop(s);
		push(Newtop, c);
	}
	while (Newtail->head != NULL)
	{
		char c = pop(Newtail);
		push(s, c);
	}
	while (Newtop->head != NULL)
	{
		char c = pop(Newtop);
		push(s, c);
	}
	printf("the new sentence is: ");
	printStack(s);
	printf("\n");
	free(Newtail);
	free(Newtop);
}

void printStack(Stack* s)
{
	if (s->head == NULL)
	{
		printf("the stack is empty\n");
		return;
	}
	charNode* temp = s->head;
	Stack* helpstack = (Stack*)malloc(sizeof(Stack));
	if (!helpstack)
	{
		printf("alloction faild\n");
		exit(1);
	}
	initStack(helpstack);
	while (temp != NULL)
	{
		push(helpstack, temp->data);
		temp = temp->next;
	}
	temp = helpstack->head;
	while (temp != NULL)
	{
		printf("%c", temp->data);
		temp = temp->next;
	}
	free(helpstack);
}