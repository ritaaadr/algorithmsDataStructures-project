
#ifndef BSTITRINORD_H
#define BSTITRINORD_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../stack/stack.h"

#include "bst.h"

#include "stack/vec/stackvec.h"
#include "../stack/lst/stacklst.h"


/* ************************************************************************** */

typedef struct BSTInOrderIterator
{
  BSTNode* curr;
  StackObject* stack;

} BSTInOrderIterator;

/* ************************************************************************** */

ITRType* ConstructBSTInOrderIterator();
void DestructBSTInOrderIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructInOrder(void* treeStruct);

void itrDestructInOrder(void* iterator);

bool itrTerminatedInOrder(void* iterator);

void *  itrElementInOrder(void* iterator);

void itrSuccessorInOrder(void* iterator);

#endif
