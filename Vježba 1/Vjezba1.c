//1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
//zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
//studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova/max_br_bodova*100

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1) //-1 magicni broj mrale
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)

int countStudentsFromFile(char* filename){ //šalješ pointer, ne datoteku
    FILE* fp=NULL;
    int count =0;
    char buffer[MAX_LINE]={0};

    //otvaranje datoteke, (i ne otvaranje i ne postojanje datoteke)
    fp=fopen(filename,"r");
    if (fp==NULL){ 
        printf("Datoteka %s se nije otvorila!", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }
    //brojanje-dok nije kraj filea, uspoređujemo s \n, da ne brojimo prazne
    while (!feof(fp)){
        fgets(buffer,MAX_LINE,fp);
        if (strcmp("\n", buffer)!=0){
            count++;
        }
    }
    fclose(fp);  //svaku datoteku je lijeo zatvoriti
    return count;
}

int main(void){
    char filename[MAX_FILE_NAME]={0};
    printf("Unesi ime datoteke:\n");
    scanf(" %s", filename);
    printf("Broj studenata je %d", countStudentsFromFile(filename));
    return 0;
}