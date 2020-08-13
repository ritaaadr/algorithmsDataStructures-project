
#include <bst/bst.h>
#include "itr.h"

/* ************************************************************************** */

ITRObject * itrConstruct(ITRType* type, void* Struct)
{
    //quando lo construisco l'iteratore deve già puntare al primo elemento in base alla visita scelta
    if(Struct == NULL){
        return NULL;
    } else {
        //BSTNode *root = (BSTNode *) treeStruct;
        ITRObject *iterator = (ITRObject *) malloc(sizeof(ITRObject));
        iterator->type = type;
        iterator->implementation = type->itr_Construct(Struct);

        return iterator;
    }
}

/* ************************************************************************** */

void itrDestruct(ITRObject* iterator)
{
    assert(iterator);

    //if con !terminated?
    iterator->type->itr_Destruct(iterator->implementation);
    free(iterator);
}

/* ************************************************************************** */

bool itrTerminated(ITRObject* iterator)
{
    if(iterator!= NULL) {
        return iterator->type->itr_Terminated(iterator->implementation);
    } else return NULL;
}

/* ************************************************************************** */

void * itrElement(ITRObject* iterator)
{
    if(iterator != NULL) {
        return iterator->type->itr_Element(iterator->implementation);
    } else return NULL;
}

/* ************************************************************************** */

void itrSuccessor(ITRObject* iterator)
{
    if(iterator!= NULL) {
        return iterator->type->itr_Successor(iterator->implementation);
    } else return;
}

/* ************************************************************************** */