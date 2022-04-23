#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Stack.h"
#include "Queue.h"
#define SIZE 100
void printQueue(Queue* q);
void printStack(Stack* s);

void main()
{
	int option = -1;
	while (option != 0)
	{
		printf("what would you want to check?\n");
		printf("1- stack\n");
		printf("2- queue\n");
		printf("0- exit\n");
		scanf(" %d", &option);
		switch (option)
		{
		case (0):
		{
			printf("\nyou chose to exit, bye\n");
			break;
		}
		case (1):// stack
		{
			int choice = -1;
			int i = 0;
			char string[SIZE];
			printf("enter a sentence\n");
			fseek(stdin, 0, SEEK_END);
			gets(string);
			int stringSize = strlen(string);
			char* sentence = (char*)malloc(sizeof(char) * stringSize + 1);
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
			while (sentence[i] != NULL)
			{
				push(s, sentence[i++]);
			}
			while (choice != 0)
			{
				printf("what would you want to do?\n");
				printf("1- flip between hashes\n");
				printf("2 - check if a string is palindrom\n");
				printf("3- rotate a stack\n");
				printf("0- exit\n");
				printf("enter your choice: \n");
				scanf(" %d", &choice);
				switch (choice)
				{
				case (0):// exit
				{
					printf("you chose to exit\n");
					destroyStack(s);
					free(sentence);
					break;
				}
				case (1):
				{
					flipBetweenHashes(sentence);
					printf("the new sentence is: \n");
					printStack(s);
					printf("\n");
					break;
				}
				case (2):
				{
					int res = isPalindrome(s);
					if (res)
						printf("the sentence is palindrom\n\n");
					else printf("the sentence is not palindrom\n\n");
				}
				break;
				case (3):
				{
					printf("enter a number: ");
					scanf(" %d", &i);
					rotateStack(s, i);
				}
				break;
				default:
					printf(" invalid selection, try again");
					break;
				}
			}
		}break;
		case (2):// queue
		{
			int num, size;
			unsigned int temp;
			Queue* q = (Queue*)malloc(sizeof(Queue));
			if (!q)
			{
				printf("allocation failed\n");
				exit(1);
			}
			initQueue(q);
			printf("how many numbers you whant in queue?\n");
			scanf(" %d", &size);
			printf("enter numbers to put in queue:\n");
			for (int i = 0; i < size; i++) // put into new queue
			{
				scanf("%u", &temp);
				enqueue(q, temp);
			}
			num = -1;
			while (num != 0)
			{
				printf("what you want to do next?\n");
				printf("1- rotate the queue\n");
				printf("2- cut and replace the queue\n");
				printf("3- order the queue\n");
				printf("0- exit\n");
				scanf(" %d", &num);
				switch (num)
				{
				case(1)://rotate queue
				{
					rotateQueue(q);
					printQueue(q);
				}break;
				case(2)://cutandreplace
				{
					cutAndReplace(q);
					printQueue(q);
				}break;
				case(3):// sortkidsfirst
				{
					sortKidsFirst(q);
					if (q->head == NULL)
						break;
					printQueue(q);
				}break;
				case(0)://exit
				{
					printf("you chose to exit\n");
					destroyQueue(q);
					break;
				}
				default:printf("try again\n");
					break;
				}

			}
		}break;
		default:
		{
			printf("choose again\n");
			break;
		}
		}
	}
}