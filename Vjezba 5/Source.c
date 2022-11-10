#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (256)
#define FILE_DIDNT_OPEN_ERROR (-1)
#define MALLOC_ERROR (-1)

typedef struct lista* pozicija;
typedef struct lista {
	int el; //element(broj)
	pozicija next;
}lista;

lista* stvaranje();
int push(pozciija, pozicija);

int main() {
	lista* stog = NULL;
	stog = stvaranje();
	FILE* fp = NULL;
	fp = fopen("filename.txt", "r");
	if (fp == NULL)
	{
		printf("Datoteka nije uspjesno otvorena!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	char buffer[MAX_LINE] = { 0 };
	fgets(buffer, MAX_LINE, fp);
	int n;
	if (strcmp("\r\n", buffer) != 0) //izvrsava se ako red nije prazan
	{
		int check = 0, p = 0;
		check=sscanf(buffer, "%d", &n);
		if (check == 1)
		{
			push(n,)
		}
		else
		{
			sscanf(buffer, "%c", &);
		}
	}
	return 0;
}

lista* stvaranje()
{
	lista* p = NULL;
	p = malloc(sizeof(lista));              //alociramo meoriju
	if (p == NULL) {
		printf("Greska u alokaciji memorije\n");
	}
	else
		p->next = NULL;                         //njegov pointeric stavljamo na onog sljedeceg
	return p;
}

int push(pozicija temp, pozicija p)  //temp je taj sta se dodaje, p je iza koga
{
	temp->next = p->next;                     //taj koji stvorimo pokazuje na ono na sto je p pokazivao (stvaramo ize?u p i prvog)
	p->next = temp;                           //a p pokazuje na njega
	return 0;
}