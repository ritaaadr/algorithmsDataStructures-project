
#include <bst/rec/bstrec.h>
#include <adt/int/adtint.h>
#include <adt/rec/adtrec.h>
#include <adt/vert/adtvert.h>
#include "graphitrpreord.h"
#include "../stack/vec/stackvec.h"


/* ************************************************************************** */

ITRType* ConstructGraphPreOrderIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructGraphPreOrderIterator;
    type->itr_Destruct = &itrDestructGraphPreOrderIterator;
    type->itr_Terminated = &itrTerminatedGraphPreOrderIterator;
    type->itr_Element = &itrElementGraphPreOrderIterator;
    type->itr_Successor = &itrSuccessorGraphPreOrderIterator;

    return type;
}

/* ************************************************************************** */

void DestructGraphPreOrderIterator(ITRType* type)
{
    free(type);
}

/* ************************************************************************** */

void * itrConstructGraphPreOrderIterator(void* graphStruct) {

    GraphObject *graphObject = (GraphObject *) graphStruct;

    GraphPreOrderIterator *iter = (GraphPreOrderIterator *) malloc(sizeof(GraphPreOrderIterator));
    //Inizializzo il graph, l'iteratore e il curr
    iter->graph = graphObject;

    BSTType* bstType = ConstructBSTRecursive();
    iter->treeOfColors = bstConstruct(bstType);

    //lo inserisco anche nello stack per gestire la "risalita"
    StackType* stkType = ConstructStackVecType();
    iter->stack = stkConstruct(stkType);
    iter->verticesIterator = graphVertices(iter->graph);

    DataObject* tmp = itrElement(iter->verticesIterator);
    iter->curr = adtGetVertexId(tmp->value);
    iter->currEdg = graphVertexEdges(iter->graph, iter->curr);

    if(iter->currEdg != NULL ) {
        DataType* intDataType = ConstructIntDataType();
        DataObject* elemToPush = adtConstruct(intDataType);
        adtSetValue(elemToPush, &iter->curr);
        stkPush(iter->stack, elemToPush);
    }

    return iter;
}

/* ************************************************************************** */

void itrDestructGraphPreOrderIterator(void* iterator)
{
    GraphPreOrderIterator* iter = (GraphPreOrderIterator*)iterator;

    bstDestruct(iter->treeOfColors);
    itrDestruct(iter->verticesIterator);
    stkDestruct(iter->stack);
}

/* ************************************************************************** */

bool itrTerminatedGraphPreOrderIterator(void* iterator)
{
    GraphPreOrderIterator* iter = (GraphPreOrderIterator*)iterator;
    return bstSize(iter->treeOfColors) == graphVertexNumber(iter->graph);
}

/* ************************************************************************** */

void * itrElementGraphPreOrderIterator(void* iterator)
{
    GraphPreOrderIterator* iter = (GraphPreOrderIterator*)iterator;
    DataType *recType = ConstructRecordDataType();
    DataObject *structOfColors = adtConstruct(recType);
    DataObject* ret = graphGetVertexData(iter->graph, iter->curr);
    structOfColors->value = adtInitializeRec(structOfColors->value, iter->curr, 1);
    bstInsert(iter->treeOfColors, structOfColors);
    return ret;
}

/* ************************************************************************** */

void itrSuccessorGraphPreOrderIterator(void* iterator)
{
    GraphPreOrderIterator *iter = (GraphPreOrderIterator *) iterator;

    DataType *recType = ConstructRecordDataType();
    DataObject *data = adtConstruct(recType);

    DataType *intDataType = ConstructIntDataType();
    DataObject *intDO = adtConstruct(intDataType);

    data->value = adtInitializeRec(data->value, iter->curr, 1);
    if (!stkEmpty(iter->stack) && iter->currEdg == NULL) {
        while (iter->currEdg == NULL && !stkEmpty(iter->stack)) {
            iter->curr = *(int *) adtGetValue(stkTop(iter->stack));
            iter->currEdg = graphVertexEdges(iter->graph, iter->curr);

            iter->curr = *((int *) itrElement(iter->currEdg));
            iter->curr = *((int *) itrElement(iter->currEdg));
            data->value = adtInitializeRec(data->value, iter->curr, 1);

            while (bstExists(iter->treeOfColors, data) && !itrTerminated(iter->currEdg)) {
                itrSuccessor(iter->currEdg);
                if (itrTerminated(iter->currEdg)) {
                    stkPop(iter->stack);
                    iter->currEdg = NULL;
                    break;
                }
                iter->curr = *((int *) itrElement(iter->currEdg));
                data->value = adtInitializeRec(data->value, iter->curr, 1);
            }
        }
    }

    if (stkEmpty(iter->stack) && iter->currEdg == NULL) {
        while (bstExists(iter->treeOfColors, data) && !itrTerminated(iter->verticesIterator)) {
            itrSuccessor(iter->verticesIterator);
            if (itrTerminated(iter->verticesIterator)) {
                return;
            }
            DataObject *dat = itrElement(iter->verticesIterator);
            iter->curr = adtGetVertexId(dat->value);
            data->value = adtInitializeRec(data->value, iter->curr, 1);
        }
    }
    if (iter->currEdg != NULL) {
        while (bstExists(iter->treeOfColors, data) && !itrTerminated(iter->currEdg)) {
            iter->curr = *((int *) itrElement(iter->currEdg));
            data->value = adtInitializeRec(data->value, iter->curr, 1);
            itrSuccessor(iter->currEdg);
            if (itrTerminated(iter->currEdg)) {
                stkPop(iter->stack);
                iter->currEdg = NULL;
                break;
            }
        }
    }
    data->value = adtInitializeRec(data->value, iter->curr, 1);
    if (bstExists(iter->treeOfColors, data)) {
        while (bstExists(iter->treeOfColors, data) && !itrTerminated(iter->verticesIterator)) {
            itrSuccessor(iter->verticesIterator);
            if (itrTerminated(iter->verticesIterator)) {
                return;
            }
            DataObject *dat = itrElement(iter->verticesIterator);
            iter->curr = adtGetVertexId(dat->value);
            data->value = adtInitializeRec(data->value, iter->curr, 1);
        }
    }
    iter->currEdg = graphVertexEdges(iter->graph, iter->curr);
    if (iter->currEdg != NULL) {
        adtSetValue(intDO, &iter->curr);
        stkPush(iter->stack, intDO);
    }
}




