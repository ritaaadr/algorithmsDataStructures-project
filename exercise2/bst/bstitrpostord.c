
#include "bstitrpostord.h"
#include "../stack/vec/stackvec.h"
#include "../stack/lst/stacklst.h"
#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

ITRType* ConstructBSTPostOrderIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructPostOrder;
    type->itr_Destruct = &itrDestructPostOrder;
    type->itr_Element = &itrElementPostOrder;
    type->itr_Successor = &itrSuccessorPostOrder;
    type->itr_Terminated = &itrTerminatedPostOrder;

    return type;

}

/* ************************************************************************** */

void DestructBSTPostOrderIterator(ITRType* type)
{
    free(type);
}

/* ************************************************************************** */

void * itrConstructPostOrder(void* treeStruct)
{
    BSTNode* root = (BSTNode*)treeStruct;

    BSTPostOrderIterator* iter = (BSTPostOrderIterator*)malloc(sizeof(BSTPostOrderIterator));

    StackType* stkType=ConstructStackVecType();
    StackObject* stack=stkConstruct(stkType);

    BSTNode* node = root;
    //iter->last = NULL;

    DataType* ptrType = ConstructPtrDataType();
    DataObject* ptr = adtConstruct(ptrType);

    while(node != NULL && (node->LeftPtr != NULL || node->RightPtr != NULL)){
        adtSetValue(ptr, node);
        stkPush(stack, ptr);
        if(node->LeftPtr != NULL){
            node = node->LeftPtr;
        } else {
            node = node->RightPtr;
        }
    }

    adtDestruct(ptr);
    iter->curr = node;
    iter->stack = stack;
    iter->last = node;

    return iter;
}

/* ************************************************************************** */

void itrDestructPostOrder(void* iterator)
{
    BSTPostOrderIterator* iter = (BSTPostOrderIterator*)iterator;

    stkDestruct(iter->stack);
    free(iter);

}

/* ************************************************************************** */

bool itrTerminatedPostOrder(void* iterator)
{
    BSTPostOrderIterator* iter = (BSTPostOrderIterator*)iterator;

    return iter->curr == NULL && stkEmpty(iter->stack);
}

/* ************************************************************************** */

void *  itrElementPostOrder(void* iterator)
{
    BSTPostOrderIterator* iter = (BSTPostOrderIterator*)iterator;

    return iter->curr;
}

/* ************************************************************************** */

void itrSuccessorPostOrder(void* iterator) {

    BSTPostOrderIterator *iter = (BSTPostOrderIterator *) iterator;

    DataType *ptrtype = ConstructPtrDataType();
    DataObject *ptr = adtConstruct(ptrtype);

    DataObject* data;

    if(iter->curr == iter->last) {
        iter->curr=NULL;
    }

    while((!stkEmpty(iter->stack)) || (iter->curr!=NULL)) {
        if (iter->curr!=NULL) {
            adtSetValue(ptr,iter->curr);
            stkPush(iter->stack,ptr);
            iter->curr=iter->curr->LeftPtr;
        }
        else {
            data=stkTop(iter->stack);
            iter->curr = data->value;
            adtDestruct(data);
            if((iter->curr->RightPtr!= NULL) && (iter->last!=iter->curr->RightPtr)) {
                iter->curr=iter->curr->RightPtr;
            }
            else {
                iter->last=iter->curr;
                stkPop(iter->stack);
                break;
            }
        }
    }
    adtDestruct(ptr);
}

/* ************************************************************************** */