#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	const char *piplineType;
	struct _node *next;
} Node;

typedef struct _linkedList {
	Node *head;
	Node *tail;
	Node *before;
	Node *current;
	int nodeCreateCount;
} List;

void Linkedinit(List **plist) {
	(*plist) = (List*)malloc(sizeof(List));
	(*plist)->head = NULL;
	(*plist)->current = NULL;
	(*plist)->before = NULL;
	(*plist)->tail = NULL;
}

void LinkedInsert(List *plist, const char *piplineType) {
	Node* newnode = (Node*)malloc(sizeof(Node));

	newnode->piplineType = piplineType;

	if (plist->head == NULL) {
		plist->before = plist->head;
		plist->current = newnode;
		newnode->next = plist->tail;
		plist->head = newnode;
	}
	else {
		plist->before = plist->current;
		plist->current = newnode;
		plist->before->next = plist->current;
		newnode->next = plist->tail;
	}

}

void display(List *plist) {
	plist->current = plist->head;
	while (plist->current != NULL)
	{
		printf("%s  ", plist->current->piplineType);
		plist->current = plist->current->next;
	}
	printf("\n\n");
}

int LinkedListSearchProc(List *plist, char **pipline) {
	plist->current = plist->head;
	int pipcount = 0;
	while (plist->current->next != NULL)
	{
		if (plist->current->piplineType == pipline)
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			pipcount++;
		}
		else
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			continue;
		}
	}
	if (pipcount == 0) {
		printf("찾으시는 모양의 배관이 없습니다.\n\n");
	}
	else {
		printf("찾으시는 모양의 배관이 %d개 있습니다.\n\n", pipcount);
	}
	return 0;
}

int pipRuleCheck(List *plist) {
	plist->current = plist->head;
	int count = 1;

	while (plist->current->next != NULL)
	{
		if (plist->current->piplineType == "━" && plist->current->next->piplineType == "┃")
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			count++;
			continue;
		}
		else if (plist->current->piplineType == "━" && plist->current->next->piplineType == "┓")
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			count++;
			continue;
		}
		else if (plist->current->piplineType == "┓" && plist->current->next->piplineType == "┃")
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			count++;
			continue;
		}
		else if (plist->current->piplineType == "┃" && plist->current->next->piplineType == "┗")
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			count++;
			continue;
		}
		else if (plist->current->piplineType == "┗" && plist->current->next->piplineType == "━")
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			count++;
			continue;
		}
		else if (plist->current->piplineType == "┃" && plist->current->next->piplineType == "┃")
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			count++;
			continue;
		}
		else if (plist->current->piplineType == "━" && plist->current->next->piplineType == "━")
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			count++;
			continue;
		}
		else
		{
			plist->before = plist->current;
			plist->current = plist->current->next;
			continue;
		}
	}
	return count;
}

int main()
{
	List *link = NULL;
	int select;

	Linkedinit(&link);

	printf("배관 10개 입력 : 1. ━ 2. ┃ 3.┛ 4. ┓ 5. ┗ \n");
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &select);

		switch (select) {
		case 1:
			LinkedInsert(link, "━");
			break;
		case 2:
			LinkedInsert(link, "┃");
			break;
		case 3:
			LinkedInsert(link, "┛");
			break;
		case 4:
			LinkedInsert(link, "┓");
			break;
		case 5:
			LinkedInsert(link, "┗");
			break;
		}
	}
	display(link);


	printf("검색할 배관 입력 : 1. ━ 2. ┃ 3.┛ 4. ┓ 5. ┗ \n");
	scanf("%d", &select);
	switch (select) {
	case 1:
		LinkedListSearchProc(link, "━");
		break;
	case 2:
		LinkedListSearchProc(link, "┃");
		break;
	case 3:
		LinkedListSearchProc(link, "┛");
		break;
	case 4:
		LinkedListSearchProc(link, "┓");
		break;
	case 5:
		LinkedListSearchProc(link, "┗");
		break;
	}

	if (pipRuleCheck(link) == 10)
	{
		printf("승인\n");
	}
	else
	{
		printf("미승인\n");
	}
}