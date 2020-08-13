#include "../stack/vec/stackvec.h"
#include <bst/rec/bstrec.h>
#include <adt/vert/adtvert.h>
#include <adt/rec/adtrec.h>
#include <adt/int/adtint.h>
#include "graphitrpostord.h"

ITRType* ConstructGraphPostOrderIterator()
{
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->itr_Construct = &itrConstructGraphPostOrderIterator;
    type->itr_Destruct = &itrDestructGraphPostOrderIterator;
    type->itr_Terminated = &itrTerminatedGraphPostOrderIterator;
    type->itr_Element = &itrElementGraphPostOrderIterator;
    type->itr_Successor = &itrSuccessorGraphPostOrderIterator;

    return type;
}

void DestructGraphPostOrderIterator(ITRType* type)
{
    free(type);
}

void * itrConstructGraphPostOrderIterator(void* graphStruct)
{
    GraphObject* graph = (GraphObject *) graphStruct;

    GraphPostOrderIterator *iter = (GraphPostOrderIterator *) malloc(sizeof(GraphPostOrderIterator));

    iter->graph = graph;
    DataType* intDataType = ConstructIntDataType();
    DataObject* intData = adtConstruct(intDataType);

    BSTType* bstType = ConstructBSTRecursive();
    iter->treeOfColors = bstConstruct(bstType);
    DataObject* elemToSearch = adtConstruct(intDataType);

    StackType* stkType = ConstructStackVecType();
    iter->stack = stkConstruct(stkType);

    ITRObject* vertItr = graphVertices(iter->graph);
    iter->verticesIterator = vertItr;

    DataObject* vertData = itrElement(vertItr);
    iter->curr = adtGetVertexId(vertData->value);
    iter->currEdg = graphVertexEdges(iter->graph, iter->curr);

    ITRObject* edges = NULL;

    int elem;
    while (iter->currEdg != NULL && !itrTerminated(iter->currEdg)) {

        adtSetValue(intData, &iter->curr);
        stkPush(iter->stack, intData);
        iter->curr = *((int*)itrElement(iter->currEdg));
        edges = graphVertexEdges(iter->graph, iter->curr);

        if (edges == NULL) {
            break;
        }

        iter->currEdg = edges;
        elem = *((int*)itrElement(iter->currEdg));
        adtSetValue(elemToSearch, &elem);
        while (!itrTerminated(iter->currEdg) && stkExists(iter->stack, elemToSearch)) {
            itrSuccessor(iter->currEdg);
            if (itrTerminated(iter->currEdg)) {
                stkPop(iter->stack);
                break;
            }
            elem = *((int*)itrElement(iter->currEdg));
            adtSetValue(elemToSearch, &elem);
        }
        if (itrTerminated(iter->currEdg)) {
            iter->currEdg = NULL;
        }
    }
    return iter;
}

void itrDestructGraphPostOrderIterator(void* iterator)
{
    GraphPostOrderIterator* iter = (GraphPostOrderIterator*)iterator;

    itrDestruct(iter->verticesIterator);
    stkDestruct(iter->stack);
}

bool itrTerminatedGraphPostOrderIterator(void* iterator)
{
    GraphPostOrderIterator* iter = (GraphPostOrderIterator*)iterator;
    return bstSize(iter->treeOfColors) == graphVertexNumber(iter->graph);
}


void * itrElementGraphPostOrderIterator(void* iterator)
{
    GraphPostOrderIterator* iter = (GraphPostOrderIterator*)iterator;

    DataType* recType = ConstructRecordDataType();
    DataObject* structOfColors = adtConstruct(recType);

    DataObject* ret = graphGetVertexData(iter->graph, iter->curr);
    structOfColors->value = adtInitializeRec(structOfColors->value, iter->curr, 1);
    bstInsert(iter->treeOfColors, structOfColors);
    return ret;
}


void itrSuccessorGraphPostOrderIterator(void* iterator) {
    GraphPostOrderIterator *iter = (GraphPostOrderIterator *) iterator;

    DataType *intDataType = ConstructIntDataType();
    DataType *recType = ConstructRecordDataType();
    DataObject *data = adtConstruct(recType);

    data->value = adtInitializeRec(data->value, iter->curr, 1);
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
        iter->currEdg = graphVertexEdges(iter->graph, iter->curr);
        if (iter->currEdg != NULL) {
            DataObject *elemToSearch = adtConstruct(intDataType);

            adtSetValue(elemToSearch, &iter->curr);
            if (!stkExists(iter->stack, elemToSearch)) {
                stkPush(iter->stack, elemToSearch);
            }
        }
    }
    if (!stkEmpty(iter->stack)) {
        iter->curr = *(int *) adtGetValue(stkTop(iter->stack));
        iter->currEdg = graphVertexEdges(iter->graph, iter->curr);
        uint elem;
        DataObject *elemToSearch = adtConstruct(intDataType);
        while (iter->currEdg != NULL && !itrTerminated(iter->currEdg)) {
            elem = *((int *) itrElement(iter->currEdg));
            adtSetValue(elemToSearch, &elem);
            data->value = adtInitializeRec(data->value, elem, 1);

            while (!itrTerminated(iter->currEdg) &&
                   (stkExists(iter->stack, elemToSearch) || bstExists(iter->treeOfColors, data))) {
                itrSuccessor(iter->currEdg);
                if (itrTerminated(iter->currEdg)) {
                    break;
                }
                elem = *((int *) itrElement(iter->currEdg));
                adtSetValue(elemToSearch, &elem);
                data->value = adtInitializeRec(data->value, elem, 1);
            }
            if (itrTerminated(iter->currEdg)) {
                iter->currEdg = NULL;
            } else {
                iter->curr = elem;
                adtSetValue(elemToSearch, &elem);
                if (!stkExists(iter->stack, elemToSearch)) {
                    stkPush(iter->stack, elemToSearch);
                }
                iter->currEdg = graphVertexEdges(iter->graph, iter->curr);
            }
        }
        int valueOnTop = *(int *) adtGetValue(stkTop(iter->stack));
        if (iter->currEdg == NULL && valueOnTop == iter->curr) {
            stkPop(iter->stack);
        }
    }
    bstBreadthMap(iter->treeOfColors, &stampaMap, NULL);
}