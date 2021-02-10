#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

/*
INPUT:
    Node **meals_head: reference of the meal's linked list
    char *name: name of the meal
    int count: number of the meals

METHOD:
    Creates a meal and a node containing that meal. Append it to meal's linked list end.
*/
void add_meal(Node **meals_head, char *name, int count){
    
    struct Meal *p;
    struct Node *q, *temp;
    
    temp=(struct Node*)(malloc(sizeof(struct Node)));
    temp->next=NULL;
    temp->node=(struct Meal*)(malloc(sizeof(struct Meal)));
    p=temp->node;
    p->name=name;
    p->count=count;
    
    if(*meals_head == NULL){
        *meals_head = temp;
    }
    else{
        q  = *meals_head; 
        while(q->next != NULL){
            q = q->next;
        }
        q->next = temp;
    }
}
/*
INPUT:
    Node **philosophers_head: reference of the philosopher's linked list
    char *name: name of the philosopher
    char *favorite_meal: favorite meal
    int age: age of the philosopher

METHOD:
    Creates a philosopher and a node containing that philosopher. 
    Append it to philosopher's linked list end.
*/
void add_philosopher(Node **philosophers_head, char *name, char *favorite_meal, int age){
    
    struct Philosopher *p;
    struct Node *q, *temp;
    
    temp=(struct Node*)(malloc(sizeof(struct Node)));
    temp->next=NULL;
    temp->node=(struct Philosopher*)(malloc(sizeof(struct Philosopher)));
    p=temp->node;
    p->name=name;
    p->favorite_meal=favorite_meal;
    p->age=age;
    p->sitting=0;

    if(*philosophers_head == NULL){
        *philosophers_head = temp;
    }
    else{
        q  = *philosophers_head; 
        while(q->next != NULL){
            q = q->next;
        }
        q->next = temp;
    }
}
/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    Node *philosophers: philosopher's linked list

METHOD:
    Places philosophers into a circular linked list in ascending order of ages.
*/
void place_philosophers(Node **table_head, Node *philosophers){
    
    struct Node *q, *temp;
    struct Philosopher *ins,*out;

    while(1){
        temp=(struct Node*)(malloc(sizeof(struct Node)));/*Straight Table*/
        temp->next=NULL;
        temp->node=philosophers->node;
        ((struct Philosopher*)temp->node)->sitting=1;
        
        if(*table_head == NULL){
            *table_head = temp;
        }
        else{
            q  = *table_head;
            ins=q->node;
            out=philosophers->node;
            
            if((ins->age)>(out->age)){
                temp->next=q;
                *table_head = temp;
            }
            else{
                ins=q->next->node;
                while(q->next != NULL && (ins->age)<(out->age)){
                    ins=q->next->node;
                    if((ins->age)>(out->age)){break;}
                    q = q->next;
                }
                temp->next=q->next;
                q->next = temp;
            }
        }
        if(philosophers->next == NULL){break;}
        *philosophers = *philosophers->next;
    }
    q  = *table_head; /*Full Circle*/
    while(q->next != NULL){
        q = q->next;
    }
    q->next = *table_head;
}
/*
INPUT:
    Node **table_head: reference of the circular linked list (table)
    int index: index of the philosopher to be removed
    int size_of_table: number of philosophers in the table

METHOD:
    Removes a philosopher from table.
*/
void remove_philosopher(Node **table_head, int index, int size_of_table){
    struct Node *q,*temp;
    int i;
    if(index==0){
        ((struct Philosopher*)(*table_head)->node)->sitting=0;
        *table_head=(*table_head)->next;
        q=*table_head;
        for(i=2;i<size_of_table;++i){
            q=q->next;
        }
        temp=q->next->next;
        q->next=temp;
    }
    else{
        q=*table_head;
        for(i=1;i<index;++i){
            q=q->next;
        }
        ((struct Philosopher*)(q->next)->node)->sitting=0;
        temp=q->next->next;
        q->next=temp;
    }
}
/*
INPUT:
    Node *table: Circular linked list
    Node *meals: Meal's linked list

METHOD:
    Serves favorite meals and reduce their counts. Use strcmp function from string.h
*/
void serve_meals(Node *table, Node *meals){
    struct Node *q,*p;
    struct Philosopher *temp;
    struct Meal *eat;
    q = table;
    p = meals;
    while(1){
        temp=q->node;
        p = meals;
        eat=p->node;
            while(p->next!=NULL && strcmp(eat->name,temp->favorite_meal)){
                p=p->next;
                eat=p->node;
            }
        if((eat->count)>0){eat->count=(eat->count)-1;}
        if(q->next==table){break;}
        q=q->next;
    }    
}
/*
INPUT:
    Node *list: A linked list
    void (*helper_print)(void *): Reference of a helper print function

METHOD:
    Prints items in the linked list using helper print function
*/
void print_list(Node *list, void (*helper_print)(void *)){
    while(list->next != NULL){
        helper_print(list->node);
        list=list->next;
    }
    if(list->next == NULL)
    helper_print(list->node);
}

/*
INPUT:
    void *meal: void meal pointer

METHOD:
    Cast void pointer to a meal pointer and prints it's content
*/
void print_meal_node(void *meal){
    struct Meal *p;
    p=meal;
    printf("Name: %s, count: %d\n",p->name,p->count);
}

/*
INPUT:
    void *philosopher: void philosopher pointer

METHOD:
    Cast void pointer to a philosopher pointer and prints it's content
*/
void print_philosopher_node(void *philosopher){
    struct Philosopher *p;
    p=philosopher;
    printf("Name: %s, favorite meal: %s, age: %d\n",p->name,p->favorite_meal,p->age);
}

/*
INPUT:
    Node *table: Circular linked list

METHOD:
    Prints the formation as <prev> <current> <next>
*/
void print_table(Node *table){
    struct Node *james;
    struct Philosopher *p1,*p2,*p3;
    int i,lenght;
    lenght=get_length(table);
    james=table;
    while(james->next!=table){
        james=james->next;
    }
    for(i=0;i<lenght;++i){
        p1=james->node;
        p2=james->next->node;
        p3=james->next->next->node;
        printf("%s -> %s -> %s\n",p1->name,p2->name,p3->name);
        james=james->next;
    }
}

/*
INPUT:
    Node *list: A linked list

OUTPUT:
    Size of the linked list in an integer format

METHOD:
    Calculates the size of the linked list and returns it.
*/
int get_length(Node *list){
    struct Node *q;
    int i=1;
    q=list;
    while(q->next!=list && q->next!=NULL){
        q=q->next;
        ++i;
    }
    return i;
}

/*
INPUT:
    Node *philosophers: Philosopher's linked list

OUTPUT:
    Philosopher pointer at given index.

METHOD:
    Finds the philosopher at given index and returns it's reference.
*/
Philosopher *get_philosopher(Node *philosophers, int index){ 
    struct Philosopher *p;
    struct Node *q;
    int i;
    q=philosophers;
    for(i=0;i<index;++i){
        q=q->next;
    }
    p=q->node;
    return p;
}

