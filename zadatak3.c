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
Pozicija Pretraga(Pozicija);
Pozicija pretPretraga(Pozicija);
int Brisi(Pozicija);
int unosIza(Pozicija);
int unosIspred(Pozicija);
int Sortiraj(Pozicija);
int citajDat(Pozicija);
int pisiDat(Pozicija);

int main()
{
	Pozicija who = NULL;
	struct osoba head;
	head.next = NULL;
	int br = 0, provjera = 0;
	char prez[20] = { 0 };

	while (1) {
		printf("\tKoju funkciju zelite izvrsiti:\n");
		printf("\t1 - Dodaj element na pocetak liste\n");
		printf("\t2 - Ispisi listu\n");
		printf("\t3 - Dodaj element na kraj liste\n");
		printf("\t4 - Pronadi element (po prezimenu)\n");
		printf("\t5 - Izbrisi element iz liste\n");
		printf("\t6 - Dodaj element iza postojeceg\n");
		printf("\t7 - Dodaj element ispred postojeceg\n");
		printf("\t8 - Sortiraj listu\n");
		printf("\t9 - Upisi listu iz datoteke\n");
		printf("\t10 - Citaj listu iz datoteke\n");
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
			who = Pretraga(&head);
			if (who == NULL)
				printf("Osoba ne postoji!\n");
			else
				printf("\nTrazena osoba:\n%s %s %d\n", who->ime, who->prezime, who->godina);
			break;
		case 5:
			Brisi(&head);
			break;
		case 6:
			unosIza(&head);
			break;
		case 7:
			unosIspred(&head);
			break;
		case 8:
			Sortiraj(&head);
			printf("Sortirana lista:\n");
			Ispisi(&head);
			break;
		case 9:
			provjera = citajDat(&head); 
			if (provjera == -1) printf("Problem s otvaranjem datoteke!\n");
			break;
		case 10:
			provjera = pisiDat(head.next);
			if (provjera == -1) printf("Problem s otvaranjem datoteke!\n");
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
		printf("\n%s %s %d", p->ime, p->prezime, p->godina);
		p = p->next;
	}

	printf("\n\n");
	return 0;
}

int unosKraj(Pozicija p)
{
	while (p->next != NULL)
		p = p->next;

	unosPocetak(p);

	return 0;
}
Pozicija Pretraga(Pozicija p)
{
	char prez[20] = {0};
	printf("Unesite prezime osobe (koju trazite / iza koje unosite): \n");
	scanf(" %s", prez);
	p = p->next;
	while (p != NULL && strcmp(p->prezime, prez))
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

int unosIza(Pozicija p)
{
	p = Pretraga(p);
	if (p == NULL) return -1;

	unosPocetak(p);

	return 0;
}

int unosIspred(Pozicija p)
{
	p = pretPretraga(p);
	if (p == NULL) return -1;

	unosPocetak(p);

	return 0;
}

int Sortiraj(Pozicija p)
{
	Pozicija prevj = p, j = NULL, end = NULL, temp = NULL;

	while (p->next != end)
	{
		prevj = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{

				temp = j->next;
				prevj->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prevj = j;
			j = j->next;
		}
		end = j;
	}

	return 0;
}

int citajDat(Pozicija p)
{
	Pozicija temp = NULL;
	FILE * dat = NULL;
	char str[20];

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);
	if (strchr(str, '.') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "r");

	if (dat == NULL)
		return -1;
	while (!feof(dat))
	{
		Pozicija temp = NULL;
		temp = (Pozicija)malloc(sizeof(struct osoba));

		if (temp == NULL) return -1;

		fscanf(dat, " %s %s %d", temp->ime, temp->prezime, &temp->godina);
		temp->next = p->next;
		p->next = temp;
		p = temp;
	}
	fclose(dat);

	return 0;
}

int pisiDat(Pozicija p)
{
	FILE * dat;
	char str[20];

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);
	if (strchr(str, '.') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "w");

	if (dat == NULL)
		return -1;
	fprintf(dat, "\tPOPIS LJUDI\n\n");
	while (p != NULL)
	{
		fprintf(dat, "%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
		p = p->next;
	}

	fclose(dat);
	return 0;
}
