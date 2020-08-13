
#ifndef ADTREC_H
#define ADTREC_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

typedef struct t_depositoVestiti{
    int index1; //Taglia
    int index2; //quantita'

}Deposito;

/* ************************************************************************** */

DataType* ConstructRecordDataType();
void DestructRecordDataType(DataType* type);

/* ************************************************************************** */

void* adtConstructRec();
void adtDestructRec(void*);

void* adtGetValueRec(void*);
void adtSetValueRec(void**, void*);

void adtRandomValueRec(void*);
void adtReadFromKeyboardRec(void*);
void adtWriteToMonitorRec(void*);

void* adtCloneRec(void*);
int adtCompareRec(void*, void*);

void* adtInitializeRec(void*, uint, uint);

#endif
