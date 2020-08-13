
#ifndef ADTVERT_H
#define ADTVERT_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

typedef struct VertStruct{
    uint label; //ID
    DataObject* data;
    uint ArrayPos;
}VertStruct;

/* ************************************************************************** */

DataType* ConstructVertDataType();
void DestructVertDataType(DataType* type);

/* ************************************************************************** */

void* adtConstructVert();
void* adtInitializeVertex(uint, DataObject*);

void adtDestructVert(void*);

void adtWriteToMonitorVert(void*);

void* adtCloneVert(void*);
int adtCompareLabel(void*, void*);
int adtCompareVert(void* val, void* valx);
int adtCompareMapIndex(void* val, void* valx);

uint adtGetVertexId(void*);
uint adtGetVertexArrayPos(void* val);
void * adtSetValueVert(DataObject* val, DataObject* valx);
void* adtGetVertexData(void* vert);

//void* adtGetValueVert(void*);
//void adtSetValueVert(void**, void*);
//void adtReadFromKeyboardVert(void*);

#endif
