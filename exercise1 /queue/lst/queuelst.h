
#ifndef QUEUELST_H
#define QUEUELST_H

/* ************************************************************************** */

#include "../queue.h"

/* ************************************************************************** */

typedef struct QueueLst QueueLst;
typedef struct Node Node;
struct QueueLst
{
     Node*  front;
     Node* rear;
     int num_nodes;
};

/* ************************************************************************** */
struct Node
{
    DataObject* elements;
    Node* next;
};


/* ************************************************************************** */

QueueType* ConstructQueueLstType();
void DestructQueueLstType(QueueType* type);

/* ************************************************************************** */

void * queConstructLstType();
void queDestructLstType(void *queue);

bool queEmptyLstType(void *queue);
DataObject * queHeadLstType(void *queue);
void queDequeueLstType(void *queue);
void queEnqueueLstType(void *queue, DataObject* elemx);
DataObject * queHeadNDequeueLstType(void *queue);

void queClearLstType(void* queue);

void * queCloneLstType(void *queue);
bool queEqualLstType(void *queue, void *queuex);

void queMapLStType(void* queue, MapFun fun , void* par);
void queFoldLstType(void* queue, FoldFun fun , void* accum , void* par);


#endif
