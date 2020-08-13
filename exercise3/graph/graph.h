
#ifndef GRAPH_H
#define GRAPH_H

/* ************************************************************************** */

#include "../list/list.h"
#include "../utility.h"
#include "../adt/adt.h"
#include "../itr/itr.h"

/* ************************************************************************** */

typedef struct GraphVertex {
    uint label;
    DataObject* value;
}GraphVertex;

/* ************************************************************************** */

typedef void* (*GraphConstruct)();
typedef void (*GraphDestruct)(void*);

typedef bool (*GraphEmpty)(void*);

typedef void* (*GraphClone)(void*);
typedef void* (*GraphTranspose)(void*);

typedef bool (*GraphInsertVertex)(void*, DataObject*, uint);
typedef bool (*GraphRemoveVertex)(void*, uint, uint*);

typedef bool (*GraphInsertEdge)(void*, uint, uint);
typedef bool (*GraphRemoveEdge)(void*, uint, uint);

typedef bool (*GraphExistsVertex)(void*, uint);
typedef bool (*GraphExistsEdge)(void*, uint, uint);

typedef DataObject* (*GraphGetVertexData)(void*, uint);
typedef void (*GraphSetVertexData)(void*, uint, DataObject*);

typedef uint (*GraphVertexFromPointer)(void*, void*);

typedef ITRObject* (*GraphVertices)(void*);

typedef ITRObject* (*GraphVertexEdges)(void*, uint);

typedef bool (*GraphEqual)(void*, void*);

typedef int (*GraphShortestPath)(void*, uint, uint);

typedef bool (*GraphIsAcyclic)(void*);

typedef void* (*GraphTopologicalOrder)(void*);

typedef void* (*GraphMaximalReachableSubgraph)(void*, uint);

typedef void* (*GraphSCCGraph)(void*);

typedef void (*GraphPreOrderMap)(void*, MapFun, void*);
typedef void (*GraphPostOrderMap)(void*, MapFun, void*);
typedef void (*GraphBreadthMap)(void*, MapFun, void*);
typedef void (*GraphPreOrderFold)(void*, FoldFun, void*, void*);
typedef void (*GraphPostOrderFold)(void*, FoldFun, void*, void*);
typedef void (*GraphBreadthFold)(void*, FoldFun, void*, void*);

/* ************************************************************************** */

typedef struct GraphRepresentation
{
  GraphConstruct  graph_construct;
  GraphDestruct  graph_destruct;
  GraphEmpty  graph_empty;
  GraphClone  graph_clone;
  GraphTranspose graph_transpose;
  GraphInsertVertex graph_insertVertex;
  GraphRemoveVertex graph_removeVertex;
  GraphInsertEdge graph_insertEdge;
  GraphRemoveEdge graph_removeEdge;
  GraphExistsVertex graph_existsVertex;
  GraphExistsEdge graph_existsEdge;
  GraphGetVertexData graph_getVertexData;
  GraphSetVertexData graph_setVertexData;
  GraphVertexFromPointer graph_vertexFromPointer;
  GraphVertices graph_vertices;
  GraphVertexEdges graph_vertexEdges;
} GraphRepresentation;

typedef struct GraphType
{
  GraphRepresentation* graph_representation;
  GraphEqual graph_equal;
  GraphShortestPath graph_shortestPath;
  GraphIsAcyclic graph_isAcyclic;
  GraphTopologicalOrder graph_topologicalOrder;
  GraphMaximalReachableSubgraph graph_maximalReachableSubgraph;
  GraphSCCGraph graph_SCCGraph;
  GraphPreOrderMap graph_preOrderMap;
  GraphPostOrderMap graph_postOrderMap;
  GraphBreadthMap graph_breadthMap;
  GraphPreOrderFold graph_preOrderFold;
  GraphPostOrderFold graph_postOrderFold;
  GraphBreadthFold graph_breadthFold;
} GraphType;

typedef struct GraphObject
{
    GraphType* type;
    void* structure;
    uint numEdges;
    uint numVertex;
} GraphObject;

/* ************************************************************************** */

GraphObject* graphConstruct(GraphType*);
void graphDestruct(GraphObject*);

bool graphEmpty(GraphObject*);

uint graphVertexNumber(GraphObject*);
uint graphEdgeNumber(GraphObject*);

void graphClear(GraphObject*);

GraphObject* graphClone(GraphObject*);

GraphObject* graphTranspose(GraphObject*);

void graphInsertVertex(GraphObject*, DataObject*, uint);
void graphRemoveVertex(GraphObject*, uint);

void graphInsertEdge(GraphObject*, uint, uint);
void graphRemoveEdge(GraphObject*, uint, uint);

bool graphExistsVertex(GraphObject*, uint);
bool  graphExistsEdge(GraphObject*, uint, uint);

DataObject* graphGetVertexData(GraphObject*, uint);
void graphSetVertexData(GraphObject*, uint, DataObject*); //controlla tipo di ritorno

uint graphVertexFromPointer(GraphObject* graph, GraphVertex* graphVert);

ITRObject* graphVertices(GraphObject*);
ITRObject* graphVertexEdges(GraphObject*, uint);

bool graphEqual(GraphObject*, GraphObject*);

bool graphExistsVertexWithData(GraphObject*, DataObject*);

int graphShortestPath(GraphObject*, uint, uint);

bool graphIsAcyclic(GraphObject*);
ITRObject* graphTopologicalOrder(GraphObject*);

GraphObject* graphMaximalReachableSubgraph(GraphObject*, uint);

GraphObject* graphSCCGraph(GraphObject*);

void graphPreOrderMap(GraphObject*, MapFun, void*);
void graphPostOrderMap(GraphObject*, MapFun, void*);
void graphBreadthMap(GraphObject*, MapFun, void*);
void graphPreOrderFold(GraphObject*, FoldFun, void*, void*);
void graphPostOrderFold(GraphObject*, FoldFun, void*, void*);
void graphBreadthFold(GraphObject*, FoldFun, void*, void*);

void* vertexConstruct(DataType*);

/* ************************************************************************** */

#endif
