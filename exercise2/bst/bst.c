
#include "bst.h"
#include "queue/queue.h"
#include "queue/lst/queuelst.h"
#include "queue/vec/queuevec.h"

/* ************************************************************************** */

//funzione che mi alloca un albero vuoto
BSTObject * bstConstruct(BSTType* type)
{
    BSTObject * tree = (BSTObject*)malloc(sizeof(BSTObject));

    tree->root = NULL;
    tree->size = 0;
    tree->type = type;

    return tree;
}

/* ************************************************************************** */

void bstDestruct(BSTObject* tree)
{
    assert(tree);

    if(tree->root) {
        tree->type->bst_Destruct(tree->root);
    }
    free(tree);
}

/* ************************************************************************** */

bool bstEmpty(BSTObject* tree)
{
    assert(tree);

    return tree->size == 0;
}

/* ************************************************************************** */

int bstSize(BSTObject* tree)
{
    assert(tree);

    return tree->size;
}

/* ************************************************************************** */

void bstClear(BSTObject* tree)
{
    assert(tree);
    assert(!bstEmpty(tree));
    assert(tree->root);

    if(tree->root != NULL){
        tree->type->bst_Destruct(tree->root);
        tree->size = 0;
        tree->root = NULL;
    }
}

/* ************************************************************************** */

BSTObject *  bstClone(BSTObject* tree)
{
    assert(tree);

    BSTObject * TreeClone = (BSTObject*)malloc(sizeof(BSTObject));
    TreeClone->type = tree->type;
    TreeClone->size = tree->size;
    TreeClone->root = tree->type->bst_Clone(tree->root);

    return TreeClone;
}

/* ************************************************************************** */

bool bstEqual(BSTObject* tree, BSTObject* treex)
{
    assert(tree);
    assert(treex);

    if(tree->size != treex->size || tree->type != treex->type) {
        return false;
    }

    return tree->type->bst_Equal(tree->root, treex->root);
}

/* ************************************************************************** */

bool bstExists(BSTObject* tree, DataObject* elem)
{
    assert(tree);
    assert(elem);

    return tree->type->bst_Exists(tree->root, elem);
}

/* ************************************************************************** */

void * bstInsert(BSTObject* tree, DataObject* elem)
{
    if (elem != NULL) {
        tree->root = tree->type->bst_Insert(tree->root, elem, &tree->size);
    } else {
        printf("Impossibile inserire: elemento non esistente\n");
    }
    return tree;
}

/* ************************************************************************** */

void * bstRemove(BSTObject* tree, DataObject* elem )
{
    assert(tree);

    if(!bstExists(tree, elem)){
        printf("Elemento da rimuovere non presente in struttura\n");
    } else {
        if(elem != NULL && tree->root != NULL) {
            tree->type->bst_Remove(tree->root, elem);
            tree->size--;
        }
    }

    return tree;
}

/* ************************************************************************** */

DataObject * bstGetMin(BSTObject* tree)
{
    assert(tree);

    if(!bstEmpty(tree)) {
        return tree->type->bst_GetMin(tree->root);
    }
    return NULL;
}

/* ************************************************************************** */

DataObject * bstGetNRemoveMin(BSTObject* tree)
{
    assert(tree);
    DataObject* ret = NULL;

    if(tree->size==1) {
        ret = tree->root->data;
        free(tree->root);
    } else if(tree->root->LeftPtr == NULL && tree->root->RightPtr != NULL) {
        BSTNode* tmp = tree->root;
        tree->root = tree->root->RightPtr;
        ret = tmp->data;
        free(tmp);
    } else if(!bstEmpty(tree)){
        ret = tree->type->bst_GetNRemoveMin(tree->root, NULL);
    }

    tree->size--;

    if(ret != NULL) {
        return ret->value;
    }
    else return NULL;
}

/* ************************************************************************** */

void * bstRemoveMin(BSTObject* tree)
{
    assert(tree);

    if(tree->size == 0){
        return NULL;
    }
    if(tree->size==1){
        adtDestruct(tree->root->data);
        free(tree->root);
        tree->root = NULL;
    } else if(tree->root->LeftPtr == NULL && tree->root->RightPtr!=NULL) {
        BSTNode* tmp = tree->root;
        tree->root = tree->root->RightPtr;
        adtDestruct(tmp->data);
        free(tmp);
    } else if(!bstEmpty(tree)) {
        tree->type->bst_RemoveMin(tree->root, NULL);
    }
    tree->size--;
    return tree;

}

/* ************************************************************************** */

DataObject * bstGetMax(BSTObject* tree)
{
    assert(tree);

    if(!bstEmpty(tree)) {
        return tree->type->bst_GetMax(tree->root);
    }
    return NULL;
}

/* ************************************************************************** */

DataObject * bstGetNRemoveMax(BSTObject* tree)
{
    assert(tree);
    DataObject* ret = NULL;

    if(tree->size==1){
        ret = tree->root->data;
        free(tree->root);
    } else if(tree->root->RightPtr == NULL && tree->root->LeftPtr!=NULL) {
        BSTNode* tmp = tree->root;
        tree->root = tree->root->LeftPtr;
        ret = tmp->data;
        free(tmp);
    } else if(!bstEmpty(tree)) {
        tree->size--;
        ret = tree->type->bst_GetNRemoveMax(tree->root, NULL);
    }

    tree->size--;

    if(ret != NULL) {
        return ret->value;
    }
    else return NULL;
}

/* ************************************************************************** */

void bstRemoveMax(BSTObject* tree)
{
    assert(tree);
    DataObject* ret = NULL;

        if (tree->size == 1) {
            adtDestruct(tree->root->data);
            free(tree->root);
            tree->root = NULL;
        } else if (tree->root->RightPtr == NULL && tree->root->LeftPtr != NULL) {
            BSTNode *tmp = tree->root;
            tree->root = tree->root->LeftPtr;
            ret = tmp->data;
            free(tmp);
        } else if (!bstEmpty(tree)) {
            tree->type->bst_GetNRemoveMax(tree->root, NULL);
         }
    tree->size--;
}

/* ************************************************************************** */

void * bstGetPredecessor(BSTObject* tree, DataObject* elem)
{
    assert(tree);

    if(tree->size == 1){
        if(adtCompare(tree->root->data, elem) < 0){
            return tree->root->data;
        } else {
            return NULL;
        }
    } else if(!bstEmpty(tree)){
        DataObject* ret = tree->type->bst_GetPredecessor(tree->root, elem);
        if(ret != NULL) {
            return adtClone(ret);
        }
    }
    return NULL;
}

/* ************************************************************************** */

DataObject * bstGetNRemovePredecessor(BSTObject* tree, DataObject* elem)
{
    assert(tree);

    if(tree->size == 1){
        if(adtCompare(tree->root->data, elem) < 0){
            tree->size--;
            DataObject* ret = adtClone(tree->root->data);
            adtDestruct(tree->root->data);
            free(tree->root);
            return ret;
        }
    } else if(!bstEmpty(tree)){
        BSTNode* tmp = tree->type->bst_GetNRemovePredecessor(tree->root, elem, NULL);

        if(tmp != NULL) {
            tree->size--;
            return tmp->data;
        } else printf("Non trovato\n");
    }
    return NULL;
}

/* ************************************************************************** */

void bstRemovePredecessor(BSTObject* tree, DataObject* elem)
{
    assert(tree);

    if(tree->size == 1){
        if(adtCompare(tree->root->data, elem) < 0) {
            tree->size--;
            adtDestruct(tree->root->data);
            free(tree->root);
        } else printf("Elemento non trovato\n");
    } else if(!bstEmpty(tree)){
        tree->type->bst_RemovePredecessor(tree->root, elem, NULL);
        tree->size--;
    }
}

/* ************************************************************************** */

void * bstGetSuccessor(BSTObject* tree, DataObject* elem)
{
    assert(tree);

    if(tree->size == 1){
        if(adtCompare(tree->root->data, elem) > 0) {
            return tree->root->data;
        } else if(adtCompare(tree->root->data, elem) < 0) {
            return NULL;
        }
    } else if(!bstEmpty(tree)){
        //if(bstExists(tree, elem)) {
            DataObject* ret = tree->type->bst_GetSuccessor(tree->root, elem);
            if(ret != NULL) {
                return adtClone(ret);
            }
        //} else return NULL;
    }
    return NULL;
}

/* ************************************************************************** */

DataObject * bstGetNRemoveSuccessor(BSTObject* tree, DataObject* elem)
{
    assert(tree);

    if(tree->size == 1){
        if(adtCompare(tree->root->data, elem)>0){
            tree->size--;
            DataObject* ret = adtClone(tree->root->data);
            adtDestruct(tree->root->data);
            free(tree->root);
            return ret;
        }
    } else if(!bstEmpty(tree)){
        BSTNode* tmp = tree->type->bst_GetNRemoveSuccessor(tree->root, elem, NULL);
        if(tmp != NULL) {
            tree->size--;
            return tmp->data;
        } else printf("Non trovato\n");
    }
    return NULL;
}

/* ************************************************************************** */

void bstRemoveSuccessor(BSTObject* tree, DataObject* elem)
{
    assert(tree);

    if(tree->size == 1) {
        if (adtCompare(tree->root->data, elem) > 0) {
            tree->size--;
            adtDestruct(tree->root->data);
            free(tree->root);
        } else printf("Elemento non presente\n");
    } else if(!bstEmpty(tree)){
        tree->type->bst_RemoveSuccessor(tree->root, elem, NULL);
        tree->size--;
    }
}

/* ************************************************************************** */

void bstPreOrderMap(BSTObject* tree, MapFun fun, void* par)
{
    assert(tree);

    if(!bstEmpty(tree)){
        tree->type->bst_PreOrderMap(tree->root, fun, par);
    } else {
        printf("Albero vuoto\n");
    }
}

/* ************************************************************************** */

void bstInOrderMap(BSTObject* tree, MapFun fun, void* par)
{
    assert(tree);
    assert(tree->root);

    tree->type->bst_InOrderMap(tree->root, fun, par);
}

/* ************************************************************************** */

void bstPostOrderMap(BSTObject* tree, MapFun fun, void* par)
{
    assert(tree);
    assert(tree->root);

    tree->type->bst_PostOrderMap(tree->root, fun, par);
}

/* ************************************************************************** */

void bstBreadthMap(BSTObject* tree, MapFun fun, void* par)
{
    assert(tree);
    assert(tree->root);

    tree->type->bst_BreadthMap(tree->root, fun, par);
}

/* ************************************************************************** */

void bstPreOrderFold(BSTObject* tree, FoldFun fun, void* accum, void* par)
{
    assert(tree);
    assert(tree->root);

    tree->type->bst_PreOrderFold(tree->root, fun, accum, par);
}

/* ************************************************************************** */

void bstInOrderFold(BSTObject* tree, FoldFun fun, void* accum, void* par)
{
    assert(tree);
    assert(tree->root);

    tree->type->bst_InOrderFold(tree->root, fun, accum, par);
}

/* ************************************************************************** */

void bstPostOrderFold(BSTObject* tree, FoldFun fun, void* accum, void* par)
{
    assert(tree);
    assert(tree->root);

    tree->type->bst_PostOrderFold(tree->root, fun, accum, par);
}

/* ************************************************************************** */

void bstBreadthFold(BSTObject* tree, FoldFun fun, void* accum, void* par)
{
    assert(tree);
    assert(tree->root);

    tree->type->bst_BreadthFold(tree->root, fun, accum, par);
}

/* ************************************************************************** */
