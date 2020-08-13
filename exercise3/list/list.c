#include "list.h"

/* ************************************************************************** */

Lst* listInsert(Lst* list, uint vertexLab)
{
    Lst* curr = list;

    //se voglio inserire in testa
    if(curr == NULL){
        list = (Lst*)malloc(sizeof(Lst));
        list->label = vertexLab;
        list->next = NULL;
        return list;
    }

    //altrimenti:
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = (Lst*)malloc(sizeof(Lst));
    curr->next->label = vertexLab;
    curr->next->next = NULL;

    return list;
}

/* ************************************************************************** */

void listDestruct(Lst* list){
    if(list != NULL) {
        free(list);
    }
}

/* ************************************************************************** */

void* listClear(Lst* list)
{
    Lst* curr = list;
    while(curr != NULL){
        list = listRemove(list, curr->label);
        curr = curr->next;
    }
    return list;
}

/* ************************************************************************** */

Lst* listClone(Lst* list)
{
    if(list != NULL){
        Lst* CloneLst = (Lst*)malloc(sizeof(Lst));
        CloneLst->label = list->label;
        CloneLst->next = listClone(list->next);

        return CloneLst;
    }
    return NULL;
}

/* ************************************************************************** */

Lst* listRemove(Lst* list , uint label)
{
    if(list == NULL){
        return NULL;
    }
    Lst* curr = list;
        //se voglio eliminare la testa controllo che l'etichetta passata sia uguale a quella del curr
        if (curr->label == label) {
            list = curr->next;
            free(curr);

            return list;
        }

        //altrimenti:
        Lst *prev = curr;
        while (curr != NULL && curr->label != label) {
            prev = curr;
            curr = curr->next;
        }
        if(curr != NULL){
            Lst* tmp = curr;
            prev->next = curr->next;
            free(tmp);
        }
        return list;
}

/* ************************************************************************** */

bool listExists(Lst* list, uint label)
{
    Lst* curr = list;
    while(curr != NULL && label != list->label){
        curr = curr->next;
    }
    if(curr == NULL){
        return false;
    }
    if(label == curr->label){
        return true;
    }
    return false;
}

/* ************************************************************************** */

int listSize(Lst* list)
{
    int count=0;
    Lst* curr = list;
    while(curr != NULL){
        count = count +1;
        curr = curr->next;
    }
    return count;
}

/* ************************************************************************** */

/*void lstMap(Lst* list, MapFun fun, void* par)
{
    Lst* curr = list->next;

    while(curr != NULL){
        fun(curr->data->value, par);
        curr = curr->next;
    }
}


void lstFold(Lst* list, FoldFun fun , void* accum, void* par)
{
    Lst* curr = list->next;

    while(curr != NULL){
        fun(curr->data->value, accum, par);
        curr = curr->next;
    }
}*/

/* ************************************************************************** */

