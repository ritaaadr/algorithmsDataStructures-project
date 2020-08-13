#ifndef GRAPHITRBREADTH_H
#define GRAPHITRBREADTH_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../queue/queue.h"

#include "graph.h"

/* ************************************************************************** */

typedef struct GraphBreadthIterator
{
    GraphObject* graph;
    QueueObject* queue;
    DataObject* curr;
    ITRObject* verticesItr;
    BSTObject* treeOfColors;
}GraphBreadthIterator;

/* ************************************************************************** */
ITRType * ConstructGraphBreadthIterator();
void  DestructGraphBreadthIterator(ITRType *tipo);

/* ************************************************************************** */

void* itrConstructBreadthIterator(void* gra);

void itrDestructBreadthIterator(void* iterator);

bool itrTerminatedBreadthIterator(void* iterator);

void* itrElementBreadthIterator(void* iterator);

void  itrSuccessorBreadthIterator(void* iterator);

#endif

