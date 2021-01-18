#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tree;
typedef struct tree* Position;

struct stack;
typedef struct stack* Pos;

struct tree {
	char el[10];
	Position left;
	Position right;
};

struct stack {
	Position stablo;
	Pos next;
};

Position CreateNewTree();
Pos CreateNewStack();
int Push(Pos, Position);
Position Pop(Pos);
int ReadFile(Pos, Position);
int PrintInorder(Position);

int main() {
	struct stack head;
	Position root = NULL;

	head.next = NULL;
	int provjera = 0;

	provjera = ReadFile(&head, root);
	if (provjera != 0) {
		printf("Greska! provjera = %d\n", provjera);
	}

	PrintInorder(head.next->stablo);

	return 0;
}
int ReadFile(Pos p, Position s) {
	char* fileName = NULL, *buffer = NULL;
	FILE* dat = NULL;
	Position st = NULL;
	int  i = 0;

	fileName = (char *)malloc(30 * sizeof(char));
	if (fileName == NULL) return -2;

	buffer = (char *)malloc(30 * sizeof(char));
	if (buffer == NULL) return -2;

	printf("Upisi ime datoteke: ");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	dat = fopen(fileName, "r");
	if (dat == NULL) return -3;

	while (!feof(dat)) {
		memset(buffer, 0, 30);

		fscanf(dat, "%s", buffer);
		

		if (isdigit(buffer[0])) 
		{
			st = CreateNewTree();
			if (st == NULL) return -1;

			strcpy(st->el, buffer); 
			i = Push(p, st);
			if (i != 0) return -5;

		}
		else if (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/')
		{
			st = CreateNewTree();
			if (st == NULL) return -1;

			strcpy(st->el, buffer);
			st->right = Pop(p);
			st->left = Pop(p);

			i = Push(p, st);
		}
		else
			continue;
	}

	fclose(dat);
	free(fileName);
	free(buffer);

	return 0;
}

int PrintInorder(Position s) {
	if (s != NULL) {
		PrintInorder(s->left);
		printf(" %s ", s->el);
		PrintInorder(s->right);
	}
	return 0;
}

Position CreateNewTree() {
	Position q = NULL;
	q = (Position)malloc(sizeof(struct tree));
	if (q == NULL) return q;

	q->left = q->right = NULL;
	return q;
}

Pos CreateNewStack() {
	Pos q = NULL;
	q = (Pos)malloc(sizeof(struct stack));
	if (q == NULL) return q;

	q->next = q->stablo = NULL;
	return q;
}

int Push(Pos p, Position s) {
	if (p == NULL || s == NULL) return -6;

	Pos q = NULL;
	q = CreateNewStack();
	if (q == NULL) return -2;

	q->stablo = s;

	q->next = p->next;
	p->next = q;

	return 0;
}

Position Pop(Pos p) {
	if (p == NULL) return NULL;
	if (p->next == NULL) return NULL;

	Pos temp = NULL;
	Position stablo = NULL;

	temp = p->next;
	stablo = temp->stablo;

	p->next = temp->next;
	free(temp);
	return (stablo);
}

