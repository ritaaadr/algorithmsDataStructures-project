
#include <adt/vert/adtvert.h>
#include <bst/bstitrpreord.h>
#include "itrlist.h"
#include "adt/ptr/adtptr.h"
#include "matitr.h"
#include "edgitr .h"

/* ************************************************************************** */

uint getLabelFromIndex(BSTObject* tree, uint index);

/* ************************************************************************** */

ITRType* ConstructItrGraphEdgIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructGraphEdg;
    type->itr_Destruct = &itrDestructGraphEdg;
    type->itr_Terminated = &itrTerminatedGraphEdg;
    type->itr_Element = &itrElementGraphEdg;
    type->itr_Successor = &itrSuccessorGraphEdg;

    return type;
}

/* ************************************************************************** */

void DestructItrGraphEdgIterator(ITRType* type)
{
    free(type);
}


/* ************************************************************************** */

void * itrConstructGraphEdg(void* t_matrix)
{
    GraphEdg* iter = (GraphEdg*)malloc(sizeof(GraphEdg));
    GraphEdgStruct* graphEdgStruct = (GraphEdgStruct*)t_matrix;

    iter->graph = graphEdgStruct->graph;
    iter->curr = graphEdgStruct->vertexIndex;
    iter->currAdj = 0;

    uint i = iter->curr;
    if(i<iter->graph->matrixSize){
        while(iter->currAdj<iter->graph->matrixSize && !iter->graph->MatrixAdj[i][iter->currAdj]){
            iter->currAdj++;
        }
    } else {
        iter->currAdj = iter->graph->matrixSize;
    }
    return iter;
}


/* ************************************************************************** */

void itrDestructGraphEdg(void* iterator)
{
    GraphEdg* iter = (GraphEdg*)iterator;

    free(iter);
}

/* ************************************************************************** */

bool itrTerminatedGraphEdg(void* iterator)
{
    GraphEdg* iter = (GraphEdg*)iterator;
   return  iter->currAdj == iter->graph->matrixSize;
}

/* ************************************************************************** */

void * itrElementGraphEdg(void* iterator)
{
    GraphEdg* iter = (GraphEdg*)iterator;
    iter->currAdjLabel = getLabelFromIndex(iter->graph->BSTvertices, iter->currAdj);

    return &iter->currAdjLabel;
}

/* ************************************************************************** */

void itrSuccessorGraphEdg(void* iterator) {
    GraphEdg* iter = (GraphEdg*)iterator;

    uint i = iter->curr;
    iter->currAdj++;
    while(iter->currAdj<iter->graph->matrixSize && !iter->graph->MatrixAdj[i][iter->currAdj]){
        iter->currAdj++;
    }
}

/* ************************************************************************** */

uint getLabelFromIndex(BSTObject* tree, uint index){

    ITRType* type = ConstructBSTPreOrderIterator();
    ITRObject* iter = itrConstruct(type, tree->root);

    bool found = false;
    uint ret=0;
    while(!itrTerminated(iter) && found==false){
        BSTNode* node = itrElement(iter);
        DataObject* tmp = node->data;
        int currIndex = ((VertStruct*)tmp->value)->ArrayPos;
        if(index == currIndex){
            found = true;
            ret = ((VertStruct*)tmp->value)->label;
        }
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    return ret;
}