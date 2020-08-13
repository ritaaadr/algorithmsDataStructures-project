#ifndef EXERCISE3_LIST_H
#define EXERCISE3_LIST_H

/* ************************************************************************** */

#include "../utility.h"
#include "../adt/adt.h"

/* ************************************************************************** */

typedef struct VertexesLst_t {
    struct VertexesLst_t* next;
    uint label;
}Lst;


/* ************************************************************************** */

Lst* listInsert(Lst*, uint);
Lst* listClone(Lst*);
bool listExists(Lst*, uint);
void listDestruct(Lst*);
void* listClear(Lst*);
Lst* listRemove(Lst*, uint);
int listSize(Lst*);

#endif //EXERCISE3_LIST_H
