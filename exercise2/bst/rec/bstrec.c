
#include "bstrec.h"
#include "queue/queue.h"
#include "queue/lst/queuelst.h"
#include "queue/vec/queuevec.h"
#include "adt/ptr/adtptr.h"

/* ************************************************************************** */

BSTType * ConstructBSTRecursive()
{
    BSTType * type = (BSTType*)malloc(sizeof(BSTType));

    type->bst_Destruct = &bstDestructRec;

    type->bst_Clone = &bstCloneRec;

    type->bst_Equal = &bstEqualRec;

    type->bst_Exists = &bstExistsRec;

    type->bst_Insert = &bstInsertRec;

    type->bst_Remove = &bstRemoveRec;

    type->bst_PreOrderMap = &bstPreOrderMapRec;
    type->bst_InOrderMap = &bstInOrderMapRec;
    type->bst_PostOrderMap = &bstPostOrderMapRec;
    type->bst_BreadthMap = bstBreadthMapRec;

    type->bst_GetMin = &bstGetMinRec;
    type->bst_GetNRemoveMin = &bstGetNRemoveMinRec;
    type->bst_RemoveMin = &bstRemoveMinRec;

    type->bst_GetMax = &bstGetMaxRec;
    type->bst_GetNRemoveMax = &bstGetNRemoveMaxRec;
    type->bst_RemoveMax = &bstRemoveMaxRec;

    type->bst_GetPredecessor = &bstGetPredecessorRec;
    type->bst_GetNRemovePredecessor = &bstGetNRemovePredecessorRec;
    type->bst_RemovePredecessor = &bstRemovePredecessorRec;

    type->bst_GetSuccessor = &bstGetSuccessorRec;
    type->bst_GetNRemoveSuccessor = &bstGetNRemoveSuccessorRec;
    type->bst_RemoveSuccessor = &bstRemoveSuccessorRec;

    type->bst_PreOrderFold = &bstPreOrderFoldRec;
    type->bst_InOrderFold = &bstInOrderFoldRec;
    type->bst_PostOrderFold = &bstPostOrderFoldRec;
    type->bst_BreadthFold = &bstBreadthFoldRec;

    return type;

}

void DestructBSTRecursive(BSTType* type) {
    free(type);
}

/* ************************************************************************** */

void bstDestructRec(void* treeroot)
{
    BSTNode* root = (BSTNode*)treeroot;

    if(root != NULL) {

        bstDestructRec(root->LeftPtr);
        bstDestructRec(root->RightPtr);
        adtDestruct(root->data);
        free(root);
    }
}

/* ************************************************************************** */

void *  bstCloneRec(void* treeroot)
{
    BSTNode * root = (BSTNode*)treeroot;

    if(root == NULL){
        return NULL;
    }

    BSTNode * newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->data = adtClone(root->data);
    newNode->LeftPtr = bstCloneRec(root->LeftPtr);
    newNode->RightPtr = bstCloneRec(root->RightPtr);


    return newNode;
}

/* ************************************************************************** */


bool bstEqualRec(void* treeroot, void* treerootx)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* rootx = (BSTNode*)treerootx;

    if(root == NULL && rootx== NULL) {
        return true;
    }
    if(root == NULL || rootx==NULL){
        return false;
    }
    if( adtCompare(root->data, rootx->data)==0){
        if((bstEqualRec(root->LeftPtr, rootx->LeftPtr)) && (bstEqualRec(root->RightPtr, rootx->RightPtr))) {
            return true;
        }
    }
    return false;
}

/* ************************************************************************** */

bool bstExistsRec(void* treeroot, DataObject* elem)
{
    BSTNode* root = (BSTNode*)treeroot;

    if(root==NULL){
        return false;
    }
    if(adtCompare(root->data, elem)==0){
        return true;
    }
    if(adtCompare(root->data, elem) > 0){
        return bstExistsRec(root->LeftPtr, elem);
    }
    return bstExistsRec(root->RightPtr, elem);
}

/* ************************************************************************** */

void * bstInsertRec(void* treeroot, DataObject* elem, int* size) {
    assert(elem);
    BSTNode * root = (BSTNode*)treeroot;

    if(root == NULL ){
        BSTNode * newNode = (BSTNode *) malloc(sizeof(BSTNode));
        newNode->data = adtClone(elem);

        newNode->LeftPtr = newNode->RightPtr = NULL;
        root = newNode;
        *((int*)size) = *((int*)size)+1;
    } else {
        if (adtCompare(root->data, elem) > 0) {
            root->LeftPtr = bstInsertRec(root->LeftPtr, elem, size);


        } else if (adtCompare(root->data, elem) < 0) {
            root->RightPtr = bstInsertRec(root->RightPtr, elem, size);

        } else {
            printf("Elemento gia' esistente\n");
        }

    }

    return root;
}

/* ************************************************************************** */

void * bstRemoveRec(void* treeroot, DataObject* elem )
{
    BSTNode * root = (BSTNode*)treeroot;

    if(root == NULL){
        printf("Albero vuoto\n");
    } else if(adtCompare(root->data, elem) > 0){
        root->LeftPtr = bstRemoveRec(root->LeftPtr, elem);
    } else if(adtCompare(root->data, elem) < 0){
        root->RightPtr = bstRemoveRec(root->RightPtr, elem);
    } else {
      //se il nodo da togliere non ha figli
      if(root->LeftPtr == NULL && root->RightPtr == NULL){
          adtDestruct(root->data);
          free(root);
          root = NULL;
      }
      //se il nodo ha un figlio
      else if(root->LeftPtr == NULL){
        BSTNode * tmp = root;
        root = root->RightPtr;
        free(tmp);
    } else if(root->RightPtr == NULL){
      BSTNode * tmp = root;
      root = root->LeftPtr;
      free(tmp);
      }
      // se il nodo da 2 figli
      else {
          BSTNode* tmp = bstGetMinRec(root->RightPtr);
          root->data = tmp->data;
          root->RightPtr = bstRemoveRec(root->RightPtr, tmp->data);
      }
    }

    return root;
}

/* ************************************************************************** */

void * bstGetMinRec(void* treeroot)
{
    BSTNode * root = (BSTNode*)treeroot;

    if(root == NULL){
        printf("Albero vuoto\n");
        return NULL;
    } else if(root->LeftPtr == NULL){
        return root->data;
    }
    return bstGetMinRec(root->LeftPtr);

}

/* ************************************************************************** */

void * bstGetNRemoveMinRec(void* treeroot, void * prenode)
{
    BSTNode * root = (BSTNode*)treeroot;
    BSTNode * pred = (BSTNode*)prenode;

    if(root == NULL){
        return NULL;
    } else if (root->LeftPtr != NULL ) {
       return bstGetNRemoveMinRec(root->LeftPtr, root);
    } if(root->LeftPtr && root->RightPtr && pred == NULL){
            pred = root;
            root = root->RightPtr;
            return pred;
        } else if(root == pred->LeftPtr){
            pred->LeftPtr = root->RightPtr;
        } else {
        pred->RightPtr = root->RightPtr;
    }
    return root;
}

/* ************************************************************************** */

void * bstRemoveMinRec(void* treeroot, void * prenode)
{
    BSTNode * root = (BSTNode*)treeroot;
    BSTNode * pred = (BSTNode*)prenode;

    if(root ==NULL){
        return NULL;
    } else if (root->LeftPtr != NULL ) {
       return bstRemoveMinRec(root->LeftPtr, root);
    } if(root->LeftPtr && root->RightPtr && pred == NULL){
        pred = root;
        root = root->RightPtr;
        return pred;
    } else if(root == pred->LeftPtr){
        pred->LeftPtr = root->RightPtr;
    } else {
        pred->RightPtr = root->RightPtr;
    }
    return root->data;
}


/* ************************************************************************** */

void * bstGetNRemoveMaxRec(void* treeroot, void*prenode)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* pred = (BSTNode*)prenode;
    BSTNode* max = NULL;

    if(root == NULL) {
        printf("Albero vuoto\n");
        return NULL;
    }
        if(root->RightPtr!= NULL) {
            return bstGetNRemoveMaxRec(root->RightPtr, root);
        } else if(root== pred->RightPtr){
            pred->RightPtr=root->LeftPtr;
        }else{
            pred->LeftPtr=root->LeftPtr;
        }
        return  root;
    }



/* ************************************************************************** */

void * bstRemoveMaxRec(void* treeroot, void* prenode)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* pred = (BSTNode*)prenode;


    if(root == NULL) {
        printf("Albero vuoto\n");
        return NULL;
    }
    if(root->RightPtr!= NULL) {
        return bstRemoveMaxRec(root->RightPtr, root);
    } else if(root== pred->RightPtr){
        pred->RightPtr=root->LeftPtr;
    }else{
        pred->LeftPtr=root->LeftPtr;
    }
    return root;
}

/* ************************************************************************** */

void * bstGetMaxRec(void* treeroot)
{
    BSTNode * root = (BSTNode*)treeroot;

    if(root == NULL){
        printf("Albero vuoto\n");
        return NULL;
    } else if(root->RightPtr == NULL ) {
        return root->data;

    } else return bstGetMaxRec(root->RightPtr);
}

/* ************************************************************************** */

void * bstGetPredecessorRec(void* treeroot, DataObject* elem)
{
    BSTNode* pred = NULL;
    BSTNode* root = (BSTNode*)treeroot;

    if(root != NULL) {
        if (adtCompare(root->data, elem)==0) {
            if (root->LeftPtr != NULL) {
                pred = bstGetMaxRec(root->LeftPtr);
            }
        } else if (adtCompare(root->data, elem) > 0) {
            pred = bstGetPredecessorRec(root->LeftPtr, elem);


        } else if(adtCompare(root->data, elem) < 0){
            pred = bstGetPredecessorRec(root->RightPtr, elem);
            if (pred == NULL) {
                pred = root;
            }
        }
    }

    return pred;
}

/* ************************************************************************** */

void * bstGetNRemovePredecessorRec(void* treeroot, DataObject* elem, void* prenode) {

    BSTNode *pred=NULL;
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* ancestor = (BSTNode*)prenode;

    if(root != NULL){
        if(adtCompare(root->data , elem) == 0){
            if(root->LeftPtr!=NULL){

                pred=bstGetNRemoveMaxRec(root->LeftPtr , root);
                return  pred;
            }
        }
        if( adtCompare(root->data , elem) >0 ){
            pred=bstGetNRemovePredecessorRec(root->LeftPtr , elem , root);
        }
        if(adtCompare(root->data  , elem) <0 ){
            pred=bstGetNRemovePredecessorRec(root->RightPtr , elem , root);
            if( pred==NULL) {
                pred = root;

                BSTNode *toRemove = pred;

                if (ancestor == NULL){
                    BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                    ret->data=adtConstruct(pred->data->type);

                    toRemove=bstGetNRemoveMinRec(pred->RightPtr, pred);
                    ret->data = pred->data;
                    pred->data = toRemove->data;
                    return  ret;
                } else {
                    if (pred->RightPtr == NULL) {

                        if (ancestor->RightPtr == pred) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->RightPtr;
                        }
                    } else if (pred->LeftPtr == NULL) {

                        if (ancestor->RightPtr == pred) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->RightPtr;
                        }
                    } else {
                        BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                        ret->data=adtConstruct(pred->data->type);

                        toRemove=bstGetNRemoveMinRec(pred->RightPtr , pred);
                        ret->data = pred->data;
                        pred->data = toRemove->data;
                        return  ret;
                    }
                }
            }
        }
    }

    return pred;
}

/* ************************************************************************** */

void * bstRemovePredecessorRec(void* treeroot, DataObject* elem, void* prenode)
{
    BSTNode *pred=NULL;
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* ancestor = (BSTNode*)prenode;

    if(root != NULL){
        if(adtCompare(root->data , elem) == 0){
            if(root->LeftPtr!=NULL){

                pred=bstGetNRemoveMaxRec(root->LeftPtr , root);
                return  pred;
            }
        }
        if( adtCompare(root->data , elem) >0 ){
            pred=bstRemovePredecessorRec(root->LeftPtr , elem , root);
        }
        if(adtCompare(root->data  , elem) <0 ){
            pred=bstRemovePredecessorRec(root->RightPtr , elem , root);
            if( pred==NULL) {
                pred = root;


                BSTNode *toRemove = pred;

                if (ancestor == NULL){
                    BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                    ret->data=adtClone(pred->data);

                    toRemove=bstGetNRemoveMinRec(pred->RightPtr , pred);
                    ret->data = pred->data;
                    pred->data = toRemove->data;
                    return  ret;
                } else {
                    if (pred->RightPtr == NULL) {

                        if (ancestor->RightPtr == pred) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->RightPtr;
                        }
                    } else if (pred->LeftPtr == NULL) {

                        if (ancestor->RightPtr == pred) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->RightPtr;
                        }
                    } else {
                        BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                        ret->data=adtClone(pred->data);

                        toRemove=bstGetNRemoveMinRec(pred->RightPtr , pred);
                        ret->data = pred->data;
                        pred->data = toRemove->data;
                        return  ret;
                    }


                }

            }
        }

    }


    return pred;
}

/* ************************************************************************** */

void * bstGetNRemoveSuccessorRec(void* treeroot, DataObject* elem, void* prenode)
{

    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* ancestor = (BSTNode*)prenode;
    BSTNode *next=NULL;
    if(root != NULL) {
        if (adtCompare(root->data, elem)==0) {
            if (root->RightPtr != NULL) {
                next = bstGetNRemoveMinRec(root->RightPtr , root);
                return  next;
            }
        }
        if (adtCompare(root->data, elem) > 0){

            next = bstGetNRemoveSuccessorRec(root->LeftPtr, elem , root);
            if (next == NULL) {
                next = root;

                BSTNode *toRemove = next;
                if (ancestor == NULL){
                    BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                    ret->data=adtClone(next->data);

                    toRemove=bstGetNRemoveMinRec(next->RightPtr , next);

                    ret->data = next->data;
                    next->data = toRemove->data;

                    return  ret;
                } else {
                    if (next->RightPtr == NULL) {

                        if (ancestor->RightPtr == next) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->LeftPtr;
                        }
                    } else if (next->LeftPtr == NULL) {

                        if (ancestor->RightPtr == next) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->RightPtr;
                        }
                    } else {
                        BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                        ret->data=adtClone(next->data);

                        toRemove=bstGetNRemoveMinRec(next->RightPtr , next);

                        next->data = toRemove->data;
                        return  ret;
                    }
                }

            }
        }
        if(adtCompare(root->data , elem) <0) {
            next = bstGetNRemoveSuccessorRec(root->RightPtr, elem , root);
        }
    }
    return next;

}


/* ************************************************************************** */

void * bstRemoveSuccessorRec(void* treeroot, DataObject* elem, void* prenode)
{

    BSTNode *next=NULL;
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* ancestor = (BSTNode*)prenode;

    if(root != NULL){
        if(adtCompare(root->data , elem) == 0){
            if(root->LeftPtr!=NULL){

                next=bstGetNRemoveMinRec(root->LeftPtr , root);
                return  next;
            }
        }
        if( adtCompare(root->data , elem) < 0 ){
            next=bstGetNRemoveSuccessorRec(root->RightPtr , elem , root);
        }
        if(adtCompare(root->data  , elem) > 0 ){
            next=bstGetNRemoveSuccessorRec(root->LeftPtr , elem , root);
            if( next==NULL) {
                next = root;


                BSTNode *toRemove = next;

                if (ancestor == NULL){
                    BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                    ret->data=adtConstruct(next->data->type);

                    toRemove=bstGetNRemoveMinRec(next->RightPtr , next);
                    ret->data = next->data;

                    next->data = toRemove->data;
                    return  ret;
                } else {
                    if (next->RightPtr == NULL) {

                        if (ancestor->RightPtr == next) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->LeftPtr;
                        }
                    } else if (next->LeftPtr == NULL) {

                        if (ancestor->RightPtr == next) {
                            ancestor->RightPtr = toRemove->RightPtr;
                        } else {
                            ancestor->LeftPtr = toRemove->RightPtr;
                        }
                    } else {
                        BSTNode *ret=( BSTNode *) malloc(sizeof(BSTNode));
                        ret->data=adtConstruct(next->data->type);

                        toRemove=bstGetNRemoveMinRec(next->RightPtr , next);
                        ret->data = next->data;
                        next->data = toRemove->data;
                        return  ret;
                    }


                }

            }
        }

    }

    return next;
}

/* ************************************************************************** */

void * bstGetSuccessorRec(void* treeroot, DataObject* elem)
{
    BSTNode* succ = NULL;
    BSTNode* root = (BSTNode*)treeroot;

    if(root != NULL) {
        if (adtCompare(root->data, elem)==0) {
            if (root->RightPtr != NULL) {
                succ = bstGetMinRec(root->RightPtr);
            }
        } else if (adtCompare(root->data, elem) > 0) {
            succ = bstGetSuccessorRec(root->LeftPtr, elem);
            if (succ == NULL) {
                succ = root;
            }
        } else if(adtCompare(root->data, elem) < 0){
            succ = bstGetSuccessorRec(root->RightPtr, elem);


        }

    }

    return succ;
}

/* ************************************************************************** */

void bstPreOrderMapRec(void* treeroot, MapFun fun, void* par)
{
    BSTNode * root = (BSTNode*)treeroot;

    if(root != NULL){
        fun(root->data, par);
        bstPreOrderMapRec(root->LeftPtr, fun, par);
        bstPreOrderMapRec(root->RightPtr,fun,par);

    }
}

/* ************************************************************************** */

void bstInOrderMapRec(void* treeroot, MapFun fun, void* par)
{
    BSTNode * root = (BSTNode*)treeroot;

    if(root != NULL) {
        bstInOrderMapRec(root->LeftPtr, fun, par);
        fun(root->data, par);
        bstInOrderMapRec(root->RightPtr,fun, par);
    }
}

/* ************************************************************************** */

void bstPostOrderMapRec(void* treeroot, MapFun fun, void* par)
{
    BSTNode * root = (BSTNode*)treeroot;

    if(root != NULL) {
        bstPostOrderMapRec(root->LeftPtr, fun, par);
        bstPostOrderMapRec(root->RightPtr, fun, par);
        fun(root->data, par);
    }

}

/* ************************************************************************** */

void bstBreadthMapRec(void* treeroot, MapFun fun, void* par)
{
    BSTNode * root = (BSTNode*)treeroot;

    QueueType * type =  ConstructQueueLstType();
    QueueObject * queue = queConstruct(type);

    DataType* ptrType = ConstructPtrDataType();
    DataObject *ptr = adtConstruct(ptrType);

    adtSetValue(ptr,root);
    queEnqueue(queue, ptr);

    while(!queEmpty(queue)) {
        DataObject* topValue = queHeadNDequeue(queue);
        BSTNode* curr = (BSTNode*)adtGetValue(topValue);
        fun(curr->data, par);

        if(curr->LeftPtr != NULL){
            adtSetValue(ptr, curr->LeftPtr);
            queEnqueue(queue, ptr);
        }
        if(curr->RightPtr != NULL){
            adtSetValue(ptr, curr->RightPtr);
            queEnqueue(queue, ptr);
        }
    }
    queDestruct(queue);
    adtDestruct(ptr);
    DestructPtrDataType(ptrType);
}


/* ************************************************************************** */

void bstPreOrderFoldRec(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    if(root != NULL){
        fun(root->data, accum, par);
        bstPreOrderFoldRec(root->LeftPtr, fun, accum, par);
        bstPreOrderFoldRec(root->RightPtr, fun, accum, par);
    }
}

/* ************************************************************************** */

void bstInOrderFoldRec(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    if(root != NULL){
        bstInOrderFoldRec(root->LeftPtr, fun, accum, par);
        fun(root->data, accum, par);
        bstInOrderFoldRec(root->RightPtr, fun, accum, par);
    }
}

/* ************************************************************************** */

void bstPostOrderFoldRec(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    if(root != NULL){
        bstPostOrderFoldRec(root->LeftPtr, fun, accum, par);
        bstPostOrderFoldRec(root->RightPtr, fun, accum, par);
        fun(root->data, accum, par);
    }
}

/* ************************************************************************** */

void bstBreadthFoldRec(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode * root = (BSTNode*)treeroot;

    QueueType * type =  ConstructQueueLstType();
    QueueObject * queue = queConstruct(type);

    DataType* ptrType = ConstructPtrDataType();
    DataObject *ptr = adtConstruct(ptrType);

    adtSetValue(ptr,root);
    queEnqueue(queue, ptr);

    while(!queEmpty(queue)) {
        DataObject* topValue = queHeadNDequeue(queue);
        BSTNode* curr = (BSTNode*)adtGetValue(topValue);
        fun(curr->data, accum, par);

        if(curr->LeftPtr != NULL){
            adtSetValue(ptr, curr->LeftPtr);
            queEnqueue(queue, ptr);
        }

        if(curr->RightPtr != NULL){
            adtSetValue(ptr, curr->RightPtr);
            queEnqueue(queue, ptr);
        }
    }

    queDestruct(queue);
    adtDestruct(ptr);
    DestructPtrDataType(ptrType);
}

/* ************************************************************************** */