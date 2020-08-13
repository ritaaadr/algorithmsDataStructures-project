
#include "bstitr.h"

#include "../bstitrpreord.h"
#include "../bstitrinord.h"
#include "../bstitrpostord.h"
#include "../bstitrbreadth.h"
#include "adt/adt.h"
#include "adt/ptr/adtptr.h"
/* ************************************************************************** */

BSTType* ConstructBSTIterative()
{
    BSTType* type = (BSTType*)malloc(sizeof(BSTType));

    type->bst_Destruct = &bstDestructItr;

    type->bst_Equal = &bstEqualItr;

    type->bst_Insert = &bstInsertItr;

    type->bst_Clone = &bstCloneItr;

    type->bst_Exists = &bstExistsItr;

    type->bst_Remove = &bstRemoveItr;

    type->bst_GetNRemoveMin = &GetNRemoveMinItr;
    type->bst_GetMin = &bstGetMinItr;
    type->bst_RemoveMin = &bstRemoveMinItr;
    type->bst_GetMax = &bstGetMaxItr;
    type->bst_GetNRemoveMax = &GetNRemoveMaxItr;
    type->bst_RemoveMax = &bstRemoveMaxItr;

    type->bst_GetPredecessor = &bstGetPredecessorItr;
    type->bst_GetNRemovePredecessor = &bstGetNRemovePredecessorItr;
    type->bst_RemovePredecessor = &bstRemovePredecessorItr;
    type->bst_GetSuccessor = &bstGetSuccessorItr;
    type->bst_GetNRemoveSuccessor = &bstGetNRemoveSuccessorItr;
    type->bst_RemoveSuccessor = &bstRemoveSuccessorItr;

    type->bst_PreOrderMap = &bstPreOrderMapItr;
    type->bst_PostOrderMap = &bstPostOrderMapItr;
    type->bst_InOrderMap = &bstInOrderMapItr;
    type->bst_BreadthMap = &bstBreadthMapItr;

    type->bst_PreOrderFold = &bstPreOrderFoldItr;
    type->bst_PostOrderFold = &bstPostOrderFoldItr;
    type->bst_InOrderFold = &bstInOrderFoldItr;
    type->bst_BreadthFold = &bstBreadthFoldItr;

    return type;
}

/* ************************************************************************** */

void DestructBSTIterative(BSTType* type)
{
    free(type);
}

/* ************************************************************************** */

bool bstEqualItr(void* treeroot, void* treerootx)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* rootx = (BSTNode*)treerootx;
    BSTNode* node = NULL;
    BSTNode* nodex = NULL;

    ITRType* itrType = ConstructBSTPreOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);

    ITRObject* iterx = itrConstruct(itrType, rootx);

    while(!itrTerminated(iter) && !itrTerminated(iterx)){
        node = (BSTNode*)itrElement(iter);
        nodex = (BSTNode*)itrElement(iterx);
        if(adtCompare(node->data, nodex->data) != 0){
            return false;
        }
        itrSuccessor(iter);
        itrSuccessor(iterx);
    }
    if(!itrTerminated(iter) || !itrTerminated(iterx)){
        return false;
    }
    return true;

}

/* ************************************************************************** */

void bstDestructItr(void* treeroot)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTPostOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);

    DataType* ptrType = ConstructPtrDataType();
    DataObject* ptr = adtConstruct(ptrType);
    BSTNode* node;

    while(!itrTerminated(iter)){
        ptr->value = (BSTNode*)itrElement(iter);
        node = ptr->value;
        free(node);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructBSTPostOrderIterator(itrType);
}

/* ************************************************************************** */

bool bstExistsItr(void* treeroot, DataObject* elem)
{
    BSTNode* root = (BSTNode*)treeroot;

    BSTNode* curr = root;

        while(curr != NULL){
            if(adtCompare(curr->data, elem) > 0){
                curr = curr->LeftPtr;
            } else if (adtCompare(curr->data, elem) < 0){
                curr = curr->RightPtr;
            } else if (adtCompare(curr->data, elem) == 0){
                return true;
            }
        }
        return false;

}

/* ************************************************************************** */

void * bstRemoveItr(void* treeroot, DataObject* elem )
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode *pred = NULL, *curr = root;

    while (curr) {
        if (adtCompare(curr->data, elem) > 0) {
            pred = curr;
            curr = curr->LeftPtr;
        } else if (adtCompare(curr->data, elem) < 0) {
            pred = curr;
            curr = curr->RightPtr;
        } else {
           // *isRemoved = true;
            if (pred) {
                if (pred->LeftPtr == curr) {
                    pred->LeftPtr = RemoveRoot(pred->LeftPtr);
                } else {
                    pred->RightPtr = RemoveRoot(pred->RightPtr);
                }
                curr = NULL;
            } else {
                return RemoveRoot(curr);
            }
        }
    }
    return root;
}

/* ************************************************************************** */

void * RemoveRoot(void* treeroot)
{
    BSTNode* root = (BSTNode*) treeroot;

    if (root) {
        if (root->LeftPtr && root->RightPtr) {
            DataObject* tmpData;
            root->RightPtr = GetNRemoveMinItr(root->RightPtr, &tmpData);
            adtDestruct(root->data);
            root->data = tmpData;
        }
        else {
            BSTNode* tmp = root;
            adtDestruct(root->data);
            root = !(root->LeftPtr) ? root->RightPtr : root->LeftPtr;
            free(tmp);
        }
    }
    return root;
    }


/* ************************************************************************** */

void * bstGetMinItr(void* treeroot)
{
    BSTNode * root = (BSTNode*)treeroot;
    BSTNode* curr = root;
    DataObject* ret = NULL;

    if(root == NULL){
        return NULL;
    }
    while(curr->LeftPtr != NULL) {
        curr = curr->LeftPtr;
    }

    if(curr != NULL){
        ret = adtClone(curr->data);
        return ret;
    }
    printf("il minimo e': ");
    adtWriteToMonitor(ret);
    return NULL;
}

/* ************************************************************************** */

void * GetNRemoveMinItr(void * treeroot , void * treefather){
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* previous = (BSTNode*)treefather;

    BSTNode* curr = root;
    BSTNode* ancestor = previous;

    while(curr->LeftPtr !=NULL){
        ancestor=curr;
        curr= curr->LeftPtr;
    }

        if (curr == ancestor->LeftPtr) {
            ancestor->LeftPtr = curr->RightPtr;
        } else ancestor->RightPtr = curr->RightPtr;

    return curr;
}

/* ************************************************************************** */

void * bstRemoveMinItr(void* treeroot, void * treefather)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* previous = (BSTNode*)treefather;

    BSTNode* curr=NULL;
    BSTNode* ancestor=NULL;

    ancestor=previous;
    curr=root;

    while(curr->LeftPtr != NULL){
        ancestor=curr;
        curr= curr->LeftPtr;
    }
    if(curr == ancestor->LeftPtr){
        ancestor->LeftPtr = curr->RightPtr;
    } else ancestor->RightPtr = curr->RightPtr;

    return root;
}

/* ************************************************************************** */

void * bstGetMaxItr(void* treeroot)
{
    BSTNode* root = (BSTNode*)treeroot;

    BSTNode* curr = root;

    while(curr->RightPtr !=NULL){
        curr= curr->RightPtr;
    }

    if (curr != NULL) {
       DataObject* ret = adtClone(curr->data);
       return ret;
    }

    return NULL;

}

/* ************************************************************************** */

void * GetNRemoveMaxItr(void * treeroot , void * treefather){

    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* previous = (BSTNode*)treefather;

    BSTNode* curr=NULL;
    BSTNode* ancestor=NULL;

    ancestor=previous;
    curr=root;

    while(curr->RightPtr !=NULL){
        ancestor=curr;
        curr= curr->RightPtr;
    }
    if(curr == ancestor->RightPtr){
        ancestor->RightPtr = curr->LeftPtr;
    } else ancestor->LeftPtr = curr->LeftPtr;

    return curr;
}

/* ************************************************************************** */

void * bstRemoveMaxItr(void* treeroot, void* prenode)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* previous = (BSTNode*)prenode;

    BSTNode* curr=NULL;
    BSTNode* ancestor=NULL;

    ancestor=previous;
    curr=root;

    while(curr->RightPtr !=NULL){
        ancestor=curr;
        curr= curr->RightPtr;
    }
    if(curr == ancestor->RightPtr){
        ancestor->RightPtr = curr->LeftPtr;
    } else ancestor->LeftPtr = curr->LeftPtr;

    return curr;
}

/* ************************************************************************** */

void * bstGetSuccessorItr(void* treeroot, DataObject* elem)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* curr = root;
    BSTNode* node = NULL;

    while(curr != NULL && adtCompare(curr->data, elem) != 0){
        if(adtCompare(curr->data, elem) < 0){
            curr = curr->RightPtr;
        } else if(adtCompare(curr->data, elem) > 0) {
            node = curr;
            curr = curr->LeftPtr;
        }
    }
    if(curr != NULL && curr->RightPtr != NULL){
        node = bstGetMinItr(curr->RightPtr);
    }

    if(node != NULL) {
        return node->data;
    }
    else return NULL;
}

/* ************************************************************************** */

void * bstGetPredecessorItr(void* treeroot, DataObject* elem)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* curr = root;
    BSTNode* pred = NULL;
    BSTNode* ancestor = NULL;

    while(curr != NULL) {
        if (adtCompare(curr->data, elem) > 0) {
            curr = curr->LeftPtr;
        } else if (adtCompare(curr->data, elem) < 0) {
            ancestor = curr;
            curr = curr->RightPtr;
        } else if (adtCompare(curr->data, elem) == 0) {
            if(curr->LeftPtr != NULL) {
                pred = bstGetMaxItr(curr->LeftPtr);
                if(pred) {
                    return adtClone(pred->data);
                }
                else return NULL;
            } else if(curr->LeftPtr == NULL && curr->RightPtr != NULL){
                pred = ancestor;
            }
            if(curr->LeftPtr == NULL && curr->RightPtr == NULL){
                pred = ancestor;
            }
            if(pred) {
                return adtClone(pred->data);
            }
        }
    }
    if(ancestor != NULL) {
        return ancestor->data;
    }
    else return NULL;
}

/* ************************************************************************** */

void * bstGetNRemovePredecessorItr(void* treeroot, DataObject* elem, void* prenode)
{

    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* ancestor = (BSTNode*)prenode;

    BSTNode *curr = root;
    BSTNode *pred = NULL;
    BSTNode *ret = NULL;

    while(curr != NULL && adtCompare(curr->data, elem) != 0){
        if(adtCompare(curr->data, elem) < 0){
            if(pred != NULL) {
                ancestor = pred;
            }
            pred = curr;
            curr = curr->RightPtr;
        }else{
            ancestor = curr;
            curr = curr->LeftPtr;
        }
    }

    if(curr == NULL || curr->LeftPtr == NULL){
        ret = pred;
        BSTNode *elemToRemove = pred;
        if(pred == NULL){
            return NULL;
        }
        if(pred->RightPtr == NULL && pred->LeftPtr == NULL){
            BSTNode *retnode = (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data= adtConstruct(pred->data->type);

            retnode->data->value = adtGetValue(pred->data);
            adtSetValue(pred->data, elemToRemove->data->value);

            if(ancestor->RightPtr == pred){
                ancestor->RightPtr = elemToRemove->RightPtr;
            }else{
                ancestor->LeftPtr = elemToRemove->RightPtr;
            }
            return retnode;
        }

        if(pred->RightPtr!=NULL){
            BSTNode *retnode = (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data = adtConstruct(pred->data->type);

            elemToRemove = GetNRemoveMinItr(pred->RightPtr, pred);
            retnode->data->value = adtGetValue(pred->data);
            adtSetValue(pred->data, elemToRemove->data->value);

            return retnode;
        }else if(pred->LeftPtr!=NULL){
            BSTNode *retnode = (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data= adtConstruct(pred->data->type);

            elemToRemove= GetNRemoveMaxItr(pred->LeftPtr, pred);
            retnode->data->value= adtGetValue(pred->data);
            adtSetValue(pred->data, elemToRemove->data->value);
        }
    }else{
        ret = GetNRemoveMaxItr(curr->LeftPtr, curr);
    }

    return ret;
    }



/* ************************************************************************** */

void * bstRemovePredecessorItr(void* treeroot, DataObject* elem, void* prenode)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* ancestor = (BSTNode*)prenode;

    BSTNode *curr = root;
    BSTNode *pred = NULL;
    BSTNode *ret = NULL;

    while(curr != NULL && adtCompare(curr->data, elem) != 0){
        if(adtCompare(curr->data, elem) < 0){
            if(pred != NULL) {
                ancestor = pred;
            }
            pred = curr;
            curr = curr->RightPtr;
        }else{
            ancestor = curr;
            curr = curr->LeftPtr;
        }
    }

    if(curr == NULL || curr->LeftPtr == NULL){
        ret = pred;
        BSTNode* elemToRemove = pred;
        if(pred == NULL){
            return NULL;
        }
        if(pred->RightPtr == NULL && pred->LeftPtr == NULL){
            BSTNode *retnode = (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data= adtConstruct(pred->data->type);

            retnode->data->value = adtGetValue(pred->data);
            adtSetValue(pred->data, elemToRemove->data->value);

            if(ancestor->RightPtr == pred){
                ancestor->RightPtr = elemToRemove->RightPtr;
            }else{
                ancestor->LeftPtr = elemToRemove->RightPtr;
            }
            return retnode;
        }

        if(pred->RightPtr!=NULL){
            BSTNode* retnode = (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data = adtConstruct(pred->data->type);

            elemToRemove = GetNRemoveMinItr(pred->RightPtr, pred);
            retnode->data->value = adtGetValue(pred->data);
            adtSetValue(pred->data, elemToRemove->data->value);

            return retnode;
        }else if(pred->LeftPtr!=NULL){
            BSTNode* retnode = (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data= adtConstruct(pred->data->type);

            elemToRemove= GetNRemoveMaxItr(pred->LeftPtr, pred);
            retnode->data->value= adtGetValue(pred->data);
            adtSetValue(pred->data, elemToRemove->data->value);
        }
    }else{
        ret = GetNRemoveMaxItr(curr->LeftPtr, curr);
    }

    return ret;
}


/* ************************************************************************** */

void * bstInsertItr(void* treeroot, DataObject* elem, int* size)
{
        BSTNode* root = (BSTNode*)treeroot;

        BSTNode *ancestor= NULL;
        BSTNode *curr= root;

        while(curr != NULL){
            if(adtCompare(curr->data, elem)>0){
                ancestor= curr;
                curr= curr->LeftPtr;
            }else if(adtCompare(curr->data, elem)<0){
                ancestor= curr;
                curr= curr->RightPtr;
            }else{
                return root;
            }
        }

        curr = (BSTNode*)malloc(sizeof(BSTNode));
        curr->data= adtClone(elem);
        *((int*)size) = *((int*)size)+1;

    if(ancestor == NULL){
            curr->LeftPtr = curr->RightPtr = NULL;
            root= curr;
        }else if(adtCompare(ancestor->data, elem)>0){
            curr->LeftPtr = curr->RightPtr = NULL;
            ancestor->LeftPtr= curr;
        }else{
            curr->LeftPtr = curr->RightPtr = NULL;
            ancestor->RightPtr= curr;
        }
        return root;

}

/* ************************************************************************** */

void * bstGetNRemoveSuccessorItr(void* treeroot, DataObject* elem, void* prenode)
{

        BSTNode* root = (BSTNode*)treeroot;
        BSTNode* ancestor = (BSTNode*)prenode;

        BSTNode *curr= root;
        BSTNode *succ= NULL;
        BSTNode *ret= NULL;

        while(curr!=NULL && adtCompare(curr->data, elem)!=0){
            if(adtCompare(curr->data, elem)<0){
                ancestor = curr;
                curr= curr->RightPtr;
            }else{
                if(succ != NULL) {
                    ancestor = succ;
                }
                succ= curr;
                curr= curr->LeftPtr;
            }
        }

        if(curr== NULL || curr->RightPtr==NULL){
            ret= succ;

            BSTNode *del= succ;
            if(succ==NULL){
                return NULL;
            }

            if(succ->RightPtr==NULL && succ->LeftPtr==NULL){
                BSTNode *retnode= (BSTNode*)malloc(sizeof(BSTNode));
                retnode->data= adtConstruct(succ->data->type);

                retnode->data->value= adtGetValue(succ->data);
                adtSetValue(succ->data, del->data->value);

                if(ancestor->RightPtr==succ){
                    ancestor->RightPtr= del->RightPtr;
                }else{
                    ancestor->LeftPtr= del->LeftPtr;
                }
                return retnode;
            }

            if(ancestor == NULL){
                BSTNode *retnode= (BSTNode*)malloc(sizeof(BSTNode));
                retnode->data= adtConstruct(succ->data->type);

                del= GetNRemoveMinItr(succ->RightPtr, succ);

                retnode->data->value= adtGetValue(succ->data);
                adtSetValue(succ->data, del->data->value);
                return retnode;
            }else{
                if(succ->RightPtr == NULL){
                    if(ancestor->RightPtr==succ){
                        ancestor->RightPtr= del->RightPtr;
                    }else{
                        ancestor->LeftPtr= del->LeftPtr;
                    }
                }else if(succ->LeftPtr == NULL){
                    if(ancestor->RightPtr == succ){
                        ancestor->RightPtr= del->RightPtr;
                    }else{
                        ancestor->LeftPtr= del->RightPtr;
                    }
                }else{
                    BSTNode *retnode = (BSTNode*)malloc(sizeof(BSTNode));
                    retnode->data= adtConstruct(succ->data->type);

                    del= GetNRemoveMaxItr(succ->LeftPtr, succ);

                    retnode->data->value= adtGetValue(succ->data);
                    adtSetValue(succ->data, del->data->value);

                    return retnode;
                }
            }
        }else{
            ret = GetNRemoveMinItr(curr->RightPtr, curr);
        }

        return ret;
    }



/* ************************************************************************** */

void * bstRemoveSuccessorItr(void* treeroot, DataObject* elem, void* prenode)
{
    BSTNode* root = (BSTNode*)treeroot;
    BSTNode* ancestor = (BSTNode*)prenode;

    BSTNode *curr= root;
    BSTNode *succ= NULL;
    BSTNode *ret= NULL;

    while(curr!=NULL && adtCompare(curr->data, elem)!=0){
        if(adtCompare(curr->data, elem)<0){
            ancestor = curr;
            curr= curr->RightPtr;
        }else{
            if(succ != NULL) {
                ancestor = succ;
            }
            succ= curr;
            curr= curr->LeftPtr;
        }
    }

    if(curr== NULL || curr->RightPtr==NULL){
        ret= succ;

        BSTNode *del= succ;
        if(succ==NULL){
            return NULL;
        }

        if(succ->RightPtr==NULL && succ->LeftPtr==NULL){
            BSTNode *retnode= (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data= adtConstruct(succ->data->type);

            retnode->data->value= adtGetValue(succ->data);
            adtSetValue(succ->data, del->data->value);

            if(ancestor->RightPtr==succ){
                ancestor->RightPtr= del->RightPtr;
            }else{
                ancestor->LeftPtr= del->LeftPtr;
            }
            return retnode;
        }

        if(ancestor == NULL){
            BSTNode *retnode= (BSTNode*)malloc(sizeof(BSTNode));
            retnode->data= adtConstruct(succ->data->type);

            del= GetNRemoveMinItr(succ->RightPtr, succ);

            retnode->data->value= adtGetValue(succ->data);
            adtSetValue(succ->data, del->data->value);
            return retnode;
        }else{
            if(succ->RightPtr == NULL){
                if(ancestor->RightPtr==succ){
                    ancestor->RightPtr= del->RightPtr;
                }else{
                    ancestor->LeftPtr= del->LeftPtr;
                }
            }else if(succ->LeftPtr == NULL){
                if(ancestor->RightPtr == succ){
                    ancestor->RightPtr= del->RightPtr;
                }else{
                    ancestor->LeftPtr= del->RightPtr;
                }
            }else{
                BSTNode *retnode = (BSTNode*)malloc(sizeof(BSTNode));
                retnode->data= adtConstruct(succ->data->type);

                del= GetNRemoveMaxItr(succ->LeftPtr, succ);

                retnode->data->value= adtGetValue(succ->data);
                adtSetValue(succ->data, del->data->value);

                return retnode;
            }
        }
    }else{
        ret = GetNRemoveMinItr(curr->RightPtr, curr);
    }

    return ret;
}

/* ************************************************************************** */

void *  bstCloneItr(void* treeroot)
{

    BSTNode* root=(BSTNode*)treeroot;

    if(root==NULL)
    {
        return NULL;
    }

    StackType* stkType = ConstructStackVecType();
    StackObject* stack = stkConstruct(stkType);

    DataType* ptrType = ConstructPtrDataType();
    DataObject* ptr = adtConstruct(ptrType);

    DataObject* data;
    BSTNode* clone;
    BSTNode* newClone;

    clone = (BSTNode*)malloc(sizeof(BSTNode));
    clone->data = adtClone(root->data);
    clone->LeftPtr = NULL;
    clone->RightPtr = NULL;

    BSTNode* newRoot = clone;

        while(root != NULL) {
            if(root->LeftPtr != NULL && clone->LeftPtr == NULL) {

                newClone=(BSTNode*)malloc(sizeof(BSTNode));
                newClone->data=adtClone(root->LeftPtr->data);
                newClone->LeftPtr = newClone->RightPtr = NULL;
                clone->LeftPtr=newClone;
                adtSetValue(ptr,clone);
                stkPush(stack,ptr);
                adtSetValue(ptr,root);
                stkPush(stack,ptr);
                root=root->LeftPtr;
                clone=clone->LeftPtr;

            } else if(root->RightPtr != NULL && clone->RightPtr == NULL) {

                newClone=(BSTNode*)malloc(sizeof(BSTNode));
                newClone->data=adtClone(root->RightPtr->data);
                newClone->LeftPtr = newClone->RightPtr = NULL;
                clone->RightPtr = newClone;
                adtSetValue(ptr,clone);
                stkPush(stack,ptr);
                adtSetValue(ptr,root);
                stkPush(stack,ptr);
                root = root->RightPtr;
                clone = clone->RightPtr;
            } else {
                if(!stkEmpty(stack)) {
                    data=stkTopNPop(stack);
                    root=(BSTNode*)adtGetValue(data);
                    adtDestruct(data);
                    data=stkTopNPop(stack);
                    clone=(BSTNode*)adtGetValue(data);
                    adtDestruct(data);
                } else {
                    root=NULL;
                    clone=NULL;
                }
            }
        }
    return newRoot;
}

/* ************************************************************************** */

void bstPreOrderMapItr(void* treeroot, MapFun fun,  void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTPreOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);
    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, par);
        itrSuccessor(iter);
    }

}

/* ************************************************************************** */

void bstPostOrderMapItr(void* treeroot, MapFun fun,  void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTPostOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);

    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, par);
        itrSuccessor(iter);
    }

}

/* ************************************************************************** */


void bstInOrderMapItr(void* treeroot, MapFun fun,  void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTInOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);
    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, par);
        itrSuccessor(iter);
    }

}

/* ************************************************************************** */

void bstBreadthMapItr(void* treeroot, MapFun fun, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTBreadthIterator();
    ITRObject* iter = itrConstruct(itrType, root);
    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, par);
        itrSuccessor(iter);
    }
}

/* ************************************************************************** */

void bstPreOrderFoldItr(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTPreOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);
    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, accum, par);
        itrSuccessor(iter);
    }
}


/* ************************************************************************** */

void bstInOrderFoldItr(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTInOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);
    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, accum, par);
        itrSuccessor(iter);
    }
}

/* ************************************************************************** */

void bstPostOrderFoldItr(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTPostOrderIterator();
    ITRObject* iter = itrConstruct(itrType, root);

    StackType* stkType = stkConstructVecType();
    StackObject* stack = stkConstruct(stkType);

    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, accum, par);
        itrSuccessor(iter);
    }

}

/* ************************************************************************** */

void bstBreadthFoldItr(void* treeroot, FoldFun fun, void* accum, void* par)
{
    BSTNode* root = (BSTNode*)treeroot;

    ITRType* itrType = ConstructBSTBreadthIterator();
    ITRObject* iter = itrConstruct(itrType, root);
    BSTNode* node;

    while(!itrTerminated(iter)){
        node = (BSTNode*)itrElement(iter);
        fun(node->data, accum, par);
        itrSuccessor(iter);
    }
}