#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct lista;
typedef struct lista* Lista;
struct lista {
	int broj;
	Lista next;
};

int Unos(Lista);
int Ispis(Lista);
int Uniraj(Lista, Lista, Lista);
int Presjeci(Lista, Lista, Lista);

int main()
{
	struct lista prva, druga, unija, presjek;
	prva.next = NULL;
	druga.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;

	Unos(&prva);
	Unos(&druga);

	Ispis(prva.next);
	Ispis(druga.next);

	Uniraj(prva.next, druga.next, &unija);
	Presjeci(prva.next, druga.next, &presjek);

	Ispis(unija.next);
	Ispis(presjek.next);
}


int Unos(Lista L)
{
	char str[20];
	FILE * dat = NULL;
	Lista q = NULL;

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);
	if (strchr(str, '.') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "r");
	if (dat == NULL) return -1;

	while (!feof(dat))
	{
		q = (Lista)malloc(sizeof(struct lista));
		if (q == NULL) return -1;
		q->next = NULL;

		fscanf(dat, "%d", &q->broj);

		q->next = L->next;
		L->next = q;
	}
	fclose(dat);
}

int Ispis(Lista L)
{
	if (L == NULL) return -1;
	while (L != NULL)
	{
		printf("%d", L->broj);
		L = L->next;
	}
	printf("\n");
	return 0;
}

int Uniraj(Lista jedan, Lista dva, Lista unija)
{
	Lista q = NULL, Pocetak = jedan, PocetakR = unija;

	if (jedan == NULL && dva == NULL) return -1;

	while (jedan != NULL)
	{
		Lista q = NULL;
		q = (Lista)malloc(sizeof(struct lista));
		if (q == NULL) return q;

		q->next = NULL;

		if (q == NULL) return -1;
		q->broj = jedan->broj;

		q->next = unija->next;
		unija->next = q;
		unija = q;

		jedan = jedan->next;
	}

	unija = PocetakR;

	while (dva != NULL)
	{
		jedan = Pocetak;
		while (jedan != NULL && jedan->broj != dva->broj)
		{
			jedan = jedan->next;
		}

		if (jedan == NULL)
		{
			Lista q = NULL;
			q = (Lista)malloc(sizeof(struct lista));
			if (q == NULL) return q;

			q->next = NULL;

			if (q == NULL) return -1;
			q->broj = dva->broj;

			while (unija->next != NULL && unija->next->broj < q->broj)
				unija = unija->next;
			q->next = unija->next;
			unija->next = q;
			unija = PocetakR;
		}

		dva = dva->next;
	}
	return 0;

}
int Presjeci(Lista jedan, Lista dva, Lista presjek)
{
	Lista q = NULL;
	while (jedan != NULL && dva != NULL)
	{
		if (jedan->broj > dva->broj)
			dva = dva->next;
		else if (jedan->broj < dva->broj)
			jedan = jedan->next;
		else
		{
			Lista q = NULL;
			q = (Lista)malloc(sizeof(struct lista));
			if (q == NULL) return q;

			q->next = NULL;
			if (q == NULL) return -1;
			q->broj = jedan->broj;

			q->next = presjek->next;
			presjek->next = q;
			presjek = q;
			jedan = jedan->next;
			dva = dva->next;
		}
	}
	return 0;

}
