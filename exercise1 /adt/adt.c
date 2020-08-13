
#include "adt.h"

/* ************************************************************************** */

// Funziona
DataObject* adtConstruct(DataType* type) {
  DataObject *obj = (DataObject*)malloc(sizeof(DataObject));
  obj->type = type;
  obj->value = type->construction();
  return obj;
}

/* ************************************************************************** */

// Funziona
void adtDestruct(DataObject* obj) {

    if(obj != NULL && obj->value!=NULL) {
        obj->type->destruction(obj->value);
        free(obj);
    }
}

/* ************************************************************************** */

// Funziona
void* adtGetValue(DataObject* obj)
{
    assert(obj);
    assert(obj->value);
    return obj->type->getValue(obj->value);
}

/* ************************************************************************** */

// Funziona
void adtSetValue(DataObject* obj, void* x)
{
  obj->type->setValue(obj->value,x);
}

/* ************************************************************************** */
//Funziona
void adtRandomValue(DataObject* obj)
{
  obj->type->randomValue(obj->value);
}

/* ************************************************************************** */
//Funziona
void adtReadFromKeyboard(DataObject* obj)
{
    obj->type->readFromKeyboard(obj->value);
}

/* ************************************************************************** */
//Funziona
void adtWriteToMonitor(DataObject* obj)
{
  obj->type->writeToMonitor(obj->value);
}

/* ************************************************************************** */

// Funziona
DataObject* adtClone(DataObject *obj)
{
  DataObject* objx = (DataObject*)malloc(sizeof(DataObject));
  objx->type = obj->type;
  objx->value = obj->type->clone(obj->value);
  return objx;
}

/* ************************************************************************** */

int adtCompare(DataObject* obj, DataObject* objx)
{
    //Funziona
  assert(obj->type==objx->type);
  return obj->type->compare(obj->value,objx->value);
}

/* ************************************************************************** */
