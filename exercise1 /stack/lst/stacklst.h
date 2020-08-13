
#ifndef STACKLST_H
#define STACKLST_H

/* ************************************************************************** */

#include "../stack.h"

/* ************************************************************************** */

typedef struct StackLst StackLst;

struct StackLst
{
  DataObject* elements;
  StackLst* next;
};



/* ************************************************************************** */

StackType* ConstructStackLstType();
void DestructStackLstType(StackType* type);

/* ************************************************************************** */

void * stkConstructLstType();
void stkDestructLstType(void* stack);
bool stkEmptyLstType(void* stack);
DataObject* stkTopLstType(void* stack);
void stkPushLstType(void* stack, DataObject* val);
void stkClearLstType(void* stack);
void stkPopLstType(void* stack);
DataObject* stkTopNPopLstType(void* stack);
void* stkCloneLstType(void* stack);
bool stkEqualLstType(void* stack, void* stackx);
void stkMapLstType(void* stack, MapFun fun, void* par);
void stkFoldLstType(void* stack, FoldFun, void* accum, void* par);

#endif
