#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//codice per il progetto di API

//idee
//le relazioni vanno messe in una lista concatenata semplice, ordinata per ordine alfabetico

//struct

typedef struct relation{
    char rel_name[1000];
    struct entity *entities;
}relation;

typedef struct entity{
    char name[100];

}entity;

//prototypes
void addent_f(char name[]);
void delent_f(char name[]);
void addrel_f(char name1[], char name2[], char rel[]);
void delrel_f(char name1[], char name2[], char rel[]);
void report_f();

int main(){

    //parser

    char input_text[1000];

    char param1[100];
    char param2[1000];
    char param3[1000];

    relation rel;
    rel.entities=NULL;

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
            addrel_f(param1, param2, param3);
        }
        else if(strcmp(input_text, "delrel")==0){
            scanf("%s", param1);
            scanf("%s", param2);
            scanf("%s", param3);
            delrel_f(param1, param2, param3);
        }
        else if(strcmp(input_text, "report")==0){
            report_f();
        }
    }while (strcmp(input_text, "end")!=0);

    return 0;
}

void addent_f(char name[]){
    
}

void delent_f(char name[]){
    
}

void addrel_f(char name1[], char name2[], char rel[]){
    
}

void delrel_f(char name1[], char name2[], char rel[]){
    
}

void report_f(){
    
}