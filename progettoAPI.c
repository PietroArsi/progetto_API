#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHNUM 2053
#define RED 1
#define BLACK 0
#define TO 1
#define FROM 0

//codice per il progetto di API

typedef struct relation{
    char* rel_name_p;   //dinamico
    struct relation *next;
    struct relation_node *tree;
    struct ent_node* ent_tree;
    int max;
}relation;

typedef struct entity{
    char* name_p;
    struct entity *next;
}entity;

typedef struct relation_node{
    entity* from;
    entity* to;
    struct relation_node *p;
    struct relation_node *left;
    struct relation_node *right;
    //struct relation_node *root;
    short int color;
}relation_node;

typedef struct ent_node{
    entity* ent;
    short int ingresso;
    //struct ent_node* next;
    //bst
    struct ent_node *p;
    struct ent_node *left;
    struct ent_node *right;
    //struct ent_node *root;
}ent_node;

typedef struct nodes_to_delete{
    relation_node* node;
    struct nodes_to_delete* next;
}nodes_to_delete;

typedef struct ents_to_print{
    ent_node* node;
    struct ents_to_print* next;
}ents_to_print;

typedef struct ents_to_delete{
    ent_node* node;
    struct ents_to_delete* next;
}ents_to_delete;

//prototypes
void addent_f(char name[], entity* ht_entities[]);
void delent_f(char name[], entity* ht_entities[], relation **rel_list);
void addrel_f2(char name1[], char name2[], char rel[], relation **rel_list, entity* ht_entities[]);
void delrel_f(char name1[], char name2[], char rel[], relation **rel_list, entity* ht_entities[]);
void report_f(relation **rel_list);
int check_ent_hash(unsigned int, char name[], entity* ht_entities[]);
unsigned int hash_function_entities(char name[]);
//void alphabetical_ent_insert(relation** rel_elem, char entity_id[], entity* ht_entities[]);
void tree_find(relation* reltype, relation_node* root, relation_node* rel, char name[], nodes_to_delete**);
relation_node* tree_find_rel(relation* reltype, relation_node* root, relation_node* rel, char name1[], char name2[]);
void inorder_tree_walk(relation_node* relnode);
relation_node* tree_minimum(relation_node* nodo);
relation_node* tree_maximum(relation_node* nodo);
relation_node* tree_successor(relation_node* nodo);
void list_insert(nodes_to_delete** cestino, relation_node* nodetodelete);
void left_rotate(relation** rel,relation_node* x);
void right_rotate(relation** rel,relation_node* x);
int RB_insert(relation** rel,relation_node* z, entity* ht_entities[]);
void RB_insert_FIXUP(relation** rel,relation_node* z);
relation_node* RB_delete(relation** rel,relation_node* z);
void RB_delete_FIXUP(relation** rel,relation_node* z);
//void tree_delete_ent(); //da usare per la entlist
ent_node* tree_search_ent(ent_node* root, ent_node* entnode, char name[]); //da usare per la entlist
ent_node* tree_delete_function(relation** reltype,ent_node* z); //da usare per la entlist
void ent_tree_insert(relation *reltype, ent_node* node);  //da usare per la entlist
void tree_dimcount_ent(relation* reltype, ent_node* root, ent_node* entnode, char name[]); //da usare per la entlist
void tree_find_max(ent_node*, int*); //da usare per la entlist
void tree_find_ents(ent_node* entnode, int* max, ents_to_print**list); //da usare per la entlist
void list_insert_tail(ents_to_print** list, ent_node* entnode); //da usare per la entlist
void print2D(relation_node *root);
void print2DUtil(relation_node *root, int space);
ent_node* tree_successor_ent(ent_node* x);
ent_node* tree_maximum_ent(ent_node* nodo);
ent_node* tree_minimum_ent(ent_node* nodo);
void ent_tree_walk(ent_node* relnode);
void print_ents_with_max(ent_node*, int);
void printa_stringa(char*);


//nodo NIL
relation_node* NIL;
ent_node* ENIL;


int main(){

    //inizializzo il nodo NIL
    NIL=malloc(sizeof(relation_node));
    NIL->color=BLACK;
    ENIL=malloc(sizeof(ent_node));

    //parser

    char input_text[1000];
    char* tok=malloc(sizeof(char)*11);
    
    //FILE * f=fopen("/Users/pietroarsi/Desktop/POLI/API/progetto API/batch2.1.in", "r");

    char* param1=malloc(sizeof(char)*101);
    char* param2=malloc(sizeof(char)*101);
    char* param3=malloc(sizeof(char)*101);

    //inizializzo la lista di relazioni
    relation* rel=NULL;
    //inizializzo la lista per la report
    //ent_list* lista=NULL;

    //inizializzo la hash table
    entity* ht_entities[HASHNUM];
    for(int i=0;i<HASHNUM;i++){
        ht_entities[i]=NULL;
    }

    int paraculo=0;
    //char pars[2]=" ";

    do{
        //leggo l'input e faccio strcmp per vedere cosa devo fare

        //da fare: regolare i buffer per l'input a seconda di quanto sono grandi gli input
        
        
        fgets(input_text, 1000, stdin);
        //printf("---%s---\n", input_text);
        //input_text=input_text+ "\0";

        tok=strtok(input_text, " \n");
        //printf("%s\n", tok);
        if(strcmp(tok, "addent")==0){
            //fgets(param1, 101, stdin);
            param1=strtok(NULL, " \n");
            //printf("%s\n", param1);
            //printf("addent\n");
            addent_f(param1, ht_entities);
        }
        else if(strcmp(tok, "delent")==0){
            //fgets(param1, 101, stdin);
            param1=strtok(NULL, " \n");
            delent_f(param1, ht_entities, &rel);
        }
        else if(strcmp(tok, "addrel")==0){
            // fgets(param1, 101, stdin);
            // fgets(param2, 101, stdin);
            // fgets(param3, 101, stdin);
            param1=strtok(NULL, " \n");
            param2=strtok(NULL, " \n");
            param3=strtok(NULL, " \n");
            //printf("addrel\n");
            addrel_f2(param1, param2, param3, &rel, ht_entities);
        }
        else if(strcmp(tok, "delrel")==0){
            // fgets(param1, 101, stdin);
            // fgets(param2, 101, stdin);
            // fgets(param3, 101, stdin);
            param1=strtok(NULL, " \n");
            param2=strtok(NULL, " \n");
            param3=strtok(NULL, " \n");
            delrel_f(param1, param2, param3, &rel, ht_entities);
        }
        else if(strcmp(tok, "report")==0){
            //printf("ciao");
            report_f(&rel);
        }
    }while (strcmp(tok, "end")!=0);

    return 0;
}

void addent_f(char name[], entity* ht_entities[]){
    //uso un'hash function per aggiungere le entita' alla hash table
    //come hash function uso      k mod 2053
    unsigned int hashval=hash_function_entities(name);
    int bool=check_ent_hash(hashval, name, ht_entities);
    if(bool==(1)){
        return;
    }

    entity* newent=malloc(sizeof(entity));
    char* ent_tocopy=malloc((strlen(name)+1)*sizeof(char));
    strcpy(ent_tocopy, name);
    newent->name_p=ent_tocopy;
    newent->next=ht_entities[hashval];
    ht_entities[hashval]=newent;
}

void delent_f(char name[], entity* ht_entities[], relation **rel_list){
    unsigned int hashval=hash_function_entities(name);
    int bool=check_ent_hash(hashval, name, ht_entities);
    if(bool==(0)){
        //printf("ho gia' eliminato %s\n", name);
        return;
    }

    //prima devo eliminare ogni entita' name da ogni ent_list
    relation* rel_cursor=*rel_list;
    nodes_to_delete* cestino=NULL;
    nodes_to_delete* cest_cursore;
    nodes_to_delete* old;

    ent_node*found=ENIL;

    relation_node* el=NIL;

    //printf("delent di %s\n", name);
    while(rel_cursor!=NULL){
        //scorro le relazioni
        //elimino la ent dall'alberto delle ent della report
        //printf("max di %s prima: %d\n",rel_cursor->rel_name_p ,rel_cursor->max);

        found=tree_search_ent(rel_cursor->ent_tree, rel_cursor->ent_tree, name);;

        if(found!=ENIL){
            free(tree_delete_function(&rel_cursor, found));
            rel_cursor->max=0;
            tree_find_max(rel_cursor->ent_tree, &(rel_cursor->max));
        }

        cestino=NULL;
        tree_find(rel_cursor, rel_cursor->tree, rel_cursor->tree, name, &cestino);
        //printf("max: %d\n", rel_cursor->max);
        cest_cursore=cestino;
        while(cest_cursore!=NULL){
            //printf("elimino relazione %s da %s a %s\n", rel_cursor->rel_name_p, cest_cursore->node->from->name_p, cest_cursore->node->to->name_p);
            free(RB_delete(&rel_cursor, (cest_cursore->node)));
            old=cest_cursore;
            cest_cursore=cest_cursore->next;
            free(old);
        }
        rel_cursor->max=0;
        tree_find_max(rel_cursor->ent_tree, &(rel_cursor->max));
        //printf("max di %s dopo: %d\n",rel_cursor->rel_name_p ,rel_cursor->max);
        rel_cursor=rel_cursor->next;
    }


    //cerco l'entita' nell'hash table e la elimino
    entity *temp_cursor=ht_entities[hashval];
    if(ht_entities[hashval]==NULL){
        //se lo slot dell'hashtable è vuoto esco
        return;
    }
    else{
        //altrimento lo slot ha qualcosa dentro
        if(ht_entities[hashval]!=NULL && strcmp(ht_entities[hashval]->name_p, name)==0){
            //devo eliminare il primo della lista
            entity* todelete_e=ht_entities[hashval];
            ht_entities[hashval]=ht_entities[hashval]->next;
            free(todelete_e->name_p);
            free(todelete_e);
            return;
        }
        do{
            //comincio a guardare quelli dopo
            if(temp_cursor->next!=NULL && strcmp(temp_cursor->next->name_p, name)==0){
                //ho trovato l'entita' da togliere
                entity* todelete=temp_cursor->next;
                temp_cursor->next=temp_cursor->next->next;
                free(todelete->name_p);
                free(todelete);
                return;
            }
            temp_cursor=temp_cursor->next;
        }while(temp_cursor!=NULL);
    }
}

void addrel_f2(char name1[], char name2[], char rel[], relation** rel_list, entity* ht_entities[]){
    //se non ci sono le entita' esco subito
    unsigned int hashval1=hash_function_entities(name1);
    unsigned int hashval2=hash_function_entities(name2);
    int bool1=check_ent_hash(hashval1, name1, ht_entities);
    int bool2=check_ent_hash(hashval2, name2, ht_entities);
    if(bool1==(0) || bool2==(0)){
        return;
    }

    //scorro la lista con un cursore temporaneo
    relation *temp_cursor=*rel_list;

    //int positioned=0;
    int found=0;
    entity* toentity;

    if((temp_cursor==NULL) || (strcmp(((temp_cursor)->rel_name_p), rel)>0)){
        //inserisco in testa
        //la lista dei tipi di relazioni è vuota ma devo verificare di star monitorando entrambe le entita'
        relation * newrel=malloc(sizeof(relation));

        char* rel_tocopy=malloc((strlen(rel)+1)*sizeof(char));
        strcpy(rel_tocopy, rel);
        newrel->rel_name_p=rel_tocopy;

        newrel->ent_tree=ENIL;
        newrel->tree=NIL;
        newrel->next=(*rel_list);
        newrel->max=0;
        (*rel_list)=newrel;
        //inserisco la relazione nell'albero
        relation_node *newrel_node=malloc(sizeof(relation_node));

        entity*ent_cursor;
        //trovo la entita' 1
        found=0;
        ent_cursor=ht_entities[hashval1];
        while(found!=1 && ent_cursor!=NULL){
            if (strcmp(ent_cursor->name_p, name1)==0){
                newrel_node->from=ent_cursor;
                found=1;
            }
            ent_cursor=ent_cursor->next;
        }
        //trovo la entita' 2
        found=0;
        ent_cursor=ht_entities[hashval2];
        while(found!=1 && ent_cursor!=NULL){
            if (strcmp(ent_cursor->name_p, name2)==0){
                newrel_node->to=ent_cursor;
                found=1;
                toentity=ent_cursor;
            }
            ent_cursor=ent_cursor->next;
        }

        newrel_node->left=NIL;
        newrel_node->right=NIL;
        int check = RB_insert(&newrel, newrel_node, ht_entities);
        if(check==1){
            ent_node* newentnode=malloc(sizeof(ent_node));
            newentnode->ent=toentity;
            newentnode->ingresso=1;
            newentnode->left=ENIL;
            newentnode->right=ENIL;
            ent_tree_insert((newrel), newentnode);
            //tree_find_max((*rel_list)->ent_tree, &((*rel_list)->max));
        }
        return;
    }
    else{
        //la lista ha almeno un elemento
        do{
            if(strcmp(temp_cursor->rel_name_p,rel)==0){
                //inserisco la relazione nell'albero
                relation_node *newrel_node=malloc(sizeof(relation_node));

                entity*ent_cursor;
                //trovo la entita' 1
                found=0;
                ent_cursor=ht_entities[hashval1];
                while(found!=1 && ent_cursor!=NULL){
                    if (strcmp(ent_cursor->name_p, name1)==0){
                        newrel_node->from=ent_cursor;
                        found=1;
                    }
                    ent_cursor=ent_cursor->next;

                }
                //trovo la entita' 2
                found=0;
                ent_cursor=ht_entities[hashval2];
                while(found!=1 && ent_cursor!=NULL){
                    if (strcmp(ent_cursor->name_p, name2)==0){
                        newrel_node->to=ent_cursor;
                        found=1;
                        toentity=ent_cursor;
                    }
                    ent_cursor=ent_cursor->next;
                }
                newrel_node->left=NIL;
                newrel_node->right=NIL;
                int check = RB_insert(&temp_cursor, newrel_node, ht_entities);
                if(check==1){
                    ent_node* newentnode=malloc(sizeof(ent_node));
                    newentnode->ent=toentity;
                    newentnode->ingresso=1;
                    newentnode->left=ENIL;
                    newentnode->right=ENIL;
                    ent_tree_insert(temp_cursor, newentnode);
                    //tree_find_max(temp_cursor->ent_tree, &(temp_cursor->max));
                }
                return;
            }
            else if((temp_cursor->next==NULL) || (strcmp((temp_cursor->rel_name_p),rel)<0 && strcmp((temp_cursor->next->rel_name_p),rel)>0)){
                relation * newrel=malloc(sizeof(relation));

                char* rel_tocopy=malloc((strlen(rel)+1)*sizeof(char));
                strcpy(rel_tocopy, rel);
                newrel->rel_name_p=rel_tocopy;
                newrel->tree=NIL;
                newrel->ent_tree=ENIL;
                newrel->next=temp_cursor->next;
                newrel->max=0;
                temp_cursor->next=newrel;
                //inserisco la relazione nell'albero
                relation_node *newrel_node=malloc(sizeof(relation_node));

                entity*ent_cursor;
                //trovo la entita' 1
                found=0;
                ent_cursor=ht_entities[hashval1];
                while(found!=1 && ent_cursor!=NULL){
                    if (strcmp(ent_cursor->name_p, name1)==0){
                        newrel_node->from=ent_cursor;
                        found=1;
                    }
                    ent_cursor=ent_cursor->next;
                }
                //trovo la entita' 2
                found=0;
                ent_cursor=ht_entities[hashval2];
                while(found!=1 && ent_cursor!=NULL){
                    if (strcmp(ent_cursor->name_p, name2)==0){
                        newrel_node->to=ent_cursor;
                        found=1;
                        toentity=ent_cursor;
                    }
                    ent_cursor=ent_cursor->next;
                }

                newrel_node->left=NIL;
                newrel_node->right=NIL;
                int check = RB_insert(&newrel, newrel_node, ht_entities);
                if(check==1){
                    ent_node* newentnode=malloc(sizeof(ent_node));
                    newentnode->ent=toentity;
                    newentnode->ingresso=1;
                    newentnode->left=ENIL;
                    newentnode->right=ENIL;
                    ent_tree_insert(newrel, newentnode);
                    //tree_find_max(temp_cursor->next->ent_tree, &(temp_cursor->next->max));
                }
                return;
            }
            temp_cursor=temp_cursor->next;
        }while(temp_cursor!=NULL);
    }
}

void delrel_f(char name1[], char name2[], char rel[], relation** rel_list, entity* ht_entities[]){
    //se non ci sono le entita' esco subito
    unsigned int hashval1=hash_function_entities(name1);
    unsigned int hashval2=hash_function_entities(name2);
    int bool1=check_ent_hash(hashval1, name1, ht_entities);
    int bool2=check_ent_hash(hashval2, name2, ht_entities);
    if(bool1==(0) || bool2==(0)){
        return;
    }

    //elimino la relazione dall'albero delle relazioni
    relation* rel_cursor=*rel_list;
    while(rel_cursor!=NULL){
        if(strcmp(rel_cursor->rel_name_p, rel)==0){
            //ho trovato la relazione da eliminare
            //cerco la relazione nell'albero
            relation_node* node_todelete=tree_find_rel(rel_cursor, rel_cursor->tree, rel_cursor->tree, name1, name2);
            if(node_todelete!=NIL){
                //la relazione esiste nell'albero, quindi la elimino
                free(RB_delete(&(rel_cursor), (node_todelete)));
            }
            return;
        }
        rel_cursor=rel_cursor->next;
    }
}

void report_f(relation **rel_list){
    //devo scorrere la lista di relazioni
    relation *rel_cursor=*rel_list;
    int donesomething=0;
    int max;
    //int first=0;
    if(rel_cursor==NULL){
        //la lista e' vuota
        //printa_stringa("none\n");
        fputs("none\n", stdout);
        return;
    }
    else{
        //devo trovare, per ogni tipo di relazione, l'entita' che riceve piu' relazioni
        do{
            // //eseguo il conto per ogni tipo di relazione non vuota
            if(rel_cursor->ent_tree!=ENIL){
                //max=0;
                max=rel_cursor->max;
                //devo scorrere l'albero e stampare solo fino a che il massimo rimane quello
                if(max>0){
                    donesomething=1;
                    //printa_stringa(rel_cursor->rel_name_p);
                    fputs(rel_cursor->rel_name_p, stdout);
                    putc(' ', stdout);
                    print_ents_with_max(rel_cursor->ent_tree, max);

                    //printo il numero di rel
                    printf("%d", max);
                    putc(';', stdout);
                    if(rel_cursor->next!=NULL){
                        putc(' ', stdout);
                    }
                }
            }
            rel_cursor=rel_cursor->next;
        }while(rel_cursor!=NULL);

        if(donesomething==0){
            printa_stringa("none");
        }
        putc('\n', stdout);
    }
}

int check_ent_hash(unsigned int hashv, char name_to_check[], entity* ht_entities[]){
    entity * temp_cursor_ht = ht_entities[hashv];

    while(temp_cursor_ht!=NULL){
        if(strcmp(temp_cursor_ht->name_p, name_to_check)==0){
            //esiste
            return 1;
        }
        temp_cursor_ht=temp_cursor_ht->next;
    }
    return 0;
}

unsigned int hash_function_entities(char name_to_hash[]){

    int valor=0;

    //QUI C'E' OVERFLOW
    int len=strlen(name_to_hash);
    for(int i=0;i<len;i++){
        valor=valor+((((int)name_to_hash[i])*i));

        //printf("il valore hash di %s e' %s\n", name_to_hash, ent_val_str);
    }
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

void tree_find(relation* reltype, relation_node* root, relation_node* relnode, char name[], nodes_to_delete** cestino){
    //devo scorrere l'albero con inorder_tree_walk
    if((relnode)!=NIL){
        tree_find(reltype, root, ((relnode)->left), name, cestino);

        //verifica e eventuale inserimento nella lista
        //printf("entita' cercata: %s, nodo da %s a %s\n", name, relnode->from->name_p, relnode->to->name_p);
        int tocmp=strcmp(relnode->to->name_p, name);
        int fromcmp=strcmp(relnode->from->name_p, name);
        if((tocmp==0) || (fromcmp==0)){
            //e' da eliminare
            list_insert(cestino, relnode);
            if(fromcmp==0){
                //devo diminuire il contatore ingresso
                //printf("devo diminuire il contatore di %s\n", relnode->to->name_p);
                tree_dimcount_ent(reltype, reltype->ent_tree, reltype->ent_tree,relnode->to->name_p);
                //tree_find_max(reltype->ent_tree, &(reltype->max));
            }
        }

        tree_find(reltype, root, ((relnode)->right), name, cestino);
    }
}

relation_node* tree_minimum(relation_node* nodo){
    relation_node* curs=nodo;
    while(curs->left!=NIL){
        curs=curs->left;
    }
    return curs;
}

relation_node* tree_maximum(relation_node* nodo){
    relation_node* curs=nodo;
    while(curs->right!=NIL){
        curs=curs->right;
    }
    return curs;
}

relation_node* tree_successor(relation_node* x){
    if(x->right!=NIL){
        return tree_minimum(x->right);
    }
    relation_node* y= (x->p);
    while(y!=NIL && x==y->right){
        x=y;
        y=y->p;
    }
    return y;
}

relation_node* tree_find_rel(relation* reltype, relation_node* root, relation_node* relnode, char name1[], char name2[]){
    if(relnode==NIL || (strcmp(relnode->from->name_p, name1)==0 && strcmp(relnode->to->name_p, name2)==0)){
        if(relnode!=NIL){
            //diminuisco il counter per l'entita' to e ritorno il nodo
            tree_dimcount_ent(reltype, reltype->ent_tree, reltype->ent_tree, name2);
        }
        return relnode;
    }
    int compare=strcmp(relnode->to->name_p, name2);
    if(compare>0){
        return tree_find_rel(reltype, root, relnode->left, name1, name2);
    }
    else if(compare<0){
        return tree_find_rel(reltype, root, relnode->right, name1, name2);
    }
    else if(compare==0){
        compare=strcmp(relnode->from->name_p, name1);
        if(compare>0){
            return tree_find_rel(reltype, root, relnode->left, name1, name2);
        }
        else /*if(strcmp(relnode->from->name_p, name1)<0)*/{
            return tree_find_rel(reltype, root, relnode->right, name1, name2);
        }
    }
    return NIL;
}

void inorder_tree_walk(relation_node* relnode){
    if(relnode!=NIL){
        inorder_tree_walk(relnode->left);
        printf("nodo---> da %s a %s\n", relnode->from->name_p, relnode->to->name_p);
        inorder_tree_walk(relnode->right);
    }
}

void list_insert(nodes_to_delete** cestino, relation_node* nodetodelete){
    nodes_to_delete* newgarbage=malloc(sizeof(nodes_to_delete));
    newgarbage->next=*cestino;
    newgarbage->node=nodetodelete;
    *cestino=newgarbage;
}

void left_rotate(relation** rel,relation_node* x){
    relation_node* y= (x)->right;
    (x)->right=y->left;
    if(y->left!=NIL){
        y->left->p=(x);
    }
    y->p=(x)->p;
    if((x)->p==NIL){
        (*rel)->tree=y;
    }
    else if((x)==(x)->p->left){
        (x)->p->left=y;
    }
    else{
        (x)->p->right=y;
    }
    y->left=x;
    (x)->p=y;
}

void right_rotate(relation** rel,relation_node* y){
    //printf("%s %s\n", (*y)->from->name_p, (*y)->to->name_p);
    relation_node* x= (y)->left;
    (y)->left=x->right;
    if(x->right!=NIL){
        x->right->p=(y);
    }
    x->p=(y)->p;
    if((y)->p==NIL){
        (*rel)->tree=x;
    }
    else if((y)==(y)->p->left){
        (y)->p->left=x;
    }
    else{
        (y)->p->right=x;
    }
    x->right=y;
    (y)->p=x;
}

int RB_insert(relation** rel,relation_node* z, entity* ht_entities[]){
    //copio lo pseudocodice delle slides
    //inorder_tree_walk((*rel)->tree);

    relation_node* y=NIL;
    relation_node* x=((*rel)->tree);
    int compare;
    int check=0;
    while(x!=NIL){
        y=x;
        compare=strcmp((z)->to->name_p, x->to->name_p);
        if(compare<0){
            x=x->left;
        }
        else if(compare>0){
            //loop infinito
            x=x->right;
        }
        else if(compare==0){
            compare=strcmp((z)->from->name_p, x->from->name_p);
            //il to e' uguale allora smisto per from
            if(compare<0){
                x=x->left;
            }
            else if(compare>0){
                //printf("%s %s con %s %s\n", (*z)->from->name_p, (*z)->to->name_p, x->from->name_p, x->to->name_p);
                x=x->right;
            }
            else if(compare==0){
                //sia to che from sono uguali, allora esco senza fare nulla
                //TODO: freeo il nodo
                free(z);
                return 0;
            }
        }
    }
    (z)->p=y;
    if(y==NIL){
        //l'albero e' vuoto
        (*rel)->tree=z;
        //alphabetical_ent_insert(rel, (z)->to->name_p, ht_entities);
        check = 1;
    }
    else{
        compare=strcmp((z)->to->name_p, y->to->name_p);
        if(compare<0){
            y->left=z;
            //alphabetical_ent_insert(rel, (z)->to->name_p, ht_entities);
            check = 1;
        }
        else if(compare>0){
            y->right=z;
            //alphabetical_ent_insert(rel, (z)->to->name_p, ht_entities);
            check = 1;
        }
        else if(compare==0){
            compare=strcmp((z)->from->name_p, y->from->name_p);
            //il to e' uguale allora smisto per from
            if(compare<0){
                y->left=z;
                //alphabetical_ent_insert(rel, (z)->to->name_p, ht_entities);
                check = 1;
            }
            else if(compare>0){
                y->right=z;
                //alphabetical_ent_insert(rel, (z)->to->name_p, ht_entities);
                check = 1;
            }
            else if(compare==0){
                //sia to che from sono uguali, allora esco senza fare nulla
                //return;
            }
        }
    }
    (z)->left=NIL;
    (z)->right=NIL;
    (z)->color=RED;
    RB_insert_FIXUP(rel, z);
    return check;
}

void RB_insert_FIXUP(relation** rel,relation_node* z){ 
    relation_node* y;
    while((z)->p->color==RED){
        if((z)->p==(z)->p->p->left){
            y=(z)->p->p->right;
            if(y->color==RED){
                (z)->p->color=BLACK;
                y->color=BLACK;
                (z)->p->p->color=RED;
                (z)=(z)->p->p;
            }else if((z)==(z)->p->right){
                (z)=(z)->p;
                left_rotate(rel, z);
            }else{
                (z)->p->color=BLACK;
                (z)->p->p->color=RED;
                //printf("%s %s\n", (*z)->p->p->p->from->name_p, (*z)->p->p->p->to->name_p);
                right_rotate(rel, ((z)->p->p));
            }
        }else{
            y=(z)->p->p->left;
            if(y->color==RED){
                (z)->p->color=BLACK;
                y->color=BLACK;
                (z)->p->p->color=RED;
                (z)=(z)->p->p;
            }else if((z)==(z)->p->left){
                (z)=(z)->p;
                right_rotate(rel, z);
            }else{
                (z)->p->color=BLACK;
                (z)->p->p->color=RED;
                left_rotate(rel, ((z)->p->p));
            }
        }
    }
    (*rel)->tree->color=BLACK;
}

void RB_delete_FIXUP(relation** rel,relation_node* x){
    relation_node* w=NIL;
    while((x)!=(*rel)->tree && (x)->color==BLACK){
        if((x)==(x)->p->left){
            w=(x)->p->right;
            if(w->color==RED){
                w->color=BLACK;
                (x)->p->color=RED;
                left_rotate(rel, ((x)->p));
                w=(x)->p->right;
            }
            if(w->left->color==BLACK && w->right->color==BLACK){
                w->color=RED;
                (x)=(x)->p;
            }
            else{
                if(w->right->color==BLACK){
                    w->left->color=BLACK;
                    w->color=RED;
                    right_rotate(rel, w);
                    w=(x)->p->right;
                }
                w->color=(x)->p->color;
                (x)->p->color=BLACK;
                (w)->right->color=BLACK;
                left_rotate(rel, ((x)->p));
                (x)=(*rel)->tree;
            }
        }
        else{
            //symmetric
            w=(x)->p->left;
            if(w->color==RED){
                w->color=BLACK;
                (x)->p->color=RED;
                right_rotate(rel, ((x)->p));
                w=(x)->p->left;
            }
            if(w->right->color==BLACK && w->left->color==BLACK){
                w->color=RED;
                (x)=(x)->p;
            }
            else{
                if(w->left->color==BLACK){
                    w->right->color=BLACK;
                    w->color=RED;
                    left_rotate(rel, w);
                    w=(x)->p->left;
                }
                w->color=(x)->p->color;
                (x)->p->color=BLACK;
                (w)->left->color=BLACK;
                right_rotate(rel, ((x)->p));
                (x)=(*rel)->tree;
            }
        }
    }
    (x)->color=BLACK;
}

void print2D(relation_node *root){  
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}

void print2DUtil(relation_node *root, int space){  
    // Base case 
    if (root == NIL) 
        return; 
  
    // Increase distance between levels 
    space += 10; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = 10; i < space; i++){
        printf(" "); 
    }

    printf("%s-%s\n", root->from->name_p, root->to->name_p); 
  
    // Process left child 
    print2DUtil(root->left, space);   
}

void RB_transplant(relation** rel, relation_node *u, relation_node *v){
    if(u->p==NIL){
        (*rel)->tree=v;
    }
    else if(u==u->p->left){
        u->p->left=v;
    }
    else{
        u->p->right=v;
    }
    v->p=u->p;
}

relation_node* RB_delete(relation** rel,relation_node* z){
    relation_node* y=z;
    relation_node* x;
    int y_original_color=y->color;
    if(z->left==NIL){
        x=z->right;
        RB_transplant(rel, z, z->right);
    }
    else if(z->right==NIL){
        x=z->left;
        RB_transplant(rel, z, z->left);
    }
    else{
        y=tree_minimum(z->right);
        y_original_color=y->color;
        x=y->right;
        if(y->p==z){
            x->p=y;
        }
        else{
            RB_transplant(rel, y, y->right);
            y->right=z->right;
            y->right->p=y;
        }
        RB_transplant(rel, z, y);
        y->left=z->left;
        y->left->p=y;
        y->color=z->color;
    }
    if(y_original_color==BLACK){
        RB_delete_FIXUP(rel, x);
    }
    return z;
}

int find_max(relation* rel){
    // ent_node*curs=((rel)->next_ent);
    // int max=0;
    // while (curs!=NULL){
    //     if(curs->ingresso>max){
    //         max=curs->ingresso;
    //     }
    //     curs=curs->next;
    // }
    // return max;
    return 0;
}

void ent_tree_insert(relation *reltype, ent_node* node){
    //copio lo pseudocodice delle slides

    //int flag=(-1);

    // //cerco se l'entita' esiste gia così la reinserisco
    // ent_node* found=ENIL;
    // tree_search_ent(&found, (reltype)->ent_tree, (reltype)->ent_tree, node->ent->name_p);
    // if(found!=ENIL){
    //     found->ingresso++;
    //     ent_tree_insert(reltype, tree_delete_function(&reltype, found));
    //     free(node);
    //     return;
    // }
    // //ent_reinsert(reltype, node, 0);

    ent_node *y=ENIL;
    ent_node *x=((reltype)->ent_tree);
    int compare;
    while(x!=ENIL){
        y=x;
        //printf("ho letto %s\n", x->ent->name_p);
        
        compare=strcmp(node->ent->name_p, x->ent->name_p);
        if(compare<0){
            x=x->left;
        }
        else if(compare>0){
            x=x->right;
        }
        else if(compare==0){
            x->ingresso++;
            free(node);
            if(x->ingresso > reltype->max){
                reltype->max = x->ingresso;
            }
            //tree_find_max(reltype->ent_tree, &(reltype->max));
            return;
        }
    }
    node->p=y;
    if(y==ENIL){
        //l'albero e' vuoto
        (reltype)->ent_tree=node;
    }
    else{
        compare=strcmp(node->ent->name_p, y->ent->name_p);
        if(compare<0){
            y->left=node;
        }
        else /*if(compare>0)*/{
            y->right=node;
        }
    }
    if(node->ingresso > reltype->max){
        reltype->max = node->ingresso;
    }
}

ent_node* tree_delete_function(relation** reltype,ent_node* z){
    //segmenta qua dentro
    ent_node* x;
    ent_node* y;
    if((z)->left==ENIL || (z)->right==ENIL){
        //caso 1
        y=z;
    }else{
        //caso 2
        y=tree_successor_ent(z);
    }
    if(y->left!=ENIL){
        x=y->left;
    }
    else{
        x=y->right;
    }
    if(x!=ENIL){
        x->p=y->p;
    }
    if(y->p==ENIL){
        (*reltype)->ent_tree=x;
    }
    else if(y==(y->p->left)){
        y->p->left=x;
    }else{
        y->p->right=x;
    }
    if(y!=(z)){
        entity* ent=z->ent;
        int ingr=z->ingresso;

        (z)->ent=y->ent;
        z->ingresso=y->ingresso;

        y->ent=ent;
        y->ingresso=ingr;
        y->p=ENIL;
        y->left=ENIL;
        y->right=ENIL;
    }
    return y;
}

void tree_find_max(ent_node* entnode, int* max){
    //devo scorrere l'albero con inorder_tree_walk
    if((entnode)!=ENIL){
        tree_find_max(entnode->left, max);
        if(entnode->ingresso>*max){
            *max=entnode->ingresso;
        }
        tree_find_max(entnode->right, max);
    }
}

void tree_find_ents(ent_node* entnode, int* max, ents_to_print** list){
    //devo scorrere l'albero con inorder_tree_walk
    if((entnode)!=ENIL){
        tree_find_ents(entnode->left, max, list);
        if(entnode->ingresso==*max){
            list_insert_tail(list, entnode);
        }
        tree_find_ents(entnode->right, max, list);
    }
}

void list_insert_tail(ents_to_print** list, ent_node* entnode){
    ents_to_print* cursore=*list;
    if(*list==NULL){
        ents_to_print* newenttoprint=malloc(sizeof(ents_to_print));
        *list=newenttoprint;
        newenttoprint->next=NULL;
        newenttoprint->node=entnode;
        return;
    }
    while(cursore->next!=NULL){
        cursore=cursore->next;
    }
    ents_to_print* newenttoprint=malloc(sizeof(ents_to_print));
    cursore->next=newenttoprint;
    newenttoprint->next=NULL;
    newenttoprint->node=entnode;
}

ent_node* tree_minimum_ent(ent_node* nodo){
    ent_node* curs=nodo;
    while(curs->left!=ENIL){
        curs=curs->left;
    }
    return curs;
}

ent_node* tree_maximum_ent(ent_node* nodo){
    ent_node* curs=nodo;
    while(curs->right!=ENIL){
        curs=curs->right;
    }
    return curs;
}

ent_node* tree_successor_ent(ent_node* x){
    if(x->right!=ENIL){
        return tree_minimum_ent(x->right);
    }
    ent_node* y= (x->p);
    while(y!=ENIL && x==y->right){
        x=y;
        y=y->p;
    }
    return y;
}

ent_node* tree_search_ent(ent_node* root, ent_node* entnode, char name[]){ 
    if(entnode==ENIL || strcmp(entnode->ent->name_p, name)==0){
        // if(entnode!=ENIL){
        //     entnode->ingresso--;
        // }
        return entnode;
    }
    int compare=strcmp(entnode->ent->name_p, name);
    if(compare>0){
        return tree_search_ent(root, entnode->left, name);
    }
    else if(compare<0){
        return tree_search_ent(root, entnode->right, name);
    }
    return ENIL;
}

void tree_dimcount_ent(relation* reltype, ent_node* root, ent_node* entnode, char name[]){
    // printf("cerco %s e sono a %s\n", name, entnode->ent->name_p);
    // printf("sono a %s\n", entnode->ent->name_p);
    if(entnode==ENIL || strcmp(entnode->ent->name_p, name)==0){
        if(entnode!=ENIL){
            entnode->ingresso--;
            // if(entnode->ingresso<=0){
            //     free(tree_delete_function(&reltype, entnode));
            // }
            reltype->max=0;
            tree_find_max(reltype->ent_tree, &(reltype->max));
            //printf("contatore di %s diminuito a %d\n", entnode->ent->name_p, entnode->ingresso);
        }
        // if(((entnode->ingresso) +1)==reltype->max){
        //     tree_find_max(reltype->ent_tree, &(reltype->max));
        // }
        return;
    }
    int compare=strcmp(entnode->ent->name_p, name);
    if(compare>0){
        tree_dimcount_ent(reltype, root, entnode->left, name);
    }
    else /*if(compare<0)*/{
        tree_dimcount_ent(reltype, root, entnode->right, name);
    }
}

void ent_tree_walk(ent_node* entnode){
    if(entnode!=ENIL){
        ent_tree_walk(entnode->left);
        printf("nodo---> %s con %d in ingresso\n", entnode->ent->name_p, entnode->ingresso);
        ent_tree_walk(entnode->right);
    }
}

void print_ents_with_max(ent_node* entnode, int max){
    if(entnode!=ENIL){
        print_ents_with_max(entnode->left, max);
        if(entnode->ingresso==max){
            //fputs(entnode->ent->name_p, stdout);
            //printa_stringa(entnode->ent->name_p);
            fputs(entnode->ent->name_p, stdout);
            putc(' ', stdout);
        }
        print_ents_with_max(entnode->right, max);
    }
}

void printa_stringa(char* stringa){
    char* x=stringa;
    while (*x!='\0'){
        putchar(*x);
        x++;
    }
}