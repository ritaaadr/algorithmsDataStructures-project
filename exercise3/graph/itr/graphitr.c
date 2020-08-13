
#include <graph/graphitrpreord.h>
#include <adt/vert/adtvert.h>
#include <graph/graphitrpostord.h>
#include <graph/graphitrbreadth.h>
#include <bst/rec/bstrec.h>
#include <adt/int/adtint.h>
#include <queue/lst/queuelst.h>
#include <stack/vec/stackvec.h>
#include <list/itrlist.h>
#include <adt/ptr/adtptr.h>
#include <stack/lst/stacklst.h>
#include "graphitr.h"

/* ************************************************************************** */

GraphType* ConstructGraphIterative(GraphRepresentation* representation)
{
    GraphType* type = (GraphType*)malloc(sizeof(GraphType));

    type->graph_representation = representation;

    type->graph_equal = &graphEqualItr;

    type->graph_shortestPath = &graphShortestPathItr;

    type->graph_isAcyclic = &GraphIsAcyclicItr;

    type->graph_topologicalOrder = &graphTopologicalOrderItr;

    type->graph_maximalReachableSubgraph = &graphMaximalReachableSubgraphItr;

    type->graph_SCCGraph = &graphSCCGraphItr;

    type->graph_preOrderMap = &graphPreOrderMapItr;
    type->graph_postOrderMap = &graphPostOrderMapItr;
    type->graph_breadthMap= &graphBreadthMapItr;
    type->graph_preOrderFold = &graphPreOrderFoldItr;
    type->graph_postOrderFold = &graphPostOrderFoldItr;
    type->graph_breadthFold = &graphBreadthFoldItr;

    return type;
}

/* ************************************************************************** */

void graphPreOrderMapItr(void* graph_t, MapFun fun , void* par)
{
    GraphObject* graph = (GraphObject*)graph_t;
    ITRType* itrType = ConstructGraphPreOrderIterator();
    ITRObject* iter = itrConstruct(itrType, graph);

    DataObject* data = NULL;

    while(!itrTerminated(iter)) {
        data = itrElement(iter);
        fun(data, par);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphPreOrderIterator(itrType);
}

/* ************************************************************************** */

void graphPreOrderFoldItr(void* graph_t, FoldFun fun , void* accum, void* par)
{
    GraphObject* graph = (GraphObject*)graph_t;
    ITRType* itrType = ConstructGraphPreOrderIterator();
    ITRObject* iter = itrConstruct(itrType, graph);

    DataObject* data = NULL;

    while(!itrTerminated(iter)) {
        data = itrElement(iter);
        DataObject* work = adtGetVertexData(data->value);
        fun(work, accum, par);
        itrSuccessor(iter);
    }
    //itrDestruct(iter);
    //DestructGraphPreOrderIterator(itrType);
}

/* ************************************************************************** */

void graphPostOrderMapItr(void* graph_t, MapFun fun , void* par)
{
    GraphObject* graph = (GraphObject*)graph_t;
    ITRType* itrType = ConstructGraphPostOrderIterator();
    ITRObject* iter = itrConstruct(itrType, graph);

    DataObject* data = NULL;

    while(!itrTerminated(iter)) {
        data = itrElement(iter);
        fun(data, par);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphPreOrderIterator(itrType);
}

void graphBreadthMapItr(void* graph_t, MapFun fun , void* par)
{
    GraphObject* graph = (GraphObject*)graph_t;
    ITRType* itrType = ConstructGraphBreadthIterator();
    ITRObject* iter = itrConstruct(itrType, graph);

    DataObject* data = NULL;

    while(!itrTerminated(iter)) {
        data = itrElement(iter);
        fun(data, par);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphPreOrderIterator(itrType);
}

void graphPostOrderFoldItr(void* graph_t, FoldFun fun , void* accum, void* par)
{
    GraphObject* graph = (GraphObject*)graph_t;
    ITRType* itrType = ConstructGraphPostOrderIterator();
    ITRObject* iter = itrConstruct(itrType, graph);

    DataObject* data = NULL;

    while(!itrTerminated(iter)) {
        data = itrElement(iter);
        DataObject* work = adtGetVertexData(data->value);
        fun(work, accum, par);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphPostOrderIterator(itrType);
}

void graphBreadthFoldItr(void* graph_t, FoldFun fun , void* accum, void* par)
{
    GraphObject* graph = (GraphObject*)graph_t;
    ITRType* itrType = ConstructGraphBreadthIterator();
    ITRObject* iter = itrConstruct(itrType, graph);

    DataObject* data = NULL;

    while(!itrTerminated(iter)) {
        data = itrElement(iter);
        DataObject* work = adtGetVertexData(data->value);
        fun(work, accum, par);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphBreadthIterator(itrType);
}

bool graphEqualItr(void *gra1, void *gra2)
{
    GraphObject* graph = (GraphObject*)gra1;
    GraphObject* graphx = (GraphObject*)gra2;

    ITRObject *vertIter = graphVertices(graph);

    while(!itrTerminated(vertIter)){
        DataObject *curr = itrElement(vertIter);
        int vertId = adtGetVertexId(curr->value);

        DataObject *elemToCheck = graphGetVertexData(graphx , vertId);
        if(elemToCheck==NULL){
            return false;
        }
        // CAPIRE COME CONTROLLARE ANCHE DATAOBJECT INTERNI
        if(adtCompare(adtGetVertexData(curr->value) , adtGetVertexData(elemToCheck->value)) != 0 ){
            return false;
        }
        ITRObject *GraphEdg = graphVertexEdges(graph , vertId);
        ITRObject *GraphxEdg = graphVertexEdges(graphx , vertId);

        if(GraphEdg!=NULL && GraphxEdg !=NULL){
            while(!itrTerminated(GraphEdg) && !itrTerminated(GraphxEdg)){
                int edgCurr = *((int*)itrElement(GraphEdg));
                int edg2Curr = *((int*)itrElement(GraphxEdg));
                if( edgCurr != edg2Curr){
                    return false;
                }
                itrSuccessor(GraphxEdg);
                itrSuccessor(GraphEdg);
            }
            if( itrTerminated(GraphEdg) && !itrTerminated(GraphxEdg)){
                return false;
            }

            if( itrTerminated(GraphxEdg) && !itrTerminated(GraphEdg)){
                return false;
            }
        }
        if(GraphEdg == NULL && GraphxEdg != NULL){
            return false;
        }
        if(GraphxEdg == NULL && GraphEdg != NULL){
            return false;
        }
        itrSuccessor(vertIter);
    }
    return true;
}

int graphShortestPathItr(void *gra, uint label1, uint label2)
{

    GraphObject* graph = (GraphObject*)gra;
    BSTType *bstType = ConstructBSTRecursive();
    DataType *intType=ConstructIntDataType();
    QueueType *queType = ConstructQueueLstType();

    BSTObject* treeOfColors = bstConstruct(bstType);
    ITRObject *vertIter = graphVertices(graph);
    distance *dis[graph->numVertex];

    DataObject *elemToEnqueue=adtConstruct(intType);
    int i = 0, map1 = -1, map2 = -1;
    for (i = 0; i < graph->numVertex; i++){
        dis[i] = malloc(sizeof(distance));
        DataObject *curr = itrElement(vertIter);
        int currId = adtGetVertexId(curr->value);
        if (currId == label1) {
            map1 = i;
        }

        if (currId == label2) {
            map2 = i;
        }

        dis[i]->name = currId;
        dis[i]->distance = 0;
        itrSuccessor(vertIter);
    }
    if (map1 == -1 || map2 == -1){
        return 0;
    }
    if (map1 == map2){
        return 0;
    }

    QueueObject *queue = queConstruct(queType);
    adtSetValue(elemToEnqueue , &label1);
    queEnqueue(queue , elemToEnqueue);
    bstInsert(treeOfColors , elemToEnqueue );
    int curr;
    int z=0;
    while(!queEmpty(queue) ){
        curr= *(int*) adtGetValue(queHeadNDequeue(queue));
        int x=0;
        for (i = 0; i < graph->numVertex; i++) {
            if (dis[i]->name == curr) {
                x=i;
            }
        }
        ITRObject *edgItr= graphVertexEdges(graph , curr);
        adtSetValue(elemToEnqueue , &curr);
        while(edgItr!=NULL && !itrTerminated(edgItr)){
            int currAdj= *((int*)itrElement(edgItr));
            adtSetValue(elemToEnqueue , &currAdj);
            if(!bstExists(treeOfColors ,elemToEnqueue) ) {
                queEnqueue(queue, elemToEnqueue);
                bstInsert(treeOfColors, elemToEnqueue);
                for (i = 0; i < graph->numVertex; i++) {
                    if (dis[i]->name == currAdj) {
                        dis[i]->distance = dis[x]->distance + 1;

                    }
                }
            }
            itrSuccessor(edgItr);
        }
    }

    return dis[map2]->distance;
}

bool GraphIsAcyclicItr(void *grafo)
{
    GraphObject *graph=grafo;

    BSTType *bstType = ConstructBSTRecursive();
    BSTObject *treeOfColors = bstConstruct(bstType);
    ITRObject *vertIter = graphVertices(graph);
    DataType *intType=ConstructIntDataType();
    DataObject *elemToInset=adtConstruct(intType);
    distance* array[graph->numVertex];

    ITRObject* itrArr = graphVertices(graph);
    for(uint i=0;i<graph->numVertex;i++){
        array[i] = malloc(sizeof(distance));
        DataObject *curr = itrElement(itrArr);
        int currId = adtGetVertexId(curr->value);

        array[i]->name = currId;
        array[i]->distance = 0;
        itrSuccessor(itrArr);
    }

    while(vertIter != NULL && !itrTerminated(vertIter)){
        DataObject *data =itrElement(vertIter);
        int id = adtGetVertexId(data->value);
        adtSetValue(elemToInset , &id);
        if(!bstExists( treeOfColors , elemToInset)){
            if(isAcyclic( graph  , id , treeOfColors)){
                return  false;
            }

        }
        itrSuccessor(vertIter);
    }
    return true;
}

bool isAcyclic(GraphObject* graph, int name , BSTObject* tree)
{
    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType);

    DataType* intDataType = ConstructIntDataType();
    DataObject* elemToPush = adtConstruct(intDataType);

    adtSetValue(elemToPush, &name);
    stkPush(stack, elemToPush);

    while(!stkEmpty(stack)) {
        int current = *((int*)adtGetValue(stkTopNPop(stack)));
        adtSetValue(elemToPush, &current);
        if(!bstExists(tree, elemToPush)){
            bstInsert(tree,elemToPush);
        }

        ITRObject* edgItr = graphVertexEdges(graph, current);
        while (edgItr != NULL && !itrTerminated(edgItr)) {
            current = *((int*)itrElement(edgItr));
            adtSetValue(elemToPush, &current);
            if(!bstExists(tree, elemToPush)){
                stkPush(stack,elemToPush);
            } else {
               return true;
            }
            itrSuccessor(edgItr);
        }
    }
    return false;
}

void* graphTopologicalOrderItr(void* gra)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType *bstType = ConstructBSTRecursive();
    BSTObject *treeOfColors = bstConstruct(bstType);

    DataType *intType=ConstructIntDataType();
    DataObject *elemToInset=adtConstruct(intType);

    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType);

    ITRObject *vertIter = graphVertices(graph);
    ITRType* listType = ConstructItrListIterator();

    while(vertIter != NULL && !itrTerminated(vertIter)){
        DataObject *data =itrElement(vertIter);
        int elem= adtGetVertexId(data->value);
        adtSetValue(elemToInset , &elem);
        if(!bstExists( treeOfColors , elemToInset)){
            DfsVisitIterative(graph, elem, treeOfColors, stack);
        }
        itrSuccessor(vertIter);
    }
    Lst* list = NULL;
    int StkSize = stkSize(stack);

    for(uint i=0;i<StkSize; i++){
        int elemOnTop = *((int*)adtGetValue(stkTopNPop(stack)));
        list = listInsert(list, elemOnTop);
    }
    ITRObject* listItr = itrConstruct(listType, list);
    return listItr;
}

void DfsVisitIterative(void* gra, int elem, void* tree , void* SStack) {
    GraphObject *graph = (GraphObject *) gra;
    BSTObject *treeOfColors = (BSTObject *) tree;
    StackObject *stack = (StackObject *) SStack;

    DataType *intDataType = ConstructIntDataType();
    DataObject *elemToInsert = adtConstruct(intDataType);

    StackType *stkType = ConstructStackVecType();
    StackObject *tmpStack = stkConstruct(stkType);

    adtSetValue(elemToInsert, &elem);
    stkPush(tmpStack, elemToInsert);

    ITRObject *edgItr = NULL;
    while (!stkEmpty(tmpStack)) {
        DataObject *tmp = stkTopNPop(tmpStack);
        int *value = adtGetValue(tmp);
        int curr = *value;
        adtDestruct(tmp);
        free(value);

        if (curr > 0) {
            adtSetValue(elemToInsert, &curr);
            bstInsert(treeOfColors, elemToInsert);
            int trick = curr * -1;
            adtSetValue(elemToInsert, &trick);
            stkPush(tmpStack, elemToInsert);
            edgItr = graphVertexEdges(graph, curr);
            while (edgItr != NULL && !itrTerminated(edgItr)) {
                int currEdg = *((int *) itrElement(edgItr));
                adtSetValue(elemToInsert, &currEdg);
                if (!bstExists(treeOfColors, elemToInsert)) {
                    stkPush(tmpStack, elemToInsert);
                }
                itrSuccessor(edgItr);
            }
        } else {
            curr = curr * -1;
            adtSetValue(elemToInsert, &curr);
            stkPush(stack, elemToInsert);
        }
    }
}



void* graphMaximalReachableSubgraphItr(void* graaph , uint start)
{
    GraphObject* graph = (GraphObject*)graaph;

    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType); //stack di risalita

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* treeOfColors = bstConstruct(bstType);

    DataType* intDataType = ConstructIntDataType();
    ITRObject* edgItr = NULL;
    DataObject* elemToPush = adtConstruct(intDataType);
    adtSetValue(elemToPush, &start);
    stkPush(stack, elemToPush);

    while(!stkEmpty(stack)) {
        DataObject *tmp = stkTopNPop(stack);
        int *value = adtGetValue(tmp);
        int current = *value;
        adtDestruct(tmp);
        free(value);
        adtSetValue(elemToPush, &current);
        if(!bstExists(treeOfColors, elemToPush)){
                bstInsert(treeOfColors,elemToPush);
        }
        edgItr = graphVertexEdges(graph, current);
        while (edgItr != NULL && !itrTerminated(edgItr)) {
            current = *((int*)itrElement(edgItr));
            adtSetValue(elemToPush, &current);
            if(!bstExists(treeOfColors, elemToPush)){
                stkPush(stack,elemToPush);
            }
            itrSuccessor(edgItr);
        }
    }

    GraphObject* clone = graphClone(graph);
    ITRObject* CloneVertItr = graphVertices(clone);
    while(CloneVertItr!= NULL && !itrTerminated(CloneVertItr)){
        DataObject* currElem = itrElement(CloneVertItr);
        uint ElemId = adtGetVertexId(currElem->value);
        adtSetValue(elemToPush, &ElemId);
        if(!bstExists(treeOfColors, elemToPush)){
            graphRemoveVertex(clone, ElemId);
        }
        itrSuccessor(CloneVertItr);
    }
    return clone;
}

void* graphSCCGraphItr(void* gra)
{
    GraphObject* graph = (GraphObject*)gra;

    //creo lo stack
    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstData = adtConstruct(intDataType);

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    while(vertItr != NULL && !itrTerminated(vertItr)){
        DataObject* name = itrElement(vertItr);
        int id = adtGetVertexId(name->value);
        adtSetValue(bstData, &id);
        if(!bstExists(tree, bstData)){
            DfsVisitIterative(graph, id, tree, stack);
        }
        itrSuccessor(vertItr);
    }
    //costruisco il trasposto
    GraphObject* transpose = graphTranspose(graph);

    //pulisco l'albero dei colori
    bstClear(tree);

    GraphObject *graphRet = graphConstruct(graph->type);

    while(!stkEmpty(stack)){
        uint stackElem = *((int*)adtGetValue(stkTopNPop(stack)));
        adtSetValue(bstData, &stackElem);
        if(!bstExists(tree, bstData)) {
            DataObject* bstElemData = graphGetVertexData(graph, stackElem);
            DataObject* innerDo = adtGetVertexData(bstElemData->value);
            graphInsertVertex(graphRet, innerDo, stackElem);
            DFSVisitSCCItr(transpose, stackElem, tree, graphRet);
        }
    }
    return graphRet;
}

void DFSVisitSCCItr(GraphObject* transpose, uint stackElem, BSTObject* tree, GraphObject* graphRet)
{
    //DFS iterativa che prende in input il transposto
    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType);

    DataType* intDataType = ConstructIntDataType();
    DataObject* elemToPush = adtConstruct(intDataType);

    adtSetValue(elemToPush, &stackElem);
    stkPush(stack, elemToPush);

    while(!stkEmpty(stack)) {
        int current = *((int*)adtGetValue(stkTopNPop(stack)));
        adtSetValue(elemToPush, &current);
        if(!bstExists(tree, elemToPush)){
            bstInsert(tree,elemToPush);
        }

        ITRObject* edgItr = graphVertexEdges(transpose, current);
        while (edgItr != NULL && !itrTerminated(edgItr)) {
            current = *((int*)itrElement(edgItr));
            adtSetValue(elemToPush, &current);
            if(!bstExists(tree, elemToPush)){
                stkPush(stack,elemToPush);
            } else {
                graphInsertEdge(graphRet, current, stackElem);
            }
            itrSuccessor(edgItr);
        }
    }

}