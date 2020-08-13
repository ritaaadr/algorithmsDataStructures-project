
#include <bst/rec/bstrec.h>
#include <adt/vert/adtvert.h>
#include <queue/lst/queuelst.h>
#include <adt/int/adtint.h>
#include <graph/vertitr.h>
#include "graphmat.h"
#include "edgitr .h"

/* ************************************************************************** */

GraphRepresentation* ConstructGraphMat()
{
    GraphRepresentation* representation = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    representation->graph_construct = &graphConstructMatType;
    representation->graph_destruct = &graphDestructMatType;
    representation->graph_empty = &graphEmptyMatType;

    representation->graph_clone = &graphCloneMatType;
    representation->graph_transpose = &graphTransposeMatType;

    representation->graph_insertVertex = &graphInsertVertexMatType;
    representation->graph_removeVertex = &graphRemoveVertexMatType;
    representation->graph_insertEdge = &graphInsertEdgeMatType;
    representation->graph_removeEdge = &graphRemoveEdgeMatType;

    representation->graph_existsVertex = &graphExistsVertexMatType;
    representation->graph_existsEdge = &graphExistsEdgeMatType;

    representation->graph_getVertexData = &graphGetVertexDataMatType;
    representation->graph_setVertexData = &graphSetVertexDataMatType;

    representation->graph_vertexFromPointer = &graphVertexFromPointerMatType;
    representation->graph_vertices = &graphVerticesMatType;
    representation->graph_vertexEdges = &graphVertexEdgesMatType;

    return representation;
}

/* ************************************************************************** */

void DestructGraphMat(GraphRepresentation* representation)
{
    free(representation);
}

/* ************************************************************************** */

void* graphConstructMatType()
{
    GraphMat* graph = (GraphMat*)malloc(sizeof(GraphMat));
    BSTType* bstType = ConstructBSTRecursive();
    graph->BSTvertices = bstConstruct(bstType);
    graph->MatrixAdj = (int**)malloc(sizeof(int*)*10);
    graph->matrixSize = 10;
    for(uint k=0;k<graph->matrixSize;k++){
        graph->MatrixAdj[k] = (int*)malloc(sizeof(int)*10);
    }
    graph->index = 0; //primo indice disponibile
    graph->VertNum = 0;
    graph->itrIndex = 0;
    QueueType* queType = ConstructQueueLstType();
    QueueObject* queue = queConstruct(queType);
    graph->queue = queue;
    //inizializiamo la prima colonna
    for(uint i=0;i<graph->matrixSize;i++){
        for(uint j=0;j<graph->matrixSize;j++) {
            graph->MatrixAdj[i][j] = 0;
        }
    }
    return graph;
}

/* ************************************************************************** */

void graphDestructMatType(void* matrix)
{
    GraphMat* graph = (GraphMat*)matrix;

    if(!queEmpty(graph->queue)) {
        queClear(graph->queue);
    }
    queDestruct(graph->queue);
    bstDestruct(graph->BSTvertices);
    for(uint i=0;i<graph->matrixSize;i++){
        free(graph->MatrixAdj[i]);
    }

}

/* ************************************************************************** */

bool graphEmptyMatType(void* list)
{
    GraphMat* graph = (GraphMat*)list;

    return graph->VertNum == 0;
}

/* ************************************************************************** */

void* graphCloneMatType(void* matrix)
{
    GraphMat* graph = (GraphMat*)matrix;

    GraphMat* graphClone = (GraphMat*)malloc(sizeof(GraphMat));
    graphClone->BSTvertices = bstClone(graph->BSTvertices);
    graphClone->queue = queClone(graph->queue);
    graphClone->matrixSize = graph->matrixSize;
    graphClone->VertNum = graph->VertNum;
    graphClone->index = graph->index;
    graphClone->itrIndex = graph->itrIndex;
    graphClone->MatrixAdj = (int**)malloc(sizeof(int*)*graphClone->matrixSize);
    for(uint k=0;k<graphClone->matrixSize;k++){
        graphClone->MatrixAdj[k] = (int*)malloc(sizeof(int)*graphClone->matrixSize);
    }
    for(uint i=0;i<graph->matrixSize;i++){
        for(uint j=0;j<graph->matrixSize;j++) {
            graphClone->MatrixAdj[i][j] = graph->MatrixAdj[i][j];
        }
    }
    return graphClone;
}

/* ************************************************************************** */

void* graphTransposeMatType(void* matrix)
{
    GraphMat* graph = (GraphMat*)matrix;

    GraphMat* graphTranspose = (GraphMat*)malloc(sizeof(GraphMat));
    graphTranspose->BSTvertices = bstClone(graph->BSTvertices);
    graphTranspose->queue = queClone(graph->queue);
    graphTranspose->matrixSize = graph->matrixSize;
    graphTranspose->VertNum = graph->VertNum;
    graphTranspose->index = graph->index;
    graphTranspose->itrIndex = graph->itrIndex;
    graphTranspose->MatrixAdj = (int**)malloc(sizeof(int*)*graphTranspose->matrixSize);
    for(uint k=0;k<graphTranspose->matrixSize;k++){
        graphTranspose->MatrixAdj[k] = (int*)malloc(sizeof(int)*graphTranspose->matrixSize);
    }
    for(uint i=0;i<graph->matrixSize;i++){
        for(uint j=0;j<graph->matrixSize;j++) {
            graphTranspose->MatrixAdj[i][j] = graph->MatrixAdj[j][i];
        }
    }
    return graphTranspose;

}

/* ************************************************************************** */

bool graphInsertVertexMatType(void* list, DataObject* elem, uint label) {
    GraphMat* graph = (GraphMat*) list;

    // Creo il vertice per poter verificare se esiste o meno
    DataType* vertType = ConstructVertDataType();
    DataObject* dataObject = adtConstruct(vertType);
    dataObject->value = adtInitializeVertex(label, elem);
    dataObject->type = vertType;

    if(bstExists(graph->BSTvertices, dataObject)){
        adtDestruct(dataObject);
        free(vertType);
        return false;
    }

    // Prendo un indice da dare a quel vertice
    if(!queEmpty(graph->queue)) {
        DataObject *head = queHeadNDequeue(graph->queue);
        graph->index = *((int*)head->value);
        adtDestruct(head);
    } else {
        graph->index = graph->VertNum;
        graph->VertNum++;
    }

    // Effettuo la mappatura
    dataObject->value = MapPosition(dataObject->value, graph->index);

    // Lo inserisco nell'albero
    bstInsert(graph->BSTvertices, dataObject);

    //alloco memoria nel caso la matrice sia piena
    if(graph->index>=graph->matrixSize) {
        graph->matrixSize = graph->matrixSize * 2;
        graph->MatrixAdj = realloc(graph->MatrixAdj,(sizeof(int**)*graph->matrixSize));
        for(uint k=0;k<graph->matrixSize;k++){
            graph->MatrixAdj[k] = realloc(graph->MatrixAdj[k], sizeof(int*)*graph->matrixSize);
        }
        for (uint i = 0; i < graph->matrixSize; i++) {
            graph->MatrixAdj[i][graph->index] = 0;
            graph->MatrixAdj[graph->index][i] = 0;
        }
    }

    return true;
}

/* ************************************************************************** */
bool graphRemoveVertexMatType(void* matrix, uint VertIndex, uint* EdgNum)
{
    GraphMat* graph =  (GraphMat*)matrix;

    DataType* vertType = ConstructVertDataType();
    DataObject* vertToRemove = adtConstruct(vertType);
    vertToRemove->value = adtInitializeVertex(VertIndex, NULL);
    if(bstExists(graph->BSTvertices, vertToRemove)) {
        //salvo i dati di ciò che elimino
        DataObject* mapInfo = bstGetData(graph->BSTvertices, vertToRemove);
        uint mapIndex = adtGetVertexArrayPos(mapInfo->value);
        bstRemove(graph->BSTvertices, vertToRemove);
        for (uint i = 0; i < graph->matrixSize; i++) {
            graph->MatrixAdj[i][mapIndex] = 0;
            if(graph->MatrixAdj[mapIndex][i] == 1){
                *((int*)EdgNum) = *((int*)EdgNum)+1;
            }
            graph->MatrixAdj[mapIndex][i] = 0;

        }
        //incodo
        DataType* intType = ConstructIntDataType();
        DataObject* elemToEnqueue = adtConstruct(intType);
        adtSetValue(elemToEnqueue, &mapIndex);
        queEnqueue(graph->queue, elemToEnqueue);
        graph->VertNum--;
    } else return false;
    return true;
}

/* ************************************************************************** */

bool graphInsertEdgeMatType(void* matrix, uint label1, uint label2)
{
    GraphMat* graph = (GraphMat*)matrix;

    DataType* vertType = ConstructVertDataType();
    DataObject* vertToInsert1 = adtConstruct(vertType);
    DataObject* vertToInsert2 = adtConstruct(vertType);
    vertToInsert1->value = adtInitializeVertex(label1, NULL);
    vertToInsert2->value = adtInitializeVertex(label2, NULL);
    if(bstExists(graph->BSTvertices, vertToInsert1) && bstExists(graph->BSTvertices, vertToInsert2)) {
        DataObject *mapInfo = bstGetData(graph->BSTvertices, vertToInsert1);
        DataObject *mapInfo2 = bstGetData(graph->BSTvertices, vertToInsert2);
        uint mapIndex = adtGetVertexArrayPos(mapInfo->value);
        uint mapIndex2 = adtGetVertexArrayPos(mapInfo2->value);
        if(graph->MatrixAdj[mapIndex][mapIndex2] == 1){
            return false;
        }
        graph->MatrixAdj[mapIndex][mapIndex2] = 1;
    } else return false;
    return true;
}

/* ************************************************************************** */

bool graphRemoveEdgeMatType(void* matrix, uint label1, uint label2)
{
    GraphMat* graph = (GraphMat*)matrix;

    DataType* vertType = ConstructVertDataType();
    DataObject* vertToInsert1 = adtConstruct(vertType);
    DataObject* vertToInsert2 = adtConstruct(vertType);
    vertToInsert1->value = adtInitializeVertex(label1, NULL);
    vertToInsert2->value = adtInitializeVertex(label2, NULL);
    if(bstExists(graph->BSTvertices, vertToInsert1) && bstExists(graph->BSTvertices, vertToInsert2)) {
        DataObject *mapInfo = bstGetData(graph->BSTvertices, vertToInsert1);
        DataObject *mapInfo2 = bstGetData(graph->BSTvertices, vertToInsert2);
        uint mapIndex = adtGetVertexArrayPos(mapInfo->value);
        uint mapIndex2 = adtGetVertexArrayPos(mapInfo2->value);
        graph->MatrixAdj[mapIndex][mapIndex2] = 0;
    } else return false;
    return true;
}

/* ************************************************************************** */

bool graphExistsVertexMatType(void* matrix, uint label)
{
    GraphMat* graph = (GraphMat*)matrix;

    DataType* vertType = ConstructVertDataType();
    DataObject* vertToFind = adtConstruct(vertType);
    vertToFind->value = adtInitializeVertex(label, NULL);
    return bstExists(graph->BSTvertices, vertToFind);
}

/* ************************************************************************** */

bool graphExistsEdgeMatType(void* matrix, uint label1, uint label2)
{
    GraphMat *graph = (GraphMat *) matrix;

    DataType *vertType = ConstructVertDataType();
    DataObject *vertToInsert1 = adtConstruct(vertType);
    DataObject *vertToInsert2 = adtConstruct(vertType);
    vertToInsert1->value = adtInitializeVertex(label1, NULL);
    vertToInsert2->value = adtInitializeVertex(label2, NULL);
    if (bstExists(graph->BSTvertices, vertToInsert1) && bstExists(graph->BSTvertices, vertToInsert2)) {
        DataObject *mapInfo = bstGetData(graph->BSTvertices, vertToInsert1);
        DataObject *mapInfo2 = bstGetData(graph->BSTvertices, vertToInsert2);
        uint mapIndex = adtGetVertexArrayPos(mapInfo->value);
        uint mapIndex2 = adtGetVertexArrayPos(mapInfo2->value);
        if(graph->MatrixAdj[mapIndex][mapIndex2] == 1){
            return true;
        }
    }
    return false;

}

/* ************************************************************************** */

DataObject* graphGetVertexDataMatType(void* matrix, uint label)
{
    GraphMat* graph = (GraphMat*)matrix;

    DataType* vertType = ConstructVertDataType();
    DataObject* vertToReturn = adtConstructVert(vertType);
    vertToReturn->value = adtInitializeVertex(label, NULL);

    return bstGetData(graph->BSTvertices, vertToReturn);
}

/* ************************************************************************** */

void graphSetVertexDataMatType(void* matrix, uint label, DataObject* elem)
{
    GraphMat* graph = (GraphMat*)matrix;

    DataType* vertType = ConstructVertDataType();
    DataObject* elemToSet = adtConstruct(vertType);
    elemToSet->value = adtInitializeVertex(label, elem);
    DataObject* tmp = (DataObject*)bstGetData(graph->BSTvertices, elemToSet);
    tmp = adtSetValueVert(tmp, elem);
    adtWriteToMonitor(tmp);
}

/* ************************************************************************** */

uint graphVertexFromPointerMatType(void* matrix, void* vert)
{
    GraphMat* graph = (GraphMat*)matrix;
    GraphVertex* vertex = (GraphVertex*)vert;
    return adtGetVertexId(vertex);
}

/* ************************************************************************** */

ITRObject* graphVerticesMatType(void* matrix)
{
    GraphMat* graph = (GraphMat*)matrix;

    ITRType* itrType = ConstructVertIterator();
    ITRObject* iter = itrConstruct(itrType, graph->BSTvertices);
    return iter;
}

/* ************************************************************************** */

ITRObject* graphVertexEdgesMatType(void* matrix, uint label)
{
   GraphMat* graph = (GraphMat*)matrix;
   GraphEdgStruct* edgStruct = (GraphEdgStruct*)malloc(sizeof(GraphEdgStruct));
   edgStruct->graph = graph;

   uint* index = graphGetIndex(graph, label);
   if(index == NULL){
       edgStruct->vertexIndex = graph->matrixSize;
   } else {
       edgStruct->vertexIndex = *index;
   }
   ITRType* edgType = ConstructItrGraphEdgIterator();
   ITRObject* iterator = itrConstruct(edgType, edgStruct);
   free(edgStruct);
   return iterator;

}

/* ************************************************************************** */

void* MapPosition(void* vertValue, int index)
{
    VertStruct* vert = (VertStruct*)vertValue;
    vert->ArrayPos = index;

    return vert;
}

/* ************************************************************************** */

uint* graphGetIndex(GraphMat* graph, uint label){
    GraphMat* graphMat = (GraphMat*)graph;
    uint* ret = NULL;

    DataType* vrtType = ConstructVertDataType();
    DataObject* data = adtConstruct(vrtType);

    ((VertStruct*) data->value)->label = label;
    DataObject* index = bstGetData(graphMat->BSTvertices, data);

    if(index != NULL){
        ret = &((VertStruct*)index->value)->ArrayPos;
    }
    return ret;
}


/* ************************************************************************** */

void printListMat(void* list)
{
    GraphMat* graph = (GraphMat*)list;
    bstPreOrderMap(graph->BSTvertices, &stampaMap, NULL);
}

