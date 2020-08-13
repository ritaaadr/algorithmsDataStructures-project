
#include "stacklst.h"
/* ************************************************************************** */

StackType* ConstructStackLstType()
{
    StackType * type = (StackType*)malloc(sizeof(StackType));

    type->construct = &stkConstructLstType;
    type->destruct = &stkDestructLstType;

    type->stk_Empty = &stkEmptyLstType;
    type->stk_Top = &stkTopLstType;
    type->stk_Push = &stkPushLstType;
    type->stk_Pop = &stkPopLstType;
    type->stk_TopNPop = &stkTopNPopLstType;
    type->stk_Clear = &stkClearLstType;

    type->stk_Clone = &stkCloneLstType;
    type->stk_Equal = &stkEqualLstType;
    type->stk_Map = &stkMapLstType;
    type->stk_Fold = &stkFoldLstType;

    return type;
}

/* ************************************************************************** */

void DestructStackLstType(StackType* type)
{
    free(type);
}

/* ************************************************************************** */

void * stkConstructLstType()
{
    StackLst * obj = (StackLst*)malloc(sizeof(StackLst));

    //puntatore alla testa (nodo vuoto)
    if(obj != NULL){

        obj->elements = NULL;
        obj->next = NULL;

    }

    return obj;
}

/* ************************************************************************** */


void stkDestructLstType(void* stack)
{
    StackLst* obj = (StackLst*)stack;
    free(obj);
}

/* ************************************************************************** */

bool stkEmptyLstType(void* stack)
{
    assert(stack);

    StackLst* obj = (StackLst*)stack;
    return obj->next == NULL;
}

/* ************************************************************************** */

DataObject* stkTopLstType(void* stack)
{
    assert(stack);

    StackLst* obj = (StackLst*)stack;

    DataObject * elemToCopy = obj->next->elements;
    DataObject* ret = adtClone(elemToCopy);


    return ret;

}

/* ************************************************************************** */

void stkPushLstType(void* stack, DataObject* val)
{
    assert(stack);

    StackLst* obj = (StackLst*)stack;
    DataObject* elemToPush = adtClone(val);

    StackLst* newNode = (StackLst*) malloc(sizeof(StackLst));


   if(newNode == NULL){
       printf("Error\n");
   }else {
       newNode->elements = elemToPush;
       newNode->next = obj->next;
       obj->next = newNode;

   }

}

/* ************************************************************************** */

void stkPopLstType(void* stack)
{
    assert(stack);
    StackLst * obj = (StackLst*)stack;


    if(!stkEmptyLstType(obj)) {

        StackLst *elemToDelete = obj->next;
        adtDestruct(elemToDelete->elements);
        obj->next = elemToDelete->next;
        free(elemToDelete);
    }


}

/* ************************************************************************** */

DataObject* stkTopNPopLstType(void* stack)
{
    assert(stack);
    StackLst * obj = (StackLst*)stack;

    DataObject * elemToCopy = obj->next->elements;
    DataObject* ret = adtClone(elemToCopy);

    if(!stkEmptyLstType(obj)) {

        StackLst *elemToDelete = obj->next;
        printf("\n");
        adtDestruct(elemToDelete->elements);
        obj->next = elemToDelete->next;
        free(elemToDelete);
    }

    return ret;

}

/* ************************************************************************** */

void stkClearLstType(void* stack)
{
    StackLst* obj = (StackLst*)stack;
    DataObject* value = NULL;

    while(!stkEmptyLstType(obj)){
        stkPopLstType(obj);
    }
}

/* ************************************************************************** */

void* stkCloneLstType(void* stack)
{
    StackLst* obj = (StackLst*)stack;

    StackLst* tmp = (StackLst*)malloc(sizeof(StackLst));
    StackLst* clone = (StackLst*)malloc(sizeof(StackLst));


    StackLst* curr = obj->next;
    while(curr != NULL){
        stkPushLstType(tmp, curr->elements);
        curr = curr->next;

    }


    while(!stkEmptyLstType(tmp)) {
        DataObject* value = stkTopNPopLstType(tmp);
        stkPushLstType(clone, value);
        adtDestruct(value);
    }
        free(tmp);

    return clone;

}

/* ************************************************************************** */

bool stkEqualLstType(void* stack, void* stackx)
{
    assert(stack);
    assert(stackx);
    StackLst* obj = (StackLst*)stack;
    StackLst* objx = (StackLst*)stackx;

    StackLst* curr = obj->next;
    StackLst* currx = objx->next;

    while(curr != NULL && currx != NULL){
        if(adtCompare(curr->elements, currx->elements)!=0){
            return false;
        }
        curr = curr->next;
        currx = currx->next;
    }

    if((curr == NULL && currx != NULL) || (curr != NULL && currx == NULL)){
        return false;
    }
    return true;
}

/* ************************************************************************** */

void stkMapLstType(void* stack, MapFun fun, void* par)
{
    assert(stack);
    StackLst* obj = (StackLst*)stack;

    StackLst* curr = obj->next;

    while(curr != NULL){
        fun(curr->elements, par);
        curr = curr->next;
    }
}

/* ************************************************************************** */

void stkFoldLstType(void* stack, FoldFun fun, void* accum, void* par)
{
    assert(stack);
    StackLst* obj = (StackLst*)stack;

    StackLst* curr = obj->next;

    while(curr != NULL){
        fun(curr->elements, accum, par);
        curr = curr->next;
    }
}