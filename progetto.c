#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//codice per il progetto di API

//struct
typedef struct entity{
    char ent_name[20];
    struct entity *relation_order;
    struct entity *alphabetical_order;
}entity;

typedef struct relation{
    char rel_name[20];
    struct relation *next;
}relation;

//prototypes
void addent_f(char name[]);
void delent_f(char name[]);
void addrel_f(char name1[], char name2[], char rel[], relation *rel_list);
void delrel_f(char name1[], char name2[], char rel[], relation *rel_list);
void report_f();

int main(){
    char input_text[20];

    char param1[20];
    char param2[20];
    char param3[20];

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

    //vado all'ultimo elemento della list rel_list (delle entita')
    while(rel_cursor->next!=NULL){
        rel_cursor=rel_cursor->next;
    }
    
    //creo l'elemento e lo metto in coda
    newrel=malloc(sizeof(relation));
    strcpy(newrel->rel_name,rel);
    newrel->next=NULL;
    
    rel_cursor->next=newrel;
}

void delrel_f(char name1[], char name2[], char rel[], relation* rel_list){
    printf("Adding %s relation from %s to %s\n",rel, name1, name2);
}

void report_f(){
    printf("Reporting!\n");
}