#ifndef GRAPHITR_H
#define GRAPHITR_H

/* ************************************************************************** */

#include "../graph.h"

/* ************************************************************************** */

GraphType* ConstructGraphIterative(GraphRepresentation*);
void DestructGraphIterative(GraphType*);

typedef struct distance {
    int name;
    int distance;
}distance;

/* ************************************************************************** */

bool graphEqualItr(void* gra1, void*gra2);
int graphShortestPathItr(void *gra, uint label1, uint label2);

bool GraphIsAcyclicItr(void *grafo);
//bool isAcyclic(GraphObject* gra, int name , BSTObject* treee , distance* array[]);
bool isAcyclic(GraphObject* graph, int name , BSTObject* tree);

void* graphTopologicalOrderItr(void*);
void DfsVisitIterative(void* gra, int elem, void* tree , void* stackk);

void* graphMaximalReachableSubgraphItr(void*, uint);

void* graphSCCGraphItr(void*);
void DFSVisitSCCItr(GraphObject* transpose, uint stackElem, BSTObject* tree, GraphObject* graphRet);

void graphPreOrderMapItr(void* graph_t, MapFun fun , void* par);
void graphPreOrderFoldItr(void* graph_t, FoldFun fun , void* accum, void* par);
void graphPostOrderMapItr(void* graph_t, MapFun fun , void* par);
void graphBreadthMapItr(void* graph_t, MapFun fun , void* par);
void graphPostOrderFoldItr(void* graph_t, FoldFun fun , void* accum, void* par);
void graphBreadthFoldItr(void* graph_t, FoldFun fun , void* accum, void* par);

#endif
