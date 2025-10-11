//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

ListNode	*findNodeAndInitConnection(LinkedList *ll, int index);
int			insertExistingNode(LinkedList *ll, int index, ListNode *node);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
			case 1:
				printf("Input an integer that you want to add to the linked list 1: ");
				scanf("%d", &i);
				j = insertNode(&ll1, ll1.size, i);
				printf("Linked list 1: ");
				printList(&ll1);
				break;
			case 2:
				printf("Input an integer that you want to add to the linked list 2: ");
				scanf("%d", &i);
				j = insertNode(&ll2, ll2.size, i);
				printf("Linked list 2: ");
				printList(&ll2);
				break;
			case 3:
				printf("The resulting linked lists after merging the given linked list are:\n");
				alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
				printf("The resulting linked list 1: ");
				printList(&ll1);
				printf("The resulting linked list 2: ");
				printList(&ll2);
				removeAllItems(&ll1);
				removeAllItems(&ll2);
				break;
			case 0:
				removeAllItems(&ll1);
				removeAllItems(&ll2);
				break;
			default:
				printf("Choice unknown;\n");
				break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

ListNode	*findNodeAndInitConnection(LinkedList *ll, int index)
{
	ListNode	*cur;
	ListNode	*pre;

	if (ll == NULL || ll->head == NULL || index < 0 || index >= ll->size)
		return (NULL);
	
	cur = ll->head;
	// head 재조정 필요
	if (index == 0) 
	{
		pre = NULL;
		if (ll->size == 1)
			ll->head = NULL;
		else
			ll->head = cur->next;
	}

	while (index > 0)
	{
		pre = cur;
		cur = cur->next;
		if (cur == NULL)
			return (NULL);
		index--;
	}

	// 다음 노드 연결 
	if (pre != NULL)
		pre->next = cur->next;

	cur->next = NULL;
	ll->size--;

	return (cur);
}

int			insertExistingNode(LinkedList *ll, int index, ListNode *node)
{
	// 2번 문제에서만 의미있는 함수로 작성, head pointer가 바뀔 일이 없으니 관련해서 고려 X
	ListNode	*pre;
	ListNode	*cur;

	if (ll == NULL || node == NULL || index < 0 || index > ll->size + 1)
		return (-1);
	
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next; 
		pre->next = node;
		node->next = cur;
		ll->size++;
		return (0);
	}
	
	return (-1);
}


void 		alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	// linked list1의 alternate position(사이사이)에 list 2의 원소 넣기
		// 즉, ll2의 idx번째 원소는 ll1의 idx번째 원소 뒤에 들어감 
		// ll1.size >= ll2 -> ll2 원소 다 들어감 
	
	// 뒤에서부터 추가하면 삽입함으로써 생기는 idx 흐트러짐이 사라지지 않을까?
	// 있는 노드 재활용? 아니면 해제 -> 새로 할당?? 

	// get insert starting point
	int			idx;
	ListNode	*tmp;

	if (ll1->size == 0)
		return ;
	
	if (ll1->size >= ll2->size)
		idx = ll2->size - 1;
	else
		idx = ll1->size - 1;
	

	// merge start ! 
	while (idx >= 0)
	{
		tmp = findNodeAndInitConnection(ll2, idx);
		if (tmp == NULL)
			return ;
		if (insertExistingNode(ll1, idx + 1, tmp) == -1)
		{
			free (tmp); //삽입 실패시 유실 노드 해제
			return ;
		}
		idx--;
	}

}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
