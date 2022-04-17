#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Stack.h"
#include "Queue.h"
#define SIZE 100

void main()
{
	int choice;
	char string[SIZE];
	printf("enter a sentence\n");
	gets(string);
	int stringSize = strlen(string);
	char* sentence = (char*)malloc(sizeof(char)* stringSize + 1);
	if (!sentence)
	{
		printf("allocation faild");
		exit(1);
	}
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if (!s)
	{
		printf("allocation failed");
		exit(1);
	}
	initStack(s);
	strcpy(sentence, string);
	printf("what would you want to do?\n");
	printf("1- flip between hashes\n");
	printf("2 - check if a string is palindrom\n");
	printf("3- rotate a stack\n");
	printf("4 - exit\n");
	printf("enter your choice: ");
	scanf(" %d", &choice);
	while (choice != 4)
	{
		switch (choice)
		{
		case (1):
			flipBetweenHashes(sentence);
		break;
		case (2):
		{
			int i = 0;
			while (sentence[i] != NULL)
			{
				push(s, sentence[i++]);
			}
			int res = isPalindrome(s);
			if (res)
				printf("the sentence is palindrom\n");
			else printf("the sentence is not palindrom\n");
		}
		break;
		case (3):
		{
			int i = 0;
			while (sentence)
			{
				push(s, sentence[i]);
			}
			Stack* temp = s;
			printf("enter a number: ");
			scanf(" %d", &i);
			rotateStack(s, i);
			printf("the new sentence is: ");
			while (temp != NULL)
			{
				printf("%c", temp->head->data);
				temp->head = temp->head->next;
			}
		}
		break;
		default:
			printf(" invalid selection, try again");
		break;
		}
		scanf(" %d", &choice);
	}
	printf("you chose to exit");
	destroyStack(s);
}