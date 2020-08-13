
#include "bstitrpreord.h"

#include "../stack/vec/stackvec.h"
#include "../stack/stack.h"

#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

ITRType* ConstructBSTPreOrderIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructPreOrder;
    type->itr_Destruct = &itrDestructPreOrder;
    type->itr_Element = &itrElementPreOrder;
    type->itr_Successor = &itrSuccessorPreOrder;
    type->itr_Terminated = &itrTerminatedPreOrder;

    return type;
}

/* ************************************************************************** */

void DestructBSTPreOrderIterator(ITRType* type)
{
    free(type);
}


/* ************************************************************************** */

void * itrConstructPreOrder(void* treenode)
{
    BSTNode* root = (BSTNode*)treenode;

    BSTPreOrderIterator* iter = (BSTPreOrderIterator*)malloc(sizeof(BSTPreOrderIterator));
    //inizializzo al primo elemento da puntare, in questo caso la radice
    iter->curr = root;
    iter->stack = stkConstructVecType();

    return iter;
}


/* ************************************************************************** */

void itrDestructPreOrder(void* iterator)
{
    BSTPreOrderIterator* iter = (BSTPreOrderIterator*)iterator;
    stkDestructVecType(iter->stack);
    free(iter);
}

/* ************************************************************************** */

bool itrTerminatedPreOrder(void* iterator)
{
    BSTPreOrderIterator* iter = (BSTPreOrderIterator*)iterator;
    return iter->curr == NULL && stkEmptyVecType(iter->stack);
}

/* ************************************************************************** */

void * itrElementPreOrder(void* iterator)
{
    BSTPreOrderIterator* iter = (BSTPreOrderIterator*)iterator;
    return iter->curr;
}


/* ************************************************************************** */

void itrSuccessorPreOrder(void* iterator)
{
    BSTPreOrderIterator* iter = (BSTPreOrderIterator*)iterator;
    StackVec* stack = iter->stack;

    DataType* ptrType = ConstructPtrDataType();
    DataObject* ptr = adtConstruct(ptrType);
    ptr->value = iter->curr;

    stkPushVecType(stack, ptr);
        iter->curr = iter->curr->LeftPtr;

      while(!stkEmptyVecType(stack) && iter->curr == NULL){
        ptr = stkTopNPopVecType(stack);
        iter->curr = adtGetValue(ptr);
        iter->curr = iter->curr->RightPtr;
    }
     // adtDestruct(ptr);
     // DestructPtrDataType(ptrType);
}

/* ************************************************************************** */