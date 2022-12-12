// Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
// Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
// povratak u prethodni direktorij. Točnije program treba preko menija simulirati
// korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (256)

typedef struct cvor* pozicija;   
typedef struct cvor{   
char name[MAX_LINE];   //ime direktorija
 pozicija firstChild;      //dete
 pozicija nextSibling;
}cvor;

cvor* stvaranje();
pozicija insert(pozicija, pozicija);
pozicija find(pozicija, char*);
int userInterface(pozicija);

int main()
{
    pozicija root=NULL;
    root=stvaranje();
    strcpy(root->name,"C:");  //ne mozemo stavit za string=string, nego triba ovo
    userInterface(root);
    return 0;
}

cvor* stvaranje()
{
    cvor* c = NULL;                                   
    c = malloc(sizeof(cvor));              
    if (NULL==c){
        printf("Greska u alokaciji memorije\n");
    }
    else 
    c->firstChild = NULL;      
    c->nextSibling = NULL;                        
    return c;
}

pozicija insert(pozicija p, pozicija q)//za md //sortirani unos(po abecedi) //q dodajemo na mjesto p 
{
    if(NULL==p)
        return q;      //ako nema nuceg to misto je ono prvo
    if(strcmp(p->name,q->name)>0) //ako ima vrtimo dok ne dodjemo iza
    {
        q->nextSibling=p;
        return q;
    }
    p->nextSibling=insert(p->nextSibling,q);
    return p;
}

pozicija find(pozicija p, char* name)//za cd 
{
    while(strcmp(p->name,name)<0) //posto je pri unosu vec sortirano po abecedi, ne trebamo ic skroz do kraja, nego samo proc sve elemente koji su abecedno prije onog kojeg trazimo
        p=p->nextSibling;
    if(strcmp(p->name,name)==0)
        return p;
    else return NULL;
}

int userInterface(pozicija p)
{
    char command[MAX_LINE]={0}; //prva upisana rijec
    char name[MAX_LINE]={0}; //druga upisana rijec
    //ovde treba neka petlja koja vrti dok korisnik ne izade iz programa, takoder treba napravit provjere tipa sta ako nije korisnik nije unia nista, sta ako je unia prvu rijec a ne drugu, sta ako uneseno ime filea ne postoji
        scanf(" %s %s", command, name);
        while (command != "exit") {
        if (strcmp(command, "md") == 0)
        {
            pozicija new = NULL;
            new = stvaranje();
            strcpy(new->name, name);
            p->firstChild = insert(p->firstChild, new);
        }
        else if (strcmp(command, "cd") == 0) {
            p = find(p->firstChild, name);
        }
        else if (strcmp(command, "cd ..") == 0) {
               //ovo je ono kad moras nac tatu a nemas pointer 
        }
        else if (strcmp(command, "dir") == 0) {
            p = p->firstChild;
            while (p->nextSibling != NULL) {
                printf("%s \n", p->name);
                p = p->nextSibling;
            }
        }
        else {
            printf("Kriva naredba\n");
        }
        printf("sad si u %s\n", p->name);

        }
        
       
    return 0;
}
