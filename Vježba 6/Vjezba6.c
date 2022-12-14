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
int ispisDjece(pozicija);
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
    if(NULL==p) //ako uopce nema djece
        return NULL;
    while(strcmp(p->name,name)<0 && p->nextSibling!=NULL) 
    p=p->nextSibling;
    if(strcmp(p->name,name)==0)
        return p;
    else return NULL;
}

int ispisDjece(pozicija p)
{
    p = p->firstChild;
    while (NULL!=p){
        printf("%s \n", p->name);
        p = p->nextSibling;
    }
    return 0;
}

int userInterface(pozicija p)
{
    char input[MAX_LINE]={0}; //sve upisano
    char command[MAX_LINE]={0}; //prva upisana rijec
    char name[MAX_LINE]={0}; //druga upisana rijec
    int check=1;
    while (check==1) {
        input[0]='\0'; //postavljamo ove vrijednosti tako da ne pamti od proslog unosa
        command[0]='\0'; 
        name[0]='\0'; 
        printf("%s ", p->name); //ispisuje di smo trenutno
        fgets(input, MAX_LINE, stdin); //korisnik upise nesto
        sscanf(input," %s %s", command, name); //to sto je upisano se dijeli na dvi rijeci
        if (strcmp(command, "md") == 0 && name[0]!='\0')
        {
            pozicija new = NULL;
            new = stvaranje();
            strcpy(new->name, name);
            p->firstChild = insert(p->firstChild, new);
        }
        else if (strcmp(command, "cd") == 0 && name[0]!='\0' && strcmp(name,"..") != 0) {
            if(NULL!=find(p->firstChild, name)) //postoji li uopce to sta je korisnik upisa
                p = find(p->firstChild, name);
            else printf("No such file or directory\n");
        }
        else if (strcmp(command, "cd") == 0 && strcmp(name,"..") == 0) {
               //ovo je ono kad moras nac tatu a nemas pointer 
        }
        else if (strcmp(command, "dir") == 0 && name[0]=='\0') {
            ispisDjece(p);
        }
        else if(strcmp(command, "exit") == 0 && name[0]=='\0')
        {
            check=0;
            //sad tu jos treba obrisat sve elemente koje smo dodali u stablo
        }
        else {
            printf("Kriva naredba\n");
        }
    }
    return 0;
}
