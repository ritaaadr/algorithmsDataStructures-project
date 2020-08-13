#ifndef QUEUEVEC_H
#define QUEUEVEC_H

/* ************************************************************************** */

#include "../queue.h"

/* ************************************************************************** */

typedef struct QueueVec
{
  uint front; //puntatore alla testa
  uint rear; //puntatore alla coda
  uint dim;
  DataObject** elements;
  uint num_elem;

} QueueVec;

/* ************************************************************************** */

QueueType* ConstructQueueVecType();
void DestructQueueVecType(QueueType* type);

/* ************************************************************************** */


void * queConstructVecType();
void queDestructVecType(void *queue);

bool queEmptyVecType(void *queue);
DataObject * queHeadVecType(void *queue);
void queDequeueVecType(void *queue);
void queEnqueueVecType(void *queue, DataObject* elemx);
DataObject * queHeadNDequeueVecType(void *queue);
void queClearVecType(void* queue);

void * queCloneVecType(void *queue);
bool queEqualVecType(void *queue, void *queuex);


void queMapVecType(void* queue, MapFun fun , void* par);
void queFoldVecType(void* queue, FoldFun fun , void* accum , void* par);


/* ************************************************************************** */

#endif
