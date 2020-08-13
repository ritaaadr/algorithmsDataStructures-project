
#ifndef GRAPHBST_H
#define GRAPHBST_H

/* ************************************************************************** */

#include "../../graph.h"
#include "../../../bst/bst.h"

/* ************************************************************************** */

typedef struct Adj{
    uint id; //"etichetta"
    BSTObject* treeAdj;
}Adj;

typedef struct GraphBST
{
    uint numVertex;
    BSTObject* vertexes;
    uint size;
    Adj** adjacents;
} GraphBST;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphBST();
void DestructGraphBST(GraphRepresentation* representation);

/* ************************************************************************** */

void* graphConstructBSTType();
void graphDestructBSTType(void* tree);
bool graphEmptyBSTType(void* tree);

void* graphCloneBSTType(void* tree);
void* graphTransposeBSTType(void* tree);

bool graphInsertVertexBSTType(void* tree, DataObject* elem, uint label);
bool graphRemoveVertexBSTType(void* tree, uint VertIndex, uint* EdgNum);
bool graphInsertEdgeBSTType(void* tree, uint label1, uint label2);
bool graphRemoveEdgeBSTType(void* tree, uint label1, uint label2);

bool graphExistsVertexBSTType(void* tree, uint label);
bool graphExistsEdgeBSTType(void* tree, uint label1, uint label2);

DataObject* graphGetVertexDataBSTType(void* tree, uint label);
void graphSetVertexDataBSTType(void* tree, uint label, DataObject* elem);

uint graphVertexFromPointerBSTType(void* tree, void* vert);

ITRObject* graphVerticesBSTType(void* tree);
ITRObject* graphVertexEdgesBSTType(void* tree, uint label);

void printBst(void* tree);

#endif
