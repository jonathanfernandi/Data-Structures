#include <stdio.h>
#include <stdlib.h>

int n;

struct Node
{
	int data, height;
	Node *left, *right;
} *root;

Node *createNode(int data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->height = 1;
	
	return newNode;
}

int max(int left, int right)
{
	if(left >= right)
	{
		return left;
	}
	else
	{
		return right;
	}
}

int height(Node *curr)
{
	if(!curr)
	{
		return 0;
	}
	else
	{
		return (1 + max(height(curr->left), height(curr->right)));
	}
}

int balance(Node *curr)
{
	if(!curr)
	{
		return 0;
	}
	else
	{
		return (height(curr->left) - height(curr->right));
	}
}

Node *rightRotate(Node *curr)
{
	Node *leftChild = curr->left;
	Node *leftChildRight = leftChild->right;
	
	leftChild->right = curr;
	curr->left = leftChildRight;
	
	leftChild->height = height(leftChild);
	curr->height = height(curr);
	
	return leftChild;
}

Node *leftRotate(Node *curr)
{
	Node *rightChild = curr->right;
	Node *rightChildLeft = rightChild->left;
	
	rightChild->left = curr;
	curr->right = rightChildLeft;
	
	rightChild->height = height(rightChild);
	curr->height = height(curr);
	
	return rightChild;
}

Node *rebalance(Node *curr)
{
	curr->height = height(curr);
	int balanceValue = balance(curr);
	
	if(balanceValue > 1)
	{
		if(balance(curr->left) >= 0)
		{
			return rightRotate(curr);
		}
		else
		{
			curr->left = leftRotate(curr->left);
			return rightRotate(curr);
		}
	}
	else if(balanceValue < -1)
	{
		if(balance(curr->right) <= 0)
		{
			return leftRotate(curr);
		}
		else
		{
			curr->right = rightRotate(curr->right);
			return leftRotate(curr);
		}
	}
	else
	{
		return curr;
	}
}

Node *insert(Node *curr, Node *newNode)
{
	if(!curr)
	{
		n++;
		return newNode;
	}
	else{
		if(curr->data > newNode->data)
		{
			curr->left = insert(curr->left, newNode);
		}
		else if(curr->data < newNode->data)
		{
			curr->right = insert(curr->right, newNode);
		}
		
		return rebalance(curr);
	}
}

int countDelete;
Node *Delete(Node *curr, int key)
{
	if(!curr)
	{
		puts("Data not found");
		return curr;
	}
	else if(curr->data > key)
	{
		curr->left = Delete(curr->left, key);
	}
	else if(curr->data < key)
	{
		curr->right = Delete(curr->right, key);
	}
	else
	{
		if(!curr->left || !curr->right)
		{
			Node *temp;
			if(curr->left)
			{
				temp = curr->left;
			}
			else
			{
				temp = curr->right;
			}
			
			if(!temp)
			{
				temp = curr;
				curr = NULL;
			}
			else
			{
				*curr = *temp;
			}
			
			free(temp);
		}
		else
		{
			Node *temp = curr->left;
			
			while(temp->right)
			{
				temp = temp->right;
			}
			
			curr->data = temp->data;
			curr->left = Delete(curr->left, temp->data);
		}
		countDelete++;
		
		if(countDelete == 1)
		{
			n--;
		
			puts("Data Found");
		}
		
		if(!curr)
		{
			return NULL;
		}
		else
		{
			return rebalance(curr);
		}
	}
}

int countPrint;
void preorder(Node *curr)
{
	if(!curr)
	{
		return;
	}
	else
	{
		countPrint++;
		if(countPrint < n)
		{
			printf("%d ", curr->data);
		}
		else
		{
			printf("%d", curr->data);
		}
		preorder(curr->left);
		preorder(curr->right);
	}
}

void inorder(Node *curr)
{
	if(!curr)
	{
		return;
	}
	else
	{
		inorder(curr->left);
		countPrint++;
		if(countPrint < n)
		{
			printf("%d ", curr->data);
		}
		else
		{
			printf("%d", curr->data);
		}
		inorder(curr->right);
	}
}

void postorder(Node *curr)
{
	if(!curr)
	{
		return;
	}
	else
	{
		postorder(curr->left);
		postorder(curr->right);
		countPrint++;
		if(countPrint < n)
		{
			printf("%d ", curr->data);
		}
		else
		{
			printf("%d", curr->data);
		}
	}
}

int main()
{
	int program = 1;
	while(program)
	{
		int menu;
		puts("1. Insertion");
		puts("2. Deletion");
		puts("3. Traversal");
		puts("4. Exit");
		
		do
		{
			printf("Choose: ");
			scanf("%d", &menu);
			getchar();
		}
		while((menu < 1) || (menu > 4));
		
		switch(menu)
		{
			case 1:
			{
				int data;
				printf("Insert: ");
				
				scanf("%d", &data);
				getchar();
				
				root = insert(root, createNode(data));
				
				puts("");
				
				break;
			}
			
			case 2:
			{
				int key;
				printf("Delete: ");
				
				scanf("%d", &key);
				getchar();
				
				countDelete = 0;
				root = Delete(root, key);
				
				if(countDelete)
				{
					printf("Value %d was deleted\n", key);
				}
				
				puts("");
				
				break;
			}
			
			case 3:
			{
				countPrint = 0;
				printf("Preorder: ");
				preorder(root);
				puts("");
				
				countPrint = 0;
				printf("Inorder: ");
				inorder(root);
				puts("");
				
				countPrint = 0;
				printf("Postorder: ");
				postorder(root);
				puts("\n");
				
				break;				
			}
			
			case 4:
			{
				puts("Thank you");
				
				program--;
				
				break;
			}
		}
	}
	
	return 0;
}
