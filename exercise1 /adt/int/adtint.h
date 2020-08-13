
#ifndef ADTINT_H
#define ADTINT_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

#define MaxIntAbsRndVal 250

/* ************************************************************************** */

DataType* ConstructIntDataType();
void DestructIntDataType(DataType* type);

/* ************************************************************************** */

void* adtConstructInt();
void adtDestructInt(void*);

void* adtGetValueInt(void*);
void adtSetValueInt(void*, void*);

void adtRandomValueInt(void*);
void adtReadFromKeyboardInt(void*);
void adtWriteToMonitorInt(void*);

void* adtCloneInt(void*);
int adtCompareInt(void*, void*);

/* ************************************************************************** */

#endif
