
#ifndef STACK_H
#define STACK_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef void* (*StkConstruct)();
typedef void (*StkDestruct)(void*);

typedef bool (*StkEmpty)(void*);
typedef DataObject* (*StkTop)(void*);
typedef void (*StkPop)(void*);
typedef DataObject* (*StkTopNPop)(void*);
typedef void (*StkPush)(void*, DataObject*);
typedef void (*StkClear)(void*);

typedef void* (*StkClone)(void*);
typedef bool (*StkEqual)(void*, void*);
typedef void (*StkMap)(void*, MapFun, void*);
typedef void (*StkFold)(void*, FoldFun, void*, void*);

/* ************************************************************************** */

typedef struct StackType
{
    StkConstruct construct;
    StkDestruct  destruct;

    StkEmpty     stk_Empty;
    StkTop       stk_Top;
    StkPop       stk_Pop;
    StkTopNPop   stk_TopNPop;
    StkPush      stk_Push;
    StkClear     stk_Clear;

    StkClone     stk_Clone;
    StkEqual     stk_Equal;
    StkMap       stk_Map;
    StkFold      stk_Fold;

} StackType;

typedef struct StackObject
{
    StackType* type;
    void*      value;
    uint       dim;

} StackObject;

/* ************************************************************************** */
//li userò nel main
StackObject * stkConstruct(StackType* type);
void stkDestruct(StackObject* stack);
void stkPush(StackObject* stack, DataObject* val);
bool stkEmpty(StackObject* stack);
DataObject* stkTop(StackObject* stack);
void stkPop(StackObject* stack);
DataObject*  stkTopNPop(StackObject* stack);
void stkClear(StackObject* stack);

StackObject * stkClone(StackObject* stack);
bool stkEqual(StackObject* stack, StackObject* stackx);
int stkSize(StackObject* stack);
bool stkExists(StackObject* stack, DataObject* val);
void stkMap(StackObject* stack, MapFun fun , void* par);
void stkFold(StackObject* stack, FoldFun fun , void* accum, void* par);


/* ************************************************************************** */

#endif
