#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

struct lista;
typedef struct lista* pozLista;
typedef struct lista
{
	char grad[MAX_LINE];
	int stanovnistvo;
	pozLista Next;
}lista;

struct stablo;
typedef struct stablo* pozStablo;
typedef struct stablo
{
	char drzava[MAX_LINE];
	pozStablo right;
	pozStablo left;
	pozLista ListP;
}stablo;


int PrintInOrder(pozStablo);
int PrintList(pozLista);
int vecigradovi(pozLista, int);
int CountryCompare(pozStablo, pozStablo);
int CityCompare(pozLista, pozLista);
int unosIza(pozLista, pozLista);
int sortiraniUnosLista(pozLista, pozLista);
pozStablo unosDrzava(pozStablo, char*);
pozStablo traziDrzavu(pozStablo, char*);
pozStablo sortiraniUnosStablo(pozStablo P, pozStablo Q);
pozLista stvaranje(char*, int);
pozLista unosGradovaFile(char*);


int main()
{
	pozStablo root = NULL;
	pozStablo newroot = NULL;
	struct lista head;
	head.Next = 0;
	int broj = 0;
	char filename[MAX_LINE] = { 0 }, drzava[MAX_LINE] = { 0 };
	printf("Unesi ime datoteke:\n");
	scanf("%s", filename);
	root = unosDrzava(root, filename);
	printf("Popis dostupnih drzava:\n ---------\n");
	PrintInOrder(root);

	printf("\nOdaberi ime drzave:\n");
	scanf("%s", drzava);
	newroot = traziDrzavu(root, drzava);

	printf("Unesi minimalan broj stanovnika:\n");
	scanf("%d", &broj);
	vecigradovi(newroot->ListP, broj);
	//;
}

pozStablo unosDrzava(pozStablo P, char* filename)
{
	FILE* fp = NULL;
	char drzava[MAX_LINE] = { 0 }, imefilea[MAX_LINE] = { 0 };
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("error!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s", drzava, imefilea);  
		pozStablo Q = NULL;
		Q = (pozStablo)malloc(sizeof(stablo)); //ovdi tvaramo stablo
		if (Q == NULL)
		{
			printf("Greska!\n");
			return -1;
		}
		strcpy(Q->drzava, drzava);
		Q->left = NULL;
		Q->right = NULL;
		Q->ListP = unosGradovaFile(imefilea); // po imenu filea dodajemo gradove
		P = sortiraniUnosStablo(P, Q);
		
	}
	fclose(fp);
	return P;
}

pozStablo sortiraniUnosStablo(pozStablo P, pozStablo Q)
{
	int a = 0;
	if (P == NULL)
		return Q;
	a = CountryCompare(P, Q);
	if (a > 0)
		P->left = sortiraniUnosStablo(P->left, Q);
	else
		P->right = sortiraniUnosStablo(P->right, Q);
	return P;
}

int CountryCompare(pozStablo P, pozStablo Q)
{
	int result = 0;
	result = strcmp(P->drzava, Q->drzava);
	return result;
}

int PrintInOrder(pozStablo P) //za ispis samo drzava
{
	if (P == NULL)
		return 0;
	PrintInOrder(P->left);
	printf("%s ", P->drzava);
	PrintInOrder(P->right);
	return 0;
}

pozLista unosGradovaFile(char* filename)
{
	struct lista head; //napravimo head
	head.Next = NULL;
	FILE* fp = NULL;
	char name[MAX_LINE] = { 0 };
	int z = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error!\n");
		return -1;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %d", name, &z);
		pozLista Q = NULL;
		Q = stvaranje(name, z);
		sortiraniUnosLista(&head, Q);
		
	}
	fclose(fp);
	return head.Next;
}

pozLista stvaranje(char* name, int number)
{
	pozLista Q = NULL;
	Q = (pozLista)malloc(sizeof(lista));
	if (Q == NULL)
	{
		printf("Error!\n");
		return -1;
	}
	strcpy(Q->grad, name);
	Q->stanovnistvo = number;
	Q->Next = NULL;
	return Q;
}

int sortiraniUnosLista(pozLista P, pozLista Q)
{
	pozLista head = P;
	if (head == NULL) {
		return 0;
	}
	int br = 0;
	br = CityCompare(P, Q);
	while (head->Next != NULL && br > 0)  //vrtimo dok je veci
		head = head->Next;

	unosIza(head, Q); //i onda ga savimo
	return 0;
}

int CityCompare(pozLista P, pozLista Q)
{
	int result = 0;
	result = P->stanovnistvo - Q->stanovnistvo;
	if (result == 0)
		result = strcmp(P->Next->grad, Q->grad);
	return result;
}

int unosIza(pozLista P, pozLista Q)
{
	Q->Next = P->Next;
	P->Next = Q;
	return 0;
}

int PrintList(pozLista P)
{
	if (P->Next == NULL)
	{
		printf("Prazno!\n");
		return 1;
	}
	while (P->Next != NULL)
	{
		printf("%s ", P->Next->grad);
		P = P->Next;
	}
	return -1;
}

pozStablo traziDrzavu(pozStablo temp, char* name)
{
	if (temp == NULL)
		return NULL;
	if (strcmp(temp->drzava, name) == 0)
		return temp;
	else if (strcmp(temp->drzava, name) > 0)
		temp->left = traziDrzavu(temp->left, name);
	else if (strcmp(temp->drzava, name) < 0)
		temp->right = traziDrzavu(temp->right, name);
}

int vecigradovi(pozLista P, int x)
{
	printf("Gradovi sa vise od %d stanovnika su:\n", x);
	if (P->Next == NULL)
	{
		printf("Prazno!\n");
		return -1;
	}
	while (P->Next != NULL)
	{
		if (P->Next->stanovnistvo > x)
			printf("%s ", P->Next->grad);
		P = P->Next;
	}
	return 0;
}
