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

//Tengo traccia delle entita' in una hash table. I tipi di relazioni sono in una lista in ordine alfabetico
//Ogni tipo di relazione ha un BST ordinato con to e from
//Per la report, uso una lista in cui inserisco tutti gli elementi da stampare in ordine
//ATTENZIONE: ogni volta che finisco la report devo liberare tutta la lista

//struct

typedef struct relation{
    char rel_name[100];
    struct relation *next;
    struct relation_node *tree;
}relation;

typedef struct entity{
    char name[100];
    struct entity *next;
}entity;

typedef struct relation_node{
    char from[100];
    char to[100];
    int relations;
    struct relation_node *p;
    struct relation_node *left;
    struct relation_node *right;
    struct relation_node *root;
}relation_node;

typedef struct toprint_list{
    char idrel[100];
    char ident[100];
    int num_rel;
    struct toprint_list *next;
    struct toprint_list *prev;
}toprint_list;

//prototypes
void addent_f(char name[], entity* ht_entities[] );
void delent_f(char name[], entity* ht_entities[]);
void addrel_f(char name1[], char name2[], char rel[], relation *rel_list, entity* ht_entities[]);
void addrel_f2(char name1[], char name2[], char rel[], relation *rel_list, entity* ht_entities[]);
void delrel_f(char name1[], char name2[], char rel[], relation *rel_list, entity* ht_entities[]);
void report_f(relation *rel_list);
int check_ent_hash(char name[], entity* ht_entities[]);
int hash_function_entities(char name[]);
void tree_insert(relation_node *tree, relation_node *relation);

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
            addrel_f(param1, param2, param3, &rel, ht_entities);
        }
        else if(strcmp(input_text, "delrel")==0){
            scanf("%s", param1);
            scanf("%s", param2);
            scanf("%s", param3);
            delrel_f(param1, param2, param3, &rel, ht_entities);
        }
        else if(strcmp(input_text, "report")==0){
            report_f(&rel);
        }
    }while (strcmp(input_text, "end")!=0);

    return 0;
}

void addent_f(char name[], entity* ht_entities[]){
    //uso un'hash function per aggiungere le entita' alla hash table
    //come hash function uso      k mod 2053

    //alloco l'elemento da mettere
    entity * newent;
    newent=malloc(sizeof(entity));
    strcpy(newent->name,name);

    int hashval;

    // //hash function
    // //---------------------------------------------------------------------------------------------------------------
    // char ent_val_str[301];
    // char transformed[12];
    // int hashval;
    
    // strcpy(ent_val_str,"");

    // for(int i=0;i<strlen(name);i++){
    //     //converto ogni carattere del nome nel suo valore ascii
    //     sprintf(transformed,"%d",(int)name[i]);
    //     //ogni valore ascii viene affiancato al valore ascii del carattere prima
    //     strcat(ent_val_str, transformed);
    // }
    // //---------------------------------------------------------------------------------------------------------------
    // //fine hash function

    ///printf("Il valore hash trovato e': %s\n", ent_val_str);

    entity *temp_cursor;
    int positioned=0;

    hashval=hash_function_entities(name)%HASHNUM;
    
    //una volta trovata la chiave di hash devo mettere l'entita' nella hash table
    if(ht_entities[hashval]==NULL){
        //lo slot e' libero
        newent->next=NULL;
        ht_entities[hashval]=newent;
    }
    else if(ht_entities[hashval]!=NULL){
        //lo slot e' occupato, devo scorrere la lista per mettere l'entita' in ordine alfabetico
        temp_cursor=ht_entities[hashval];
        do{
            if(strcmp(temp_cursor->name,newent->name)<0){
                //l'entita' ha id piu' grande di quella nella lista
                if(temp_cursor->next==NULL){
                    //sono all'ultimo elemento
                    temp_cursor->next=newent;
                    newent->next=NULL;
                    positioned=1;
                }
                else if(temp_cursor->next!=NULL && strcmp(temp_cursor->next->name,newent->name)>0){
                    //ho trovato dove metterlo
                    newent->next=temp_cursor->next;
                    temp_cursor->next=newent;
                    positioned=1;
                }
            }
            if(strcmp(temp_cursor->name,newent->name)==0){
                //se l'entita' esiste gia' allora esco senza fare nulla
                free(newent);
                positioned=1;
            }
            if(temp_cursor->next==NULL){
                //sono all'ultimo elemento
                temp_cursor->next=newent;
                newent->next=NULL;
                positioned=1;
            }
            //vado avanti solo se esiste l'elemento dopo
            if(temp_cursor->next!=NULL){
                temp_cursor=temp_cursor->next;
            }
            //printf("pizza");
        }while(/* temp_cursor->next!=NULL &&  */positioned!=1);
    }
}

void delent_f(char name[], entity* ht_entities[]){
    
}

void addrel_f(char name1[], char name2[], char rel[], relation* rel_list, entity* ht_entities[]){

    //alloco la nuova relazione da mettere nella lista
    relation * newrel;
    newrel=malloc(sizeof(relation));
    strcpy(newrel->rel_name,rel);
    newrel->tree=NULL;

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
                // if(temp_cursor->next==NULL){
                //     //sono all'ultimo elemento
                //     temp_cursor->next=newrel;
                //     newrel->next=NULL;
                //     positioned=1;
                // }
                if(temp_cursor->next!=NULL && strcmp(temp_cursor->next->rel_name,newrel->rel_name)>0){
                    //ho trovato dove metterlo ma devo verificare di star monitorando entrambe le entita'
                    if(check_ent_hash(name1, ht_entities)==1){
                        if(check_ent_hash(name2, ht_entities)==1){
                            newrel->next=temp_cursor->next;
                            temp_cursor->next=newrel;
                            positioned=1;

                            //inserisco la relazione nell'albero
                            relation_node *newrel_node;
                            newrel_node=malloc(sizeof(relation_node));
                            strcpy(newrel_node->to, name2);
                            strcpy(newrel_node->from, name1);
                            newrel_node->left=NULL;
                            newrel_node->right=NULL;
                            tree_insert(newrel->tree, newrel_node);
                        }
                    }
                }
            }
            else if(strcmp(temp_cursor->rel_name,newrel->rel_name)==0){
                //se la relazione esiste gia' allora aggiungo la relazione all'albero e libero lo spazio
                free(newrel);
                positioned=1;

                //inserisco la relazione nell'albero
                relation_node *newrel_node;
                newrel_node=malloc(sizeof(relation_node));
                strcpy(newrel_node->to, name2);
                strcpy(newrel_node->from, name1);
                newrel_node->left=NULL;
                newrel_node->right=NULL;
                tree_insert(temp_cursor->tree, newrel_node);
            }
            else if(temp_cursor->next==NULL && positioned!=1){
                //sono all'ultimo elemento
                temp_cursor->next=newrel;
                newrel->next=NULL;
                positioned=1;

                //inserisco la relazione nell'albero
                relation_node *newrel_node;
                newrel_node=malloc(sizeof(relation_node));
                strcpy(newrel_node->to, name2);
                strcpy(newrel_node->from, name1);
                newrel_node->left=NULL;
                newrel_node->right=NULL;
                tree_insert(newrel->tree, newrel_node);
            }
            if(temp_cursor->next!=NULL && positioned!=1){
                temp_cursor=temp_cursor->next;
            }
        }while(/* temp_cursor->next!=NULL &&  */positioned!=1);
    }
}

void delrel_f(char name1[], char name2[], char rel[], relation* rel_list, entity* ht_entities[]){
    
}

void report_f(relation *rel_list){
    //creo la lista per stampare
    toprint_list to_print;
    toprint_list *print_cursor;
    print_cursor=&to_print;

    
}

int check_ent_hash(char name_to_check[], entity* ht_entities[]){
    
    // //hash function
    // //---------------------------------------------------------------------------------------------------------------
    // char ent_val_str[301];
    // char transformed[12];
    // int hashval;
    
    // for(int i=0;i<strlen(name_to_check);i++){
    //     //converto ogni carattere del nome nel suo valore ascii
    //     sprintf(transformed,"%d",(int)name_to_check[i]);
    //     //ogni valore ascii viene affiancato al valore ascii del carattere prima
    //     strcat(ent_val_str, transformed);
    // }
    // //---------------------------------------------------------------------------------------------------------------
    // //fine hash function

    int hashval;
    hashval=hash_function_entities(name_to_check)%HASHNUM;

    entity * temp_cursor_ht=ht_entities[hashval];

    if(temp_cursor_ht==NULL){
        //slot vuoto
        return 0;
    }
    else{
        do{
            if(strcmp(temp_cursor_ht->name, name_to_check)==0){
                //esiste
                return 1;
            }
            temp_cursor_ht=temp_cursor_ht->next;
        }while(temp_cursor_ht->next!=NULL);
    }

    return 0;
}

int hash_function_entities(char name_to_hash[]){
    //hash function
    //---------------------------------------------------------------------------------------------------------------
    char ent_val_str[301]="";
    char transformed[12];

    //QUI C'E' OVERFLOW
    
    for(int i=0;i<strlen(name_to_hash);i++){
        //converto ogni carattere del nome nel suo valore ascii
        sprintf(transformed,"%d",(int)name_to_hash[i]);
        //ogni valore ascii viene affiancato al valore ascii del carattere prima
        strcat(ent_val_str, transformed);
    }
    //---------------------------------------------------------------------------------------------------------------
    //fine hash function

    int valore=((int)ent_val_str)%HASHNUM;

    if(valore<0){
        valore=-valore;
    }

    return valore;
}

void tree_insert(relation_node *tree, relation_node *relation){
    //copio lo pseudocodice delle slides

    relation_node *y=NULL;
    relation_node *x=tree;
    while(x!=NULL){
        y=x;
        if(strcmp(relation->to, x->to)<0){
            x=x->left;
        }
        else if(strcmp(relation->to, x->to)>0){
            x=x->right;
        }
        else if(strcmp(relation->to, x->to)==0){
            //il to e' uguale allora smisto per from
            if(strcmp(relation->from, x->from)<0){
                x=x->left;
            }
            else if(strcmp(relation->from, x->from)>0){
                x=x->right;
            }
            else if(strcmp(relation->from, x->from)==0){
                //sia to che from sono uguali, allora esco senza fare nulla
                return;
            }
        }
    }
    relation->p=y;
    if(y==NULL){
        //l'albero e' vuoto
        tree=relation;
    }
    else if(strcmp(relation->to, y->to)<0){
        y->left=relation;
    }
    else{
        y->right=relation;
    }
}