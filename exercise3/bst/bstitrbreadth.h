
#ifndef BSTITRBREADTH_H
#define BSTITRBREADTH_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../queue/queue.h"

#include "bst.h"

/* ************************************************************************** */

typedef struct BSTBreadthIterator
{
  QueueObject* queue;
  BSTNode* curr;

} BSTBreadthIterator;

/* ************************************************************************** */

ITRType* ConstructBSTBreadthIterator();
void DestructBSTBreadthIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructBreadth(void* treeStruct);

void itrDestructBreadth(void* iterator);

bool itrTerminatedBreadth(void* iterator);

void *  itrElementBreadth(void* iterator);

void itrSuccessorBreadth(void* iterator);


#endif
