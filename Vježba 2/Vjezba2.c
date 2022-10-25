// Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
// A. dinamički dodaje novi element na početak liste,
// B. ispisuje listu,
// C. dinamički dodaje novi element na kraj liste,
// D. pronalazi element u listi (po prezimenu),
// E. briše određeni element iz liste,
// U zadatku se ne smiju koristiti globalne varijable

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME (747)

typedef struct osoba* pozicija;
struct osoba{
 char ime[MAX_NAME];
 char prezime[MAX_NAME];
 int godina_rodjenja;
 pozicija next;
};

void unosNaPocetakListe(pozicija o);
void unosNaKrajListe(pozicija o);
void ispisListe(pozicija o);

int main()
{
    struct osoba o={0};
    o.next=NULL;
    unosNaPocetakListe(&o);
    unosNaKrajListe(&o);
    ispisListe(&o);
    return 0;
}

void unosNaPocetakListe(pozicija o)
{
    pozicija q=NULL;
    q=(pozicija)malloc(sizeof(struct osoba));
    if(q==NULL) //provjeravamo je li malloc uspio naci prostora u memoriji
    printf("malloc error");
    else //nastavljamo ako je malloc uspio
    {
        printf("Unesite ime\n");
        scanf(" %s",q->ime);
        printf("Unesite prezime\n");
        scanf(" %s",q->prezime);
        printf("Unesite godinu rodjenja\n");
        scanf("%d",&q->godina_rodjenja);
        q->next=o->next;
        o->next=q;
    }
}
void unosNaKrajListe(pozicija o)
{
    pozicija q=NULL;
    q=(pozicija)malloc(sizeof(struct osoba));
    if(q==NULL) //provjeravamo je li malloc uspio naci prostora u memoriji
    printf("malloc error");
    else //nastavljamo ako je malloc uspio
    {
        printf("Unesite ime\n");
        scanf(" %s",q->ime);
        printf("Unesite prezime\n");
        scanf(" %s",q->prezime);
        printf("Unesite godinu rodjenja\n");
        scanf("%d",&q->godina_rodjenja);
        q->next=NULL;
        while(o->next!=NULL)
        {
            o=o->next;
        }
        o->next=q;
    }
}
void ispisListe(pozicija o)
{
    o=o->next;//o samo pokazuje na prvi element, zato ga postavljamo na o->next, tj. prvi pravi element liste
    if(o==NULL)
    printf("Lista je prazna\n");
    else while(o!=NULL)//idemo kroz listu sve dok ne dodemo do kraja
    {
        printf("\nIme: %s %s\n", o->ime, o->prezime);
        printf("Godina rodjenja: %d\n", o->godina_rodjenja);
        o=o->next;//idemo na sljedeci element liste
    }
}