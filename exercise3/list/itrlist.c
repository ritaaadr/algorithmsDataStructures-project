
#include "itrlist.h"
#include "../stack/vec/stackvec.h"
#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

ITRType* ConstructItrListIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructList;
    type->itr_Destruct = &itrDestructList;
    type->itr_Element = &itrElementList;
    type->itr_Successor = &itrSuccessorList;
    type->itr_Terminated = &itrTerminatedList;

    return type;

}

/* ************************************************************************** */

void DestructItrListIterator(ITRType* type)
{
    free(type);
}


/* ************************************************************************** */

void * itrConstructList(void* t_list)
{
    Lst* list = (Lst*)t_list;
    ListIterator* iter = (ListIterator*)malloc(sizeof(ListIterator));

    iter->list = list;
    return iter;
}


/* ************************************************************************** */

void itrDestructList(void* iterator)
{
    ListIterator* iter = (ListIterator*)iterator;

    listDestruct(iter->list);
    iter->list = NULL;
    free(iter);
}

/* ************************************************************************** */

bool itrTerminatedList(void* iterator)
{
   ListIterator* iter = (ListIterator*)iterator;
   return  listSize(iter->list) == 0;
}

/* ************************************************************************** */

void * itrElementList(void* iterator)
{
   ListIterator* iter = (ListIterator*)iterator;
   uint* ret = (uint*)malloc(sizeof(uint));
   *ret = iter->list->label;
   return ret;
}

/* ************************************************************************** */

void itrSuccessorList(void* iterator) {
    ListIterator *iter = (ListIterator *) iterator;
    iter->list = iter->list->next;
}

/* ************************************************************************** */