
#ifndef ITRLIST_H
#define ITRLIST_H

/* ************************************************************************** */

#include <stack/vec/stackvec.h>
#include "../itr/itr.h"
#include "../stack/stack.h"
//#include "bst.h"
#include "list.h"

/* ************************************************************************** */

typedef struct ListIterator
{
    Lst* list;
} ListIterator;

/* ************************************************************************** */

ITRType* ConstructItrListIterator();
void DestructItrListIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructList(void* t_list);
void itrDestructList(void* iterator);
bool itrTerminatedList(void* iterator);
void *  itrElementList(void* iterator);
void itrSuccessorList(void* iterator);



#endif
