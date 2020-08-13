
#include "queuevec.h"

/* ************************************************************************** */

QueueType* ConstructQueueVecType()
{
    QueueType* type = (QueueType*)malloc(sizeof(QueueType));

    type->que_Construct = &queConstructVecType;
    type->que_Destruct = &queDestructVecType;

    type->que_Empty = &queEmptyVecType;
    type->que_Head = &queHeadVecType;
    type->que_Dequeue = &queDequeueVecType;
    type->que_Enqueue = &queEnqueueVecType;
    type->que_HeadNDequeue = &queHeadNDequeueVecType;

    type->que_Clear = &queClearVecType;
    type->que_Clone = &queCloneVecType;
    type->que_Equal = &queEqualVecType;

    type->que_Map = &queMapVecType;
    type->que_Fold = &queFoldVecType;

    return type;
}

/* ************************************************************************** */
void DestructQueueVecType(QueueType* type)
{
    free(type);
}

/* ************************************************************************** */

void * queConstructVecType()
{
    QueueVec *obj = (QueueVec*) malloc(sizeof(QueueVec));

    assert(obj);
    obj->num_elem = 0;
    obj->front = 0;
    obj->dim = 10;
    obj->rear = 0;
    obj->elements = (DataObject**) malloc(sizeof(DataObject*) * obj->dim);

    return obj;
}

/* ************************************************************************** */


void queDestructVecType(void *queue)
{
    assert(queue);
    //assert(obj->front=0);
    QueueVec* obj = (QueueVec*)queue;

    free(obj->elements);
    free(obj);

}

/* ************************************************************************** */

void queClearVecType(void* queue)
{
    assert(queue);
    QueueVec* obj = (QueueVec*)queue;
    uint i = obj->front;

    while(i != obj->rear) {
        adtDestruct(obj->elements[i]);
        obj->num_elem = obj->num_elem-1;

        i = i+1;

        if( i == obj->dim){
            i = 0;
        }
    }
    adtDestruct(obj->elements[i]);
    obj->num_elem = obj->num_elem-1;



}

/* ************************************************************************** */

void queEnqueueVecType(void *queue, DataObject* elemx)
{
    assert(queue);
    assert(elemx);
    QueueVec* obj = (QueueVec*)queue;

    uint i = obj->front;
    uint newIndex = 0;
    DataObject* elemToInsert = adtClone(elemx);

    // Ho finito lo spazio e realloco
    if(obj->num_elem == obj->dim) {
        DataObject** newArray = (DataObject**) malloc(sizeof(DataObject*) * (obj->dim*2));

        while (i != obj->rear) {
            newArray[newIndex++] = obj->elements[i];

            i = (i + 1) % obj->dim;
        }
        // Prendo anche l'elemento finale
        newArray[newIndex] = obj->elements[i];

        // Libero il vecchio array ed aggiorno la coda
        free(obj->elements);
        obj->elements = newArray;
        obj->front = 0;
        obj->rear = newIndex;
        obj->dim = obj->dim*2;
    }

    // Gestisco il caso con zero elementi e con almeno uno
    if(obj->num_elem == 0){
        obj->elements[obj->rear] = elemToInsert;
    } else {
        obj->elements[++obj->rear] = elemToInsert;
    }

    obj->num_elem = obj->num_elem+1;
}



/* ************************************************************************** */

void queDequeueVecType(void *queue)
{
    assert(queue);
    QueueVec* obj = (QueueVec*)queue;

    // Tolgo solo se la coda ha almeno 1 elemento
    if(!queEmptyVecType(obj)) {

        adtDestruct(obj->elements[obj->front]);
        if(obj->front == obj->rear) {
           obj->rear = (obj->rear + 1) % obj->dim;
        }
        obj->front = (obj->front + 1) % obj->dim;
        obj->num_elem--;

        // Uso poco spazio, ne realloco di meno
        if((obj->num_elem * 4) == obj->dim) {
            DataObject **new_array = (DataObject **) malloc(sizeof(DataObject *) * (obj->dim/2));

            int new_front = 0;
            int old_front = obj->front;

            while (old_front != obj->rear) {
                new_array[new_front++] = obj->elements[old_front];

                old_front = (old_front + 1) % obj->dim;
            }
            // Prendo anche l'elemento finale
            new_array[new_front] = obj->elements[old_front];

            free(obj->elements);
            obj->elements = new_array;
            obj->front = 0;
            obj->rear = new_front;
            obj->dim = obj->dim / 2;
        }
    }

    obj->num_elem = obj->num_elem-1;
}

/* ************************************************************************** */

DataObject * queHeadVecType(void *queue)
{
    assert(queue);
    QueueVec* obj = (QueueVec*)queue;

    if(!queEmptyVecType(obj)) {
        DataObject* clone = adtClone(obj->elements[obj->front]);
        return clone;
    }else{
        return NULL;
    }
}

/* ************************************************************************** */

bool queEmptyVecType(void *queue)
{
    assert(queue);
    QueueVec* obj = (QueueVec*)queue;

    return obj->num_elem == 0;
}

/* ************************************************************************** */

DataObject * queHeadNDequeueVecType(void *queue)
{
    assert(queue);
    assert(!queEmptyVecType(queue));
    QueueVec* obj = (QueueVec*)queue;

    DataObject* ret = obj->elements[obj->front];

    obj->num_elem--;
    if(obj->front == obj->rear) {
        obj->rear = (obj->rear + 1) % obj->dim;
    }
    obj->front = (obj->front + 1) % obj->dim;

    // Uso poco spazio, devo reallocare
    if((obj->num_elem * 4) == obj->dim) {
        DataObject **new_array = (DataObject **) malloc(sizeof(DataObject *) * (obj->dim/2));

        int new_front = 0;
        int old_front = obj->front;

        while (old_front != obj->rear) {
            new_array[new_front++] = obj->elements[old_front];

            old_front = (old_front + 1) % obj->dim;
        }
        // Prendo anche l'elemento finale
        new_array[new_front] = obj->elements[old_front];

        free(obj->elements);
        obj->elements = new_array;
        obj->front = 0;
        obj->rear = new_front;
        obj->dim = obj->dim / 2;
    }

    return ret;
}



/* ************************************************************************** */

int queExistsVecType(void *queue, DataObject* val)
{
    assert(queue);
    assert(val);
    QueueVec* obj = (QueueVec*)queue;

    int i = obj->front;

    if(!queEmptyVecType(obj)) {
        while (i != obj->rear) {
            if (adtCompare(obj->elements[i], val) == 0) {
                return 1;
            }

            i = i + 1;

            if (i == obj->dim) {
                i = 0;
            }
        }
        adtCompare(obj->elements[obj->rear], val);
    }

    return 0;

}

/* ************************************************************************** */

void * queCloneVecType(void *queue)
{
    assert(queue);
    QueueVec* obj = (QueueVec*)queue;
    uint i = obj->front;


    QueueVec* clone = (QueueVec*)malloc(sizeof(QueueVec));

    clone->front=0;
    clone->rear=0;
    clone->dim=obj->dim;
    clone->num_elem= 0;
    clone->elements = (DataObject**)malloc(sizeof(DataObject*)*obj->dim);

    while(i != obj->rear ){

        queEnqueueVecType(clone, obj->elements[i]);
        i = i+1;
        clone->num_elem = clone->num_elem+1;

        if( i == obj->dim ) {
            i = 0;
        }
    }
    queEnqueueVecType(clone, obj->elements[i]);

    return clone;
}

/* ************************************************************************** */

bool queEqualVecType(void *queue, void *queuex)
{

    assert(queue);
    assert(queuex);

    QueueVec * obj = (QueueVec*)queue;
    QueueVec * objx = (QueueVec*)queuex;

    uint i=obj->front;

    if(obj->dim != objx->dim){
        return -1;
    }
    else {
        while (i != obj->rear) {

            if ((adtCompare(obj->elements[i], objx->elements[i])!= 0)) {
                return -1;
            }

            i++;
            if (i == obj->dim) {
                i = 0;
            }
        }
        if ((adtCompare(obj->elements[obj->rear], objx->elements[objx->rear])!=0)) {
            return -1;

        } else{
            return 1;
        }



    }

}

/* ************************************************************************** */



void queMapVecType(void* queue , MapFun fun , void* par )
{
    assert(queue);
    QueueVec* obj = (QueueVec*)queue;

    int i=obj->front;

    if(obj->num_elem==1){
        fun(obj->elements[i], par);
    }else {
        while (i != obj->rear) {
            fun(obj->elements[i], par);

            i = i+1;

            if (i == obj->dim) {
                i = 0;
            }
        }

        fun(obj->elements[i], par);


    }
}

/* ************************************************************************** */

void queFoldVecType(void* queue , FoldFun fun , void* accum , void* par)
{
    assert(queue);
    QueueVec* obj = (QueueVec*)queue;
    uint i=obj->front;

    if(obj->num_elem==1){
        fun(obj->elements[obj->rear], accum, par);
    }
    else {
        while (i != obj->rear) {
            fun(obj->elements[i], accum, par);
            i = i+1;
            if (i == obj->dim) {
                i = 0;
            }
        }
        if( i == obj->rear){
            fun(obj->elements[i], accum, par);
        }
    }

}

