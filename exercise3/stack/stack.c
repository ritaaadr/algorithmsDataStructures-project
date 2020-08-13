
#include "stack.h"

/* ************************************************************************** */

StackObject * stkConstruct(StackType* type)
{
    StackObject * stack = (StackObject*)malloc(sizeof(StackObject));

    stack->dim = 0;
    stack->type = type;
    stack->value = type->construct();

    return stack;
}

/* ************************************************************************** */

void stkDestruct(StackObject* stack)
{
    assert(stack);
    assert(stack->value);

    stack->type->destruct(stack->value);

    free(stack);
}

/* ************************************************************************** */

void stkPush(StackObject* stack, DataObject* val)
{
    assert(stack);
    assert(val);

    stack->type->stk_Push(stack->value, val);
    stack->dim = stack->dim+1;
}

/* ************************************************************************** */

bool stkEmpty(StackObject* stack)
{
    assert(stack);

    return stack->type->stk_Empty(stack->value);
}

/* ************************************************************************** */

DataObject* stkTop(StackObject* stack)
{
    assert(stack);
    assert(stack->value);

    DataObject* ret = stack->type->stk_Top(stack->value);

    return ret;
}

/* ************************************************************************** */

void stkPop(StackObject* stack)
{
    assert(stack);
    assert(!stkEmpty(stack));
    assert(stack->value);

    stack->type->stk_Pop(stack->value);
    stack->dim = stack->dim-1;

}

/* ************************************************************************** */

DataObject*  stkTopNPop(StackObject* stack)
{
    assert(stack);
    assert(stack->value);

    if(!stkEmpty(stack)) {
        DataObject *ret = stack->type->stk_TopNPop(stack->value);
        stack->dim = stack->dim - 1;

        return ret;
    }else{
        return NULL;
    }

}

/* ************************************************************************** */

void stkClear(StackObject* stack)
{
    assert(stack);
    assert(!stkEmpty(stack));
    assert(stack->value);

    stack->type->stk_Clear(stack->value);
    stack->dim = 0;
}

/* ************************************************************************** */

StackObject * stkClone(StackObject* stack)
{
    StackObject* stackx = (StackObject*)malloc(sizeof(StackObject));
    stackx->type = stack->type;
    stackx->value = stack->type->stk_Clone(stack->value);
    stackx->dim = stack->dim;

    return stackx;
}

/* ************************************************************************** */

bool stkEqual(StackObject* stack, StackObject* stackx)
{
    assert(stack->type == stackx->type);

    return stack->type->stk_Equal(stack->value, stackx->value);
}

/* ************************************************************************** */

int stkSize(StackObject* stack)
{
    return stack->dim;
}

/* ************************************************************************** */

bool stkExists(StackObject* stack, DataObject* val)
{
    assert(stack);
    assert(val);
    bool esiste = false;

    stack->type->stk_Fold(stack->value, &esisteFold, &esiste, val);

    return esiste;
}

/* ************************************************************************** */

void stkMap(StackObject* stack, MapFun fun , void* par)
{
    assert(stack);
    assert(stack->value);

    stack->type->stk_Map(stack->value,fun, par);
}

/* ************************************************************************** */

void stkFold(StackObject* stack, FoldFun fun , void* accum, void* par)
{
    assert(stack);
    assert(stack->value);

    stack->type->stk_Fold(stack->value,fun, accum, par);
}
