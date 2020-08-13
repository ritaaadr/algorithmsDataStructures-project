
#ifndef ITRBST_H
#define ITRBST_H

/* ************************************************************************** */

#include <stack/vec/stackvec.h>
#include "../itr/itr.h"
#include "../stack/stack.h"
#include "bst.h"


/* ************************************************************************** */

typedef struct BSTGraphIterator
{
   ITRObject* bstIterator;
   uint currIndex;
} BSTGraphIterator;

/* ************************************************************************** */

ITRType* ConstructItrBSTIterator();
void DestructItrBSTIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructBST(void* t_BST);
void itrDestructBST(void* iterator);
bool itrTerminatedBST(void* iterator);
void * itrElementBST(void* iterator);
void itrSuccessorBST(void* iterator);



#endif
