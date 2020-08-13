
#include <bst/rec/bstrec.h>
#include <adt/vert/adtvert.h>
#include <adt/int/adtint.h>
#include <graph/vertitr.h>
#include "graphbst.h"
#include "bstitr.h"

/* ************************************************************************** */

GraphRepresentation* ConstructGraphBST()
{
    GraphRepresentation* representation = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    representation->graph_construct = &graphConstructBSTType;
    representation->graph_destruct = &graphDestructBSTType;
    representation->graph_empty = &graphEmptyBSTType;

    representation->graph_clone = &graphCloneBSTType;
    representation->graph_transpose = &graphTransposeBSTType;

    representation->graph_insertVertex = &graphInsertVertexBSTType;
    representation->graph_removeVertex = &graphRemoveVertexBSTType;
    representation->graph_insertEdge = &graphInsertEdgeBSTType;
    representation->graph_removeEdge = &graphRemoveEdgeBSTType;

    representation->graph_existsVertex = &graphExistsVertexBSTType;
    representation->graph_existsEdge = &graphExistsEdgeBSTType;

    representation->graph_getVertexData = &graphGetVertexDataBSTType;
    representation->graph_setVertexData = &graphSetVertexDataBSTType;

    representation->graph_vertexFromPointer = &graphVertexFromPointerBSTType;
    representation->graph_vertices = &graphVerticesBSTType;
    representation->graph_vertexEdges = &graphVertexEdgesBSTType;

    return representation;
}

/* ************************************************************************** */

void DestructGraphBST(GraphRepresentation* representation)
{
    free(representation);
}

/* ************************************************************************** */

void* graphConstructBSTType()
{
    GraphBST* graph = (GraphBST*)malloc(sizeof(GraphBST));

    BSTType* type = ConstructBSTRecursive();
    graph->vertexes = bstConstruct(type);
    graph->size = 10;
    graph->numVertex = 0;
    graph->adjacents = (Adj**)malloc(sizeof(Adj*)*graph->size);
    for(uint i=0;i<graph->size;i++){
        graph->adjacents[i] = (Adj*)malloc(sizeof(Adj));
        graph->adjacents[i]->id = -1;
        graph->adjacents[i]->treeAdj = NULL;
    }
    return graph;
}

/* ************************************************************************** */

void graphDestructBSTType(void* tree)
{
    GraphBST* graph = (GraphBST*)tree;

    for(uint i=0;i<graph->size;i++){
        if(graph->adjacents[i]->id != -1){ //Controllo che il nodo dell'albero non sia vuoto
            bstClear(graph->adjacents[i]->treeAdj); //Svuoto l'albero
            bstDestruct(graph->adjacents[i]->treeAdj); //Lo distruggo
            free(graph->adjacents[i]); //Dealloco il singolo nodo
        }
    }
    free(graph->adjacents);
    bstClear(graph->vertexes);
    bstDestruct(graph->vertexes);
}

/* ************************************************************************** */

bool graphEmptyBSTType(void* tree)
{
    GraphBST* graph = (GraphBST*)tree;
    return graph->numVertex == 0;
}

/* ************************************************************************** */

void* graphCloneBSTType(void* tree)
{
    GraphBST* graph = (GraphBST*)tree;

    GraphBST* graphClone = (GraphBST*)malloc(sizeof(GraphBST));
    graphClone->numVertex = graph->numVertex;
    graphClone->size = graph->size;
    graphClone->vertexes = bstClone(graph->vertexes);
    graphClone->adjacents = (Adj**)malloc(sizeof(Adj*)*graph->size);
    for(uint i=0;i<graph->size;i++){
        graphClone->adjacents[i] = (Adj*)malloc(sizeof(Adj));
        graphClone->adjacents[i]->id = graph->adjacents[i]->id;
        if(graph->adjacents[i]->treeAdj!= NULL) {
            graphClone->adjacents[i]->treeAdj = bstClone(graph->adjacents[i]->treeAdj);
        } else {
            graphClone->adjacents[i]->treeAdj = NULL;
        }
    }

    return graphClone;
}

/* ************************************************************************** */

void* graphTransposeBSTType(void* tree)
{
    GraphBST* graph = (GraphBST*)tree;


    //costruzione del dataobject su cui fare l'exists
    DataType* type = ConstructIntDataType();
    DataObject* data = adtConstruct(type);
    //costruzione del trasposto
    GraphBST* transpose = (GraphBST*)malloc(sizeof(GraphBST));
    transpose->numVertex = graph->numVertex;
    transpose->size = graph->size;
    transpose->vertexes = bstClone(graph->vertexes);
    transpose->adjacents = (Adj**)malloc(sizeof(Adj*));
    for(uint i=0;i<graph->size;i++){
        transpose->adjacents[i] = (Adj*)malloc(sizeof(Adj));
        transpose->adjacents[i]->treeAdj = NULL;
        transpose->adjacents[i]->id = graph->adjacents[i]->id;
        if(graph->adjacents[i]->id != -1){
            for(uint j=0;j<graph->size;j++){
                if(graph->adjacents[j]->id != -1){
                    //inizializzo il dataobject
                    adtSetValue(data, &graph->adjacents[i]->id);
                    if(bstExists(graph->adjacents[j]->treeAdj, data)){
                        bstInsert(transpose->adjacents[i]->treeAdj, data);
                    }

                }
            }
        } else transpose->adjacents[i]->treeAdj = NULL;
    }
    return transpose;
}

/* ************************************************************************** */

bool graphInsertVertexBSTType(void* tree, DataObject* elem, uint label)
{
    GraphBST* graph = (GraphBST*)tree;

    //Creo ed inizializzo il vertice da inserire
    GraphVertex* vert = vertexConstruct(elem->type);
    vert->value = adtClone(elem);
    vert->label = label;
    //0. Gestisco la reallocazione dell'array
    if(graph->numVertex == graph->size){
        graph->size = graph->size*2;
        graph->adjacents = realloc(graph->adjacents, sizeof(Adj**)*graph->size);
        for(uint i= graph->numVertex; i<graph->size;i++){
            graph->adjacents[i] = (Adj*)malloc(sizeof(Adj));
            graph->adjacents[i]->id = -1;
            graph->adjacents[i]->treeAdj = NULL;
        }
    }
    //Inseriamo il vertice nell'albero:
    //1. Controllo che il valore non sia già presente
    int emptyPos = -1;
    uint i=0;
    while(i<graph->size && label!=graph->adjacents[i]->id){
        if(emptyPos == -1) { //in questo modo salvo la prima cella da poter scrivere
            if (graph->adjacents[i]->id == -1) {
                emptyPos = i; //salvo la cella
            }
        }
        i = i+1;
    }
    //Caso in cui il while non è terminato, quindi la seconda condizione è falsa
    if(i<graph->size){
        return false;
    } else {
        //2. Assegno il vertice ad un ptr
        DataType* vertType = ConstructVertDataType();
        DataObject* vertData = adtConstruct(vertType);
        vertData->value = adtInitializeVertex(label, elem);

        //3. Inserisco
        graph->adjacents[emptyPos]->id = label;
        bstInsert(graph->vertexes, vertData);
        graph->numVertex++;
        return true;
    }
}

/* ************************************************************************** */

bool graphRemoveVertexBSTType(void* tree, uint VertIndex, uint* EdgNum)
{
    GraphBST* graph = (GraphBST*)tree;

    //creo il dataobject che contiene il valore da eliminare
    DataType* dataType = ConstructIntDataType();
    DataObject* elemToRemove = adtConstruct(dataType);
    adtSetValue(elemToRemove, &VertIndex); //inizializzo il DO con il valore da rimuovere
    uint i;
    for(i=0;i<graph->size;i++){
        if(graph->adjacents[i]->id != -1){
            //lo rimuovo
            if(graph->adjacents[i]->treeAdj != NULL) {
                bstRemove(graph->adjacents[i]->treeAdj, elemToRemove);
                if(bstSize(graph->adjacents[i]->treeAdj) == 0){
                    graph->adjacents[i]->treeAdj = NULL;
                }
            }

        }
        if(graph->adjacents[i]->id == VertIndex){
            //rimozione degli adiacenti
            *EdgNum = bstSize(graph->adjacents[i]->treeAdj);
            bstClear(graph->adjacents[i]->treeAdj);
            bstDestruct(graph->adjacents[i]->treeAdj);
            graph->adjacents[i]->treeAdj = NULL;
            graph->adjacents[i]->id = -1;
            break;
        }
    }
    if(i<graph->size){
        //rimuvo dall'albero di vertici
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

bool graphInsertEdgeBSTType(void* tree, uint label1, uint label2)
{
   GraphBST* graph = (GraphBST*)tree;

    int pos = -1;
    bool exists = false;
    for(uint i=0;i<graph->size;i++){
        if(graph->adjacents[i]->id == label1 ){ //controllo la posizione
            pos = i;
        }
        if(graph->adjacents[i]->id == label2){ //Controllo che esista
            exists = true;
        }
    }
    //inserisco

    if(exists == true && pos != -1){
        //creo ed inizializzo il DO d'appoggio
        DataType* dataType = ConstructIntDataType();
        DataObject* elemToInsert = adtConstruct(dataType);
        adtSetValue(elemToInsert, &label2);
        if(graph->adjacents[pos]->treeAdj == NULL) {
            graph->adjacents[pos]->treeAdj = bstConstruct(graph->vertexes->type);
        }
        bstInsert(graph->adjacents[pos]->treeAdj, elemToInsert);
        return true;
    }
    return false;
}

/* ************************************************************************** */

bool graphRemoveEdgeBSTType(void* tree, uint label1, uint label2)
{
    GraphBST* graph = (GraphBST*)tree;

    for(uint i=0;i<graph->size;i++){
        if(graph->adjacents[i]->id == label1){
            DataType* dataType = ConstructIntDataType();
            DataObject* elemToRemove = adtConstruct(dataType);
            adtSetValue(elemToRemove, &label2);
            if(bstExists(graph->adjacents[i]->treeAdj, elemToRemove)) {
                bstRemove(graph->adjacents[i]->treeAdj, elemToRemove);
                if(bstSize(graph->adjacents[i]->treeAdj) == 0){
                    graph->adjacents[i]->treeAdj = NULL;
                }
                return true;
            } else false;
        }
    }
    return false;
}

/* ************************************************************************** */

bool graphExistsVertexBSTType(void* tree, uint label)
{
    GraphBST* graph = (GraphBST*)tree;

    bool exists = false;
    for(uint i=0;i<graph->size;i++){
        if(graph->adjacents[i]->id == label){
            exists = true;
            return exists;
        }
    }
    return exists;
}

/* ************************************************************************** */

bool graphExistsEdgeBSTType(void* tree, uint label1, uint label2)
{
    GraphBST* graph = (GraphBST*)tree;

    for(uint i=0;i<graph->size;i++){
        if(graph->adjacents[i]->id == label1){
            DataType* dataType = ConstructIntDataType();
            DataObject* elemToSearch = adtConstruct(dataType);
            adtSetValue(elemToSearch, &label2);
            if(graph->adjacents[i]->treeAdj != NULL) {
                return bstExists(graph->adjacents[i]->treeAdj, elemToSearch);
            } else {
                return false;
            }
        }
    }
    return false;
}

/* ************************************************************************** */

DataObject* graphGetVertexDataBSTType(void* tree, uint label)
{
    GraphBST* graph = (GraphBST*)tree;

    DataType* vertType = ConstructVertDataType();
    DataObject* vertToReturn = adtConstructVert(vertType);
    vertToReturn->value = adtInitializeVertex(label, NULL);

    return bstGetData(graph->vertexes, vertToReturn);
}

/* ************************************************************************** */

void graphSetVertexDataBSTType(void* tree, uint label, DataObject* elem)
{
    GraphBST* graph = (GraphBST*)tree;

    DataType* vertType = ConstructVertDataType();
    DataObject* elemToSet = adtConstruct(vertType);
    elemToSet->value = adtInitializeVertex(label, elem);
    DataObject* tmp = (DataObject*)bstGetData(graph->vertexes, elemToSet);
    tmp = adtSetValueVert(tmp, elem);
}

/* ************************************************************************** */

uint graphVertexFromPointerBSTType(void* tree, void* vert)
{
    GraphBST* graph = (GraphBST*)tree;

    GraphVertex* vertex = (GraphVertex*)vert;
    return adtGetVertexId(vertex);
}

/* ************************************************************************** */

ITRObject* graphVerticesBSTType(void* tree)
{
    GraphBST* graph = (GraphBST*)tree;

    ITRType* itrType = ConstructVertIterator();
    ITRObject* iter = itrConstruct(itrType, graph->vertexes);
    return iter;
}

/* ************************************************************************** */

ITRObject* graphVertexEdgesBSTType(void* tree, uint label)
{
   GraphBST* graph = (GraphBST*)tree;
   BSTObject* BSTVertices = NULL;

    for(uint i=0;i<graph->size;i++){
        if(graph->adjacents[i]->id == label){
            if(graph->adjacents[i]->treeAdj != NULL) {
                BSTVertices = graph->adjacents[i]->treeAdj;
            }
            break;
        }
    }
    if(BSTVertices != NULL) {
        ITRType *itrType = ConstructItrBSTIterator();
        ITRObject *iter = itrConstruct(itrType, BSTVertices);
        return iter;
    }
    return NULL;
}

/* ************************************************************************** */

void printBst(void* tree)
{
    GraphBST* graph = (GraphBST*)tree;
    bstPreOrderMap(graph->vertexes, &stampaMap, NULL);
}