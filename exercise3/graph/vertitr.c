
#include <adt/vert/adtvert.h>
#include <bst/bstitrinord.h>
#include "vertitr.h"
#include "../stack/vec/stackvec.h"
#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

ITRType* ConstructVertIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructVert;
    type->itr_Destruct = &itrDestructVert;
    type->itr_Element = &itrElementVert;
    type->itr_Successor = &itrSuccessorVert;
    type->itr_Terminated = &itrTerminatedVert;

    return type;
}

/* ************************************************************************** */

void DestructItrVertIterator(ITRType* type)
{
    free(type);
}

/* ************************************************************************** */

void * itrConstructVert(void* treenode)
{
  BSTObject* node = (BSTObject*)treenode;

  VertIterator* iter = (VertIterator*) malloc(sizeof(VertIterator));
  ITRType* itrType = ConstructBSTInOrderIterator();
  iter->bstIterator = itrConstruct(itrType, node->root);
  iter->curr = node->root->data;

  return iter;
}

/* ************************************************************************** */

void itrDestructVert(void* iterator)
{
    VertIterator* iter = (VertIterator*)iterator;

    itrDestruct(iter->bstIterator);
    free(iter);
}

/* ************************************************************************** */

bool itrTerminatedVert(void* iterator)
{
  VertIterator* iter = (VertIterator*)iterator;
  return itrTerminated(iter->bstIterator);
}

/* ************************************************************************** */

void * itrElementVert(void* iterator)
{
   VertIterator* iter = (VertIterator*)iterator;
   return iter->curr;
}

/* ************************************************************************** */

void itrSuccessorVert(void* iterator)
{
   VertIterator* iter = (VertIterator*)iterator;
    BSTNode *element = NULL;
    while (!itrTerminated(iter->bstIterator) && element == NULL) {
        itrSuccessor(iter->bstIterator);
        element = itrElement(iter->bstIterator);
    }

    if(element != NULL) {
       iter->curr = element->data;
    } else {
        iter->curr = NULL;
    }
}

/* ************************************************************************** */