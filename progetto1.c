#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//codice per il progetto di API

//struct
typedef struct entity{
    char ent_name[1000];
    struct entity *relation_order;
    struct entity *alphabetical_order;
}entity;


//every matrice contains the info about the relation between every entity
typedef struct relation{
    char rel_name[1000];
    int mat_incidenza[1000][1000];
    struct relation *next;
}relation;

//prototypes
void addent_f(char name[]);
void delent_f(char name[]);
void addrel_f(char name1[], char name2[], char rel[], relation *rel_list);
void delrel_f(char name1[], char name2[], char rel[], relation *rel_list);
void report_f();

int main(){
    char input_text[1000];

    char param1[1000];
    char param2[1000];
    char param3[1000];

    //inizializzo la lista di relazioni
    relation rel;
    rel.next=NULL;
    relation *temp_cursor;

    do{
        scanf("%s", input_text);
        //printf("%s\n", input_text);

        if(strcmp(input_text, "addent")==0){
            scanf("%s", param1);
            addent_f(param1);
        }
        else if(strcmp(input_text, "delent")==0){
            scanf("%s", param1);
            delent_f(param1);
        }
        else if(strcmp(input_text, "addrel")==0){
            scanf("%s", param1);
            scanf("%s", param2);
            scanf("%s", param3);
            addrel_f(param1, param2, param3, &rel);

            //provo a stampare le relazioni
            temp_cursor=&rel;
            while(temp_cursor->next!=NULL){
                temp_cursor=temp_cursor->next;
                printf("%s\n", temp_cursor->rel_name);
            }
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

void addent_f(char name[]){
    printf("Adding entity named %s\n", name);
}

void delent_f(char name[]){
    printf("Deleting entity named %s\n", name);
}

void addrel_f(char name1[], char name2[], char rel[], relation* rel_list){
    printf("Adding %s relation from %s to %s\n",rel, name1, name2);
    relation *newrel;
    relation *rel_cursor=rel_list;

    int mat_iniz[1000][1000];
    for(int a=0;a<1000;a++){
        for(int b=0;b<1000;b++){
            mat_iniz[a][b]=-1;
        }
    }

    // //vado all'ultimo elemento della list rel_list (delle entita')
    // while(rel_cursor->next!=NULL){
    //     rel_cursor=rel_cursor->next;
    // }
    
    // //creo l'elemento e lo metto in coda
    // newrel=malloc(sizeof(relation));
    // strcpy(newrel->rel_name,rel);
    // newrel->next=NULL;
    
    // rel_cursor->next=newrel;

    //scorro la lista per vedere se la relazione esiste già
    int found=0;
    while(rel_cursor->next!=NULL&&found!=1){
        rel_cursor=rel_cursor->next;
        if (strcmp(rel_cursor->rel_name,rel)==0){
            found=1;
        }
    }

    //se non ho trovato coincidenze, allora creo l'elemento e lo metto in coda
    if(found==0){
        newrel=malloc(sizeof(relation));
        strcpy(newrel->rel_name,rel);
        newrel->next=NULL;
        for(int a=0;a<1000;a++){
            for(int b=0;b<1000;b++){
                newrel->mat_incidenza[a][b]=-1;
            }
        }

        rel_cursor->next=newrel;
        rel_cursor=rel_cursor->next;

        //devo inserire tutte le entita' nella matrice
    }
    else if(found==1){
        //devo inserire la relazione nella matrice
    }
}

void delrel_f(char name1[], char name2[], char rel[], relation* rel_list){
    printf("Adding %s relation from %s to %s\n",rel, name1, name2);
}

void report_f(){
    printf("Reporting!\n");
}