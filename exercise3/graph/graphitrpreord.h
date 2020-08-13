
#ifndef GRAPHITRPREORD_H
#define GRAPHITRPREORD_H

/* ************************************************************************** */

#include <bst/bst.h>
#include "../itr/itr.h"
#include "../stack/stack.h"
#include "graph.h"
//#include "adt.h"

/* ************************************************************************** */

typedef struct GraphPreOrderIterator
{
  ITRObject* verticesIterator;
  uint curr; //id del vertice corrente
  BSTObject* treeOfColors; // 0 Bianco - 1 Grigio - 2 Nero
  StackObject* stack;
  GraphObject* graph;
  ITRObject* currEdg;
} GraphPreOrderIterator;

/* ************************************************************************** */

ITRType* ConstructGraphPreOrderIterator();
void DestructGraphPreOrderIterator(ITRType* type);

/* ************************************************************************** */

void * itrConstructGraphPreOrderIterator(void* graphStruct);
void itrDestructGraphPreOrderIterator(void* iterator);
bool itrTerminatedGraphPreOrderIterator(void* iterator);
void * itrElementGraphPreOrderIterator(void* iterator);
void itrSuccessorGraphPreOrderIterator(void* iterator);

#endif
