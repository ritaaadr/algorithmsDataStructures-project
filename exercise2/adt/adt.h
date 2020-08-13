
#ifndef ADT_H
#define ADT_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef void* (*ADTConstruct)();
typedef void (*ADTDestruct)(void*);

typedef void* (*ADTGetValue)(void*);
typedef void (*ADTSetValue)(void**, void*);

typedef void (*ADTRandomValue)(void*);
typedef void (*ADTReadFromKeyboard)(void*);
typedef void (*ADTWriteToMonitor)(void*);

typedef void* (*ADTClone)(void*);
typedef int (*ADTCompare)(void*,void*);

/* ************************************************************************** */

typedef struct DataType
{
    ADTConstruct construction;
    ADTDestruct destruction;
    ADTGetValue getValue;
    ADTSetValue setValue;
    ADTRandomValue randomValue;
    ADTReadFromKeyboard readFromKeyboard;
    ADTWriteToMonitor writeToMonitor;
    ADTClone clone;
    ADTCompare compare;

} DataType;

typedef struct DataObject
{
    void* value;
    DataType* type;

} DataObject;

/* ************************************************************************** */

DataObject* adtConstruct(DataType* type);
void adtDestruct(DataObject* obj);

void* adtGetValue(DataObject* obj);
void adtSetValue(DataObject* obj, void* x);

void adtRandomValue(DataObject* obj);
void adtReadFromKeyboard(DataObject* obj);
void adtWriteToMonitor(DataObject* obj);

DataObject* adtClone(DataObject *obj);
int adtCompare(DataObject* obj, DataObject* objx);

void stampaMap(DataObject* obj, void* par);
void raddoppiaMap(DataObject* obj, void* par);
void cuboMap(DataObject* obj, void* par);
void concatenazioneMap(DataObject* obj, void* par);
void sommaFold(DataObject* obj, void* par, void* parx);
void prodottoFold(DataObject* obj, void* par, void* parx);
void concatenazioneFold(DataObject* obj, void* Str, void* par);

/* ************************************************************************** */

typedef void (*MapFun)(DataObject *, void *);
typedef void (*FoldFun)(DataObject *, void *, void *);

#endif
