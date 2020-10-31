// Program koji dinamički dodaje novi element na početak liste
// Program koji ispisuje listu
// Program koji dinamički dodaje novi element na kraj liste
// Program koji pronalazi element u listi (po prezimenu)
// Program koji briše određeni element iz liste
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct osoba;
typedef struct osoba* Pozicija;

struct osoba {
	char ime[50];
	char prezime[50];
	int godina;
	Pozicija next;
};

int unosPocetak(Pozicija);
int Ispisi(Pozicija);
int unosKraj(Pozicija);
Pozicija Pretraga(Pozicija, const char*);
Pozicija pretPretraga(Pozicija);
int Brisi(Pozicija);

int main()
{
	Pozicija who = NULL;
	struct osoba head;
	head.next = NULL;
	int br = 0;
	char prez[20] = { 0 };

	while (1) {
		printf("\tKoju funkciju zelite izvrsiti:\n");
		printf("\t1 - Dodaj element na pocetak liste\n");
		printf("\t2 - Ispisi listu\n");
		printf("\t3 - Dodaj element na kraj liste\n");
		printf("\t4 - Pronadi element (po prezimenu)\n");
		printf("\t5 - Izbrisi element iz liste\n");
		printf("\t0 - Izlaz\n");

		printf("\nIzbor: \n");
		scanf("%d", &br);

		switch (br)
			{
			case 1:
				unosPocetak(&head);
				break;
			case 2:
				Ispisi(&head);
				break;
			case 3:
				unosKraj(&head);
				break;
			case 4:
				printf("Unesite prezime osobe koju trazite: \n");
				scanf(" %s", prez);

				who = Pretraga(&head, prez);

				if (who == NULL)
					printf("Osoba ne postoji!\n");
				else
					printf(" %s %s %d\n\n", who->ime, who->prezime, who->godina);
				break;
			case 5:
				Brisi(&head);
				break;
			case 0:
				printf("Izlaz iz programa!\n");
				return -1;
				break;
			default:
				printf("Greska!\n");
				break;
		}
		
	}
	return 0;
}

int unosPocetak(Pozicija p)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(struct osoba));

	if (q == NULL) return -1;

	printf("Ime:\n");
	scanf(" %s", q->ime);
	printf("Prezime:\n");
	scanf(" %s", q->prezime);
	printf("Godina rodenja:\n");
	scanf("%d", &q->godina);

	q->next = p->next;
	p->next = q;

	return 0;
}

int Ispisi(Pozicija p)
{
	if (p->next == NULL) printf("Lista je prazna!\n");
	
	p = p->next;
	while (p != NULL)
	{
			printf("\n%s %s %d\n", p->ime, p->prezime, p->godina);
			p = p->next;
	}

	return 0;
}

int unosKraj(Pozicija p)
{
	while (p->next != NULL)
		p = p->next;

	unosPocetak(p);

	return 0;
}
Pozicija Pretraga(Pozicija p, const char* trazise)
{
	p = p->next;
	while (p != NULL && strcmp(p->prezime, trazise))
	{
		p = p->next;
	}

	if (p == NULL) return p;

	return p;
}

Pozicija pretPretraga(Pozicija p)
{
	Pozicija pret = p;
	p = p->next;
	char trazise[20];
	printf("Unesite prezime osobe koju trazite:\n");
	scanf(" %s", trazise);

	while (p != NULL && strcmp(p->prezime, trazise) != 0)
	{
		pret = p;
		p = p->next;
	}

	if (p == NULL) return NULL;

	return pret;
}

int Brisi(Pozicija p)
{
	Pozicija temp = NULL;

	p = pretPretraga(p);

	if (p == NULL)
	{
		printf("\nOsoba ne postoji!\n\n");
		return -1;
	}
	
		temp = p->next;
		p->next = temp->next;
		free(temp);

	return 0;
}