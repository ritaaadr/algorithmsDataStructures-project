
#ifndef ADTFLT_H
#define ADTFLT_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

#define MaxFltAbsRndVal 250
#define MaxFltPrcRndVal 1000

/* ************************************************************************** */

DataType* ConstructFloatDataType();
void DestructFloatDataType(DataType *type);

/* ************************************************************************** */


void* adtConstructFloat(DataType* type);
void adtDestructFloat(void*);

void* adtGetValueFloat(void*);
void adtSetValueFloat(void*, void*);

void adtRandomValueFloat(void*);
void adtReadFromKeyboardFloat(void*);
void adtWriteToMonitorFloat(void*);

void* adtCloneFloat(void*);
int adtCompareFloat(void*, void*);

/* ************************************************************************** */

#endif
