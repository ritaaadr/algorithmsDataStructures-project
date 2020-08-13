
#ifndef BSTREC_H
#define BSTREC_H

/* ************************************************************************** */

#include "../bst.h"

/* ************************************************************************** */

BSTType * ConstructBSTRecursive();
void DestructBSTRecursive(BSTType* type);

/* ************************************************************************** */

void bstDestructRec(void* treeroot);

void *  bstCloneRec(void* treeroot);

bool bstEqualRec(void* treeroot, void* treerootx);

bool bstExistsRec(void* treeroot, DataObject* elem);

void * bstInsertRec(void* treeroot, DataObject* elem, int* size);

void * bstRemoveRec(void* treeroot, DataObject* elem );

void * bstGetMinRec(void* treeroot);
void * bstGetNRemoveMinRec(void* treeroot, void* prenode);
void * bstRemoveMinRec(void* treeroot, void* treefather);
void * bstGetMaxRec(void* treeroot);
void * bstGetNRemoveMaxRec(void* treeroot, void* prenode);
void * bstRemoveMaxRec(void* treeroot, void* prenode);

void * bstGetPredecessorRec(void* treeroot, DataObject* elem);
void * bstGetNRemovePredecessorRec(void* treeroot, DataObject* data, void* prenode);
void * bstRemovePredecessorRec(void* treeroot, DataObject* elem, void* prenode);
void * bstGetSuccessorRec(void* treeroot, DataObject* elem);
void * bstGetNRemoveSuccessorRec(void* treeroot, DataObject* elem, void* prenode);
void * bstRemoveSuccessorRec(void* treeroot, DataObject* elem, void* prenode);

void bstPreOrderMapRec(void* treeroot, MapFun fun, void* par);
void bstInOrderMapRec(void* treeroot, MapFun fun, void* par);
void bstPostOrderMapRec(void* treeroot, MapFun fun, void* par);
void bstBreadthMapRec(void* treeroot, MapFun fun, void* par);

void bstPreOrderFoldRec(void* treeroot, FoldFun fun, void* accum, void* par);
void bstInOrderFoldRec(void* treeroot, FoldFun fun, void* accum, void* par);
void bstPostOrderFoldRec(void* treeroot, FoldFun fun, void* accum, void* par);
void bstBreadthFoldRec(void* treeroot, FoldFun fun, void* accum, void* par);

#endif
