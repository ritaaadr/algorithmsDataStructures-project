
#ifndef EDGITR_H
#define EDGITR_H

/* ************************************************************************** */

#include "../itr/itr.h"
#include "bst.h"
#include "list.h"
#include "graphmat.h"

/* ************************************************************************** */

typedef struct GraphEdg
{
    GraphMat* graph;
    uint curr;
    uint currAdj;
    uint currAdjLabel;
} GraphEdg;

/* ************************************************************************** */

ITRType* ConstructItrGraphEdgIterator();
void DestructItrGraphEdgIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructGraphEdg(void* t_matrix);
void itrDestructGraphEdg(void* iterator);
bool itrTerminatedGraphEdg(void* iterator);
void * itrElementGraphEdg(void* iterator);
void itrSuccessorGraphEdg(void* iterator);



#endif
