#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

// Sean Szumlanski
// COP 3502, Spring 2018

#define EMPTY_LIST_ERR INT_MIN
#define EMPTY_QUEUE_ERR INT_MIN

typedef struct nodemain
{
	int data;
	struct nodemain *next;
} nodemain;

typedef struct LinkedList
{
	nodemain *head;
	nodemain *tail;
} LinkedList;

typedef struct Queue
{
	LinkedList *list;
	int size;
} Queue;

nodemain *create_node2(int data)
{
	nodemain *n = malloc(sizeof(nodemain));
	n->data = data;
	n->next = NULL;
	return n;
}

LinkedList *create_list(void)
{
	return calloc(1, sizeof(LinkedList));
}

nodemain *recursive_destroyer(nodemain *head)
{
	if (head == NULL)
		return NULL;

	recursive_destroyer(head->next);
	free(head);

	return NULL;
}

LinkedList *destroy_list(LinkedList *list)
{
	if (list == NULL)
		return NULL;

	recursive_destroyer(list->head);
	free(list);

	return NULL;
}

void tail_insert(LinkedList *list, int data)
{
	if (list == NULL)
		return;

	if (list->tail == NULL)
	{
		list->head = list->tail = create_node2(data);
		return;
	}

	list->tail->next = create_node2(data);
	list->tail = list->tail->next;
}

int head_delete(LinkedList *list)
{
	int retval;
	nodemain *temp;

	if (list == NULL || list->head == NULL)
		return EMPTY_LIST_ERR;

	retval = list->head->data;

	temp = list->head->next;

	free (list->head);

	list->head = temp;

	if (list->head == NULL)
		list->tail = NULL;

	return retval;
}
	// Create the queue. Initialize its internal linked list.
Queue *create_queue(void)
{
	Queue *q = malloc(sizeof(Queue));
	q->list = create_list();
	q->size = 0;
	return q;
}


int isEmpty(Queue *q)
{
	return (q == NULL || q->size == 0);
}

// When using linked lists, we might (naively?) assume there is always room for more.
int isFull(Queue *q)
{
	return 0;
}

// Insert element at back of queue (using tail insertion).
void enqueue(Queue *q, int data)
{
	if (q == NULL || q->list == NULL)
		return;

	q->size++;
	tail_insert(q->list, data);
}

// Remove front of queue (using head removal).
int dequeue(Queue *q)
{
	if (isEmpty(q))
		return EMPTY_QUEUE_ERR;

	q->size--;
	return head_delete(q->list);
}

// Peek at the front of the queue without dequeueing.
int peek(Queue *q)
{
	if (isEmpty(q))
		return EMPTY_QUEUE_ERR;

	return q->list->head->data;
}

// This is acting as an alias for peek(). This is slightly slower than just
// having all of peek's code in this function, but it frees us from having to
// maintain and update two different copies of the exact same code.
int front(Queue *q)
{
	return peek(q);
}

//------------------------------------------------------------------------------
//END OF COPIED CODE

int isReflection(node *a, node *b)
{
  //Base case if both node are null
  if (a == NULL && b == NULL)
  {
    return 1;
  }

  //Checks if either node is NULL which mean its not similar
  if(a == NULL || b == NULL)
  {
    return 0;
  }

  //Check if data is the same
  if(a -> data != b -> data)
  {
    return 0;
  }

  //Iterates through both side of the binary tree
  return isReflection(a -> left, b -> right) && isReflection(a -> right, b -> left);

}


node *makeReflection(node *root)
{
  if (root == NULL)
     return NULL;
  else {

		//New node for each node of new binary tree 
    node *newNode = malloc (sizeof(node));

		//Reflects binary tree making the left, right and the right, left
    newNode->data = root->data;
    newNode->left = makeReflection(root->right);
    newNode->right = makeReflection(root->left);

    return newNode;
  }
}

//taken from BST notes USING ONE QUEUE
Queue *preorder_recursive(Queue *q, node *root)
{
	if (root == NULL)
		return q;

	enqueue(q, root -> data);
	preorder_recursive(q, root->left);
	preorder_recursive(q, root->right);
}

//taken from BST notes
int postorder_recursive(Queue *q, node *root)
{
	if (root == NULL)
		return 0;


	postorder_recursive(q, root->left);
	postorder_recursive(q, root->right);
	//printf("%d ", root->data);
	if (root -> data == dequeue(q))
	{
		return 1;
	}else{
		return 0;
	}

}



int kindredSpirits(node *a, node *b)
{
	//NULL check
  if (a == NULL && b == NULL)
  {
    return 1;
  }

	//Integers determine wether or not KindredSpirits
  int i;
  int k;

	//Creation of Queue to be used in later functions
  Queue *pre = create_queue();

	//Stores binary tree a in the queue in a preorder way
	preorder_recursive(pre, a);

	//Compairs binary tree b to the queue in a postorder way
	i = postorder_recursive(pre, b);

	//clears queue
  free(pre);
  pre = create_queue();

	//Vice Versa
  preorder_recursive(pre, b);
  k = postorder_recursive(pre, a);

	//Satatment returns 1 if either i or k is 1, returns 0 if both 0
  return (i || k);

}

double difficultyRating(void)
{
  return 2.0;
}

double hoursSpent(void)
{
  return 14.0;
}
