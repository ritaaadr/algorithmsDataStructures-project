
#include "adtflt.h"

DataType* ConstructFloatDataType()
{
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construction = &adtConstructFloat;
    type->destruction = &adtDestructFloat;
    type->getValue = &adtGetValueFloat;
    type->setValue = &adtSetValueFloat;
    type->randomValue = &adtRandomValueFloat;
    type->readFromKeyboard = &adtReadFromKeyboardFloat;
    type-> writeToMonitor = &adtWriteToMonitorFloat;
    type->clone = &adtCloneFloat;
    type->compare = &adtCompareFloat;
    return type;
}

/* ************************************************************************** */

void DestructFloatDataType(DataType *type)
{
    free(type);
}

/* ************************************************************************** */

void* adtConstructFloat(DataType* type)
{
    float* elem = (float*)malloc(sizeof(float));
    *elem = 0;
    return elem;

}

/* ************************************************************************** */

void adtDestructFloat(void* val)
{
    free(val);
}

/* ************************************************************************** */

void* adtGetValueFloat(void* val)
{
    //modifica qui
    float * elem = (float*)malloc(sizeof(float));
    *elem = *((float*)val);
    return elem;
}

/* ************************************************************************** */

void adtSetValueFloat(void* val, void* valx)
{
   *((float*) val) = *((float*)valx);
}

/* ************************************************************************** */

void adtRandomValueFloat(void* val)
{

    int elem = rndNum(-MaxFltAbsRndVal, MaxFltAbsRndVal);
    float fltRand =((float) elem)/1000;

    *((float*)val) = fltRand;


}

/* ************************************************************************** */

void adtReadFromKeyboardFloat(void* val)
{
    float elemx;
    printf("Inserisci un numero: \n");
    scanf("%f", &elemx);
    *((float*)val) = elemx;

}

/* ************************************************************************** */

void adtWriteToMonitorFloat(void* val)
{
    float elemx = *((float*)val);
    printf("Valore: %f\n", elemx);
}

/* ************************************************************************** */

void* adtCloneFloat(void *val)
{
    float* elem = (float*)malloc(sizeof(float));
    *elem = *((float*)val);
    return elem;
}

/* ************************************************************************** */

int adtCompareFloat(void* val, void* valx)
{
    float a = *((float*)val);
    float b = *((float*)valx);

    if(a<b) {
        return -1;
    }
    else if(a>b){
        return 1;
    }
    else {
        return 0;
    }

}

/* ************************************************************************** */