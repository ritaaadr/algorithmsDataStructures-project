
#ifndef VERTITR_H
#define VERTITR_H

/* ************************************************************************** */

#include <stack/vec/stackvec.h>
#include "../itr/itr.h"
#include "../stack/stack.h"
//#include "bst.h"
//#include "list.h"
#include "graph.h"

/* ************************************************************************** */

typedef struct VertIterator
{
    DataObject* curr;
    ITRObject* bstIterator;
} VertIterator;

/* ************************************************************************** */

ITRType* ConstructVertIterator();
void DestructItrVertIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructVert(void* t_list);
void itrDestructVert(void* iterator);
bool itrTerminatedVert(void* iterator);
void * itrElementVert(void* iterator);
void itrSuccessorVert(void* iterator);



#endif
