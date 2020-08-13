
#ifndef ADTSTR_H
#define ADTSTR_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

#define MaxStrLen 25

/* ************************************************************************** */

DataType* ConstructStringDataType();
void DestructStringDataType(DataType*);

/* ************************************************************************** */

void* adtConstructString();
void adtDestructString(void* );

void* adtGetValueString(void*);
void adtSetValueString(void**, void*);

void adtRandomValueString(void* val);
void adtReadFromKeyboardString(void* );
void adtWriteToMonitorString(void* );

void* adtCloneString(void*);
int adtCompareString(void* , void* );

#endif
