
#include <bst/bst.h>
#include "itr.h"

/* ************************************************************************** */

ITRObject * itrConstruct(ITRType* type, void* treeStruct)
{
    //quando lo construisco l'iteratore deve già puntare al primo elemento in base alla visita scelta
    if(treeStruct == NULL){
        printf("Albero vuoto\n");
        return NULL;
    } else {
        BSTNode *root = (BSTNode *) treeStruct;


        ITRObject *iterator = (ITRObject *) malloc(sizeof(ITRObject));
        iterator->type = type;
        iterator->implementation = type->itr_Construct(root);

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
    assert(iterator);

    return iterator->type->itr_Terminated(iterator->implementation);
}

/* ************************************************************************** */

void * itrElement(ITRObject* iterator)
{
    assert(iterator);

    return iterator->type->itr_Element(iterator->implementation);
}

/* ************************************************************************** */

void itrSuccessor(ITRObject* iterator)
{
    assert(iterator);

    return iterator->type->itr_Successor(iterator->implementation);
}

/* ************************************************************************** */