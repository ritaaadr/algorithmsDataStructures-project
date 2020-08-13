
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
    void* val = NULL; // (ulong*)malloc(sizeof(ulong));
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
    //*((ulong*)val) = *((ulong*)valx);
    *val = valx;
}

/* ************************************************************************** */

void * adtClonePTr(void* val){
    return val;
}