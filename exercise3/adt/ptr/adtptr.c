
#include "adtptr.h"

/* ************************************************************************** */

DataType* ConstructPtrDataType()
{
    DataType * type = (DataType*)malloc(sizeof(DataType));

    type->construction = &adtConstructPtr;
    type->destruction = &adtDestructPtr;
    type->getValue = &adtGetValuePtr;
    type->setValue = &adtSetValuePtr;
    type->randomValue = NULL;
    type->readFromKeyboard = NULL;
    type->writeToMonitor = NULL;
    type->clone = &adtClonePTr;
    type->compare = NULL;

    return type;
}

/* ************************************************************************** */

void DestructPtrDataType(DataType* type)
{
    free(type);
}

/* ************************************************************************** */

void* adtConstructPtr()
{
    void* val = NULL;
    return val;
}

/* ************************************************************************** */

void adtDestructPtr(void* val)
{
    //niente
    val = NULL;
}

/* ************************************************************************** */

void* adtGetValuePtr(void* val)
{
    return val;
}

/* ************************************************************************** */

void adtSetValuePtr(void** val, void* valx)
{
    *val = valx;
}

/* ************************************************************************** */

void * adtClonePTr(void* val){
    return val;
}

/* ************************************************************************** */

//funzione malata che ordina i ptr
int adtComparePtr(void* ptr1, void* ptr2){
    if(ptr1 < ptr2){
        return -1;
    } else if(ptr1 > ptr2){
        return 1;
    } else return 0;
}