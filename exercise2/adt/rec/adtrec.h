
#ifndef ADTREC_H
#define ADTREC_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

typedef struct t_depositoVestiti{
    int taglia;
    int quantita;

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

#endif
