
#include <adt/vert/adtvert.h>
#include "itrlist.h"
#include "adt/ptr/adtptr.h"
#include "matitr.h"

/* ************************************************************************** */

ITRType* ConstructItrMatrixIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructMatrix;
    type->itr_Destruct = &itrDestructMatrix;
    type->itr_Terminated = &itrTerminatedMatrix;
    type->itr_Element = &itrElementMatrix;
    type->itr_Successor = &itrSuccessorMatrix;

    return type;

}

/* ************************************************************************** */

void DestructItrMatrixIterator(ITRType* type)
{
    free(type);
}


/* ************************************************************************** */

void * itrConstructMatrix(void* t_matrix)
{
    GraphMat* graph = (GraphMat*)t_matrix;

    MatrixIterator* iter = (MatrixIterator*)malloc(sizeof(MatrixIterator));
    iter->tree = graph->BSTvertices;
    iter->Adj = graph->MatrixAdj[graph->itrIndex];
    iter->matSize = graph->matrixSize;
    uint i=0;
    while( i<graph->matrixSize && iter->Adj[i] != 1){
        i = i+1;
    }
    if(i<graph->matrixSize && iter->Adj[i]==1){
        DataType* vertType = ConstructVertDataType();
        DataObject* data = adtConstruct(vertType);
        data->value = MapPosition(data->value, i);
        iter->curr = bstGetData(graph->BSTvertices, data);
        iter->position = i;
    } else {
        iter->curr = NULL;
    }
    return iter;
}


/* ************************************************************************** */

void itrDestructMatrix(void* iterator)
{
    MatrixIterator* iter = (MatrixIterator*)iterator;

    //controlla che non distruggi cose che ti servono
    adtDestruct(iter->curr);
    free(iter->Adj);
}

/* ************************************************************************** */

bool itrTerminatedMatrix(void* iterator)
{
   MatrixIterator* iter = (MatrixIterator*)iterator;
   return  iter->curr == NULL;
}

/* ************************************************************************** */

void * itrElementMatrix(void* iterator)
{
    MatrixIterator* iter = (MatrixIterator*)iterator;
    uint* lab = (uint*)malloc(sizeof(uint));
    *lab = adtGetVertexId(iter->curr->value);
    return lab;
}

/* ************************************************************************** */

void itrSuccessorMatrix(void* iterator) {
    MatrixIterator *iter = (MatrixIterator *) iterator;

    uint i;
    for(i=iter->position+1; i<iter->matSize;i++){
        if(iter->Adj[i] == 1){
            break;
        }
    }
    if(i<iter->matSize){
        DataType* vertType = ConstructVertDataType();
        DataObject* data = adtConstruct(vertType);
        data->value = MapPosition(data->value, i);
        iter->curr = bstGetData(iter->tree, data);
        iter->position = i;
    } else {
        iter->curr = NULL;
    }
}

/* ************************************************************************** */