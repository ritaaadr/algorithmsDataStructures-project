#include <adt/ptr/adtptr.h>
#include <adt/vert/adtvert.h>
#include <bst/bstitrpreord.h>
#include <list/itrlist.h>
#include <graph/vertitr.h>
#include "graphlst.h"

/* ************************************************************************** */

GraphRepresentation* ConstructGraphLst()
{
    GraphRepresentation * representation = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    representation->graph_construct = &graphConstructLstType;
    representation->graph_destruct = &graphDestructLstType;
    representation->graph_empty = &graphEmptyLstType;

    representation->graph_clone = &graphCloneLstType;
    representation->graph_transpose = &graphTransposeLstType;

    representation->graph_insertVertex = &graphInsertVertexLstType;
    representation->graph_removeVertex = &graphRemoveVertexLstType;
    representation->graph_insertEdge = &graphInsertEdgeLstType;
    representation->graph_removeEdge = &graphRemoveEdgeLstType;

    representation->graph_existsVertex = &graphExistsVertexLstType;
    representation->graph_existsEdge = &graphExistsEdgeLstType;

    representation->graph_getVertexData = &graphGetVertexDataLstType;
    representation->graph_setVertexData = &graphSetVertexDataLstType;

    representation->graph_vertexFromPointer = &graphVertexFromPointerLstType;
    representation->graph_vertices = &graphVerticesLstType;
    representation->graph_vertexEdges = &graphVertexEdgesLstType;

    return representation;
}

/* ************************************************************************** */

void DestructGraphLst(GraphRepresentation* representation)
{
    free(representation);
}

/* ************************************************************************** */

void* graphConstructLstType()
{
    BSTType* bstType = ConstructBSTRecursive();
    GraphLst* graph = (GraphLst*)malloc(sizeof(GraphLst));
    graph->vertexes = bstConstruct(bstType);
    graph->Size = 10;
    graph->array = (AdjInfo**)malloc(sizeof(AdjInfo*)*graph->Size); //alloco l'array
    for(uint i=0;i<10;i++){
        graph->array[i] = (AdjInfo*)malloc(sizeof(AdjInfo)); //alloco la singola cella
        graph->array[i]->lstAdj = NULL;
        graph->array[i]->id = -1; //Valore discriminante che ci serve per sapere il candidato chi è
    }
    graph->numVertex = 0;
    return graph;
}

/* ************************************************************************** */

void graphDestructLstType(void* list)
{
    GraphLst* graph = (GraphLst*)list;
    for(uint i=0;i<graph->Size;i++){
        if(graph->array[i]->id != -1) { //Controllo che la cella dell'array non sia vuoto
            listClear(graph->array[i]->lstAdj); //Svuoto la lista
            free(graph->array[i]); //Dealloco la singola cella dell'array
        }
    }
    free(graph->array);
    bstClear(graph->vertexes);
    bstDestruct(graph->vertexes);
}

/* ************************************************************************** */

bool graphInsertVertexLstType(void* list, DataObject* elem, uint label)
{
    int emptyPos = -1;
    GraphLst* graph = (GraphLst*)list;

    //Creo ed inizializzo il vertice da inserire
    GraphVertex* vert = vertexConstruct(elem->type);
    vert->value = adtClone(elem);
    vert->label = label;
    //0. Gestisco la reallocazione dell'array
    if(graph->numVertex == graph->Size){
        graph->Size = graph->Size*2;
        graph->array = realloc(graph->array, sizeof(AdjInfo**)*graph->Size);
        for(uint i= graph->numVertex; i<graph->Size;i++){
            graph->array[i] = (AdjInfo*)malloc(sizeof(AdjInfo));
            graph->array[i]->id = -1;
            graph->array[i]->lstAdj = NULL;
        }
    }
    //Inseriamo il vertice nell'albero:
    //1. Controllo che il valore non sia già presente
    uint i=0;
    while(i<graph->Size && label != graph->array[i]->id){
        if(emptyPos == -1) { //in questo modo salvo la prima cella da poter scrivere
            if (graph->array[i]->id == -1) {
                emptyPos = i; //salvo la cella
            }
        }
        i = i+1;
    }
    //Caso in cui il while non è terminato, quindi la seconda condizione è falsa
    if(i<graph->Size){
        return false;
    } else {
        //2. Assegno il vertice ad un ptr
        DataType* vertType = ConstructVertDataType();
        DataObject* vertData = adtConstruct(vertType);
        vertData->value = adtInitializeVertex(label, elem);

        //3. Inserisco
        graph->array[emptyPos]->id = label;
        bstInsert(graph->vertexes, vertData);
        graph->numVertex++;
        return true;
    }
}

/* ************************************************************************** */

bool graphRemoveVertexLstType(void* list, uint VertIndex, uint* EdgNum)
{
    GraphLst* graph = (GraphLst*)list;

    uint i;
    for(i=0;i<graph->Size;i++){
        if(graph->array[i]->id != -1){
            graph->array[i]->lstAdj = listRemove(graph->array[i]->lstAdj, VertIndex);
        }
        if(graph->array[i]->id == VertIndex){
            *EdgNum = listSize(graph->array[i]->lstAdj);
            graph->array[i]->lstAdj = listClear(graph->array[i]->lstAdj);
            listDestruct(graph->array[i]->lstAdj);
            graph->array[i]->lstAdj = NULL;
            graph->array[i]->id = -1;
            break;
        }
    }
    if(i<graph->Size){
        DataType* vertType = ConstructVertDataType();
        DataObject* vertToRemove = adtConstruct(vertType);
        vertToRemove->value = adtInitializeVertex(VertIndex,NULL);
        bstRemove(graph->vertexes, vertToRemove);
        graph->numVertex--;
        return true;
    }
    return false;
}

/* ************************************************************************** */

bool graphEmptyLstType(void* list)
{
    GraphLst* graph = (GraphLst*)list;
    return graph->numVertex == 0;
}

/* ************************************************************************** */

void* graphCloneLstType(void* list)
{
    GraphLst* graph = (GraphLst*)list;
    GraphLst* graphClone = (GraphLst*)malloc(sizeof(GraphLst));

    graphClone->Size = graph->Size;
    graphClone->numVertex = graph->numVertex;
    graphClone->vertexes = bstClone(graph->vertexes);
    graphClone->array = (AdjInfo**)malloc(sizeof(AdjInfo*)*graph->Size);
    for(uint i=0;i<graph->Size;i++){
        graphClone->array[i] = (AdjInfo*)malloc(sizeof(AdjInfo));
        graphClone->array[i]->lstAdj = listClone(graph->array[i]->lstAdj);
        graphClone->array[i]->id = graph->array[i]->id;
    }
    return graphClone;
}

/* ************************************************************************** */

void* graphTransposeLstType(void* list)
{
    GraphLst* graph = (GraphLst*)list;
    GraphLst* transpose = (GraphLst*)malloc(sizeof(GraphLst));
    transpose->array = (AdjInfo**)malloc(sizeof(AdjInfo*)*graph->Size);
    transpose->Size = graph->Size;
    transpose->numVertex = graph->numVertex;
    transpose->vertexes = bstClone(graph->vertexes);
    for(uint i=0;i<graph->Size;i++){
        transpose->array[i] = (AdjInfo*)malloc(sizeof(AdjInfo));
        transpose->array[i]->id = graph->array[i]->id;
        if(graph->array[i]->id != -1){
            for(uint j=0;j<graph->Size;j++){
                if(graph->array[j]->id != -1){
                    if(listExists(graph->array[j]->lstAdj, transpose->array[i]->id)) {
                       transpose->array[i]->lstAdj = listInsert(transpose->array[i]->lstAdj, graph->array[j]->id);
                    }
                }
            }
        } else transpose->array[i]->lstAdj = NULL;
    }
    return transpose;
}

/* ************************************************************************** */

bool graphInsertEdgeLstType(void* list, uint label1, uint label2)
{
    GraphLst* graph = (GraphLst*)list;

    int pos = -1;
    bool exists = false;
    for(uint i=0;i<graph->Size;i++){
        if(graph->array[i]->id ==label1 ){
            pos = i;
        }
        if(graph->array[i]->id == label2){ //Controllo che esista
            exists = true;
        }
    }
    //inserisco
    if(exists == true && pos != -1){
        graph->array[pos]->lstAdj = listInsert(graph->array[pos]->lstAdj, label2);
        return true;
    }
    return false;
}

/* ************************************************************************** */

bool graphRemoveEdgeLstType(void* list, uint label1, uint label2)
{
    GraphLst* graph = (GraphLst*)list;
    for(uint i=0;i<graph->Size;i++){
        if(graph->array[i]->id == label1){
            if(listExists(graph->array[i]->lstAdj, label2)) {
                graph->array[i]->lstAdj = listRemove(graph->array[i]->lstAdj, label2);
                return true;
            } else false;
        }
    }
    return false;
}

/* ************************************************************************** */

bool graphExistsVertexLstType(void* list, uint label)
{
    GraphLst* graph = (GraphLst*)list;

    bool exists = false;
    for(uint i=0;i<graph->Size;i++){
        if(graph->array[i]->id == label){
            exists = true;
            return exists;
        }
    }
    return exists;
}

/* ************************************************************************** */

DataObject* graphGetVertexDataLstType(void* list, uint label)
{
    GraphLst* graph = (GraphLst*)list;
    DataType* vertType = ConstructVertDataType();
    DataObject* vertToReturn = adtConstructVert(vertType);
    vertToReturn->value = adtInitializeVertex(label, NULL);

    return bstGetData(graph->vertexes, vertToReturn);
}

/* ************************************************************************** */

void graphSetVertexDataLstType(void* list, uint label, DataObject* elem)
{
    GraphLst* graph = (GraphLst*)list;

    DataType* vertType = ConstructVertDataType();
    DataObject* elemToSet = adtConstruct(vertType);
    elemToSet->value = adtInitializeVertex(label, elem);
    DataObject* tmp = (DataObject*)bstGetData(graph->vertexes, elemToSet);
    tmp = adtSetValueVert(tmp, elem);
}

/* ************************************************************************** */

bool graphExistsEdgeLstType(void* list, uint label1, uint label2)
{
    GraphLst* graph = (GraphLst*)list;

    for(uint i=0;i<graph->Size;i++){
        if(graph->array[i]->id == label1){
            return listExists(graph->array[i]->lstAdj, label2);
        }
    }
    return false;
}

/* ************************************************************************** */

uint graphVertexFromPointerLstType(void* list, void* vert)
{
    GraphLst* graph = (GraphLst*)list;
    GraphVertex* vertex = (GraphVertex*)vert;
    return adtGetVertexId(vertex);
}

/* ************************************************************************** */

ITRObject* graphVerticesLstType(void* list)
{
    GraphLst* graph = (GraphLst*)list;

    ITRType* itrType = ConstructVertIterator();
    ITRObject* iter = itrConstruct(itrType, graph->vertexes);
    return iter;
}

/* ************************************************************************** */

ITRObject* graphVertexEdgesLstType(void* list, uint label)
{
    GraphLst* graph = (GraphLst*)list;
    Lst* VertexList = NULL;

    for(uint i=0;i<graph->Size;i++){
        if(graph->array[i]->id == label && graph->array[i]->lstAdj != NULL){
         VertexList =  graph->array[i]->lstAdj;
         break;
        }
    }
    if(VertexList != NULL) {
        ITRType *itrType = ConstructItrListIterator();
        ITRObject *iter = itrConstruct(itrType, VertexList);
        return iter;
    } else return NULL;
}

/* ************************************************************************** */

void printList(void* list)
{
    GraphLst* graph = (GraphLst*)list;
    bstPreOrderMap(graph->vertexes, &stampaMap, NULL);
}

