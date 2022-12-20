// Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
// omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
// level order), brisanje i pronalaženje nekog elementa

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct cvor* pozicija;
typedef struct cvor {
    int br;   
    pozicija left;      
    pozicija right;
}cvor;

cvor* stvaranje();
pozicija insert(pozicija, pozicija);
pozicija find(pozicija, int);
pozicija delete(pozicija, int);
pozicija findMax(pozicija);
pozicija findMin(pozicija);
pozicija printInorder(pozicija);
pozicija printPreorder(pozicija);
pozicija printPostorder(pozicija);
pozicija printLevelOrder(pozicija);
int clear(pozicija);
int userInterface(pozicija, pozicija);

int main()
{
    pozicija root = NULL;
    root = stvaranje();
    userInterface(root, root);
    return 0;
}

cvor* stvaranje()
{
    cvor* c = NULL;
    c = malloc(sizeof(cvor));
    if (NULL == c) {
        printf("Greska u alokaciji memorije\n");
    }
    else
    {
        c->left = NULL;
        c->right = NULL;
    }
    return c;
}

pozicija insert(pozicija p, pozicija q)
{
    if(p==NULL)
        return q;
    if(p->br < q->br)
        p->right=insert(p->right, q);
    else if(p->br > q->br)
        p->left=insert(p->left, q);
    else
        free(q);
    return p;
}

pozicija find(pozicija p, int n)
{
    if(p==NULL)
        return NULL;
    else if(p->br > n)
        return find(p->left,n);
    else if(p->br < n)
        return find(p->right,n);
    else return p;
}

pozicija delete(pozicija p, int n)
{
    if(p==NULL)
        return NULL;
    if(p->br > n)
        p->left=delete(p->left, n);
    else if(p->br < n)
        p->right=delete(p->right, n);
    else{
        if(p->left){
            pozicija temp=findMax(p->left);
            p->br=temp->br;
            p->left=delete(p->left, temp->br);
        }
        else if(p->right){
            pozicija temp=findMin(p->right);
            p->br=temp->br;
            p->right=delete(p->right,temp->br);
        }
        else{
            free(p);
            return NULL;
        }
    }
    return p;
}

pozicija findMax(pozicija p)
{
    while(p->right!=NULL)
        p=p->right;
    return p;
}

pozicija findMin(pozicija p)
{
    while(p->left!=NULL)
        p=p->left;
    return p;
}

pozicija printInorder(pozicija p)
{
    if(p==NULL)
        return NULL;
    printInorder(p->left);
    printf("%d ",p->br);
    printInorder(p->right);
    return p;
}

int clear(pozicija p)
{
    if (p != NULL)
    {
        clear(p->left);
        clear(p->right);
        free(p);
    }
    return 0;

    // 2.Nacin:
    // while(p->left!=NULL || p->right!=NULL)
    //     delete(p,p->br);
    // free(p);
    // return 0;
}

int userInterface(pozicija p, pozicija root)
{
    int check=1;
    int n;
    while(check==1)
    {  
        printf("\nOdaberite\n");
        printf("A-Unos\n");
        printf("B-Brisanje\n");
        printf("C-Pronalazenje elementa\n");
        printf("D-Ispis elemenata - inorder\n");
        printf("E-Ispis elemenata - preorder\n");
        printf("F-Ispis elemenata - postorder\n");
        printf("G-Ispis elemenata - level order\n");
        printf("X-Izlaz iz programa\n");

        char c={0};
        scanf(" %c",&c); //korisnik unosi opciju koju zeli
        c=toupper(c); //u slucaju da je korisnik unio malo slovo, postavljamo ga na veliko slovo tako da switch case moze preopznati
        switch (c)
        {
            case 'A':
                printf("Unesite broj koji zelite unijeti\n");
                if(scanf("%d", &n)==1)//ako je korisnik zapravo unio broj
                {
                    if(!p->br) // ako root nema broj
                        p->br=n;
                    else {
                        pozicija q=NULL;
                        q=stvaranje();
                        q->br=n;
                        p=insert(p,q);
                    }
                }
                else printf("Unesite broj\n");
                break;
            case 'B':
                printf("Unesite broj koji zelite izbrisati\n");
                if(scanf("%d", &n)==1)//ako je korisnik zapravo unio broj
                    p=delete(p,n);
                else printf("Unesite broj\n");
                break;
            case 'C':
                printf("Unesite broj koji zelite naci\n");
                if(scanf("%d", &n)==1)//ako je korisnik zapravo unio broj
                {
                    if(!p->br) // ako root nema broj
                        printf("Taj broj ne postoji\n");
                    else{
                        p=find(p,n);
                        if(p==NULL)
                            printf("Taj broj ne postoji\n");
                        else printf("Taj broj postoji\n");
                    }
                }
                else 
                    printf("Unesite broj\n");
                p=root; //vracamo pokazivac na root
                break;  
            case 'D':
                p=printInorder(p);
                break;  
            case 'E':
                break;
            case 'F':
                break;
            case 'G':
                break;
            case 'X':
                check=0; 
                clear(root);
                break;
            default: //ako se nije uneseno nijedno od ponudenih slova nego nesto drugo
                printf("Unesite jedno od ponudenih slova\n");
                break;
        }
    }
    return 0;
}