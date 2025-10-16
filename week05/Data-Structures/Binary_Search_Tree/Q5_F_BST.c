//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");
	printf("4: removeNode test\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		case 4:
			printf("Input an integer that you want to remove in the Binary Search Tree: ");
			scanf("%d", &i);
			root = removeNodeFromTree(root, i);
			postOrderIterativeS2(root);
			printf("\n");
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	/
	Stack		myStack;
	Stack		rootStack;
	BSTNode		*cur;
	BSTNode		*curRoot;

	if (!root)
		return ;

	myStack.top = NULL;
	rootStack.top = NULL;

	push(&rootStack, root);
	push(&myStack, root);
	cur = NULL;
	curRoot = NULL;
	
	while (cur || myStack.top)
	{
		cur = pop(&myStack);
		if (!cur)
			return ;

		curRoot = peek(&rootStack);
		if (curRoot && cur == curRoot)
		{
			pop(&rootStack);
			push(&myStack, cur);
			if (cur->right)
			{
				push(&rootStack, cur->right);
				push(&myStack, cur->right);
			}
			if (cur->left)
			{
				push(&rootStack, cur->left);
				push(&myStack, cur->left);
			}
		}
		else
		{
			printf("%d", cur->item);
			if (myStack.top)
				printf(", ");
			else
				printf(".");
			cur = NULL;
		}
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	BSTNode	*newRoot;
	BSTNode	*parent;

	if (!root)
		return (NULL);

	if (value < root->item)
	{
		root->left = removeNodeFromTree(root->left, value);
		return (root);
	}
	else if (value > root->item)
	{
		root->right = removeNodeFromTree(root->right, value);
		return (root);
	}
	else
	{
		if (!root->left && !root->right)
			newRoot = NULL;
		else if (root->left && !root->right)
			newRoot = root->left;
		else if (!root->left && root->right)
			newRoot = root->right;
		else // 오른쪽 서브트리에서 가장 작은 값 찾기(가장 작은 값 == 가장 왼쪽 값)
		{
			parent = root;
			newRoot = root->right;
			while (newRoot->left)
			{
				parent = newRoot;
				newRoot = newRoot->left; 
			}
			
			// 자신의 부모 연결 갱신 -> 새 루트노드의 오른쪽 자식이 없어도 괜찮.. 그러면 자동으로 NULL되면서 연결 끊어줌
			if (parent != root)
				parent->left = newRoot->right;
			
			// 원래 자신의 부모 자식들 상속
			newRoot->left = root->left;
			if (newRoot != root->right)
				newRoot->right = root->right;
		}
		free (root);
		root = NULL;
		return (newRoot);
	}
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
