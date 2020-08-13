
#ifndef BST_H
#define BST_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef struct BSTNode BSTNode;

struct BSTNode
{
  DataObject* data;
  BSTNode* LeftPtr;
  BSTNode* RightPtr;
};

/* ************************************************************************** */

typedef void (*BSTDestruct)(void*);

typedef void * (*BSTClone)(void*);

typedef bool (*BSTEqual)(void*, void*);

typedef bool (*BSTExists)(void*, DataObject*);

typedef void * (*BSTInsert)(void*, DataObject*, int*);
typedef void * (*BSTRemove)(void*, DataObject*);

typedef void * (*BSTGetMin)(void*);
typedef void * (*BSTGetNRemoveMin)(void*, void*);
typedef void * (*BSTRemoveMin)(void*, void*);
typedef void * (*BSTGetMax)(void*);
typedef void * (*BSTGetNRemoveMax)(void*, void*);
typedef void * (*BSTRemoveMax)(void*, void*);

typedef void * (*BSTGetPredecessor)(void*, DataObject*);
typedef void * (*BSTGetNRemovePredecessor)(void*, DataObject*, void*);
typedef void * (*BSTRemovePredecessor)(void*, DataObject*, void*);
typedef void * (*BSTGetSuccessor)(void*, DataObject*);
typedef void * (*BSTGetNRemoveSuccessor)(void*, DataObject*, void*);
typedef void * (*BSTRemoveSuccessor)(void*, DataObject*, void*);

typedef void (*BSTPreOrderMap)(void*, MapFun, void*);
typedef void (*BSTInOrderMap)(void*, MapFun, void*);
typedef void (*BSTPostOrderMap)(void*, MapFun, void*);
typedef void (*BSTBreadthMap)(void*, MapFun, void*);
typedef void (*BSTPreOrderFold)(void*, FoldFun, void*, void*);
typedef void (*BSTInOrderFold)(void*, FoldFun, void*, void*);
typedef void (*BSTPostOrderFold)(void*, FoldFun, void*, void*);
typedef void (*BSTBreadthFold)(void*, FoldFun, void*, void*);

/* ************************************************************************** */

typedef struct BSTType
{
    BSTDestruct bst_Destruct;

    BSTClone bst_Clone;

    BSTEqual bst_Equal;

    BSTExists bst_Exists;

    BSTInsert bst_Insert;
    BSTRemove bst_Remove;

    BSTGetMin bst_GetMin;
    BSTGetNRemoveMin bst_GetNRemoveMin;
    BSTRemoveMin bst_RemoveMin;
    BSTGetMax bst_GetMax;
    BSTGetNRemoveMax bst_GetNRemoveMax;
    BSTRemoveMax bst_RemoveMax;

    BSTGetPredecessor bst_GetPredecessor;
    BSTGetNRemovePredecessor bst_GetNRemovePredecessor;
    BSTRemovePredecessor bst_RemovePredecessor;
    BSTGetSuccessor bst_GetSuccessor;
    BSTGetNRemoveSuccessor bst_GetNRemoveSuccessor;
    BSTRemoveSuccessor bst_RemoveSuccessor;

    BSTPreOrderMap bst_PreOrderMap;
    BSTInOrderMap bst_InOrderMap;
    BSTPostOrderMap bst_PostOrderMap;
    BSTBreadthMap bst_BreadthMap;
    BSTPreOrderFold bst_PreOrderFold;
    BSTInOrderFold bst_InOrderFold;
    BSTPostOrderFold bst_PostOrderFold;
    BSTBreadthFold bst_BreadthFold;

} BSTType;

typedef struct BSTObject
{
  BSTNode* root;
  int size;
  BSTType* type;

} BSTObject;

/* ************************************************************************** */

BSTObject * bstConstruct(BSTType* type);
void bstDestruct(BSTObject* tree);

bool bstEmpty(BSTObject* tree);

int bstSize(BSTObject* tree);

void bstClear(BSTObject* tree);

BSTObject *  bstClone(BSTObject* tree);

bool bstEqual(BSTObject* tree, BSTObject* treex);

bool bstExists(BSTObject* tree, DataObject* elem);

void * bstInsert(BSTObject* tree, DataObject* elem);
void * bstRemove(BSTObject* tree, DataObject* elem);

DataObject * bstGetMin(BSTObject* tree);
DataObject * bstGetNRemoveMin(BSTObject* tree);
void * bstRemoveMin(BSTObject* tree);
DataObject * bstGetMax(BSTObject* tree);
DataObject * bstGetNRemoveMax(BSTObject* tree);
void bstRemoveMax(BSTObject* tree);

void * bstGetPredecessor(BSTObject* tree, DataObject* elem);
DataObject * bstGetNRemovePredecessor(BSTObject* tree, DataObject* elem);
void bstRemovePredecessor(BSTObject* tree, DataObject* elem);
void * bstGetSuccessor(BSTObject* tree, DataObject* elem);
DataObject * bstGetNRemoveSuccessor(BSTObject* tree, DataObject* elem);
void bstRemoveSuccessor(BSTObject* tree, DataObject* elem);

void bstPreOrderMap(BSTObject* tree, MapFun fun, void* par);
void bstInOrderMap(BSTObject* tree, MapFun fun, void* par);
void bstPostOrderMap(BSTObject* tree, MapFun fun, void* par);
void bstBreadthMap(BSTObject* tree, MapFun fun, void* par);
void bstPreOrderFold(BSTObject* tree, FoldFun fun, void* accum, void* par);
void bstInOrderFold(BSTObject* tree, FoldFun fun, void* accum, void* par);
void bstPostOrderFold(BSTObject* tree, FoldFun fun, void* accum, void* par);
void bstBreadthFold(BSTObject* tree, FoldFun fun, void* accum, void* par);

/* ************************************************************************** */

#endif
