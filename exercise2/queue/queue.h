
#ifndef QUEUE_H
#define QUEUE_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef void* (*QueConstruct)();
typedef void (*QueDestruct)(void*);

typedef bool (*QueEmpty)(void*);
typedef DataObject* (*QueHead)(void*);
typedef void (*QueDequeue)(void*);
typedef DataObject* (*QueHeadNDequeue)(void*);
typedef void (*QueEnqueue)(void*, DataObject*);
typedef void (*QueClear)(void*);

typedef void* (*QueClone)(void*);
typedef bool (*QueEqual)(void*, void*);
typedef void (*QueMap)(void*, MapFun, void*);
typedef void (*QueFold)(void*, FoldFun, void*, void*);

/* ************************************************************************** */

typedef struct QueueType
{
    QueConstruct  que_Construct;
    QueDestruct  que_Destruct;

    QueEmpty  que_Empty;
    QueHead  que_Head;
    QueDequeue que_Dequeue;
    QueHeadNDequeue que_HeadNDequeue;
    QueEnqueue que_Enqueue;
    QueClear que_Clear;

    QueClone que_Clone;
    QueEqual que_Equal;
    QueMap que_Map;
    QueFold que_Fold;

} QueueType;

typedef struct QueueObject
{
    QueueType* type;
    void* value;
    uint dim;

} QueueObject;

/* ************************************************************************** */

//quelli del main
QueueObject *  queConstruct(QueueType* type);
void queDestruct(QueueObject* queue);

bool queEmpty(QueueObject* queue);
DataObject* queHead(QueueObject* queue);
void queDequeue(QueueObject* queue);
DataObject* queHeadNDequeue(QueueObject* queue);
void queEnqueue(QueueObject* queue, DataObject* val);
void queClear(QueueObject* queue);

QueueObject * queClone(QueueObject* queue);
bool queEqual(QueueObject* queue, QueueObject* queuex);
void queMap(QueueObject* queue, MapFun fun, void* par);
void queFold(QueueObject* queue, FoldFun fun, void* accum, void* par);

int queSize(QueueObject* queue);
bool queExists(QueueObject* queue, DataObject* val);

/* ************************************************************************** */

#endif
