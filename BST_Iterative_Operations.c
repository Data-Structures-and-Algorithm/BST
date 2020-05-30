#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node {
   	struct Node *lchild;
   	int info;
   	struct Node *rchild;
} Node_t;   


Node_t *get_node(int x);
void display(Node_t *p, int level);
void preorder(Node_t *p);
void inorder(Node_t *p);
void postorder(Node_t *p);
void levelorder(Node_t *p);
int height(Node_t *p);
Node_t *search(Node_t *p, int info);
Node_t *delete(Node_t *root, int info);
Node_t *min(Node_t *p);
Node_t *max(Node_t *p);
Node_t *insert(Node_t *root, int info);



#define MAX 128U

Node_t *Queue[MAX];
size_t front, rear;
void Queue_Init(void);
int isEmpty(void);
int isFull(void);
int size(void);
int peek(Node_t *node);
void enqueue(Node_t *node);
Node_t *dequeue(void);



int main(int argc, char *argv[]) 
{
	(void)argc;
	(void)argv;


	Node_t *root = NULL;

	Queue_Init();

	while (true) {
		int choice;
		printf("1. Display\n2. Search\n3. Min\n4. Max\n"
			   "5. Insert\n6. Delete\n7. Exit\n"
			   "Enter your choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				display(root, 0);
				break;
			case 2: {
				int key;
				printf("\nEnter the search key: ");
				scanf("%d", &key);
				if (search(root, key)) {
					printf("\n%d is present", key);
				} else {
					printf("\n%d not found", key);
				}
				break;
			}
			case 3:
				printf("\nMinimum = %d", min(root)->info);
				break;
			case 4:
				printf("\nMaximum = %d", max(root)->info);
				break;
			case 5: {
				int info;
				printf("\nEnter the element to be inserted: ");
				scanf("%d", &info);
				root = insert(root, info);
				break;
			}
			case 6: {
				int info;
				printf("\nEnter the element to be deleted: ");
				scanf("%d", &info);
				root = delete(root, info);
				break;
			}
			case 7:
				exit(0);
			default:
				printf("\nInvalid choice...\n");
		}

		printf("\nPress any key to continue...");

		getchar();

		while (getchar() != '\n');

		system("clear");

	}

	printf("\n");

	return 0;


}



void Queue_Init(void)
{
    front = rear = 0;
}



int isEmpty(void)
{
    return (front == rear);

}



int isFull(void)
{
    return ((rear + 1) % MAX == front);

}



int size(void)
{
    return ((MAX + (rear - front)) % MAX);
}



int peek(Node_t *node)
{
    (void)node;

    if (isEmpty()) {
        return -1;
    }

    node = Queue[front];
    return 0;
}



void enqueue(Node_t *node)
{
    if (isFull()) {
        return;
    }

    Queue[rear] = node;

    rear = (rear + 1) % MAX;
}



Node_t *dequeue(void)
{
    Node_t *node;

    if (isEmpty()) {
        return NULL;
    }

    node = Queue[front];

    front = (front + 1) % MAX;

    return node;
}





Node_t *get_node(int x)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));

	if (node == NULL) {
		printf("Memory Allocation failed...");
		exit(1);
	}

	node->lchild = NULL;
	node->info = x;
	node->rchild = NULL;

	return node;
}



void display(Node_t *p, int level)
{
	if (p == NULL) {
		return;
	}

	display(p->rchild, level + 1);

	printf("\n");

	for (int i = 0; i < level; i++) {
		printf("  ");
	}

	printf("%d", p->info);


	display(p->lchild, level + 1);
}



void preorder(Node_t *p)
{
	if (p == NULL) {
		return;
	}

	printf("%d --> ", p->info);
	preorder(p->lchild);
	preorder(p->rchild);

}



void inorder(Node_t *p)
{
	if (p == NULL) {
		return;
	}

	inorder(p->lchild);
	printf("%d --> ", p->info);
	inorder(p->rchild);

}



void postorder(Node_t *p)
{
	if (p == NULL) {
		return;
	}

	postorder(p->lchild);
	postorder(p->rchild);
	printf("%d --> ", p->info);
}



void levelorder(Node_t *p)
{
	if (p == NULL) {
		printf("Tree is empty\n");
		return;
	}

	enqueue(p);

	Node_t *temp;

	while (!isEmpty()) {
		temp = dequeue();
		printf("%d --> ", temp->info);
		if (temp->lchild != NULL) {
			enqueue(temp->lchild);
		}
		if (temp->rchild != NULL) {
			enqueue(temp->rchild);
		}
	}

}



int height(Node_t *p)
{
	if (p == NULL) {
		return 0;
	}

	int hl = height(p->lchild); 
	int hr = height(p->rchild);

	return 1 + ((hl > hr) ? hl : hr);

}




Node_t *search(Node_t *p, int info)
{
	while (p) {
		if (p->info == info) {
			return p;
		} else if (info > p->info) {
			p = p->rchild;
		} else {
			p = p->lchild;
		}
		
	}

	return NULL;
}



Node_t *delete(Node_t *root, int info)
{
	Node_t *del_node 		= root;
	Node_t *del_node_parent	= NULL;
	Node_t *del_node_child	= NULL;
	

	while ((del_node!= NULL) && (info != del_node->info)) {
		del_node_parent = del_node;
		if (info > del_node->info) {
			del_node = del_node->rchild;
		} else {
			del_node = del_node->lchild;
		}
	}

	if (del_node == NULL) {
		printf("Node not found...\n");
		return root;
	}

	if ((del_node->lchild != NULL) && (del_node->rchild != NULL)) {
		
		Node_t *inorder_succesor = del_node->rchild;

		Node_t *inorder_succesor_parent = del_node;

		while (inorder_succesor->lchild) {
			inorder_succesor_parent = inorder_succesor;
			inorder_succesor = inorder_succesor->lchild;
		}
		
		del_node->info = inorder_succesor->info;

		del_node = inorder_succesor;

		del_node_parent = inorder_succesor_parent;

	} 

	//Preorder successor has only one child
	//It can be deleted using case A or B
	
	if (del_node->lchild != NULL) {
		del_node_child = del_node->lchild;
	} else {
		del_node_child = del_node->rchild;
	}


	if (del_node_parent == NULL) {
		root = del_node_child;
	} else if (del_node == del_node_parent->lchild) {
		del_node_parent->lchild = del_node_child;
	} else {
		del_node_parent->rchild = del_node_child;
	}

	free(del_node);
	return root;
}




Node_t *min(Node_t *p)
{
	if (p == NULL) {
		return NULL;
	}

	while (p->lchild) {
		p = p->lchild;
	}

	return p;
}




Node_t *max(Node_t *p)
{
	if (p == NULL) {
		return NULL;
	}

	while (p->rchild) {
		p = p->rchild;
	}

	return p;

}



Node_t *insert(Node_t *root, int info)
{
	Node_t *temp = get_node(info);

	Node_t *current = root;

	Node_t *parent = NULL;



	while (current) {
		
		parent = current;

		if (info > current->info) {
			current = current->rchild;
		} else if (info < current->info) {
			current = current->lchild;
		} else {
			printf("Duplicate entry not allowed...\n");
			return root;
		}
	}

	if (parent == NULL) {
		root = temp;
	} else if (info > parent-> info) {
		parent->rchild = temp;
	} else {
		parent->lchild = temp;
	}

	return root;
}































