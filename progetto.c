#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//codice per il progetto di API

//prototipi
void addent_f(char name[]);
void delent_f(char name[]);
void addrel_f(char name1[], char name2[], char rel[]);
void delrel_f(char name1[], char name2[], char rel[]);
void report_f();

int main(){
    char end_text[]="end";
    char input_text[20];

    char param1[20];
    char param2[20];
    char param3[20];

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
    }while (strcmp(input_text, end_text)!=0);

    return 0;
}

void addent_f(char name[]){
    printf("Adding entity named %s\n", name);
}

void delent_f(char name[]){
    printf("Deleting entity named %s\n", name);
}

void addrel_f(char name1[], char name2[], char rel[]){
    printf("Adding <%s> relation from <%s> to <%s>\n",rel, name1, name2);
}

void delrel_f(char name1[], char name2[], char rel[]){
    printf("Adding <%s> relation from <%s> to <%s>\n",rel, name1, name2);
}

void report_f(){
    printf("Reporting!\n");
}