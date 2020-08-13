
#include <bst/bst.h>
#include <bst/rec/bstrec.h>
#include <adt/int/adtint.h>
#include <stack/stack.h>
#include <stack/vec/stackvec.h>
#include <adt/vert/adtvert.h>
#include <queue/queue.h>
#include <queue/lst/queuelst.h>
#include <list/itrlist.h>
#include <graph/itr/graphitr.h>
#include <stack/lst/stacklst.h>
#include "graphrec.h"

/* ************************************************************************** */

GraphType* ConstructGraphRecursive(GraphRepresentation* representation)
{
    GraphType* type = (GraphType*)malloc(sizeof(GraphType));

    type->graph_representation = representation;

    type->graph_equal = &graphEqualRec;

    type->graph_shortestPath = &graphShortestPathRec;

    type->graph_isAcyclic = &GraphIsAcyclicRec;

    type->graph_topologicalOrder = &graphTopologicalOrderRec;

    type->graph_maximalReachableSubgraph = &graphMaximalReachableSubgraphRec;

    type->graph_SCCGraph = &graphSCCGraphRec;

    type->graph_preOrderMap = &graphPreOrderMapRec;
    type->graph_postOrderMap = &graphPostOrderMapRec;
    type->graph_breadthMap= &graphBreadthMapRec;
    type->graph_preOrderFold = &graphPreOrderFoldRec;
    type->graph_postOrderFold = &graphPostOrderFoldRec;
    type->graph_breadthFold = &graphBreadthFoldRec;

    return type;
}

bool graphEqualRec(void* gra, void* grax)
{
    GraphObject* graph = (GraphObject*)gra;
    GraphObject* graphx = (GraphObject*)grax;

    ITRObject* vertItr = graphVertices(graph);
    return areEqualRec(vertItr ,graph ,graphx);
}

bool areEqualRec( void* iter , void* gra ,void* grax)
{
    ITRObject* vertItr = (ITRObject*)iter;
    GraphObject* graph = (GraphObject*)gra;
    GraphObject* graphx = (GraphObject*)grax;

    if(itrTerminated(vertItr)){
        return true;
    }else {
        DataObject* currElem = itrElement(vertItr);
        int vertName = adtGetVertexId(currElem->value);
        DataObject* VertData = graphGetVertexData(graphx , vertName);
        if(VertData == NULL){
            return false;
        }

        if(adtCompare(adtGetVertexData(currElem->value) , adtGetVertexData(VertData->value)) != 0 ){
            return false;
        }
        ITRObject* edg = graphVertexEdges(graph , vertName);
        ITRObject* edgx = graphVertexEdges(graphx, vertName);

        if((edg != NULL) && (edgx != NULL)){
            while(!itrTerminated(edg) && !itrTerminated(edgx)){
                uint edgElem = *((int*)itrElement(edg));
                uint edgToCheck = *((int*)itrElement(edgx));
                if(edgElem != edgToCheck){
                    return false;
                }
                itrSuccessor(edg);
                itrSuccessor(edgx);
            }
            if( itrTerminated(edg) && !itrTerminated(edgx)){
                return false;
            }

            if( itrTerminated(edgx) && !itrTerminated(edg)){
                return false;
            }
        }
        if((edg == NULL) && (edgx != NULL)){
            return false;
        }
        if((edgx == NULL) && (edg != NULL)){
            return false;
        }
        itrSuccessor(vertItr);
        return  areEqualRec(vertItr , graph , graphx);
    }
}

void* graphMaximalReachableSubgraphRec(void* gra, uint id)
{
    GraphObject* graph = (GraphObject*)gra;

    GraphObject* MaxSubgraph=NULL;

    DataType* intDataType = ConstructIntDataType();
    DataObject* elemToInsert = adtConstruct(intDataType);

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* treeOfColors = bstConstruct(bstType);

    MaximalReachDFS(graph , id , treeOfColors);

    MaxSubgraph = graphClone(graph);
    ITRObject* vertItr = graphVertices(MaxSubgraph);
    while(vertItr != NULL && !itrTerminated(vertItr)){
        DataObject *currmax= itrElement(vertItr);
        int currId = adtGetVertexId(currmax->value);
        adtSetValue(elemToInsert, &currId);
        if(!bstExists(treeOfColors , elemToInsert)){
            graphRemoveVertex(MaxSubgraph, currId);
        }
        itrSuccessor(vertItr);
    }
    return  MaxSubgraph;
}

void MaximalReachDFS(GraphObject* graph, int name , BSTObject* tree )
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* intDo = adtConstruct(intDataType);
    adtSetValue(intDo, &name);
    bstInsert(tree, intDo);

    ITRObject* edgItr = graphVertexEdges(graph,name);

    while(edgItr != NULL && !itrTerminated(edgItr)){
        uint elem = *((int*)itrElement(edgItr));
        adtSetValue(intDo, &elem);
        if(!bstExists(tree, intDo)){
            MaximalReachDFS(graph,elem,tree);
        }
        itrSuccessor(edgItr);
    }
}

int graphShortestPathRec(void* gra, uint label1, uint label2)
{
    GraphObject* graph = (GraphObject*)gra;
    BSTType *bstType = ConstructBSTRecursive();
    DataType *intType=ConstructIntDataType();
    QueueType *queType = ConstructQueueLstType();

    BSTObject* treeOfColors = bstConstruct(bstType);
    ITRObject *vertIter = graphVertices(graph);
    distanceRec *dis[graph->numVertex];

    DataObject *elemToEnqueue=adtConstruct(intType);
    int i = 0, map1 = -1, map2 = -1;
    //inizializzo array di distanze
    for (i = 0; i < graph->numVertex; i++){
        dis[i] = malloc(sizeof(distance));
        DataObject* curr = itrElement(vertIter);
        int currId = adtGetVertexId(curr->value);
        //salvo la distanza del primo vertice
        if (currId == label1) {
            map1 = i;
        }
        //salvo la distanza del secondo vertice
        if (currId == label2) {
            map2 = i;
        }
        dis[i]->name = currId;
        dis[i]->distance = 0;
        itrSuccessor(vertIter);
    }
    //controllo di esistenza
    if (map1 == -1 || map2 == -1){
        return 0;
    }
    if (map1 == map2){
        return 0;
    }
    //BFS
    QueueObject *queue = queConstruct(queType);
    adtSetValue(elemToEnqueue , &label1);
    queEnqueue(queue , elemToEnqueue);
    bstInsert(treeOfColors , elemToEnqueue );
    int curr;
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

bool GraphIsAcyclicRec(void* gra)
{
    GraphObject* graph = (GraphObject*)gra;

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
    //uso questo while per lanciare la DFS su ogni vertice
    while(vertIter != NULL && !itrTerminated(vertIter)){
        DataObject *data =itrElement(vertIter);
        int id = adtGetVertexId(data->value);
        adtSetValue(elemToInset , &id);
        if(!bstExists( treeOfColors , elemToInset)){
            if(isAcyclicUtilityRec( graph  , id , treeOfColors , array)){
                return  false;
            }
        }
        itrSuccessor(vertIter);
    }
    return true;
}

bool isAcyclicUtilityRec(GraphObject* graph, int name , BSTObject* treee , distanceRec* array[])
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* elemToInsert = adtConstruct(intDataType);
    adtSetValue(elemToInsert, &name);

    if(!bstExists(treee, elemToInsert)){
        bstInsert(treee, elemToInsert);
        int pos =0;
        //cerco il "name" nell'array di "distanze"
        for(uint i=0;i<graph->numVertex;i++){
            if(array[i]->name == name){
                array[i]->distance = 1;
                break;
            }
        }
        ITRObject* edgIter = graphVertexEdges(graph, name);
        while(edgIter!= NULL && !itrTerminated(edgIter)){
            int currElem = *((int*)itrElement(edgIter));
            //cerco il "name" nell'array di "distanze"
            for(uint i=0;i<graph->numVertex;i++){
                if(array[i]->name == currElem){
                    pos = i;
                    break;
                }
            }
            adtSetValue(elemToInsert, &currElem);
            if(!bstExists(treee,elemToInsert) && isAcyclicUtilityRec(graph, currElem, treee, array)){
                return true;
            } else {
                if(array[pos]->distance != 0){
                    return true;
                }
            }
            itrSuccessor(edgIter);
        }
    }
    //cerco il "name" nell'array di "distanze"
    int pos=0;
    for(uint i=0;i<graph->numVertex;i++){
        if(array[i]->name == name){
            pos = i;
            break;
        }
    }
    // e' gia nell'albero quindi è nero, imposto la "distanza"(colore grigio) a 0
    array[pos]->distance = 0;
    return false;
}

void graphPreOrderMapRec(void* gra, MapFun fun , void* par)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstElem = adtConstruct(intDataType);

    while(vertItr!= NULL && !itrTerminated(vertItr)){
        DataObject* elem = itrElement(vertItr);
        uint elemId = adtGetVertexId(elem->value);
        adtSetValue(bstElem, &elemId);
        if(!bstExists(tree, bstElem)){
            DFSVisit(graph, elemId, tree, fun, par);
        }
        itrSuccessor(vertItr);
    }
}

void DFSVisit( GraphObject* graph  ,int label , BSTObject* tree, MapFun fun, void* par)
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* intDo = adtConstruct(intDataType);
    adtSetValue(intDo, &label);
    bstInsert(tree, intDo);

    DataObject* curr = graphGetVertexData(graph, label);
    fun(curr, par);

    ITRObject* edgItr = graphVertexEdges(graph, label);
    while(edgItr != NULL && !itrTerminated(edgItr)){
        uint elem = *((int*)itrElement(edgItr));
        adtSetValue(intDo, &elem);
        if(!bstExists(tree, intDo)){
            DFSVisit(graph, elem, tree, fun, par);
        }
        itrSuccessor(edgItr);
    }
}

void graphPreOrderFoldRec(void* gra , FoldFun fun , void* par , void* parx)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstElem = adtConstruct(intDataType);

    while(vertItr!= NULL && !itrTerminated(vertItr)){
        DataObject* elem = itrElement(vertItr);
        uint elemId = adtGetVertexId(elem->value);
        adtSetValue(bstElem, &elemId);
        if(!bstExists(tree, bstElem)){
            DFSVisitFold(graph, elemId, tree, fun, par, parx);
        }
        itrSuccessor(vertItr);
    }
}

void DFSVisitFold( GraphObject* graph  ,int label , BSTObject* tree, FoldFun fun, void* par, void* parx)
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* intDo = adtConstruct(intDataType);
    adtSetValue(intDo, &label);
    bstInsert(tree, intDo);

    DataObject* curr = graphGetVertexData(graph, label);
    fun(curr, par, parx);

    ITRObject* edgItr = graphVertexEdges(graph, label);
    while(edgItr != NULL && !itrTerminated(edgItr)){
        uint elem = *((int*)itrElement(edgItr));
        adtSetValue(intDo, &elem);
        if(!bstExists(tree, intDo)){
            DFSVisitFold(graph, elem, tree, fun, par, parx);
        }
        itrSuccessor(edgItr);
    }
}


void graphPostOrderMapRec(void* gra, MapFun fun, void* par)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstElem = adtConstruct(intDataType);

    while(vertItr!= NULL && !itrTerminated(vertItr)){
        DataObject* elem = itrElement(vertItr);
        uint elemId = adtGetVertexId(elem->value);
        adtSetValue(bstElem, &elemId);
        if(!bstExists(tree, bstElem)){
            DFSVisitPostOrder(graph, elemId, tree, fun, par);
        }
        itrSuccessor(vertItr);
    }
}

void DFSVisitPostOrder( GraphObject* graph  ,int label , BSTObject* tree, MapFun fun, void* par)
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* intDo = adtConstruct(intDataType);
    adtSetValue(intDo, &label);
    bstInsert(tree, intDo);

    DataObject* curr = graphGetVertexData(graph, label);

    ITRObject* edgItr = graphVertexEdges(graph, label);
    while(edgItr != NULL && !itrTerminated(edgItr)){
        uint elem = *((int*)itrElement(edgItr));
        adtSetValue(intDo, &elem);
        if(!bstExists(tree, intDo)){
            DFSVisitPostOrder(graph, elem, tree, fun, par);
        }
        itrSuccessor(edgItr);
    }
    fun(curr, par);
}

void graphPostOrderFoldRec(void* gra, FoldFun fun , void* accum, void* par)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstElem = adtConstruct(intDataType);

    while(vertItr!= NULL && !itrTerminated(vertItr)){
        DataObject* elem = itrElement(vertItr);
        uint elemId = adtGetVertexId(elem->value);
        adtSetValue(bstElem, &elemId);
        if(!bstExists(tree, bstElem)){
            DFSVisitPostOrderFold(graph, elemId, tree, fun, accum, par);
        }
        itrSuccessor(vertItr);
    }
}

void DFSVisitPostOrderFold( GraphObject* graph  ,int label , BSTObject* tree, FoldFun fun,void* accum, void* par)
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* intDo = adtConstruct(intDataType);
    adtSetValue(intDo, &label);
    bstInsert(tree, intDo);

    DataObject* curr = graphGetVertexData(graph, label);

    ITRObject* edgItr = graphVertexEdges(graph, label);
    while(edgItr != NULL && !itrTerminated(edgItr)){
        uint elem = *((int*)itrElement(edgItr));
        adtSetValue(intDo, &elem);
        if(!bstExists(tree, intDo)){
            DFSVisitPostOrderFold(graph, elem, tree, fun, accum, par);
        }
        itrSuccessor(edgItr);
    }
    fun(curr, accum, par);
}

void graphBreadthMapRec(void* gra, MapFun fun, void* par)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstElem = adtConstruct(intDataType);

    while(vertItr!= NULL && !itrTerminated(vertItr)){
        DataObject* elem = itrElement(vertItr);
        uint elemId = adtGetVertexId(elem->value);
        adtSetValue(bstElem, &elemId);
        if(!bstExists(tree, bstElem)){
            DFSVisitBreadthMap(graph, elemId, tree, fun, par);
        }
        itrSuccessor(vertItr);
    }
}

void DFSVisitBreadthMap(GraphObject* graph, int elemId, BSTObject* tree, MapFun fun, void* par)
{
    DataType *intType=ConstructIntDataType();
    QueueType *queType = ConstructQueueLstType();
    DataObject* elemToEnqueue = adtConstruct(intType);

    QueueObject *queue = queConstruct(queType);
    adtSetValue(elemToEnqueue , &elemId);
    queEnqueue(queue , elemToEnqueue);
    bstInsert(tree , elemToEnqueue );
    int curr;
    while(!queEmpty(queue) ){
        curr= *(int*) adtGetValue(queHeadNDequeue(queue));
        DataObject* vert = graphGetVertexData(graph, curr);

        fun(vert, par);

        ITRObject *edgItr= graphVertexEdges(graph , curr);
        adtSetValue(elemToEnqueue , &curr);
        while(edgItr!=NULL && !itrTerminated(edgItr)){
            int currAdj= *((int*)itrElement(edgItr));
            adtSetValue(elemToEnqueue , &currAdj);
            if(!bstExists(tree ,elemToEnqueue) ) {
                queEnqueue(queue, elemToEnqueue);
                bstInsert(tree, elemToEnqueue);
            }
            itrSuccessor(edgItr);
        }
    }
}

void graphBreadthFoldRec(void* gra, FoldFun fun , void* accum, void* par)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstElem = adtConstruct(intDataType);

    while(vertItr!= NULL && !itrTerminated(vertItr)){
        DataObject* elem = itrElement(vertItr);
        uint elemId = adtGetVertexId(elem->value);
        adtSetValue(bstElem, &elemId);
        if(!bstExists(tree, bstElem)){
            DFSVisitBreadthFold(graph, elemId, tree, fun,accum, par);
        }
        itrSuccessor(vertItr);
    }
}

void DFSVisitBreadthFold(GraphObject* graph, int elemId, BSTObject* tree, FoldFun fun,void* accum, void* par)
{
    DataType *intType=ConstructIntDataType();
    QueueType *queType = ConstructQueueLstType();
    DataObject* elemToEnqueue = adtConstruct(intType);

    QueueObject *queue = queConstruct(queType);
    adtSetValue(elemToEnqueue , &elemId);
    queEnqueue(queue , elemToEnqueue);
    bstInsert(tree , elemToEnqueue );
    int curr;
    while(!queEmpty(queue) ){
        curr= *(int*) adtGetValue(queHeadNDequeue(queue));
        DataObject* vert = graphGetVertexData(graph, curr);

        fun(vert,accum, par);

        ITRObject *edgItr= graphVertexEdges(graph , curr);
        adtSetValue(elemToEnqueue , &curr);
        while(edgItr!=NULL && !itrTerminated(edgItr)){
            int currAdj= *((int*)itrElement(edgItr));
            adtSetValue(elemToEnqueue , &currAdj);
            if(!bstExists(tree ,elemToEnqueue) ) {
                queEnqueue(queue, elemToEnqueue);
                bstInsert(tree, elemToEnqueue);
            }
            itrSuccessor(edgItr);
        }
    }
}



void* graphTopologicalOrderRec(void* gra)
{
    GraphObject* graph = (GraphObject*)gra;

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* treeOfColors = bstConstruct(bstType);
    BSTObject* tree = bstConstruct(bstType);

    DataType* intType = ConstructIntDataType();
    DataObject* elemToInset = adtConstruct(intType);

    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType);

    ITRObject* vertIter = graphVertices(graph);
    ITRType* listType = ConstructItrListIterator();

    while(vertIter != NULL && !itrTerminated(vertIter)){
        DataObject* data = itrElement(vertIter);
        int elem = adtGetVertexId(data->value);
        adtSetValue(elemToInset, &elem);
        if(!bstExists(treeOfColors ,elemToInset)){
            TopologicalRec(graph, elem, treeOfColors, tree, stack);
        }
        itrSuccessor(vertIter);
    }
    Lst* list = NULL;
    int StkSize = stkSize(stack);
    for(uint i=0;i<StkSize; i++){
        DataObject *tmp = stkTopNPop(stack);
        int *value = adtGetValue(tmp);
        int elemOnTop = *value;
        adtDestruct(tmp);
        free(value);
        list = listInsert(list, elemOnTop);
    }
    ITRObject* listItr = itrConstruct(listType, list);
    return listItr;
}

void* TopologicalRec(void* gra, int elem, void* albero, void* albero2, void* sta)
{
        GraphObject* graph = (GraphObject*)gra;
        BSTObject* treeOfBlacks = (BSTObject*)albero;
        BSTObject* treeOfGreys = (BSTObject*)albero2;
        StackObject* retStack = (StackObject*)sta;

        DataType* intDataType = ConstructIntDataType();
        DataObject* intDo = adtConstruct(intDataType);
        DataObject* tmpDo = adtConstruct(intDataType);

        adtSetValue(intDo, &elem);
        bstInsert(treeOfGreys, intDo);

        ITRObject* edgItr = graphVertexEdges(graph,elem);
        while(edgItr != NULL && !itrTerminated(edgItr)){
            uint curr = *((int*)itrElement(edgItr));
            adtSetValue(tmpDo, &curr);
            if(!bstExists(treeOfBlacks, tmpDo) && !bstExists(treeOfGreys , tmpDo)){
                retStack = TopologicalRec(graph , curr, treeOfBlacks , treeOfGreys , retStack);
            }
            itrSuccessor(edgItr);
        }
        bstRemove(treeOfGreys ,intDo);
        bstInsert(treeOfBlacks ,intDo);
        stkPush(retStack ,intDo);
        return retStack;
}

void* graphSCCGraphRec(void* gra)
{
    GraphObject* graph = (GraphObject*)gra;

    //creo lo stack
    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType);

    DataType* intDataType = ConstructIntDataType();
    DataObject* bstData = adtConstruct(intDataType);

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* tree = bstConstruct(bstType);
    BSTObject* treeGreys = bstConstruct(bstType);

    ITRObject* vertItr = graphVertices(graph);

    while(vertItr != NULL && !itrTerminated(vertItr)){
        DataObject* name = itrElement(vertItr);
        int id = adtGetVertexId(name->value);
        adtSetValue(bstData, &id);
        if(!bstExists(tree, bstData)){
            stack = TopologicalRec(graph, id, tree, treeGreys, stack);
        }
        itrSuccessor(vertItr);
    }
    //costruisco il trasposto
    GraphObject* transpose = graphTranspose(graph);

    //pulisco l'albero dei colori
    bstClear(tree);

    GraphObject *graphRet = graphConstruct(graph->type);

    while(!stkEmpty(stack)){
        DataObject *tmp = stkTopNPop(stack);
        int *value = adtGetValue(tmp);
        int stackElem = *value;
        adtDestruct(tmp);
        free(value);
        adtSetValue(bstData, &stackElem);
        if(!bstExists(tree, bstData)) {
            DataObject* bstElemData = graphGetVertexData(graph, stackElem);
            DataObject* innerDo = adtGetVertexData(bstElemData->value);
            graphInsertVertex(graphRet, innerDo, stackElem);
            DFSVisitSCC(transpose, stackElem, tree, graphRet);
        }
    }
    return graphRet;
}

void* SCCUtilityRec(GraphObject* graph, uint name, BSTObject* tree, StackObject* stack)
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* intDo = adtConstruct(intDataType);

    ITRObject* edgItr = graphVertexEdges(graph,name);

    adtSetValue(intDo, &name);
    bstInsert(tree ,intDo);

    if(!stkExists(stack,intDo)) {
        stkPush(stack, intDo);
    }

    while(edgItr != NULL && !itrTerminated(edgItr)){
        uint curr = *((int*)itrElement(edgItr));
        adtSetValue(intDo, &curr);
        if(!bstExists(tree, intDo)){
            stack = SCCUtilityRec(graph , curr, tree, stack);
        }
        itrSuccessor(edgItr);
    }

    return stack;
}

void DFSVisitSCC(GraphObject* transpose, int stackElem, BSTObject* tree, GraphObject* graphToRet)
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* intDo = adtConstruct(intDataType);

    ITRObject* edgItr = graphVertexEdges(transpose,stackElem);

    adtSetValue(intDo, &stackElem);
    bstInsert(tree ,intDo);


    while(edgItr != NULL && !itrTerminated(edgItr)){
        uint curr = *((int*)itrElement(edgItr));
        adtSetValue(intDo, &curr);
        if(!bstExists(tree, intDo)){
            DFSVisitSCC(transpose,curr, tree, graphToRet);
        } else {
            //aggiungo arco da intDO a curr
            graphInsertEdge(graphToRet, curr, stackElem);
        }
        itrSuccessor(edgItr);
    }
}