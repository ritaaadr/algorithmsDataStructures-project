
#include "adtint.h"

/* ************************************************************************** */

DataType* ConstructIntDataType(){

    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construction = &adtConstructInt;
    type->destruction = &adtDestructInt;
    type->getValue = &adtGetValueInt;
    type->setValue = &adtSetValueInt;
    type->randomValue = &adtRandomValueInt;
    type->readFromKeyboard = &adtReadFromKeyboardInt;
    type->writeToMonitor = &adtWriteToMonitorInt;
    type->clone = &adtCloneInt;
    type->compare = &adtCompareInt;
    return type;
}

/* ************************************************************************** */

void DestructIntDataType(DataType* type)
{
    free(type);
}

/* ************************************************************************** */

void* adtConstructInt()
{
    int* val = (int*)malloc(sizeof(int));
    *val = 0;
    return (void*) val;
}

/* ************************************************************************** */

void adtDestructInt(void* val)
{
    free(val);
}

/* ************************************************************************** */

void* adtGetValueInt(void* val)
{
    int* elem = (int*)malloc(sizeof(int));
    *elem = *((int*)val);
    return elem;

}

/* ************************************************************************** */

void adtSetValueInt(void** val, void* valx)
{
    *((int*)(*val)) = *((int*)valx);
}

/* ************************************************************************** */

void adtRandomValueInt(void* val)
{

    *((int*)val) = rndNum(-MaxIntAbsRndVal, MaxIntAbsRndVal);

}

/* ************************************************************************** */

void adtReadFromKeyboardInt(void* val)
{

    int elem;

    scanf("%d", &elem);
    *((int*)val) = elem;
}

/* ************************************************************************** */

void adtWriteToMonitorInt(void* val)
{

    int elem = *((int*)val);
    printf("%d\n", elem);
}

/* ************************************************************************** */

void* adtCloneInt(void* val) {
    int* elem = (int*) malloc(sizeof(int));
    *elem = *((int*) val);
    return elem;
}

/* ************************************************************************** */

int adtCompareInt(void* val, void* valx)
{
    int a = *((int*)val);
    int b = *((int*)valx);

    return a-b;

}

/* ************************************************************************** */

