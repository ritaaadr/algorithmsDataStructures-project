
#include "bstitrinord.h"

#include "stack/stack.h"
#include "../stack/lst/stacklst.h"
#include "../stack/vec/stackvec.h"
#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

ITRType* ConstructBSTInOrderIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructInOrder;
    type->itr_Destruct = &itrDestructInOrder;
    type->itr_Terminated = &itrTerminatedInOrder;
    type->itr_Element = &itrElementInOrder;
    type->itr_Successor = &itrSuccessorInOrder;

    return type;
}

/* ************************************************************************** */

void DestructBSTInOrderIterator(ITRType* type)
{
    free(type);
}

/* ************************************************************************** */

void * itrConstructInOrder(void* treeStruct)
{
    BSTNode* root = (BSTNode*)treeStruct;

    BSTInOrderIterator* iter = (BSTInOrderIterator*)malloc(sizeof(BSTInOrderIterator));

    StackType *stkType = ConstructStackVecType();
    StackObject *stack = stkConstruct(stkType);
    iter->stack = stack;

    BSTNode* node = root;

    DataType* ptrType = ConstructPtrDataType();
    DataObject* ptr = adtConstruct(ptrType);

    while(node->LeftPtr != NULL ){
        adtSetValue(ptr, node);
        stkPush(iter->stack, ptr);
        node = node->LeftPtr;
    }
    iter->curr = node;
    return iter;
}

/* ************************************************************************** */

void itrDestructInOrder(void* iterator)
{
    BSTInOrderIterator* iter = (BSTInOrderIterator*)iterator;

    stkDestruct(iter->stack);
    free(iter);
}

/* ************************************************************************** */

bool itrTerminatedInOrder(void* iterator)
{
    BSTInOrderIterator* iter = (BSTInOrderIterator*)iterator;

    return iter->curr == NULL && stkEmpty(iter->stack);
}

/* ************************************************************************** */

void *  itrElementInOrder(void* iterator)
{
    BSTInOrderIterator* iter = (BSTInOrderIterator*)iterator;

    return iter->curr;
}

/* ************************************************************************** */

void itrSuccessorInOrder(void* iterator) {

    BSTInOrderIterator *iter = (BSTInOrderIterator *) iterator;

    DataType *ptrType = ConstructPtrDataType();
    DataObject *ptr = adtConstruct(ptrType);

    StackObject* stack = iter->stack;

    DataObject* tmp;

    if(iter->curr->RightPtr != NULL) {
        iter->curr = iter->curr->RightPtr;
        while( iter->curr->LeftPtr != NULL ){
            adtSetValue(ptr, iter->curr);
            stkPush(iter->stack, ptr);
            iter->curr = iter->curr->LeftPtr;
        }
    } else {
        if(!stkEmpty(stack)){
            tmp = stkTopNPop(stack);
            iter->curr = tmp->value;
            adtDestruct(tmp);
        } else {
            iter->curr = NULL;
        }
    }
}

/* ************************************************************************** */