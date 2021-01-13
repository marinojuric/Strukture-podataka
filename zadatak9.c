#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct stablo;
typedef struct stablo* Position;
struct stablo {
	int element;
	Position left;
	Position right;
};

Position addElement(int, Position);
Position printTree(Position);
Position findMax(Position);
Position findMin(Position);
Position findElement(int, Position);
Position deleteElement(int, Position);

int main()
{
	Position root = NULL, x = NULL;
	int a, el;

	do {
		printf("\n\n1 - Add new element \n");
		printf("2 - Display the tree\n");
		printf("3 - Search element\n");
		printf("4 - Delete element\n");
		printf("0 - Exit\n");

		printf("\n Enter your choice: \n");
		scanf(" %d", &a);

		switch (a)
		{
		case 1:
			printf("\nAdd new element: \n");
			scanf(" %d", &el);
			root = addElement(el, root);
			if (root == NULL) printf("Mistake.\n");
			break;

		case 2:
			x = printTree(root);
			if(x==NULL) printf("The tree is empty.\n");
			break;

		case 3:
			printf("\nSearch element: \n");
			scanf(" %d", &el);
			x = findElement(el, root);
			if (x == NULL) printf("Element does not exist.\n");
			else printf("Element %d is found.\n", x->element);
			break;

		case 4:
			printf("\nPick the element you want to delete: \n");
			scanf(" %d", &el);
			root = deleteElement(el, root);
			if (root == NULL) printf("Mistake.\n");
			break;

		case 0:
			printf("\n Exit. \n");
			break;

		default:
			printf("\nWrong! Try again.\n");
		}

	} while (a != 0);

}

Position addElement(int x, Position P)
{
	if (P == NULL)
	{
		P = (Position)malloc(sizeof(struct stablo));
		if (P == NULL) return NULL;
		P->element = x;
		P->left = P->right = NULL;
	}

	else if (x < P->element)
		P->left = addElement(x, P->left);		//opcenito pokusaj ne koristit rekurzije

	else if (x > P->element)
		P->right = addElement(x, P->right);

	else
		printf("Element already exists. \n");

	return P;
}
Position printTree( Position P)				//inorder
{
	if (NULL == P)
		return P;

	printTree(P ->left);
	printf("%d ", P ->element);					//ako je ovo prvo preorder
	printTree(P ->right);					//ako je zamijenjeno right i left onda je postorder

	return P;
}

Position findMin(Position P)
{
	if (P != NULL)
	{
		if (P->left != NULL)
		{
			while (P->left != NULL)
				P = P->left;
		}
	}

	return P;
}

Position findMax(Position P)
{
	if (P != NULL)
	{
		if (P->right != NULL)
		{
			while (P->right != NULL)
				P = P->right;
		}
	}

	return P;
}

Position findElement(int x, Position P)
{
	if (P == NULL) return NULL;

	if (x < P->element)
		return findElement(x, P->left);
	else if (x > P->element)
		return findElement(x, P->right);
	else
		return P;
}

Position deleteElement(int x, Position P)
{
	Position tmp = NULL;

	if (P != NULL)
	{
		if (x < P->element)
			P->left = deleteElement(x, P->left);
		else if (x > P->element)
			P->right = deleteElement(x, P->right);
		else
		{
			if (P->right != NULL && P->left != NULL) //ima dvoje djece
			{
				tmp = findMin(P->right);
				P->element = tmp->element;

				P->right = deleteElement(tmp->element, P->right);
			}
			else
			{
				tmp = P;

				if (P->left != NULL)
					P = P->right;
				else
					P = P->left;
				free(tmp);
			}
		}
	}
	return P;
}
