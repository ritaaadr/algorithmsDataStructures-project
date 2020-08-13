
#include <bst/bstitrpreord.h>
#include "bstitr.h"
#include "../stack/vec/stackvec.h"
#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

ITRType* ConstructItrBSTIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructBST;
    type->itr_Destruct = &itrDestructBST;
    type->itr_Element = &itrElementBST;
    type->itr_Successor = &itrSuccessorBST;
    type->itr_Terminated = &itrTerminatedBST;

    return type;
}

/* ************************************************************************** */

void DestructItrBSTIterator(ITRType* type)
{
    free(type);
}


/* ************************************************************************** */

void * itrConstructBST(void* t_BST)
{
    BSTObject* AdjTree = (BSTObject*)t_BST;
    ITRType* itrType = ConstructBSTPreOrderIterator();
    ITRObject* iter = itrConstruct(itrType, AdjTree->root);
    BSTGraphIterator* graphIter = (BSTGraphIterator*)malloc(sizeof(BSTGraphIterator));
    graphIter->bstIterator = iter;
    BSTNode* elem = itrElement(graphIter->bstIterator);
    if(elem != NULL) {
        DataObject *tmp = elem->data;
        graphIter->currIndex = *((int *) tmp->value);
    }

    return graphIter;
}


/* ************************************************************************** */

void itrDestructBST(void* iterator)
{
    BSTGraphIterator* graphIter = (BSTGraphIterator*)iterator;

    itrDestruct(graphIter->bstIterator);
    free(graphIter);
}

/* ************************************************************************** */

bool itrTerminatedBST(void* iterator)
{
    BSTGraphIterator* graphIter = (BSTGraphIterator*)iterator;
    return  itrTerminated(graphIter->bstIterator);
}

/* ************************************************************************** */

void * itrElementBST(void* iterator)
{
   BSTGraphIterator* graphIter = (BSTGraphIterator*)iterator;
   uint* pointer = (uint*)malloc(sizeof(uint));
   *pointer = graphIter->currIndex;
   return pointer;
}

/* ************************************************************************** */

void itrSuccessorBST(void* iterator) {
    BSTGraphIterator* graphIter = (BSTGraphIterator*)iterator;

    BSTNode *element = NULL;
    while (!itrTerminated(graphIter->bstIterator) && element == NULL) {
        itrSuccessor(graphIter->bstIterator);
        element = itrElement(graphIter->bstIterator);
    }

    if(element != NULL) {
        graphIter->currIndex = *((int*)adtGetValue(element->data));
    } else {
        graphIter->currIndex = 0;
    }
}


/* ************************************************************************** */