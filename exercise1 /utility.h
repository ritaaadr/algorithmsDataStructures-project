

#ifndef UTILITY_H
#define UTILITY_H

/* ************************************************************************** */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "adt/adt.h"

/* ************************************************************************** */

typedef unsigned int uint;

/* ************************************************************************** */

typedef struct DataType DataType;
typedef struct DataObject DataObject;

/* ************************************************************************** */

int rndNum(int a, int b);

/* ************************************************************************** */

void getStr(char * str, uint len);

/* ************************************************************************** */

void stampaMap(DataObject* obj, void* par);
void esisteFold(DataObject* obj, void* accum, void* ElemToFind);
void sommaFold(DataObject* obj, void* par, void* parx);
void concatenazioneFold(DataObject* element, void* concatStr, void* maxSize);
void prodottoFold(DataObject* obj, void* par, void* parax);
void raddoppiaMap(DataObject* obj, void* par);
void quadratoMap(DataObject* obj, void* par);
void mapUppercase(DataObject* obj, void* par);



#endif
