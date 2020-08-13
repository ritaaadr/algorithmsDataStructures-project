#include <adt/vert/adtvert.h>
#include <bst/bstitrpreord.h>
#include "utility.h"

#include "adt/adt.h"
#include "adt/int/adtint.h"
#include "adt/flt/adtflt.h"
#include "adt/str/adtstr.h"
#include "adt/ptr/adtptr.h"
#include "adt/rec/adtrec.h"

#include "stack/stack.h"
#include "stack/vec/stackvec.h"
#include "stack/lst/stacklst.h"

#include "queue/queue.h"
#include "queue/vec/queuevec.h"
#include "queue/lst/queuelst.h"

#include "bst/bst.h"
#include "bst/rec/bstrec.h"
#include "bst/itr/bstitr.h"

#include "graph/graph.h"
#include "graph/rec/graphrec.h"
#include "graph/itr/graphitr.h"
#include "graph/rep/mat/graphmat.h"
#include "graph/rep/lst/graphlst.h"
#include "graph/rep/bst/graphbst.h"

bool DFS(GraphObject* transposto, int vertId, BSTObject* bst);
bool trovaForesta(GraphObject* graph);

int main()
{
 GraphRepresentation* rep = ConstructGraphLst();
 GraphType* graphType = ConstructGraphRecursive(rep);
 GraphObject* graph = graphConstruct(graphType);

    DataType* intDataType = ConstructIntDataType();
    DataObject* data = adtConstruct(intDataType);

    int x = 5;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 1;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 12;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 9;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 11;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 4;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 2;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 6;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 13;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 15;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    x = 17;
    adtSetValue(data, &x);
    graphInsertVertex(graph, data, x);

    graphInsertEdge(graph, 5, 1);
    graphInsertEdge(graph, 1, 12);
    graphInsertEdge(graph, 5, 9);
    graphInsertEdge(graph, 9, 11);
    graphInsertEdge(graph, 5, 4);
    graphInsertEdge(graph, 4, 2);
    graphInsertEdge(graph, 2, 6);
   //graphInsertEdge(graph, 12, 11);

    if(trovaForesta(graph)==true){
        printf("Il grafo e' una foresta\n");
    } else {
        printf("Il grafo non e' una foresta\n");
    }

}

bool trovaForesta(GraphObject* graph)
{
    GraphObject* transposto = graphTranspose(graph);

    BSTType* bstType = ConstructBSTRecursive();
    BSTObject* bst = bstConstruct(bstType);

    DataObject* radice = NULL;
    ITRObject* vertItr = graphVertices(transposto);
    while(vertItr!= NULL && !itrTerminated(vertItr)){
        DataObject* vert = itrElement(vertItr);
        int vertId = adtGetVertexId(vert->value);
        printf("Sto sul vertice %d\n", vertId);
        ITRObject* edgItr = graphVertexEdges(transposto, vertId);
        if(edgItr == NULL){
            radice = vert;
            bstInsert(bst, vert);
            break;
        }
        itrSuccessor(vertItr);
    }

    ITRObject* itrVert = graphVertices(graph);
    bool ret = false;
    if(radice == NULL){
        return false;
    } else {
        int rad = adtGetVertexId(radice->value);
        printf("radice e' %d\n", rad);
        while(itrVert != NULL && !itrTerminated(itrVert)) {
            DataObject *vert = itrElement(itrVert);
            if (vert != radice) {
                int vertId = adtGetVertexId(vert->value);
                printf("vertice in esplorazione e' %d\n", vertId);
                if (!bstExists(bst, vert)) {
                    ret = DFS(transposto, vertId, bst);
                    if(ret==false){
                        printf("Sto sul vertice %d\n", vertId);
                        return false;
                    }
                }
            }
            itrSuccessor(itrVert);
        }
    }
    return ret;
}

bool DFS(GraphObject* transposto, int vertId, BSTObject* bst)
{
    DataType* intDataType = ConstructIntDataType();
    DataObject* data = adtConstruct(intDataType);

    adtSetValue(data, &vertId);
    bstInsert(bst, data);

    ITRObject* edgItr = graphVertexEdges(transposto, vertId);
    while(edgItr!= NULL && !itrTerminated(edgItr)){
        int curr = *((int*)itrElement(edgItr));
        adtSetValue(data, &curr);
        if(!bstExists(bst, data)){
            DFS(transposto, curr, bst);
        } else {
            return false;
        }
        itrSuccessor(edgItr);
    }
    return true;
}
