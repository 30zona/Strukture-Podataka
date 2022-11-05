// Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
// čitaju iz datoteke.
// Napomena: Eksponenti u datoteci nisu nužno sortirani.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (256)
#define FILE_DIDNT_OPEN_ERROR (-1)
#define EMPTY_LIST (-1)

typedef struct polinom* pozicija;   
typedef struct polinom{   
 int koef; //koeficijent
 int pot; //potencija
 pozicija next;
}polinom;

polinom* stvaranje();
int unosIza(pozicija, pozicija);
int sortiraniUnos(pozicija, pozicija);
int sortiraniUnosIzDatoteke(char*, pozicija[]);
int ispisPolinoma(pozicija);
int brisiSve(pozicija);

int main()
{
    pozicija listaPolinoma[2]={0}; //zasad imamo 2 polinoma, mogli bi poslije dinamicki broj polinoma tako da koristimo pokazivac na poziciju
    for(int i=0;i<2;i++)
    listaPolinoma[i]=stvaranje();
    sortiraniUnosIzDatoteke("polinomi.txt",listaPolinoma);
    for(int i=0;i<2;i++)
    brisiSve(listaPolinoma[i]);
    return 0;
}

polinom* stvaranje()
{
    polinom* p = NULL;                                   
    p = malloc(sizeof(polinom));              //alociramo meoriju
    if (p==NULL){
        printf("Greska u alokaciji memorije\n");
    }
    else 
    p->next = NULL;                         //njegov pointeric stavljamo na onog sljedeceg
    return p;
}

int unosIza(pozicija temp, pozicija p)
{
    temp->next=p->next;                     //taj koji stvorimo pokazuje na ono na sto je p pokazivao (stvaramo izeđu p i prvog)
    p->next=temp;                           //a p pokazuje na njega
    return 0;
}

int sortiraniUnos(pozicija temp, pozicija p)
{
    while(p->next!=NULL  &&  temp->pot > p->next->pot)
    {
        p=p->next;
    }
    unosIza(temp,p);
    return 0;
}

int sortiraniUnosIzDatoteke(char* filename, pozicija listaPolinoma[])
{
    FILE* fp=NULL;
    fp=fopen(filename,"r");
    if (fp == NULL)
	{
		printf("Datoteka nije uspjesno otvorena!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
    int p=0,p2=0,i=0,j=0,k=0,check=0;
    char buffer[MAX_LINE]={0};
    while(!feof(fp))
    {
        fgets(buffer,MAX_LINE,fp); //procita jedan red datoteke
        pozicija temp=NULL;
        temp=stvaranje();
        check=sscanf(buffer,"%d %d %n",&temp->koef,&temp->pot,&p); //sscanf u varijablu check vraca broj elemenata koje je uspjesno skenira. %n uz to ubraja i spaceove, znaci u slucaju nase datoteke ce sada check biti 2, jer je skeniralo dva broja, a p ce biti 4 jer uz ta 2 broja racuna i 2 spacea
        sortiraniUnos(temp,listaPolinoma[k]);
        p2=p2+p; //p2 koristimo da se krecemo dalje kroz string
        while(check==2) //prestajemo vrtiti kroz red kada dode do kraja, to jest kad sscanf vise ne moze nista skenirati
        {    
            temp=stvaranje();
            check=sscanf(buffer+p2,"%d %d %n",&temp->koef,&temp->pot,&p); //buffer+p2 - sada se vise ne gleda cijeli buffer(cijeli red datoteke), nego buffer BEZ onoga sta smo vec skenirali
            if(check==2)
            sortiraniUnos(temp,listaPolinoma[k]);
            p2=p2+p;
        }
        p2=0;//postavljamo p2 na 0 jer idemo na sljedeci red
        k++;//povecavamo k jer idemo na sljedeci red
    }
    return 0;
}

int ispisPolinoma(pozicija p)
{
    if(p==NULL){                                   //provjeramo postoji li uopce
        printf("Prazno\n");
        return EMPTY_LIST;
    }

    printf("Polinom:\n");
    while(p!=NULL)                              //idemo kroz listu sve dok ne dodemo do kraja
    {
        switch (p->koef)
        {
            case 1:
                printf("x");
                break;
            default: 
                printf("%dx",p->koef);
                break;
        }
        switch (p->pot)
        {
            case 1:
                break;
            default: 
                printf("^%d",p->pot);
                break;
        }
        
        if(p->next!=NULL)
        printf(" + ");
        
        p=p->next;                              //idemo na sljedeci element liste
    }
    printf("\n");
    return 0;
}

int brisiSve(pozicija p)
{
    pozicija temp=NULL;              
    while(p->next!=NULL)
    {
        temp = p->next;      //privremeni postane ono na sto p pokazuje (prvi pravi u nizu)                                    
        p->next = temp->next;    //a p umijesto na njega, pokazuje na ono sto pokazuje on (onaj iza, drugi u nizu)
        free(temp);             //tako smo izbacili taj temp(prvi u nizu), prespojili ga, i sad ga mozemo free-at
    }
    free(p);                 //tako vrtimo sve dok p vise ne pokazuje na nista (nema vise clanova niza), i ond brisemo i p
    return 0;
}
