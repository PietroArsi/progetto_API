#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHNUM 2053

//codice per il progetto di API

//idee

//le relazioni vanno messe in una lista concatenata semplice, ordinata per ordine alfabetico
//ogni elemento "relazione" nella lista contiene un grafo con liste di adiacenza per le entita'
//ordinate in ordine di maggior numero di relazioni.
//oltre a questo, tengo un'altra organizzata come hashtable in cui tengo l'elenco completo delle entita' monitorate
//per controllare se devo aggiungere o no le relazioni

//oppure

//faccio un array 

//struct

typedef struct relation{
    char rel_name[1000];
    struct relation *next;
}relation;

typedef struct entity{
    char name[100];
    struct entity *next;
}entity;

//prototypes
void addent_f(char name[], entity* ht_entities[] );
void delent_f(char name[], entity* ht_entities[]);
void addrel_f(char name1[], char name2[], char rel[], relation *rel_list);
void delrel_f(char name1[], char name2[], char rel[], relation *rel_list);
void report_f();
void check_ent_hash(char name[], entity* ht_entities[]);

int main(){

    //parser

    char input_text[100];

    char param1[100];
    char param2[100];
    char param3[100];

    //inizializzo la lista di relazioni
    relation rel;
    rel.next=NULL;

    //inizializzo la hash table
    entity *ht_entities[HASHNUM];
    for(int i=0;i<HASHNUM;i++){
        ht_entities[i]=NULL;
    }

    do{
        //leggo l'input e faccio strcmp per vedere cosa devo fare

        //da fare: regolare i buffer per l'input a seconda di quanto sono grandi gli input
        
        scanf("%s", input_text);
        //printf("%s\n", input_text);

        if(strcmp(input_text, "addent")==0){
            scanf("%s", param1);
            addent_f(param1, ht_entities);
        }
        else if(strcmp(input_text, "delent")==0){
            scanf("%s", param1);
            delent_f(param1, ht_entities);
        }
        else if(strcmp(input_text, "addrel")==0){
            scanf("%s", param1);
            scanf("%s", param2);
            scanf("%s", param3);
            addrel_f(param1, param2, param3, &rel);
        }
        else if(strcmp(input_text, "delrel")==0){
            scanf("%s", param1);
            scanf("%s", param2);
            scanf("%s", param3);
            delrel_f(param1, param2, param3, &rel);
        }
        else if(strcmp(input_text, "report")==0){
            report_f();
        }
    }while (strcmp(input_text, "end")!=0);

    return 0;
}

void addent_f(char name[], entity* ht_entities[]){
    //uso un'hash function per aggiungere le entita' alla hash table
    //come hash function uso      k mod 2053

    //alloco l'elemento da mettere, da mettere poi dentro cosi' alloco solo se strettamente necessario
    entity * newent;
    newent=malloc(sizeof(entity));
    strcpy(newent->name,name);

    char ent_val_str[301];
}

void delent_f(char name[], entity* ht_entities[]){
    
}

void addrel_f(char name1[], char name2[], char rel[], relation* rel_list){

    //alloco la nuova relazione da mettere nella lista
    relation * newrel;
    newrel=malloc(sizeof(relation));
    strcpy(newrel->rel_name,rel);

    //scorro la lista con un cursore temporaneo
    relation *temp_cursor;
    temp_cursor=rel_list;

    int positioned=0;

    if(rel_list->next==NULL){
        //la lista delle entities è vuota ma devo verificare di star monitorando entrambe le entita'
        newrel->next=NULL;
        rel_list->next=newrel;
        return;
    }
    else{
        //la lista ha almeno un elemento, vado a quell'elemento
        temp_cursor=temp_cursor->next;

        do{
            if(strcmp(temp_cursor->rel_name,newrel->rel_name)<0){
                if(temp_cursor->next==NULL){
                    //sono all'ultimo elemento
                    temp_cursor->next=newrel;
                    newrel->next=NULL;
                    positioned=1;
                }
                else if(temp_cursor->next!=NULL && strcmp(temp_cursor->next->rel_name,newrel->rel_name)>0){
                    //ho trovato dove metterlo ma devo verificare di star monitorando entrambe le entita'
                    newrel->next=temp_cursor->next;
                    temp_cursor->next=newrel;
                    positioned=1;
                }
            }
            if(strcmp(temp_cursor->rel_name,newrel->rel_name)==0){
                //se la relazione esiste gia' allora esco senza fare nulla
                positioned=1;
            }
        }while(/* temp_cursor->next!=NULL &&  */positioned!=1);
    }
}

void delrel_f(char name1[], char name2[], char rel[], relation* rel_list){
    
}

void report_f(){
    
}