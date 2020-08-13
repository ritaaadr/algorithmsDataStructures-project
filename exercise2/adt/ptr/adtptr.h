
#ifndef ADTPTR_H
#define ADTPTR_H

/* ************************************************************************** */

#include "../adt.h"

typedef unsigned long ulong;

/* ************************************************************************** */

#define MaxIntAbsRndVal 250

/* ************************************************************************** */

DataType* ConstructPtrDataType();
void DestructPtrDataType(DataType* type);

/* ************************************************************************** */

void * adtConstructPtr();
void adtDestructPtr(void*);

void * adtGetValuePtr(void*);
void adtSetValuePtr(void**, void*);
void * adtClonePTr(void*);

#endif
