#include <adt/int/adtint.h>
#include <bst/rec/bstrec.h>
#include <adt/rec/adtrec.h>
#include <queue/lst/queuelst.h>
#include <adt/vert/adtvert.h>
#include <queue/vec/queuevec.h>
#include "graphitrbreadth.h"
/* ************************************************************************** */

ITRType* ConstructGraphBreadthIterator()
{
    ITRType* type= ( ITRType * ) malloc(sizeof(ITRType));
    type->itr_Construct=&itrConstructBreadthIterator;
    type->itr_Destruct=&itrDestructBreadthIterator;
    type->itr_Terminated=&itrTerminatedBreadthIterator;
    type->itr_Element=&itrElementBreadthIterator;
    type->itr_Successor=&itrSuccessorBreadthIterator;
    return type;
}

void DestructGraphBreadthIterator(ITRType* type)
{
    free(type);
}

void* itrConstructBreadthIterator(void* gra)
{
    GraphObject* graph = (GraphObject*)gra;
    GraphBreadthIterator* iter = (GraphBreadthIterator*)malloc(sizeof(GraphBreadthIterator));

    QueueType* queueType = ConstructQueueLstType();
    DataType* recType = ConstructRecordDataType();
    DataType* intDataType = ConstructIntDataType();
    DataObject* data = adtConstruct(intDataType);
    BSTType* bstType = ConstructBSTRecursive();

    iter->queue = queConstruct(queueType);
    iter->graph = graph;
    iter->treeOfColors = bstConstruct(bstType);
    iter->verticesItr = graphVertices(graph);

    if(!itrTerminated(iter->verticesItr)){
        iter->curr = itrElement(iter->verticesItr);
        DataObject* bstData = adtConstruct(recType);
        uint index = adtGetVertexId(iter->curr->value);
        bstData->value = adtInitializeRec(bstData->value, index, 1);
        bstInsert(iter->treeOfColors, bstData);

        ITRObject* EdgesIterator = graphVertexEdges(iter->graph, adtGetVertexId(iter->curr->value));
        while(EdgesIterator!=NULL && !itrTerminated(EdgesIterator)){
            uint vertId = *((int*)itrElement(EdgesIterator));
            DataObject *structOfColors = adtConstruct(recType);
            structOfColors->value = adtInitializeRec(structOfColors->value, vertId, 1);
            adtSetValue(data, &vertId);

            if(!bstExists(iter->treeOfColors , structOfColors)){
                bstInsert(iter->treeOfColors, structOfColors);
                queEnqueue(iter->queue, data);
            }
            itrSuccessor(EdgesIterator);
        }
        itrSuccessor(iter->verticesItr);
    } else {
        iter->curr = NULL;
    }
    return iter;
}

void itrDestructBreadthIterator(void* iterator)
{
    GraphBreadthIterator* iter = (GraphBreadthIterator*)iterator;
    bstDestruct(iter->treeOfColors);
    queDestruct(iter->queue);

    free(iter);
}

bool itrTerminatedBreadthIterator(void *iterator)
{
    GraphBreadthIterator* iter = (GraphBreadthIterator*)iterator;
    return iter->curr==NULL && queEmpty(iter->queue);
}

void* itrElementBreadthIterator(void* iterator)
{
    GraphBreadthIterator* iter = (GraphBreadthIterator*)iterator;
    return iter->curr;
}

void  itrSuccessorBreadthIterator(void* iterator)
{
    GraphBreadthIterator* iter = (GraphBreadthIterator*)iterator;
    DataType* intDataType = ConstructIntDataType();
    DataType* recType = ConstructRecordDataType();
    bool success = false;

    while(!success){
        if(!queEmpty(iter->queue)){
            DataObject* frontElement = queHeadNDequeue(iter->queue);
            int index = *(int*) adtGetValue(frontElement);
            iter->curr= graphGetVertexData(iter->graph , index);
            success = true;

            //utilizzo l'albero per settare il colore "nero"
            DataObject* bstData = adtConstruct(recType);
            DataObject* current= adtConstruct(intDataType);
            bstData->value = adtInitializeRec(bstData->value, index, 1);
            bstInsert(iter->treeOfColors, bstData);

            if(iter->curr!= NULL) {
                ITRObject* edgIter = graphVertexEdges(iter->graph, adtGetVertexId(iter->curr->value));
                while (edgIter != NULL && !itrTerminated(edgIter)) {
                    int edge = *((int *)itrElement(edgIter));
                    bstData->value = adtInitializeRec(bstData->value, edge, 1);
                    adtSetValue(current, &edge);

                    if (!bstExists(iter->treeOfColors, current)) {
                        bstInsert(iter->treeOfColors, current);
                        queEnqueue(iter->queue, current);
                    }
                    itrSuccessor(edgIter);
                }
            }
        }else if (!itrTerminated(iter->verticesItr)){
            while( iter->verticesItr!=NULL  && !itrTerminated(iter->verticesItr)) {
                DataObject* element = itrElement(iter->verticesItr);
                int idElement = adtGetVertexId(element->value);
                DataObject *data = adtConstruct(recType);
                data->value = adtInitializeRec(data->value, idElement, 1);
                DataObject* newCurr = adtConstruct(intDataType);
                adtSetValue(newCurr , &idElement);

                if (!bstExists(iter->treeOfColors, data)) {
                    bstInsert(iter->treeOfColors, data);
                    queEnqueue(iter->queue , newCurr);
                }
                itrSuccessor(iter->verticesItr);
            }
        } else  {
            iter->curr = NULL;
            success = true;
        }
    }
}