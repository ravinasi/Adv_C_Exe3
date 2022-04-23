#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Stack.h"
#include "Queue.h"
#define SIZE 100
void printQueue(Queue* q);

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
			printf("enter your choice: ");
			scanf("%d", &choice);
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
				scanf("%d", &i);
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
		}
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
		}
		default:
		{
			printf("choose again\n");
			break;
		}
		}
	}
}