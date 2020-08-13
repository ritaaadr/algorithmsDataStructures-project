
#include "bstitrbreadth.h"

#include "../queue/vec/queuevec.h"
#include "../queue/lst/queuelst.h"

#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

ITRType* ConstructBSTBreadthIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructBreadth;
    type->itr_Destruct = &itrDestructBreadth;
    type->itr_Terminated = &itrTerminatedBreadth;
    type->itr_Element = &itrElementBreadth;
    type->itr_Successor = &itrSuccessorBreadth;

    return type;
}

/* ************************************************************************** */

void DestructBSTBreadthIterator(ITRType* type)
{
   free(type);
}

/* ************************************************************************** */

void * itrConstructBreadth(void* treeStruct)
{
    BSTNode* root = (BSTNode*)treeStruct;

    BSTBreadthIterator* iter = (BSTBreadthIterator*)malloc(sizeof(BSTBreadthIterator));

    QueueType* queTyp = ConstructQueueVecType();
    QueueObject* queue = queConstruct(queTyp);

    DataType* ptrType = ConstructPtrDataType();
    DataObject* ptr = adtConstruct(ptrType);
    iter->queue = queue;

    iter->curr = root;
    if(iter->curr->LeftPtr != NULL){
        adtSetValue(ptr, iter->curr->LeftPtr);
        queEnqueue(queue, ptr);
    }
    if(iter->curr->RightPtr != NULL){
        adtSetValue(ptr, iter->curr->RightPtr);
        queEnqueue(queue,ptr);
    }

    return iter;

}

/* ************************************************************************** */

void itrDestructBreadth(void* iterator)
{
    BSTBreadthIterator* iter = (BSTBreadthIterator*)iterator;

    queDestruct(iter->queue);
    free(iter);
}

/* ************************************************************************** */

bool itrTerminatedBreadth(void* iterator)
{
    BSTBreadthIterator* iter = (BSTBreadthIterator*)iterator;

    return iter->curr == NULL && queEmpty(iter->queue);
}

/* ************************************************************************** */

void *  itrElementBreadth(void* iterator)
{
    BSTBreadthIterator* iter = (BSTBreadthIterator*)iterator;

    return iter->curr;
}

/* ************************************************************************** */

void itrSuccessorBreadth(void* iterator)
{
    BSTBreadthIterator* iter = (BSTBreadthIterator*)iterator;

    DataObject* tmp = NULL;

    DataType* ptrType = ConstructPtrDataType();
    DataObject* ptr = adtConstruct(ptrType);

    if(!queEmpty(iter->queue)){
        tmp = queHeadNDequeue(iter->queue);
        iter->curr = tmp->value;


        if(iter->curr->LeftPtr != NULL){
            adtSetValue(ptr, iter->curr->LeftPtr);
            queEnqueue(iter->queue, ptr);
        }

        if(iter->curr->RightPtr != NULL){
            adtSetValue(ptr, iter->curr->RightPtr);
            queEnqueue(iter->queue,ptr);
        }

    } else {
        iter->curr = NULL;
    }

}

/* ************************************************************************** */