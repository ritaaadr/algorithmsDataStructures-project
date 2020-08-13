
#ifndef GRAPHLST_H
#define GRAPHLST_H

/* ************************************************************************** */

#include <bst/bst.h>
#include "../../graph.h"
#include "bst/rec/bstrec.h"
#include <adt/vert/adtvert.h>

/* ************************************************************************** */

typedef struct AdjInfo{
    uint id; //"etichetta"
    Lst* lstAdj;
}AdjInfo;

typedef struct GraphLst
{
  AdjInfo** array;
  uint numVertex;
  BSTObject* vertexes;
  uint Size;
} GraphLst;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphLst();
void DestructGraphLst(GraphRepresentation* representation);

/* ************************************************************************** */

void* graphConstructLstType();
void graphDestructLstType(void* list);
bool graphEmptyLstType(void* list);

void* graphCloneLstType(void* list);
void* graphTransposeLstType(void* list);

bool graphInsertVertexLstType(void* list, DataObject* elem, uint label);
bool graphRemoveVertexLstType(void* list, uint VertIndex, uint* EdgNum);
bool graphInsertEdgeLstType(void* list, uint label1, uint label2);
bool graphRemoveEdgeLstType(void* list, uint label1, uint label2);

bool graphExistsVertexLstType(void* list, uint label);
bool graphExistsEdgeLstType(void* list, uint label1, uint label2);

DataObject* graphGetVertexDataLstType(void* list, uint label);
void graphSetVertexDataLstType(void* list, uint label, DataObject* elem);

uint graphVertexFromPointerLstType(void* list, void* vert);

ITRObject* graphVerticesLstType(void* list);
ITRObject* graphVertexEdgesLstType(void* list, uint label);

void printList(void* list);

#endif
