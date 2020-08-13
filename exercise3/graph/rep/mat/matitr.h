
#ifndef MATITR_H
#define MATITR_H

/* ************************************************************************** */

#include "../itr/itr.h"
//#include "bst.h"
//#include "list.h"
#include "graphmat.h"

/* ************************************************************************** */

typedef struct MatrixIterator
{
    DataObject* curr;
    int matSize;
    int* Adj;
    BSTObject* tree;
    int position, index;
} MatrixIterator;

/* ************************************************************************** */

ITRType* ConstructItrMatrixIterator();
void DestructItrMatrixIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructMatrix(void* t_matrix);
void itrDestructMatrix(void* iterator);
bool itrTerminatedMatrix(void* iterator);
void * itrElementMatrix(void* iterator);
void itrSuccessorMatrix(void* iterator);

#endif
