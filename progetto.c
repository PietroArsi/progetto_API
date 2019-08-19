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

//NOTE

//check_ent_hash fa abbastanza schifo
//inorder_tree_count fa ultra mega super stra schifo

//struct

typedef struct relation{
    char rel_name[100];
    struct relation *next;
    struct relation_node *tree;
    int max;
    struct ent_list* next_ent;
}relation;

typedef struct entity{
    char name[100];
    struct entity *next;
}entity;

typedef struct relation_node{
    char from[100];
    char to[100];
    int relations;
    char reltype[100];
    struct relation_node *p;
    struct relation_node *left;
    struct relation_node *right;
    struct relation_node *root;
}relation_node;

typedef struct ent_list{
    char entid[100];
    int ingresso;
    struct ent_list* next;
}ent_list;

//prototypes
void addent_f(char name[], entity* ht_entities[]);
void delent_f(char name[], entity* ht_entities[], relation **rel_list);
void addrel_f(char name1[], char name2[], char rel[], relation **rel_list, entity* ht_entities[]);
void delrel_f(char name1[], char name2[], char rel[], relation **rel_list, entity* ht_entities[]);
void report_f(relation **rel_list);
int check_ent_hash(char name[], entity* ht_entities[]);
int hash_function_entities(char name[]);
void tree_insert(relation **reltype, relation_node **relation);
void inorder_tree_count(relation_node* rel_list, ent_list** lista);
void alphabetical_ent_insert(relation** rel_elem, char entity_id[]);
void tree_delete(relation_node** rel, char name[]);
//void inorder_tree_walk(relation_node* relnode);
//void merge_sort();

int main(){

    //parser

    char input_text[101]="";

    char param1[101]="";
    char param2[101]="";
    char param3[101]="";
    // for(int n=0;n<101;n++){
    //     param1[n]="";
    //     param2[n]="";
    //     param3[n]="";
    //     input_text[n]="";
    // }
    // param1[0]='\0';
    // param2[0]='\0';
    // param3[0]='\0';
    // input_text[0]='\0';

    //inizializzo la lista di relazioni
    relation* rel=NULL;
    //inizializzo la lista per la report
    //ent_list* lista=NULL;

    //inizializzo la hash table
    entity* ht_entities[2053];
    for(int i=0;i<HASHNUM;i++){
        ht_entities[i]=NULL;
    }

    //int first=0;

    do{
        //leggo l'input e faccio strcmp per vedere cosa devo fare

        //da fare: regolare i buffer per l'input a seconda di quanto sono grandi gli input
        
        scanf("%s", input_text);
        //printf("%s\n", input_text);
        //input_text=input_text+ "\0";

        if(strcmp(input_text, "addent")==0){
            scanf("%s", param1);
            //printf("addent\n");
            addent_f(param1, ht_entities);
        }
        else if(strcmp(input_text, "delent")==0){
            scanf("%s", param1);
            delent_f(param1, ht_entities, &rel);
        }
        else if(strcmp(input_text, "addrel")==0){
            scanf("%s", param1);
            scanf("%s", param2);
            scanf("%s", param3);
            //printf("addrel\n");
            addrel_f(param1, param2, param3, &rel, ht_entities);
        }
        else if(strcmp(input_text, "delrel")==0){
            scanf("%s", param1);
            scanf("%s", param2);
            scanf("%s", param3);
            delrel_f(param1, param2, param3, &rel, ht_entities);
        }
        else if(strcmp(input_text, "report")==0){
            // if(first==0){
            //     first=1;
            // }else{
            //     fputs("\n", stdout);
            // }
            //printf("report\n");
            report_f(&rel);
        }
    }while (strcmp(input_text, "end")!=0);

    return 0;
}

void addent_f(char name[], entity* ht_entities[]){
    //uso un'hash function per aggiungere le entita' alla hash table
    //come hash function uso      k mod 2053

    if(check_ent_hash(name, ht_entities)==1){
        return;
    }

    // //alloco l'elemento da mettere
    // entity * newent;
    // newent=malloc(sizeof(entity));
    // strcpy(newent->name,name);

    int hashval;

    entity *temp_cursor;
    int positioned=0;

    hashval=(hash_function_entities(name));

    //printf("valore passato: %d\n", hashval);
    temp_cursor=ht_entities[hashval];
    
    //una volta trovata la chiave di hash devo mettere l'entita' nella hash table
    if(temp_cursor==NULL){
        //lo slot e' libero
        entity * newent;
        newent=malloc(sizeof(entity));
        strcpy(newent->name,name);
        newent->next=NULL;
        ht_entities[hashval]=newent;
    }
    else if(temp_cursor!=NULL){
        //lo slot e' occupato, devo scorrere la lista per mettere l'entita' in ordine alfabetico
        temp_cursor=ht_entities[hashval];
        do{
            if(strcmp(temp_cursor->name,name)<0){
                //l'entita' ha id piu' grande di quella nella lista
                if(temp_cursor->next==NULL){
                    //sono all'ultimo elemento
                    entity * newent;
                    newent=malloc(sizeof(entity));
                    strcpy(newent->name,name);
                    temp_cursor->next=newent;
                    newent->next=NULL;
                    positioned=1;
                }
                else if(temp_cursor->next!=NULL && strcmp(temp_cursor->next->name,name)>0){
                    //ho trovato dove metterlo
                    entity * newent;
                    newent=malloc(sizeof(entity));
                    strcpy(newent->name,name);
                    newent->next=temp_cursor->next;
                    temp_cursor->next=newent;
                    positioned=1;
                }
            }
            else if(strcmp(temp_cursor->name,name)==0 && positioned!=1){
                //se l'entita' esiste gia' allora esco senza fare nulla
                //free(newent);
                positioned=1;
            }
            if(temp_cursor->next==NULL && positioned!=1){
                //sono all'ultimo elemento
                entity * newent;
                newent=malloc(sizeof(entity));
                strcpy(newent->name,name);
                temp_cursor->next=newent;
                newent->next=NULL;
                positioned=1;
            }
            //vado avanti solo se esiste l'elemento dopo
            if(temp_cursor->next!=NULL){
                temp_cursor=temp_cursor->next;
            }
        }while(positioned!=1);
    }
}

void delent_f(char name[], entity* ht_entities[], relation **rel_list){
    int hashval;

    entity *temp_cursor;

    hashval=(hash_function_entities(name));

    temp_cursor=ht_entities[hashval];
    
    //cerco l'entita' nell'hash table e la elimino
    if(temp_cursor==NULL){
        return;
    }
    else if(temp_cursor!=NULL){
        temp_cursor=ht_entities[hashval];
        do{
            if(temp_cursor->next!=NULL){
                if(strcmp(temp_cursor->next->name, name)==0){
                    //ho trovato l'entita' da togliere
                    entity* todelete=temp_cursor->next;
                    temp_cursor->next=temp_cursor->next->next;
                    free(todelete);
                }
                temp_cursor=temp_cursor->next;
            }
        }while(temp_cursor!=NULL);
    }

    //ora devo eliminare ogni relazione che comprende <name> in to o in from
    relation* rel_cursor=*rel_list;
    while(rel_cursor!=NULL){
        tree_delete(&(rel_cursor->tree), name);
        rel_cursor=rel_cursor->next;
    }
}

void addrel_f(char name1[], char name2[], char rel[], relation** rel_list, entity* ht_entities[]){
    //se non ci sono le entita' esco subito
    if(check_ent_hash(name1, ht_entities)!=1 || check_ent_hash(name2, ht_entities)!=1){
        return;
    }
    
    //scorro la lista con un cursore temporaneo
    relation *temp_cursor;
    temp_cursor=*rel_list;

    int positioned=0;

    if(temp_cursor==NULL){
        //la lista dei tipi di relazioni è vuota ma devo verificare di star monitorando entrambe le entita'
        relation * newrel;
        newrel=malloc(sizeof(relation));
        strcpy(newrel->rel_name,rel);
        newrel->tree=NULL;
        newrel->next=NULL;
        *rel_list=newrel;
        newrel->next_ent=NULL;

        //inserisco la relazione nell'albero
        relation_node *newrel_node;
        newrel_node=malloc(sizeof(relation_node));
        strcpy(newrel_node->to, name2);
        strcpy(newrel_node->from, name1);
        newrel_node->left=NULL;
        newrel_node->right=NULL;
        strcpy(newrel_node->reltype, rel);
        tree_insert(&newrel, &newrel_node);
                
        return;
    }
    else{
        //la lista ha almeno un elemento

        if(*rel_list!=NULL && strcmp((*rel_list)->rel_name, rel)>0 && (*rel_list)->next==NULL){
            relation * newrel;
            newrel=malloc(sizeof(relation));
            strcpy(newrel->rel_name,rel);
            newrel->tree=NULL;
            newrel->next=(*rel_list);
            (*rel_list)=newrel;
            newrel->next_ent=NULL;

            //inserisco in testa

            //inserisco la relazione nell'albero
            relation_node *newrel_node;
            newrel_node=malloc(sizeof(relation_node));
            strcpy(newrel_node->to, name2);
            strcpy(newrel_node->from, name1);
            newrel_node->left=NULL;
            newrel_node->right=NULL;
            strcpy(newrel_node->reltype, rel);
            tree_insert(&newrel, &newrel_node);

            return;
        }

        do{
            if(strcmp(temp_cursor->rel_name,rel)<0){
                if(temp_cursor->next!=NULL && strcmp(temp_cursor->next->rel_name,rel)>0){
                    relation * newrel;
                    newrel=malloc(sizeof(relation));
                    strcpy(newrel->rel_name,rel);
                    newrel->tree=NULL;

                    newrel->next=temp_cursor->next;
                    temp_cursor->next=newrel;
                    newrel->next_ent=NULL;

                    //inserisco la relazione nell'albero
                    relation_node *newrel_node;
                    newrel_node=malloc(sizeof(relation_node));
                    strcpy(newrel_node->to, name2);
                    strcpy(newrel_node->from, name1);
                    newrel_node->left=NULL;
                    newrel_node->right=NULL;
                    strcpy(newrel_node->reltype, rel);
                    tree_insert(&newrel, &newrel_node);

                    return;
                }
                else if(temp_cursor->next==NULL){

                    relation * newrel;
                    newrel=malloc(sizeof(relation));
                    strcpy(newrel->rel_name,rel);
                    newrel->tree=NULL;

                    newrel->next=temp_cursor->next;
                    temp_cursor->next=newrel;
                    newrel->next_ent=NULL;

                    //inserisco la relazione nell'albero
                    relation_node *newrel_node;
                    newrel_node=malloc(sizeof(relation_node));
                    strcpy(newrel_node->to, name2);
                    strcpy(newrel_node->from, name1);
                    newrel_node->left=NULL;
                    newrel_node->right=NULL;
                    strcpy(newrel_node->reltype, rel);
                    tree_insert(&newrel, &newrel_node);

                    return;
                }
            }
            else if(strcmp(temp_cursor->rel_name,rel)==0){
                //inserisco la relazione nell'albero
                relation_node *newrel_node;
                newrel_node=malloc(sizeof(relation_node));
                strcpy(newrel_node->to, name2);
                strcpy(newrel_node->from, name1);
                newrel_node->left=NULL;
                newrel_node->right=NULL;
                strcpy(newrel_node->reltype, rel);
                tree_insert(&temp_cursor, &newrel_node);

                return;
            }
            else if(temp_cursor->next==NULL){
                //sono all'ultimo elemento
                relation * newrel;
                newrel=malloc(sizeof(relation));
                strcpy(newrel->rel_name,rel);
                newrel->tree=NULL;

                temp_cursor->next=newrel;
                newrel->next=NULL;
                //positioned=1;
                newrel->next_ent=NULL;

                //inserisco la relazione nell'albero
                relation_node *newrel_node;
                newrel_node=malloc(sizeof(relation_node));
                strcpy(newrel_node->to, name2);
                strcpy(newrel_node->from, name1);
                newrel_node->left=NULL;
                newrel_node->right=NULL;
                strcpy(newrel_node->reltype, rel);
                tree_insert(&newrel, &newrel_node);

                return;
            }
            if(temp_cursor->next!=NULL){
                temp_cursor=temp_cursor->next;
            }
        }while(positioned!=1);
    }
}

void delrel_f(char name1[], char name2[], char rel[], relation** rel_list, entity* ht_entities[]){
    
}

void report_f(relation **rel_list){
    //devo scorrere la lista di relazioni
    relation *rel_cursor=*rel_list;
    ent_list* curs;
    if(rel_cursor==NULL){
        //la lista e' vuota
        fputs("none\n", stdout);
        return;
    }
    else{
        //devo trovare, per ogni tipo di relazione, l'entita' che riceve piu' relazioni
        do{
            // //eseguo il conto per ogni tipo di relazione non vuota
            // if(rel_cursor->tree!=NULL){
                fputs(rel_cursor->rel_name, stdout);
                fputs(" ", stdout);
            //     lista=NULL;
            //     inorder_tree_count(rel_cursor->tree, &lista);

            //     //ora ho la classifica delle entita' di questo tipo di relazione
                //trovo il massimo
                curs=((rel_cursor)->next_ent);
                int max=curs->ingresso;
                while (curs!=NULL){
                    if(curs->ingresso>max){
                        max=curs->ingresso;
                    }
                    curs=curs->next;
                }
                //rileggo la lista stampando solo gli elementi con ingresso=max
                curs=((rel_cursor)->next_ent);

                while (curs!=NULL){
                    if(curs->ingresso==max){
                        fputs(curs->entid, stdout);
                        fputs(" ", stdout);
                    }
                    curs=curs->next;
                }
                //printo il numero di rel
                printf("%d;", max);
                if(rel_cursor->next!=NULL){
                    putchar(' ');
                }
            rel_cursor=rel_cursor->next;
        }while(rel_cursor!=NULL);
        putchar('\n');
    }
}

int check_ent_hash(char name_to_check[], entity* ht_entities[]){

    int hashval;
    hashval=hash_function_entities(name_to_check);
    //printf("controllo: %s\n", name_to_check);

    entity * temp_cursor_ht = ht_entities[hashval];

    if(temp_cursor_ht==NULL){
        //slot vuoto
        return 0;
    }
    else{
        do{
            if(strcmp(temp_cursor_ht->name, name_to_check)==0){
                //esiste
                //printf("found\n");
                return 1;
            }
            temp_cursor_ht=temp_cursor_ht->next;
        }while(temp_cursor_ht!=NULL);
    }
    //printf("not found\n");
    return 0;
}

int hash_function_entities(char name_to_hash[]){
    //hash function
    //---------------------------------------------------------------------------------------------------------------
    //char ent_val_str[301]="";
    //char transformed[12];

    int valor=0;

    //QUI C'E' OVERFLOW
    //char*robe = NULL;
    for(int i=0;i<strlen(name_to_hash);i++){
        // //converto ogni carattere del nome nel suo valore ascii
        // sprintf(transformed,"%d",(int)name_to_hash[i]);
        // //ogni valore ascii viene affiancato al valore ascii del carattere prima
        // strcat(ent_val_str, transformed);
        valor=valor+((((int)name_to_hash[i])*i));
        
        // sprintf(transformed,"%ld",( strtol(ent_val_str, &robe, 10) )%HASHNUM);
        // strcpy(ent_val_str, transformed);

        //printf("il valore hash di %s e' %s\n", name_to_hash, ent_val_str);
    }
    //---------------------------------------------------------------------------------------------------------------
    //fine hash function

    //int valore=((int)ent_val_str);
    //long int valore = strtol(ent_val_str,&robe,10);

    if(valor<0){
        valor=-valor;
    }
    //printf("%ld e' il valore di %s\n", valore, name_to_hash);

    valor=valor%HASHNUM;
    return valor;
    //return 0;
}

void tree_insert(relation **reltype, relation_node **z){
    //copio lo pseudocodice delle slides

    relation_node *y=NULL;
    relation_node *x=(*reltype)->tree;
    //relation_node *z=*relation;
    while(x!=NULL){
        y=x;
        if(strcmp((*z)->to, x->to)<0){
            x=x->left;
        }
        else if(strcmp((*z)->to, x->to)>0){
            x=x->right;
        }
        else if(strcmp((*z)->to, x->to)==0){
            //il to e' uguale allora smisto per from
            if(strcmp((*z)->from, x->from)<0){
                x=x->left;
            }
            else if(strcmp((*z)->from, x->from)>0){
                x=x->right;
            }
            else if(strcmp((*z)->from, x->from)==0){
                //sia to che from sono uguali, allora esco senza fare nulla
                return;
            }
        }
    }
    (*z)->p=y;
    if(y==NULL){
        //l'albero e' vuoto
        (*reltype)->tree=*z;
        alphabetical_ent_insert(reltype, (*z)->to);
    }
    else if(strcmp((*z)->to, y->to)<0){
        y->left=*z;
        alphabetical_ent_insert(reltype, (*z)->to);
    }
    else if(strcmp((*z)->to, y->to)>0){
        y->right=*z;
        alphabetical_ent_insert(reltype, (*z)->to);
    }
    else if(strcmp((*z)->to, y->to)==0){
        //il to e' uguale allora smisto per from
        if(strcmp((*z)->from, y->from)<0){
            y->left=*z;
            alphabetical_ent_insert(reltype, (*z)->to);
        }
        else if(strcmp((*z)->from, y->from)>0){
            y->right=*z;
            alphabetical_ent_insert(reltype, (*z)->to);
        }
        else if(strcmp((*z)->from, y->from)==0){
            //sia to che from sono uguali, allora esco senza fare nulla
            return;
        }
    }
}

void inorder_tree_count(relation_node* relnode, ent_list** lista){
    if(relnode!=NULL){
        inorder_tree_count(relnode->left, lista);

        //qui in mezzo devo fare la verifica per l'inserimento nella lista
        //creo il cursore per scorrere le entita'
        ent_list* cursor=*lista;
        int found=0;
        //scorro la lista di entita', se l'entita' esiste aggiungo 1 al conto, se non esiste creo l'entita' con to 1
        if(cursor==NULL){
            //la lista e' vuota
            ent_list* newent=malloc(sizeof(ent_list));
            strcpy(newent->entid, relnode->to);
            newent->next=NULL;
            newent->ingresso=1;
            *lista=newent;
            cursor=(*lista)->next;
            found=1;
        }
        else{
            while(cursor!=NULL&&found==0){
                if(strcmp(cursor->entid, relnode->to)==0){
                    //ho trovato lo stesso to
                    cursor->ingresso++;
                    found=1;
                }
                else{
                    if(cursor->next==NULL){
                        //sono all'ultimo elemento e non ho trovato corrispondenze quindi aggiungo
                        ent_list* newent=malloc(sizeof(ent_list));
                        strcpy(newent->entid, relnode->to);
                        cursor->next=newent;
                        newent->next=NULL;
                        newent->ingresso=1;
                        found=1;
                    }
                }
                cursor=cursor->next;
            }
        }

        inorder_tree_count(relnode->right, lista);
    }
}

// void inorder_tree_walk(relation_node* relnode){
//     if(relnode!=NULL){
//         inorder_tree_walk(relnode->left);
//         printf("to: %s, from: %s\n", relnode->to, relnode->from);
//         inorder_tree_walk(relnode->right);
//     }
// }

// void merge_sort(){

// }

void alphabetical_ent_insert(relation** rel_elem, char entity_id[]){
    //inserisco la relazione nella lista contenuta nella relazione
    ent_list* cursore=(*rel_elem)->next_ent;
    if(cursore==NULL){
        //va in testa
        //printf("testa1\n");
        ent_list* newent_list=malloc(sizeof(ent_list));
        strcpy(newent_list->entid, entity_id);
        newent_list->ingresso=1;
        newent_list->next=(*rel_elem)->next_ent;   //crea problemi
        //printf("ciao\n");
        (*rel_elem)->next_ent=newent_list;
        return;
    }
    else if(strcmp((*rel_elem)->next_ent->entid, entity_id)>0){
        //va in testa
        //printf("testa2\n");
        ent_list* newent_list=malloc(sizeof(ent_list));
        strcpy(newent_list->entid, entity_id);
        newent_list->ingresso=1;
        newent_list->next=(*rel_elem)->next_ent;
        (*rel_elem)->next_ent=newent_list;
        return;
    }
    else{
        do{
            if(strcmp(cursore->entid, entity_id)<0){
                if(cursore->next==NULL){
                    ent_list* newent_list=malloc(sizeof(ent_list));
                    strcpy(newent_list->entid, entity_id);
                    newent_list->ingresso=1;
                    newent_list->next=cursore->next;
                    cursore->next=newent_list;
                    return;
                }
                else if(strcmp(cursore->next->entid, entity_id)>0){
                    ent_list* newent_list=malloc(sizeof(ent_list));
                    strcpy(newent_list->entid, entity_id);
                    newent_list->ingresso=1;
                    newent_list->next=cursore->next;
                    cursore->next=newent_list;
                    return;
                }
            }
            else if(strcmp(cursore->entid, entity_id)==0){
                cursore->ingresso++;
                return;
            }
            cursore=cursore->next;
            if(cursore->next==NULL){
                //metto in coda
                ent_list* newent_list=malloc(sizeof(ent_list));
                strcpy(newent_list->entid, entity_id);
                newent_list->ingresso=1;
                newent_list->next=cursore->next;
                cursore->next=newent_list;
                return;
            }
        }while (cursore!=NULL);
    }
    //printf("pizza\n");
    //fine inserimento
}

void tree_delete(relation_node** relnode, char name[]){
    //devo scorrere l'albero con inorder_tree_walk
    if((*relnode)!=NULL){
        tree_delete(&(*relnode)->left, name);
        
        //qui devo eliminare l'elemento
        if(strcmp((*relnode)->to, name)==0 || strcmp((*relnode)->from, name)==0){
            if((*relnode)->left==NULL && (*relnode)->right==NULL){
                //caso 1
                relation_node* todelete=*relnode;
                
            }
        }

        tree_delete(&(*relnode)->right, name);
    }
}