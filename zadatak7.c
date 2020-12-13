#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct stog;
typedef struct stog* Pozicija;
struct stog {
	int element;
	Pozicija next;
};

int push(int, Pozicija);
int pop(Pozicija);
int citaj(Pozicija);
int kalkulator(int, int, int*, char);

int main()
{
	struct stog head;
	head.next = NULL;

	citaj(&head);

	printf("Rezultat je %d\n", head.next->element);

	return 0;
}

int push(int x, Pozicija P)
{
	if (P == NULL) return -1;

	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(struct stog));
	if (q == NULL) return -2;
	q->next = NULL;

	q->element = x;

	q->next = P->next;
	P->next = q;

	return 0;
}

int pop(Pozicija P)
{
	Pozicija temp = NULL;

	int x;

	temp = P->next;
	x = temp->element;

	P->next = temp->next;
	free(temp);

	return x;
}

int citaj(Pozicija P)
{
	char* ime = NULL, *stack = NULL;
	FILE* fp = NULL;
	int operand1, operand2, rez;

	ime = (char*)malloc(20 * sizeof(char));
	if (ime == NULL) return -1;

	stack = (char*)malloc(40 * sizeof(char));
	if (stack == NULL) return -1;

	printf("Upisi ime datoteke:\n");
	scanf(" %s", ime);

	if (strchr(ime, '.') == NULL) strcat(ime, ".txt");

	fp = fopen(ime, "r");
	if (fp == NULL) return -3;

	while (!feof(fp))
	{
		memset(stack, 0, 30);

		fscanf(fp, " %s", stack);

		if (isdigit(stack[0]))
		{
			sscanf(stack, "%d", &rez); //vraca 1 ako je upisan uspjesno 1 element, obavezno nauci koristit
			push(rez, P);
		}
		else if (stack[0] == '+' || stack[0] == '-' || stack[0] == '*' || stack[0] == '/')
		{
			operand2 = pop(P);
			operand1 = pop(P);
			kalkulator(operand1, operand2, &rez, stack[0]);
			push(rez, P);
		}
		else return -7;
	}

	fclose(fp);
	free(ime);

	return 0;
}

int kalkulator(int x, int y, int* rez, char c)
{
	switch (c) {
	case '+':
		*rez = x + y;
		break;
	case '-':
		*rez = x - y;
		break;
	case '*':
		*rez = x * y;
		break;
	case '/':
		if (y == 0)
		{
			printf("Dijeljenje s nulom!\n");
			return -3;
		}
		else
			*rez = x / y;
		break;
	default:
		printf("Greska!!\n");
		return -4;
	}

	return 0;
}