
#include "queuelst.h"

/* ************************************************************************** */


QueueType* ConstructQueueLstType()
{
    QueueType* type = (QueueType*)malloc(sizeof(QueueType));

    type->que_Construct = &queConstructLstType;
    type->que_Destruct = &queDestructLstType;

    type->que_Empty = &queEmptyLstType;
    type->que_Head = &queHeadLstType;
    type->que_Dequeue = &queDequeueLstType;
    type->que_Enqueue = &queEnqueueLstType;
    type->que_HeadNDequeue = &queHeadNDequeueLstType;

    type->que_Clear = &queClearLstType;

    type->que_Clone = &queCloneLstType;
    type->que_Equal = &queEqualLstType;

    type->que_Map = &queMapLStType;
    type->que_Fold = &queFoldLstType;

    return type;
}

/* ************************************************************************** */

void DestructQueueLstType(QueueType* type)
{
    free(type);
}

/* ************************************************************************** */

void * queConstructLstType()
{
    QueueLst * obj = (QueueLst*)malloc(sizeof(QueueLst));

    if(obj != NULL){

        obj->num_nodes = 0;
        obj->front = NULL;
        obj->rear = NULL;
    }
    return obj;
}

/* ************************************************************************** */

void queEnqueueLstType(void *queue, DataObject* elemx)
{
    assert(queue);
    assert(elemx);
    QueueLst* obj = (QueueLst*)queue;
    DataObject* elemToEnqueue = adtClone(elemx);

    //salvo il valore il un nodo temporaneo
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->elements = elemToEnqueue;
    tmp->next = NULL;

    if(obj->front == NULL){
        obj->front = tmp;
        obj->num_nodes = 1;
    }else {
        obj->rear->next = tmp;
        obj->num_nodes = obj->num_nodes + 1;
    }
    obj->rear = tmp;

}

/* ************************************************************************** */

void queDestructLstType(void* queue)
{
    QueueLst* obj = (QueueLst*)queue;
    free(obj);
}

/* ************************************************************************** */

bool queEmptyLstType(void *queue)
{
    assert(queue);
    QueueLst* obj = (QueueLst*)queue;

    return obj->num_nodes == 0;
}

/* ************************************************************************** */

DataObject * queHeadLstType(void *queue)
{
    assert(queue);
    QueueLst* obj = (QueueLst*)queue;

    if(!queEmptyLstType(obj)){
        DataObject* clone = adtClone(obj->front->elements);
        return clone;
    }else return NULL;
}

/* ************************************************************************** */

void queDequeueLstType(void *queue)
{
    assert(queue);
    QueueLst* obj = (QueueLst*)queue;

    Node* tmp = obj->front;
    adtDestruct(tmp->elements);

    //caso in cui la queue è vuota
    if(obj->front == NULL){
        return;
    }

    //se ho un elemento
    if(obj->front == obj->rear){
        obj->front = obj->rear = NULL;
    }else {
        obj->front = tmp->next;
    }

    free(tmp);
    obj->num_nodes = obj->num_nodes-1;

}

/* ************************************************************************** */

DataObject * queHeadNDequeueLstType(void *queue)
{
    assert(queue);
    QueueLst* obj = (QueueLst*) queue;

    if(!queEmptyLstType(obj)){
        DataObject* returnObj = obj->front->elements;

        Node* tmp = obj->front;
        obj->front = tmp->next;
        free(tmp);

        obj->num_nodes = obj->num_nodes-1;

        return returnObj;
    }

    return NULL;
}

/* ************************************************************************** */

void queClearLstType(void* queue)
{
    assert(queue);
    QueueLst* obj = (QueueLst*)queue;

    while(!queEmptyLstType(obj)){
        queDequeueLstType(obj);
    }

}

/* ************************************************************************** */

void * queCloneLstType(void *queue)
{
    QueueLst* obj = (QueueLst*)queue;

    QueueLst* clone = (QueueLst*)malloc(sizeof(QueueLst));
    Node* curr = obj->front;

    while(curr != NULL){
        DataObject* value = adtClone(curr->elements);
        queEnqueueLstType(clone, value);
        curr = curr->next;
    };
    return clone;
}

/* ************************************************************************** */

bool queEqualLstType(void *queue, void *queuex)
{
    assert(queue);
    assert(queuex);
    QueueLst* obj = (QueueLst*)queue;
    QueueLst* objx = (QueueLst*)queuex;

    Node* curr = obj->front;
    Node* currx = objx->front;

    if(obj->num_nodes != objx->num_nodes){
        return false;
    }

    if(curr != NULL && currx != NULL){
        if(adtCompare(curr->elements, currx->elements)!= 0){
            return false;
        }
        curr = curr->next;
        currx = currx->next;
    }
    return true;


}

/* ************************************************************************** */

void queMapLStType(void* queue, MapFun fun , void* par)
{
    assert(queue);
    QueueLst* obj = (QueueLst*)queue;

    Node* curr = obj->front;

    while(curr != NULL){
        fun(curr->elements, par);
        curr = curr->next;
    }
}

/* ************************************************************************** */

void queFoldLstType(void* queue, FoldFun fun , void* accum , void* par)
{
    assert(queue);
    QueueLst* obj = (QueueLst*)queue;

    Node* curr = obj->front;

    while(curr != NULL){
        fun(curr->elements, accum, par);
        curr = curr->next;
    }

}
