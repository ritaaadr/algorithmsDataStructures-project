
#ifndef BSTITRPOSTORD_H
#define BSTITRPOSTORD_H

#include "stack/stack.h"
#include "stack/vec/stackvec.h"
#include "../stack/lst/stacklst.h"

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../stack/stack.h"

#include "bst.h"

/* ************************************************************************** */

typedef struct BSTPostOrderIterator
{
    BSTNode* curr;
    StackObject* stack;
    BSTNode* last;

} BSTPostOrderIterator;

/* ************************************************************************** */

ITRType* ConstructBSTPostOrderIterator();
void DestructBSTPostOrderIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructPostOrder(void* treeStruct);

void itrDestructPostOrder(void* iterator);

bool itrTerminatedPostOrder(void* iterator);

void *  itrElementPostOrder(void* iterator);

void itrSuccessorPostOrder(void* iterator);


#endif
