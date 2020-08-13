
#ifndef STACKVEC_H
#define STACKVEC_H

/* ************************************************************************** */

#include "../stack.h"

/* ************************************************************************** */

typedef struct StackVec
{
  uint index;
  DataObject** elements;
  uint alloc_mem;

} StackVec;

/* ************************************************************************** */

StackType* ConstructStackVecType();
void DestructStackVecType(StackType* type);


/* ************************************************************************** */

void * stkConstructVecType();
void stkDestructVecType(void* stack);

bool stkEmptyVecType(void *stack);
DataObject* stkTopVecType(void *stack);
void stkPopVecType(void *stack);
DataObject*  stkTopNPopVecType(void *stack);
void stkPushVecType(void *stack, DataObject* x);
void stkClearVecType(void*);

void * stkCloneVecType(void *stack);
bool stkEqualVecType(void *stack, void *stackx);
int stkExistsVecType(void *stack, DataObject* x);

void stkMapVecType(void *stack, MapFun fun, void *par);
void stkFoldVecType(void *stack, FoldFun fun2, void* val, void* par);

/* ************************************************************************** */

#endif
