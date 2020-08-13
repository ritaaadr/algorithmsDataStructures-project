
#include "queue.h"

/* ************************************************************************** */

QueueObject *  queConstruct(QueueType* type)
{
    QueueObject * queue = (QueueObject* )malloc(sizeof(QueueObject));

    queue->dim = 0;
    queue->type = type;
    queue->value = type->que_Construct();

    printf("Queue costruita\n");

    return queue;

}

/* ************************************************************************** */

void queDestruct(QueueObject* queue)
{
    assert(queue);
    assert(queue->value);

    queue->type->que_Destruct(queue->value);

    free(queue);
}

/* ************************************************************************** */

void queEnqueue(QueueObject* queue, DataObject* val)
{
    assert(queue);
    assert(val);

    queue->type->que_Enqueue(queue->value, val);
    queue->dim = queue->dim+1;

}

/* ************************************************************************** */

bool queEmpty(QueueObject* queue)
{
    assert(queue);

    return queue->type->que_Empty(queue->value);
}

/* ************************************************************************** */

DataObject* queHead(QueueObject* queue)
{
    assert(queue);
    assert(queue->value);

    DataObject* ret = queue->type->que_Head(queue->value);

    return ret;
}

/* ************************************************************************** */

void queDequeue(QueueObject* queue)
{
   assert(queue);
   assert(!queEmpty(queue));
   assert(queue->value);

   queue->type->que_Dequeue(queue->value);
   queue->dim = queue->dim-1;

}

/* ************************************************************************** */

void queClear(QueueObject* queue)
{
    assert(queue);
    assert(!queEmpty(queue));
    assert(queue->value);

    queue->type->que_Clear(queue->value);
    queue->dim = 0;
}

/* ************************************************************************** */

DataObject* queHeadNDequeue(QueueObject* queue)
{
    assert(queue);
    assert(!queEmpty(queue));
    assert(queue->value);

    DataObject* ret = queue->type->que_Head(queue->value);
    queue->type->que_Dequeue(queue->value);
    queue->dim = queue->dim-1;

    return ret;

}

/* ************************************************************************** */

QueueObject * queClone(QueueObject* queue)
{
    QueueObject* queuex = (QueueObject*)malloc(sizeof(QueueObject));
    queuex->type = queue->type;
    queuex->value = queue->type->que_Clone(queue->value);
    queuex->dim = queue->dim;

    return queuex;
}

/* ************************************************************************** */

bool queEqual(QueueObject* queue, QueueObject* queuex)
{
    assert(queue->type == queuex->type);

    return queue->type->que_Equal(queue->value, queuex->value);
}

/* ************************************************************************** */

int queSize(QueueObject* queue)
{
    return queue->dim;
}

/* ************************************************************************** */

bool queExists(QueueObject* queue, DataObject* val)
{
    assert(queue);
    assert(val);

    bool exists = false;

    queue->type->que_Fold(queue->value, &esisteFold, &val, val);

    return exists;
}

/* ************************************************************************** */

void queMap(QueueObject* queue, MapFun fun, void* par)
{
    assert(queue);
    assert(queue->value);

    queue->type->que_Map(queue->value, fun, par);
}

/* ************************************************************************** */

void queFold(QueueObject* queue, FoldFun fun, void* accum, void* par)
{
    assert(queue);
    assert(queue->value);

    queue->type->que_Fold(queue->value, fun, accum, par);
}