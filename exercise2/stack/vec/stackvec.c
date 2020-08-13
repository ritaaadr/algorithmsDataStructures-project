
#include "stackvec.h"

/* ************************************************************************** */

StackType* ConstructStackVecType()
{
    StackType* type = (StackType*)malloc(sizeof(StackType));

    type->construct = &stkConstructVecType;
    type->destruct = &stkDestructVecType;

    type->stk_Empty = &stkEmptyVecType;
    type->stk_Top = &stkTopVecType;
    type->stk_Pop = &stkPopVecType;
    type->stk_TopNPop = &stkTopNPopVecType;
    type->stk_Push = &stkPushVecType;
    type->stk_Clear = &stkClearVecType;

    type->stk_Clone = &stkCloneVecType;
    type->stk_Equal = &stkEqualVecType;
    type->stk_Map = &stkMapVecType;
    type->stk_Fold = &stkFoldVecType;

    return type;
}

void DestructStackVecType(StackType* type)
{
    free(type);
}


/* ************************************************************************** */

void * stkConstructVecType()
{

    StackVec *obj=(StackVec *)malloc(sizeof(StackVec));

    if(obj!=NULL)
    {
        obj->elements=(DataObject**)malloc(4*sizeof(DataObject*));
        obj->index=0;
        obj->alloc_mem=4;
    }
    return obj;
}

/* ************************************************************************** */

void stkDestructVecType(void* stack)
{
    StackVec* obj = (StackVec*)stack;

    free(obj->elements);
    free(obj);
}

/* ************************************************************************** */

void stkPushVecType(void *stack, DataObject* x)
{
    assert(stack);
    assert(x);
    StackVec* obj = (StackVec*)stack;

    DataObject* objx = adtClone(x);
    if(obj->index==obj->alloc_mem){
        obj->alloc_mem = obj->alloc_mem*2;
        obj->elements = (DataObject**)realloc(obj->elements, sizeof(DataObject*)*obj->alloc_mem);
    }
    obj->elements[obj->index]=objx;
    obj->index++;


}

/* ************************************************************************** */


DataObject*  stkTopVecType(void *stack)
{
    StackVec* obj = (StackVec*)stack;

    if(!(stkEmptyVecType(obj))){
        DataObject* elem_to_return = obj->elements[obj->index-1];
        DataObject* toReturn = adtClone(elem_to_return);

        return toReturn;
    }
    else{
        return NULL;
    }


}

/* ************************************************************************** */

DataObject* stkTopNPopVecType(void *stack)
{
    StackVec* obj = (StackVec*)stack;

    if(!(stkEmptyVecType(obj))){
        DataObject* elem_to_copy = obj->elements[--obj->index];

        return elem_to_copy;
    }
    else{
        return NULL;
    }
}

/* ************************************************************************** */

bool stkEmptyVecType(void *stack)
{
    assert(stack);
    StackVec* obj = (StackVec*)stack;

    return obj->index==0;

}

/* ************************************************************************** */

void stkClearVecType(void* stack)
{
    DataObject* value = NULL;
    StackVec* obj = (StackVec*)stack;
    int index = 0;

    while(!stkEmptyVecType(obj)){
        stkPopVecType(obj);
    }
}


/* ************************************************************************** */



void stkPopVecType(void *stack)
{

    assert(stack);
    StackVec* obj = (StackVec*)stack;

    if(!stkEmptyVecType(obj)) {
        DataObject *elementToPop = obj->elements[--obj->index];
        adtDestruct(elementToPop);
    }
}

/* ************************************************************************** */

void * stkCloneVecType(void *stack)
{

    StackVec* obj = (StackVec*)stack;

    StackVec *ret=(StackVec*)malloc(sizeof(StackVec));
    ret->alloc_mem=obj->alloc_mem;
    ret->index=obj->index;
    ret->elements=(DataObject**)malloc(sizeof(DataObject*)*ret->alloc_mem);

    for(uint i=0;i<obj->index;i++){
        ret->elements[i]=adtClone(obj->elements[i]);
    }

    return ret;
}

/* ************************************************************************** */

bool stkEqualVecType(void *stack, void *stackx)
{

    assert(stack);
    assert(stackx);
    StackVec* obj = (StackVec*)stack;
    StackVec* objx = (StackVec*)stackx;

    if(obj->alloc_mem!=objx->alloc_mem){
        return false;
    }
    else{
        for(uint i=0;i<obj->index;i++){
            if(!adtCompare(obj->elements[i], objx->elements[i])){
                return -1;
            }
        }
        return 1;
    }
}

/* ************************************************************************** */

int stkExistsVecType(void *stack, DataObject* x)
{

    assert(stack);
    assert(x);
    StackVec* obj = (StackVec*)stack;

    for(uint i=0;i<obj->alloc_mem; i++){
        if(adtCompare(obj->elements[i],x)){
            return 1;
        }
    }
    return -1;
}

/* ************************************************************************** */

void stkMapVecType(void *stack, MapFun fun , void *par)
{
    assert(stack);
    StackVec* obj = (StackVec*)stack;
    uint i=0;

    for(i=0;i<obj->index;i++)
    {
        fun(obj->elements[i], par);
    }
}

/* ************************************************************************** */

void stkFoldVecType(void *stack, FoldFun fun2, void* val, void* par){

    assert(stack);
    StackVec* obj = (StackVec*)stack;

    for(uint i=0;i<obj->index;i++)
    {
        fun2(obj->elements[i], val, par);
    }


}

