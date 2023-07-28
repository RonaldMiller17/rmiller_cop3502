#include <stdio.h>
#include <stdlib.h>

static int countsAllocated = 0;

struct Node
{
	int value;
	struct Node* next;
};

void printList(struct Node* head)
{
	struct Node* tmp = head;
	while (tmp != NULL)
	{
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

struct Node* allocateNode(int value)
{
	struct Node* node = (struct Node *) malloc(sizeof(struct Node));
	node->value = value;
	node->next = NULL;
	countsAllocated++;
	return node;
}

void* freeList(struct Node** pHead)
{
	struct Node* tmp = *pHead;
	while (tmp != NULL)
	{
		*pHead = tmp->next;
		free(tmp);
		tmp = *pHead;
		countsAllocated--;
	}

	return *pHead;
}

struct Node* intersectionList(struct Node **ppNumbers1, struct Node **ppNumbers2)
{
	// ************************
	// Do not modify this part
	// ************************
	struct Node* pIntersectionList = NULL;

	// Modify this part to compute the intersection of 2 lists
	// You cannot allocate memory in this part of the code
	// that is: you cannot use malloc, or allocateNode

    struct Node* tmp1 = *ppNumbers1;
    struct Node* tmp2 = *ppNumbers2;
    struct Node* tail = pIntersectionList;

    while (tmp1 != NULL && tmp2 != NULL)
    {
        if (tmp1->value == tmp2->value)
        {
            tail = tmp1;
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
            tail->next = NULL;
            tail = tail->next;
        }
        else if (tmp1->value < tmp2->value)
        {
            tmp1 = tmp1->next;
        }
        else
        {
            tmp2 = tmp2->next;
        }
    }

	// ************************
	// Do not modify this part
	// ************************
	printf("List 1 after intersectionList:\n");
	printList(*ppNumbers1);
	printf("List 2 after intersectionList:\n");
	printList(*ppNumbers2);

	freeList(ppNumbers1);
	freeList(ppNumbers2);

	*ppNumbers1 = NULL;
	*ppNumbers2 = NULL;

	return (pIntersectionList);
}


void insert(struct Node** pHead, int value)
{
	struct Node* newNode = allocateNode(value);
	newNode->next = *pHead;
	*pHead = newNode;
}

int main(void)
{
	int i, numInputs;
	char* str;
	float average;
	int value;
	int index;
	int* numArray = NULL;
	int countOfNums1;
	int countOfNums2;
	struct Node* head1 = NULL;
	struct Node* head2 = NULL;
	struct Node* head3 = NULL;

	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		head1 = NULL;
		head2 = NULL;
		head3 = NULL;
		fscanf(inFile, " %d %d\n", &countOfNums1, &countOfNums2);
		for (i = 0; i < countOfNums1; i++)
		{
			fscanf(inFile," %d", &value);
			insert(&head1, value);
		}
		for (i = 0; i < countOfNums2; i++)
		{
			fscanf(inFile, " %d", &value);
			insert(&head2, value);
		}

		printf("List 1:\n");
		printList(head1);
		printf("List 2:\n");
		printList(head2);

		printf("Memory Allocated before intersection subset : %d\n", countsAllocated);
		head3 = intersectionList(&head1, &head2);
		printf("List 3:\n");
		printList(head3);

		freeList(&head3);
		printf("Memory Allocated after free : %d\n", countsAllocated);
	}

	fclose(inFile);
}