// Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
// čitaju iz datoteke.
// Napomena: Eksponenti u datoteci nisu nužno sortirani.

//reci pari da se dogovorite jel zovemo u mainu head->next, ili pisemo u programu head=head->next, poludicu ovako
//trenutno spaja samo 2, al u mainu se moze samo napravit petlja u kojoj rezultantnu proglasavamo listom1, i onda sve zajedno opet spajamo
//s nekom novom listom

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (256)
#define FILE_DIDNT_OPEN_ERROR (-1)
#define EMPTY_LIST (-1)
#define MALLOC_ERROR (-1)
#define NOT_FOUND_ERROR (-1)

typedef struct polinom* pozicija;   
typedef struct polinom{   
 int koef; //koeficijent
 int pot; //potencija
 pozicija next;
}polinom;

polinom* stvaranje();
int unosIza(pozicija, pozicija);
int unosPrijeOdredenog(pozicija, pozicija);
int sortiraniUnos(pozicija, pozicija);
int sortiraniUnosIzDatoteke(char*, pozicija[]);
int ispisPolinoma(pozicija);
pozicija mergeliste(pozicija, pozicija);
int brisiSve(pozicija);
pozicija onajIspred(pozicija);
int count(char*);
int srediPolinom(pozicija);
int brisanjeSljedecegElementa(pozicija);
pozicija umnozakPolinoma(pozicija, pozicija);

int main()
{
    int n=count("polinomi.txt");
    
    pozicija* listaPolinoma=NULL; 
    listaPolinoma=malloc(n*sizeof(struct polinom));
    if (listaPolinoma==NULL){
        printf("Greska u alokaciji memorije\n");
        return MALLOC_ERROR;
    }
    for(int i=0;i<n;i++)
    listaPolinoma[i]=stvaranje();
    sortiraniUnosIzDatoteke("polinomi.txt",listaPolinoma);
    for(int i=0;i<n;i++){
    printf("Polinom %i:\n", i+1);
    ispisPolinoma(listaPolinoma[i]->next);
    }
    pozicija r=NULL;
    int check=0;
    printf("Upisite 1 za zbroj polinoma, 2 za umnozak polinoma.");
    scanf("%d",&check);
    switch (check)
    {
    case 1:
        for(int i=0;i<n-1;i++){
        r=(mergeliste(listaPolinoma[i]->next, listaPolinoma[i+1]->next));
        listaPolinoma[i+1]=r;
        }
        if(listaPolinoma[1]!=NULL)
        {
            printf("\nZbroj polinoma:\n");
            ispisPolinoma(r->next);
        }
        break;
    case 2:
        for(int i=0;i<n-1;i++){
        r=(umnozakPolinoma(listaPolinoma[i]->next, listaPolinoma[i+1]->next));
        listaPolinoma[i+1]=r;
        }
        if(listaPolinoma[1]!=NULL)
        {
            printf("\nUmnozak polinoma:\n");
            ispisPolinoma(r->next);
        }
        break;
    default:
        break;
    }
    for(int i=0;i<n;i++)
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

int unosIza(pozicija temp, pozicija p)  //temp je taj sta se dodaje, p je iza koga
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
        if (strcmp("\r\n", buffer)!=0) //izvrsava se ako red nije prazan
        {
            pozicija temp=NULL;
            temp=stvaranje();
            check=sscanf(buffer,"%d %d %n",&temp->koef,&temp->pot,&p); //sscanf u varijablu check vraca broj elemenata koje je uspjesno skenira. %n uz to ubraja i spaceove, znaci u slucaju nase datoteke ce sada check biti 2, jer je skeniralo dva broja, a p ce biti 4 jer uz ta 2 broja racuna i 2 spacea
            if(temp->koef!=0 || temp->pot!=0)
                sortiraniUnos(temp,listaPolinoma[k]);
            p2=p2+p; //p2 koristimo da se krecemo dalje kroz string
            while(check==2) //prestajemo vrtiti kroz red kada dode do kraja, to jest kad sscanf vise ne moze nista skenirati
            {    
                temp=stvaranje();
                check=sscanf(buffer+p2,"%d %d %n",&temp->koef,&temp->pot,&p); //buffer+p2 - sada se vise ne gleda cijeli buffer(cijeli red datoteke), nego buffer BEZ onoga sta smo vec skenirali
                if(check==2)
                if(temp->koef!=0 || temp->pot!=0)
                    sortiraniUnos(temp,listaPolinoma[k]);
                p2=p2+p;
            }
            p2=0;//postavljamo p2 na 0 jer idemo na sljedeci red
            k++;//povecavamo k jer idemo na sljedeci red
        }
    }
    return 0;
}

int ispisPolinoma(pozicija p)
{
    if(p==NULL){                                   //provjeramo postoji li uopce
        printf("Prazno\n");
        return EMPTY_LIST;
    }

    //printf("Polinom:\n");
    while(p!=NULL)                              //idemo kroz listu sve dok ne dodemo do kraja
    {
        switch (p->koef)
        {
            case 1:
                if(p->pot != 0)
                printf("x");
                break;
            case 0:
                break;
            default: 
                if(p->pot != 0)
                printf("%dx",p->koef);
                break;
        }
        switch (p->pot)
        {
            case 1:
                break;
            case 0:
                if(p->koef != 0)
                printf("%d",p->koef);
                break;
            default: 
                printf("^%d",p->pot);
                break;
        }
        
        if(p->next!=NULL && p->next->koef!=0)
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

pozicija onajIspred(pozicija p)               

{
    pozicija head=NULL;                                            //imamo prvog
    pozicija nova=p->next;                                 //i onaj iza
    while(head!=p){   //uspoređujemo tog iza sa traženim
        p=nova;                                           //ovde vrtimo oba napried, dok ne nađemo onaj koji nam treba  
        nova=nova->next;                                 
    }
    return p;                                           //i na kraju, kad se taj trazeni podudara, vracamo onaj prethodni
}

int count(char* filename){ //šalješ pointer, ne datoteku
    FILE* fp=fopen(filename,"r");;
    int count =0;
    char buffer[MAX_LINE]={0};
    
    //brojanje-dok nije kraj filea, uspoređujemo s \n, da ne brojimo prazne
    while (!feof(fp)){
        fgets(buffer,MAX_LINE,fp);
        if (strcmp("\r\n", buffer)!=0){
            count++;
        }
    }
    fclose(fp);  //svaku datoteku je lijepo zatvoriti
    return count;
}

int unosPrijeOdredenog(pozicija head,pozicija p) //i ode ces moc maknit char
{
    head=onajIspred(head);  //sad radimo istu stvar kao za unosNakon, samo sto cemo vratit element prije i unjet iza njega
    unosIza(head,p);
    return 0;
}


pozicija mergeliste(pozicija l1, pozicija l2){
    pozicija Rezultantna=stvaranje();

     while(l1 != NULL && l2 != NULL)
    {
        pozicija temp=stvaranje();
        if(l1->pot==l2->pot){
        
        temp->pot = l1->pot;
        temp->koef = l1->koef+l2->koef;
        sortiraniUnos(temp, Rezultantna);
        l1 = l1->next;
        l2 = l2->next;
        }

        else if(l1->pot>l2->pot){
            temp->pot = l1->pot;
            temp->koef = l1->koef;
            sortiraniUnos(temp, Rezultantna);
            l1 = l1->next;
        }

        else{
        temp->pot = l2->pot;
        temp->koef = l2->koef;
        sortiraniUnos(temp, Rezultantna);
        l2 = l2->next;
        }


    }

    while(l1!=NULL){
        pozicija temp=stvaranje();
        temp->pot = l1->pot;
        temp->koef = l1->koef;
        sortiraniUnos(temp, Rezultantna);
        l1=l1->next;
    }

        while(l2!=NULL){
        pozicija temp=stvaranje();
        temp->pot = l2->pot;
        temp->koef = l2->koef;
        sortiraniUnos(temp, Rezultantna);
        l2=l2->next;
    }
    srediPolinom(Rezultantna);
    return Rezultantna;
}

int srediPolinom(pozicija p) //salje se p u pozivu
{
    while(p->next->next!=NULL)
    {
        if(p->next->pot==p->next->next->pot)
        {
            p->next->koef=p->next->koef+p->next->next->koef;
            if(p->next->koef==0)
            {
                brisanjeSljedecegElementa(p->next);                    
                brisanjeSljedecegElementa(p);
            }
            else 
            brisanjeSljedecegElementa(p->next);   
        }
        else p=p->next;
    }
    return 0;
}

int brisanjeSljedecegElementa(pozicija p) //poziva se element prije onoga kojeg zelimo brisat
{
    pozicija temp = p->next;                                       
    p->next = temp->next;                               
    free(temp);   
    return 0;
}

pozicija umnozakPolinoma(pozicija l1, pozicija l2)
{
    pozicija Rezultantna=stvaranje();
    pozicija temp2=NULL;
    while(l1!=NULL)
    {
        temp2=l2;
        while(l2!=NULL)
        {   
            pozicija temp=stvaranje();
            temp->pot = (l1->pot)+(l2->pot);
            temp->koef = (l1->koef)*(l2->koef);
            sortiraniUnos(temp, Rezultantna);
            l2=l2->next;
        }
        l2=temp2;
        l1=l1->next;
    }
    srediPolinom(Rezultantna);
    return Rezultantna;
}