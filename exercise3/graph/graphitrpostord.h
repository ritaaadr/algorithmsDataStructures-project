#ifndef GRAPHITRPOSTORD_H
#define GRAPHITRPOSTORD_H

#include <bst/bst.h>
#include "../itr/itr.h"
#include "../stack/stack.h"
#include "graph.h"


typedef struct GraphPostOrderIterator
{
    ITRObject* verticesIterator;
    uint curr; //id del vertice corrente
    BSTObject* treeOfColors; // 0 Bianco - 1 Grigio - 2 Nero
    StackObject* stack;
    GraphObject* graph;
    ITRObject* currEdg;
} GraphPostOrderIterator;


ITRType* ConstructGraphPostOrderIterator();
void DestructGraphPostOrderIterator(ITRType* type);


void * itrConstructGraphPostOrderIterator(void* graphStruct);
void itrDestructGraphPostOrderIterator(void* iterator);
bool itrTerminatedGraphPostOrderIterator(void* iterator);
void * itrElementGraphPostOrderIterator(void* iterator);
void itrSuccessorGraphPostOrderIterator(void* iterator);

#endif
