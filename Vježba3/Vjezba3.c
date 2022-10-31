// Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
// A. dinamički dodaje novi element na početak liste,
// B. ispisuje listu,
// C. dinamički dodaje novi element na kraj liste,
// D. pronalazi element u listi (po prezimenu),
// E. briše određeni element iz liste,
// U zadatku se ne smiju koristiti globalne varijable

// 3. Prethodnom zadatku dodati funkcije:
// A. dinamički dodaje novi element iza određenog elementa,
// B. dinamički dodaje novi element ispred određenog elementa,
// C. sortira listu po prezimenima osoba,
// D. upisuje listu u datoteku,
// E. čita listu iz datoteke.

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_NAME (25)
#define MAX_FILENAME (30)
#define MAX_LINE (256)
#define MALLOC_ERROR (-1)
#define EMPTY_LIST (-1)
#define PERSON_NOT_FOUND (-1)
#define EXIT_PROGRAM (-1)
#define FILE_DIDNT_OPEN_ERROR (-1)


typedef struct osoba* pozicija;   

typedef struct osoba{             //ovdi ga definiramo, struktura sa podacima i nextom
 char ime[MAX_NAME];
 char prezime[MAX_NAME];
 int godina_rodjenja;
 pozicija next;
}osoba;

int unosIza(pozicija);
int unosNaPocetakListe(pozicija);
int unosNaKrajListe(pozicija);
int ispisListe(pozicija);
pozicija pronalaziElement(char*, pozicija);
pozicija onajIspred(char*, pozicija);
osoba* stvaranje();                 //ovo san doda funkcijica koja pravi onaj malloc i stvari koje se ponavljaju
int brisanjeElementa(char*, pozicija);
int unosNakonOdredenog(char*, pozicija);
int unosPrijeOdredenog(char*, pozicija);
int userInterface(pozicija);
int brisiSve(pozicija);
int sortPoPrezimenu(pozicija);
int unosIzDatoteke(pozicija, char*);
int ispisUDatoteku(pozicija, char*);



int main()        //u mainu ih samo zovemo
{
    pozicija head = NULL;
    head=stvaranje();
    int check=0;
    while(check!=EXIT_PROGRAM) //sve dok ne unesemo da zelimo izaci iz programa(dok ne unesemo X)
    check=userInterface(head);
    brisiSve(head);
    free(head);
    return 0;
}

osoba* stvaranje()
{
    osoba* o = NULL;                                   
    o = (osoba*)malloc(sizeof(osoba));              //alociramo meoriju
    if (o==NULL){
        printf("Greska u alokaciji memorije\n");
    }
    else 
    o->next = NULL;                                 //njegov pointeric
    return o;
}

int ispisListe(pozicija o)
{
    if(o==NULL){                                   //provjeramo postoji li itko uopce
        printf("Lista je prazna\n");
        return EMPTY_LIST;
    }

    printf("Lista:\n");
    while(o!=NULL)//idemo kroz listu sve dok ne dodemo do kraja
    {
        printf("Ime: %s %s\n", o->ime, o->prezime);
        printf("Godina rodjenja: %d\n", o->godina_rodjenja);
        o=o->next;//idemo na sljedeci element liste
    }
    return 0;
}

int unosIza(pozicija head) //ovo je bia kod funkcije unosNaPocetakListe, doda sam je jer smo pozivali funkciju unosNaPocetakListe u drugim funkcijama, ali nismo dodavali na pocetak liste nego negdi drugdi, pa je ovako intuitivnije, bolje ime
{ 
    pozicija q=NULL;
    q=stvaranje();
    printf("Unesite ime\n");
    scanf(" %s",q->ime);                   //sve stvari unosimo sa scanf, i spremamo ih na mjesto u strukturi q tipa pozicija
    printf("Unesite prezime\n");
    scanf(" %s",q->prezime);
    printf("Unesite godinu rodjenja\n");
    scanf("%d",&q->godina_rodjenja);       // za godinu koja je int treba &
    q->next=head->next;
    head->next=q;
    return 0;
}

int unosNaPocetakListe(pozicija head)
{ 
    unosIza(head);
    return 0;
}

int unosNaKrajListe(pozicija head)
{                                    //stavljamo q na pocetak
    while(head->next != NULL)                              //vrtimo dok ne stignemo na kraj
    {
        head = head->next;                                   
    }
    unosIza(head);                          //i onda unesemo, kao da je pocetak, samo saljemo taj prevrceni q, a ne head
    return 0;
}

pozicija pronalaziElement(char* str, pozicija head)
{
    while(head!=NULL && strcmp(head->prezime, str)!=0){               //uspoređuje uneseni sa svakim i gleda dolazimo li do kraja
        head=head->next;                                              
    }
    if (head==NULL){
        printf("Osoba nije pronađena\n");
    }
    return head;
}

int brisanjeElementa(char* str, pozicija head)
{
    pozicija o = NULL;
    o = onajIspred(str, head);                                 //na neku poziciju stavimo onaj koji je ispred
    if(o == NULL)
    return PERSON_NOT_FOUND;

    pozicija temp = o->next;                                       
    o->next = temp->next;
    free(temp);

    return 0;
}

pozicija onajIspred(char* str, pozicija head)               
{
    pozicija s=NULL, nova=NULL;               
    s= head; //imamo prvog
    nova=head->next; //i onaj iza
    while(nova!=NULL && strcmp(nova->prezime, str)!=0){   //gledamo kakav je taj iza
        s=nova;                                           //ovde vrtimo oba napried, dok ne nađemo onaj koji nam treba  
        nova=nova->next;                                 
    }
    if (nova==NULL){ //ako smo dosli do kraja liste bez da smo nasli osobu, ona nije pronadena
        printf("Osoba nije pronađena\n");
        return NULL;
    }
    else return s;                                           //i na kraju vracamo onaj prethodni
}

int unosNakonOdredenog(char* str,pozicija head)
{
    head=pronalaziElement(str,head);
    if(head==NULL)
    return EMPTY_LIST;
    else unosIza(head);
    return 0;
}

int unosPrijeOdredenog(char* str,pozicija head)
{
    head=onajIspred(str,head);
    if(head==NULL)
    return EMPTY_LIST;
    else unosIza(head);
    return 0;
}

int userInterface(pozicija head)
{
    printf("\nOdaberite\n");
    printf("A-Unos na pocetak liste\n");
    printf("B-Unos na kraj liste\n");
    printf("C-Brisanje elementa liste\n");
    printf("D-Unos nakon odredenog elementa liste\n");
    printf("E-Unos prije odredenog elementa liste\n");
    printf("F-Sortiranje liste po prezimenu\n");
    printf("G-Unesite datoteku u listu\n");
    printf("H-Ispisite listu u datoteku\n");
    printf("I-ispis liste\n");
    printf("X-Izlaz iz programa\n");

    char c={0}, str[MAX_NAME]={0}, filename[MAX_FILENAME]={0}; 
    scanf(" %c",&c); //korisnik unosi opciju koju zeli
    c=toupper(c); //u slucaju da je korisnik unio malo slovo, postavljamo ga na veliko slovo tako da switch case moze preopznati
    switch (c)
    {
        case 'A':
            unosNaPocetakListe(head);
            break;
        case 'B':
            unosNaKrajListe(head);
            break;
        case 'C':
            if(head->next==NULL)
            printf("Lista je prazna\n");
            else 
            {
                printf("Koju osobu zelite izbrisati(upisite prezime)\n");
                scanf(" %s",str);
                brisanjeElementa(str,head);
            }
            break;  
        case 'D':
            if(head->next==NULL)
            printf("Lista je prazna\n");
            else
            {
                printf("Nakon koje osobe zelite unijeti?(upisite prezime)\n");
                scanf(" %s",str);
                unosNakonOdredenog(str,head);
            }
            break;  
        case 'E':
            if(head->next==NULL)
            printf("Lista je prazna\n");
            else
            {
                printf("Prije koje osobe zelite unijeti?(upisite prezime)\n");
                scanf(" %s",str);
                unosPrijeOdredenog(str,head);
            }
            break;
        case 'F':
            if(head->next==NULL)
            printf("Lista je prazna\n");
            else sortPoPrezimenu(head);
            break;
        case 'I':
            ispisListe(head->next);
            break;  
        case 'G':
            printf("Unesi ime datoteke:\n");
            scanf(" %s", filename);
            unosIzDatoteke(head, filename);
            break;
        case 'H':
            if(head->next==NULL)
            printf("Lista je prazna\n");
            else
            {   
                printf("Unesi ime datoteke:\n");
                scanf(" %s", filename);
                ispisUDatoteku(head->next, filename);
            }
            break;
        case 'X':
            return EXIT_PROGRAM; 
            break;
        default: //ako se nije uneseno nijedno od ponudenih slova nego nesto drugo
            printf("Unesite jedno od ponudenih slova\n");
            break;
    }
    return 0;
}

int brisiSve(pozicija head)
{
    pozicija temp=NULL;
    while(head->next!=NULL)
    {
        temp = head->next;                                       
        head->next = temp->next;
        free(temp);
    }
    return 0;
}

int sortPoPrezimenu(pozicija i) //bubble sort
{   
    pozicija j=NULL, prev_j=NULL,temp=NULL,end=NULL;
    while(i->next!=end)
    {
        prev_j=i;
        j=i->next;
        while(j->next!=end)
        {
            if(strcmp(j->prezime, j->next->prezime)>0) //usporedivanje prezimena
            {
                temp=j->next;
                prev_j->next=temp;
                j->next=temp->next;
                temp->next=j;
                j=temp;
            }
            else if(strcmp(j->prezime, j->next->prezime)==0) //ako su prezimena ista, usporedujemo imena
                if(strcmp(j->ime, j->next->ime)>0) //usporedivanje imena
                {
                    temp=j->next;
                    prev_j->next=temp;
                    j->next=temp->next;
                    temp->next=j;
                    j=temp;
                }
            prev_j=j; //idemo na sljedecu poziciju u listi
            j=j->next; //idemo na sljedecu poziciju u listi
        }
        end=j; //kraj sad vise nije zadnji element liste nego predzadnji, a u sljedecoj vrtnji petlje predpredzadnji itd
    }
    return 0;
}

int unosIzDatoteke(pozicija head, char* filename){
    FILE*fp=NULL;
    fp=fopen(filename,"r");
    if (fp==NULL){
        printf("Trazena datoteka ne postoji\n");
        return FILE_DIDNT_OPEN_ERROR;
    }

    int count=0;
    char buffer[MAX_LINE]={0};
    //brojanje-dok nije kraj filea, uspoređujemo s \n, da ne brojimo prazne
    while (!feof(fp)){
    fgets(buffer,MAX_LINE,fp);
    if (strcmp("\n", buffer)!=0){
        count++;
        }
    }
    fclose(fp);
    fp=fopen(filename,"r");
    pozicija o=NULL;
    for(int i=0;i<count;i++)
    {
        o=stvaranje();
        fscanf(fp,"%s %s %d", o->ime, o->prezime, &o->godina_rodjenja);
        o->next=head->next;
        head->next=o;
    }
    fclose(fp);
    return 0;
}

int ispisUDatoteku(pozicija head,char* filename){
    FILE* fp=NULL;
    fp=fopen(filename,"w");
    pozicija o=NULL;
    o=head;
    while(o!=NULL)
    {
        fprintf(fp,"%s %s %d\n", o->ime, o->prezime, o->godina_rodjenja);
       o=o->next;
    }
    fclose(fp);
    return 0;
}