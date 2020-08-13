
#ifndef BSTITRPREORD_H
#define BSTITRPREORD_H

/* ************************************************************************** */

#include <stack/vec/stackvec.h>
#include "../itr/itr.h"

#include "../stack/stack.h"

#include "bst.h"

/* ************************************************************************** */

typedef struct BSTPreOrderIterator
{
  BSTNode* curr;
  StackVec* stack;

} BSTPreOrderIterator;

/* ************************************************************************** */

ITRType* ConstructBSTPreOrderIterator();
void DestructBSTPreOrderIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructPreOrder(void* treeStruct);

void itrDestructPreOrder(void* iterator);

bool itrTerminatedPreOrder(void* iterator);

void *  itrElementPreOrder(void* iterator);

void itrSuccessorPreOrder(void* iterator);



#endif
