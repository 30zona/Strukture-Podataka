//zadaci za tebe Paro su na linijama 45 i 80

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
int push(int, pozicija);
int ispisListe(pozicija);
int pull(pozicija);

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
    char bufferr[MAX_LINE] = { 0 };
    char* buffer = bufferr;
    int offset;
    int n;
    int sum = 0;
    int temp = 0;
    char znak = 0;
    int count = 0;

    int num = 0;

    while (count < 8) {                          //napravi funkciju koja prebroji brojeve u fileu(uvijek treba bit jedna manje operacija nego li je brojeva, tako da u while saljes (broj (brojeva)*2) -2                 ili ako to neznas, prebroji sve komponente (i brojeve i znakove) i salji taj broj -1


        fgets(buffer, MAX_LINE, fp);
        if (sscanf(buffer, " %d%n", &n, &offset) == 1)
        {
            printf("%d\n", n);
            push(n, stog);
            buffer += offset;

        }
        if (sscanf(buffer, " %d%n", &n, &offset) != 1) {
            sscanf(buffer, " %c%n", &n, &offset);
            switch (n)
            {
            case '+':
                temp = ((stog->next->next->el) + (stog->next->el));
                pull(stog);
                push(temp, stog);
                buffer += offset;
                break;
            case '*':
                temp = ((stog->next->next->el) * (stog->next->el));
                pull(stog);
                push(temp, stog);
                buffer += offset;

                break;
            case '-':
                temp = ((stog->next->el) - (stog->next->next->el));
                pull(stog);
                push(temp, stog);
                buffer += offset;
                break;
            case '/':
                (float)temp = ((float)(stog->next->el) / (stog->next->next->el));   //ELEMENT JE INT VEC UNUTAR STRUKURE; PA TIH PAR STVARI PROMINI, I NEMOJ DA BUDE RUZNI ISPIS 5.0000 stavi 1 decimalu
                pull(stog);
                push(temp, stog);
                buffer += offset;
                break;
            default:
                printf("\nError-greska u fileu, sadrzi nedozvoljen znak\n");
                goto jaje;
            }
        }
        count++;
    }
    ispisListe(stog->next);
    jaje:
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

int push(int n, pozicija p)            //temp je taj sta se dodaje, p je iza koga
{
    pozicija temp = stvaranje();
    temp->el = n;
    temp->next = p->next;                     //taj koji stvorimo pokazuje na ono na sto je p pokazivao (stvaramo ize?u p i prvog)
    p->next = temp;                           //a p pokazuje na njega
    return 0;
}

int ispisListe(pozicija o)
{
    if (o == NULL) {                                   //provjeramo postoji li itko uopce
        printf("Lista je prazna\n");
        return -1;
    }

    printf("Rezultat:\n");
    while (o != NULL)                              //idemo kroz listu sve dok ne dodemo do kraja
    {
        printf("%d\n", o->el);
        o = o->next;                              //idemo na sljedeci element liste
    }
    return 0;
}

int brisi(pozicija p)
{
    pozicija temp = NULL;
        temp = p->next;      //privremeni postane ono na sto p pokazuje (prvi pravi u nizu)                                    
        p->next = temp->next;    //a p umijesto na njega, pokazuje na ono sto pokazuje on (onaj iza, drugi u nizu)
        free(temp);             //tako smo izbacili taj temp(prvi u nizu), prespojili ga, i sad ga mozemo free-at              
        return 0;
}

int pull(pozicija p) {   //najnepotrebnija funkcija ikad, al ajde
    brisi(p);
    brisi(p);
}
