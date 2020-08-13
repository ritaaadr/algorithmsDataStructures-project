
#ifndef GRAPHMAT_H
#define GRAPHMAT_H

/* ************************************************************************** */

#include <bst/bst.h>
#include <queue/queue.h>
#include "../../graph.h"
#include "matitr.h"

/* ************************************************************************** */

typedef struct GraphMat
{
    int** MatrixAdj;
    BSTObject* BSTvertices;
    QueueObject* queue;
    int VertNum, matrixSize, index;
    int itrIndex;
} GraphMat;

typedef struct GraphEdgStruct
{
    GraphMat* graph;
    uint vertexIndex;
} GraphEdgStruct;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphMat();
void DestructGraphMat(GraphRepresentation* representation);

/* ************************************************************************** */

void* graphConstructMatType();
void graphDestructMatType(void* matrix);
bool graphEmptyMatType(void* list);

void* graphCloneMatType(void* matrix);
void* graphTransposeMatType(void* matrix);

bool graphInsertVertexMatType(void* list, DataObject* elem, uint label);
bool graphRemoveVertexMatType(void* matrix, uint VertIndex, uint* EdgNum);
bool graphInsertEdgeMatType(void* matrix, uint label1, uint label2);
bool graphRemoveEdgeMatType(void* matrix, uint label1, uint label2);

bool graphExistsVertexMatType(void* matrix, uint label);
bool graphExistsEdgeMatType(void* matrix, uint label1, uint label2);

DataObject* graphGetVertexDataMatType(void* matrix, uint label);
void graphSetVertexDataMatType(void* matrix, uint label, DataObject* elem);

uint graphVertexFromPointerMatType(void* matrix, void* vert);

ITRObject* graphVerticesMatType(void* matrix);
ITRObject* graphVertexEdgesMatType(void* matrix, uint label);

void* MapPosition(void* vertValue, int index);
uint* graphGetIndex(GraphMat* graph, uint label);


#endif
