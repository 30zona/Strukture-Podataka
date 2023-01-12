//Napisati program koji čita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država.Uz
//ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
//države.Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
//broj_stanovnika.
//a) Potrebno je formirati sortiranu vezanu listu država po nazivu.Svaki čvor vezane liste
//sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
//b) Potrebno je formirati stablo država sortirano po nazivu.Svaki čvor stabla sadrži vezanu
//listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.

#define _CRT_SECURE_NO_WARNINGS

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (256)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stablo* pozStablo;
typedef struct stablo {
    char grad[MAX_LINE];
    int broj;
    pozStablo left;
    pozStablo right;
}stablo;

typedef struct lista* pozLista;
typedef struct lista {
    char drzava[MAX_LINE];
    pozLista next;
    pozStablo root;
}lista;



int unosIza(pozLista, pozLista);
int sortiraniUnos(pozLista, pozLista);
int sortiraniUnosIzDatoteke(char*, pozLista);
lista* stvaranjeLista();
void ispisListe(pozLista o);

int main() {
    pozLista head = NULL;
    head = stvaranjeLista();
    sortiraniUnosIzDatoteke("drzave.txt", head);
    ispisListe(head);
	return 0;
}

lista* stvaranjeLista()
{
    lista* l = NULL;
    l = malloc(sizeof(lista));
    if (l == NULL) {
        printf("Greska u alokaciji memorije\n");
    }
    else {
        l->next = NULL;
        l->root = NULL;
    }

    return l;
}
int unosIza(pozLista temp, pozLista p)  //temp je taj sta se dodaje, p je iza koga
{
    temp->next = p->next;                     //taj koji stvorimo pokazuje na ono na sto je p pokazivao (stvaramo izeđu p i prvog)
    p->next = temp;                           //a p pokazuje na njega
    return 0;
}

int sortiraniUnos(pozLista temp, pozLista p)
{
    while (p->next != NULL && strcmp(temp, p)>0)
    {
        p = p->next;
    }
    unosIza(temp, p);
    return 0;
}

int sortiraniUnosIzDatoteke(char* filename, pozLista head)
{
    FILE* fp = NULL;                                    
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Datoteka nije uspjesno otvorena!\n");
        return FILE_DIDNT_OPEN_ERROR;
    }
    char buffer[MAX_LINE] = { 0 };
    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp); 
            pozLista temp = NULL;
            temp = stvaranjeLista();
            sscanf(buffer, " %s", temp);
            sortiraniUnos(temp, head);

    }
    fclose(fp);
    return 0;
}

void ispisListe(pozLista o)
{
    if (o == NULL) {                                  
        printf("Lista je prazna\n");
    }

    printf("Lista:\n");
    while (o != NULL)
    {
        printf("%s\n", o->drzava);
        
        o = o->next;
    }
}
