#include <stdio.h>
#include "Stack.h"

Stack* intervesionWord(Stack* s);
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
	int i=0, hashAmount = 0;	
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
	Stack* temp = tempstack;
	while (temp->head != NULL)// flip and count hashes
	{
		push(s, temp->head->data);
		if (temp->head->data == '#')
			hashAmount++;
		temp->head = temp->head->next;
	}
	destroyStack(tempstack);
	if (hashAmount % 2 == 1) // odd number of hashes
	{
		printf("odd number of hashes");
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
			s->head = s->head->next;
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
		s->head = s->head->next;
	}
	while (newstack->head != NULL)
	{
		printf("%c", newstack->head->data);
		newstack->head = newstack->head->next;
	}
	free(newstack);
	return s->head->next;
}

int isPalindrome(Stack* s)
{
	// לבדוק 5 ו-6
	// המחסנית המקורית נמחקת
	
	if (s->head == NULL)// empty stack
		return 1;
	Stack* smallstack = (Stack*)malloc(sizeof(Stack));
	if (!smallstack)
	{
		printf("allocation error");
		return;
	}
	initStack(smallstack);
	int count = 0;
	/*Stack** temp1 = &s;
	(*temp1)->head = (*temp1)->head->next;*/
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	if (!temp)
	{
		printf("allocation error");
		return;
	}
	initStack(temp);
	while (s->head != NULL)// check stack size
	{
		count++;
		push(temp, pop(s));
	}
	if (count == 1)// if there is one char in the sentence
		return 1;
	for (int i = 0; i < count/2; i++)// push into small stack
	{
		push(smallstack, temp->head->data);
		push(s, temp->head->data);
		pop(temp);
	}
	if (count % 2 == 1) // odd size of stack
	{
		pop(temp);
		push(s, temp->head->data);
	}
	for (int i = 0; i < count/2; i++)// equal test between the stacks
	{
		if (smallstack->head->data != temp->head->data)
			return 0;
		push(s, temp->head->data);
		pop(temp);
		pop(smallstack);
	}
	free(smallstack);
	free(temp);
	return 1;
}

void rotateStack(Stack* s, int n)
{
	//לבדוק על 5 ו-6
	if (n <= 0)// if n is negetiv
	{
		printf("can't rotate - negetiv number");
		return;
	}
	Stack* temp;
	int size = 0;
	temp = s;
	while (temp != NULL)// check stack size
		size++;
	if (n >= size)
		return;
	Stack* helpStack = (Stack*)malloc(sizeof(Stack));
	if (!helpStack)
	{
		printf("allocation error");
		return;
	}
	Stack* Newstack = (Stack*)malloc(sizeof(Stack));
	if (!Newstack)
	{
		printf("allocation error");
		return;
	}
	for (int i = 0; i < size - n; i++)// קידום לאיבר
	{
		push(helpStack, s->head->data);
		pop(s);
		s->head = s->head->next;
	}
	for (int i = 0; i < n; i++)// push to newstack
	{
		push(Newstack, s->head->data);
		pop(s);
		s->head = s->head->next;
	}	
	while (helpStack != NULL)
	{
		push(s, helpStack->head->data);
		pop(helpStack);
		helpStack->head = helpStack->head->next;
	}
	while (Newstack != NULL)
	{
		push(s, Newstack->head->data);
		pop(Newstack);
		Newstack->head = Newstack->head->next;
	}
}