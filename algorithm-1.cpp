#include <stdio.h>
#include <stdlib.h>

int n = 10;

struct Node
{
	int data, color;
	struct Node *parent, *left, *right;
} *root;

Node *createNode(int data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	newNode->data = data;
	newNode->parent = newNode->left = newNode->right = NULL;
	newNode->color = 1;
	
	return newNode;
}

Node *insert(Node *curr, Node *newNode)
{
	if(!curr)
	{
		return newNode;
	}
	else{
		if(newNode->data < curr->data)
		{
			curr->left = insert(curr->left, newNode);
			curr->left->parent = curr;
		}
		else if(newNode->data > curr->data)
		{
			curr->right = insert(curr->right, newNode);
			curr->right->parent = curr;
		}
		
		return curr;
	}
}

void leftRotate(Node *temp)
{
	Node *tempRight = temp->right;
	temp->right = tempRight->left;
	
	if(temp->right)
	{
		temp->right->parent = temp;
	}
	tempRight->parent = temp->parent;
	
	if(!temp->parent)
	{
		root = tempRight;
	}
	else if(temp == temp->parent->left)
	{
		temp->parent->left = tempRight;
	}
	else
	{
		temp->parent->right = tempRight;
	}
	tempRight->left = temp;
	temp->parent = tempRight;
}

void rightRotate(Node *temp)
{
	Node *tempLeft = temp->left;
	temp->left = tempLeft->right;
	
	if(temp->left)
	{
		temp->left->parent = temp;
	}
	tempLeft->parent = temp->parent;
	
	if(!temp->parent)
	{
		root = tempLeft;
	}
	else if(temp == temp->parent->left)
	{
		temp->parent->left = tempLeft;
	}
	else
	{
		temp->parent->right = tempLeft;
	}
	tempLeft->right = temp;
	temp->parent = tempLeft;
}

void fix(Node *curr)
{
	while((curr != root) && (curr->color && curr->parent->color))
	{
		Node *currParent = curr->parent, *currGrandparent = currParent->parent;
		
		if(currParent == currGrandparent->left)
		{
			Node *currUncle = currGrandparent->right;
			
			if(currUncle && currUncle->color)
			{
				(currGrandparent->color)++;
				(currParent->color)--;
				(currUncle->color)--;
				curr = currGrandparent;
			}
			else if(curr == currParent->right)
			{
				leftRotate(currParent);
				curr = currParent;
				currParent = curr->parent;
			}
			else
			{
				rightRotate(currGrandparent);
				int temp = currParent->color;
				currParent->color = currGrandparent->color;
				currGrandparent->color = temp;
				curr = currParent;
			}
		}
		else
		{
			Node *currUncle = currGrandparent->left;
			
			if(currUncle && currUncle->color)
			{
				(currGrandparent->color)++;
				(currParent->color)--;
				(currUncle->color)--;
				curr = currGrandparent;
			}
			else if(curr == currParent->left)
			{
				rightRotate(currParent);
				curr = currParent;
				currParent = curr->parent;
			}
			else
			{
				leftRotate(currGrandparent);
				int temp = currParent->color;
				currParent->color = currGrandparent->color;
				currGrandparent->color = temp;
				curr = currParent;
			}
		}
	}
}

int count;
void inorder(Node *curr)
{
	if(!curr)
	{
		return;
	}
	else
	{
		inorder(curr->left);
		count++;
		if(count < n)
		{
			printf("%d ", curr->data, curr->color);
		}
		else
		{
			printf("%d\n", curr->data, curr->color);
		}
		inorder(curr->right);
	}
}

int main()
{
	int data[n] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
	
	for(int i = 0; i < n; i++)
	{
		Node *temp = createNode(data[i]);
		
		root = insert (root, temp);
		
		fix(temp);
		root->color = 0;
	}
	
	count = 0;
	puts("Inorder Traversal of Created Tree");
	inorder(root);
	
	return 0;
}
