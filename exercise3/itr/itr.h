
#ifndef ITR_H
#define ITR_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef void *  (*ITRConstruct)();

typedef void (*ITRDestruct)(void*);

typedef bool (*ITRTerminated)(void*);

typedef void * (*ITRElement)(void*);

typedef void  (*ITRSuccessor)(void*);

/* ************************************************************************** */

typedef struct ITRType
{
  ITRConstruct itr_Construct;
  ITRDestruct  itr_Destruct;
  ITRTerminated  itr_Terminated;
  ITRElement  itr_Element;
  ITRDestruct  itr_Successor;
} ITRType;

typedef struct ITRObject
{
  ITRType * type;
  void * implementation;

} ITRObject;

/* ************************************************************************** */

//dipende dal tipo di implementazione scelta
ITRObject * itrConstruct(ITRType* type, void* Struct);

void itrDestruct(ITRObject* iterator);

//funzione che mi dice se ho analizzato tutto l'albero o meno
bool itrTerminated(ITRObject* iterator);

//funzione che mi restituisce l'elemento a cui punta l'iteratore
void *  itrElement(ITRObject* iterator);

//funzione che mi fa andare al prossimo nodo
void itrSuccessor(ITRObject* iterator);

/* ************************************************************************** */

#endif
