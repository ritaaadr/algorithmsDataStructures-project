
#ifndef BSTITR_H
#define BSTITR_H

/* ************************************************************************** */

#include "../bst.h"


/* ************************************************************************** */

BSTType* ConstructBSTIterative();
void DestructBSTIterative(BSTType* type);

/* ************************************************************************** */

void bstDestructItr(void* treeroot);

void *  bstCloneItr(void* treeroot);

bool bstEqualItr(void* treeroot, void* treerootx);

bool bstExistsItr(void* treeroot, DataObject* elem);

void * bstInsertItr(void* treeroot, DataObject* elem, int* size);

void * bstRemoveItr(void* treeroot, DataObject* elem );

void bstPreOrderMapItr(void* treeroot, MapFun fun,  void* par);

void * RemoveRoot(void* treeroot);

void * bstGetMinItr(void* treeroot);
void * GetNRemoveMinItr(void * treeroot , void * treefather);
void * bstRemoveMinItr(void* treeroot, void * treefather);
void * bstGetMaxItr(void* treeroot);
void * GetNRemoveMaxItr(void * treeroot , void * treefather);
void * bstRemoveMaxItr(void* treeroot, void* prenode);

void * bstGetPredecessorItr(void* treeroot, DataObject* elem);
void * bstGetNRemovePredecessorItr(void* treeroot, DataObject* elem, void* prenode);
void * bstRemovePredecessorItr(void* treeroot, DataObject* elem, void* prenode);
void * bstGetSuccessorItr(void* treeroot, DataObject* elem);
void * bstGetNRemoveSuccessorItr(void* treeroot, DataObject* elem, void* prenode);
void * bstRemoveSuccessorItr(void* treeroot, DataObject* elem, void* prenode);

void bstPreOrderMapItr(void* treeroot, MapFun fun, void* par);
void bstInOrderMapItr(void* treeroot, MapFun fun, void* par);
void bstPostOrderMapItr(void* treeroot, MapFun fun, void* par);
void bstBreadthMapItr(void* treeroot, MapFun fun, void* par);

void bstPreOrderFoldItr(void* treeroot, FoldFun fun, void* accum, void* par);
void bstInOrderFoldItr(void* treeroot, FoldFun fun, void* accum, void* par);
void bstPostOrderFoldItr(void* treeroot, FoldFun fun, void* accum, void* par);
void bstBreadthFoldItr(void* treeroot, FoldFun fun, void* accum, void* par);

void* bstGetDataItr(void* roott, DataObject* elemToFind);

#endif
