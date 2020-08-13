
#ifndef GRAPHREC_H
#define GRAPHREC_H

/* ************************************************************************** */

#include "../graph.h"

/* ************************************************************************** */

typedef struct distanceRec {
    int name;
    int distance;
}distanceRec;

GraphType* ConstructGraphRecursive(GraphRepresentation*);
void DestructGraphRecursive(GraphType*);

bool graphEqualRec(void*, void*);
bool areEqualRec( void* iter , void* gra ,void* grax);

int graphShortestPathRec(void*, uint, uint);

bool GraphIsAcyclicRec(void*);
bool isAcyclicUtilityRec(GraphObject* graph, int name , BSTObject* treee , distanceRec* array[]);

void* graphTopologicalOrderRec(void* gra);

void* graphMaximalReachableSubgraphRec(void*, uint );
void MaximalReachDFS(GraphObject* graph, int name , BSTObject* tree );

void* graphSCCGraphRec(void*);

void graphPreOrderMapRec(void*, MapFun, void*);
void graphPostOrderMapRec(void*, MapFun, void*);
void graphBreadthMapRec(void*, MapFun, void*);
void graphPreOrderFoldRec(void*, FoldFun, void*, void*);
void graphPostOrderFoldRec(void*, FoldFun, void*, void*);
void graphBreadthFoldRec(void*, FoldFun, void*, void*);

void DFSVisit( GraphObject* graph  ,int label , BSTObject* tree, MapFun fun, void* par);
void DFSVisitPostOrder( GraphObject* graph  ,int label , BSTObject* tree, MapFun fun, void* par);
void DFSVisitFold( GraphObject* graph  ,int label , BSTObject* tree, FoldFun fun, void* par, void* parx);
void DFSVisitPostOrderFold( GraphObject* graph  ,int label , BSTObject* tree, FoldFun fun,void* accum, void* par);
void DFSVisitBreadthMap(GraphObject* graph,int elemId, BSTObject* tree, MapFun fun, void* par);
void DFSVisitBreadthFold(GraphObject* graph, int elemId, BSTObject* tree, FoldFun fun,void* accum, void* par);
void* TopologicalRec(void* gra, int elem, void* albero, void* albero2, void* sta);
void* SCCUtilityRec(GraphObject* graph, uint name, BSTObject* tree, StackObject* stack);
void DFSVisitSCC(GraphObject* transpose, int stackElem, BSTObject* tree, GraphObject* graphToRet);

#endif
