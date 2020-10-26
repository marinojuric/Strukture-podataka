// Program koji racuna koliko studenata(linija) ima u datoteci
// Program koji ucitava zapis iz datoteke
// Program koji ispisuje zapis iz datoteke
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student {
	char ime[50];
	char prezime[50];
	int bodovi;
	double rel_bodovi;
}stud;

int brojac(const char* dat) // Funkcija broji linije datoteke
{
	int broj = 0;
	char linija[50] = {0};
	FILE* f = NULL;
	int i;
	f = fopen(dat, "r");

	if (f == NULL)
	{
		printf("Datoteka ne postoji.\n");
		return -1;
	}

	for (i = 0; i < 1; i++)
		while (fgetc(f) != '\n');	// Preskakanje jednog reda
	while (fgets(linija, 50, f) != NULL)
		broj++;

	return broj;
}

int kopija(const char* dat, stud* stude, int br) // Funkcija kopira podatke u strukturu iz datoteke
{
	FILE* f = NULL;
	int i;
	f = fopen(dat, "r");

	if (f == NULL)
	{
		printf("Datoteka ne postoji.\n");
		return -1;
	}

	for (i = 0; i < 1; i++)
		while (fgetc(f) != '\n');	// Preskakanje jednog reda

	for (i = 0; i < br; i++)
	{
		fscanf(f, "%s %s %d", stude[i].ime, &stude[i].prezime, &stude[i].bodovi);
	}

	return 0;
}

int relativni(stud* s, int br) // Funkcija racuna relativan broj bodova
{
	int i;
	for (i = 0; i < br; i++)
	{
		s[i].rel_bodovi = (double)s[i].bodovi / 50 * 100;
	}

	return 0;
}

int ispis(stud* s, int br) // Funkcija ispisuje strukturu
{
	int i;
	for (i = 0; i < br; i++)
	{
		printf("\n%s %s %d %lf\n", s[i].ime, s[i].prezime, s[i].bodovi, s[i].rel_bodovi);
	}
	return 0;
}
int main()
{
	int br = 0;
	FILE* fp = NULL;
	stud* s;

	fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("Datoteka ne postoji.\n");
		return -1;
	}

	br = brojac("data.txt");

	printf("Broj studenata je %d\n", br);

	s = (stud*)malloc(br * sizeof(stud));

	kopija("data.txt", s, br);

	relativni(s, br);
	
	ispis(s, br);

	fclose(fp);
	free(s);
	return 0;
}
