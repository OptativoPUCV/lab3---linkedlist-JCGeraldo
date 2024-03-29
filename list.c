#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * lista = (List *)malloc(sizeof(List));
    lista-> head = NULL;
    lista-> tail = NULL;
    lista-> current = NULL;
    return lista;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL){
        return NULL;
    }
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if(list->current  && list->current->next){
        list->current = list->current->next;
        return list -> current -> data;
    }
    return NULL;
}

void * lastList(List * list) {
    if(list->current && list->tail){
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if(list->current && list->current->prev){
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node * nuevo = createNode(data);
    if(list->head == NULL){
        list->head = nuevo;
        list->tail = nuevo;
    }
    else{
        nuevo->next = list->head;
        list->head->prev = nuevo;
        list->head = nuevo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * nuevo = createNode(data);
    if(list->head == NULL){
        list->head = nuevo;
        list->tail = nuevo;
    }
    else{
        nuevo->next = list->current->next;
        nuevo->prev = list->current;
        if(list->current->next)list->current->next->prev = nuevo;
        list->current->next = nuevo;
        if(list->current == list->tail)list->tail = nuevo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->current == NULL)return NULL;
    void * data = list->current->data;
    Node * aux = list->current->next;
    if(list->current->prev)list->current->prev->next = list->current->next;
    if(list->current->next)list->current->next->prev = list->current->prev;
    if(list->current == list->head)list->head = list->current->next;
    if(list->current == list->tail)list->tail = list->current->prev;
    free(list->current);
    list->current = aux;
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}