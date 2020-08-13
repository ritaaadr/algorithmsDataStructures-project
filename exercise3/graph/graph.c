
#include "graph.h"

/* ************************************************************************** */

GraphObject* graphConstruct(GraphType* type)
{
    GraphObject* graph = (GraphObject*)malloc(sizeof(GraphObject));

    graph->type = type;
    graph->numEdges = 0;
    graph->numVertex = 0;
    graph->structure = type->graph_representation->graph_construct();

    return graph;
}

/* ************************************************************************** */

void graphDestruct(GraphObject* graph) {
    assert(graph);

    if (graph->structure != NULL) {
        graph->type->graph_representation->graph_destruct(graph->structure);
    }
    free(graph->structure);
    free(graph);
}

/* ************************************************************************** */

bool graphEmpty(GraphObject* graph)
{
    assert(graph);
    return graph->type->graph_representation->graph_empty(graph->structure);
}


/* ************************************************************************** */

uint graphVertexNumber(GraphObject* graph)
{
    assert(graph);
    return graph->numVertex;
}

/* ************************************************************************** */

uint graphEdgeNumber(GraphObject* graph)
{
    assert(graph);
    return graph->numEdges;

}

/* ************************************************************************** */

void graphClear(GraphObject* graph)
{
    assert(graph);
    if(graph->structure != NULL) {
        graph->type->graph_representation->graph_destruct(graph->structure);
    }
    graph->numEdges = 0;
    graph->numVertex = 0;
}

/* ************************************************************************** */

GraphObject* graphClone(GraphObject* graph)
{
    assert(graph);
        GraphObject *graphClone = (GraphObject *) malloc(sizeof(GraphObject));

        graphClone->type = graph->type;
        graphClone->numEdges = graph->numEdges;
        graphClone->numVertex = graph->numVertex;
        graphClone->structure = graph->type->graph_representation->graph_clone(graph->structure);
    return graphClone;
}

/* ************************************************************************** */

GraphObject* graphTranspose(GraphObject* graph)
{
    assert(graph);
    GraphObject* graphTranspose = (GraphObject*)malloc(sizeof(GraphObject));

    graphTranspose->type = graph->type;
    graphTranspose->numEdges = graph->numEdges;
    graphTranspose->numVertex = graph->numVertex;
    graphTranspose->structure = graph->type->graph_representation->graph_transpose(graph->structure);

    return graphTranspose;
}

/* ************************************************************************** */

void graphInsertVertex(GraphObject* graph, DataObject* elem, uint label)
{
    assert(graph);
    assert(elem);

    bool success = graph->type->graph_representation->graph_insertVertex(graph->structure, elem, label);
    if(success == true){
        GraphVertex* InsertedVertex = (GraphVertex*)malloc(sizeof(GraphVertex));
        InsertedVertex->value = elem;
        InsertedVertex->label = label;
        graph->numVertex++;
    }
}

/* ************************************************************************** */

void graphRemoveVertex(GraphObject* graph, uint label)
{
    assert(graph);
    uint numEdges = 0;
    bool success = graph->type->graph_representation->graph_removeVertex(graph->structure, label, &numEdges);
    if(success == true){
        graph->numEdges = graph->numEdges - numEdges;
        graph->numVertex--;
    }
}

/* ************************************************************************** */

void graphInsertEdge(GraphObject* graph, uint label1 , uint label2)
{
    assert(graph);
    bool success = graph->type->graph_representation->graph_insertEdge(graph->structure,label1, label2);
    if(success == true){
        graph->numEdges++;
    }
}

/* ************************************************************************** */

void graphRemoveEdge(GraphObject* graph, uint label1, uint label2)
{
    assert(graph);

    bool success = graph->type->graph_representation->graph_removeEdge(graph->structure, label1, label2);
    if(success == true){
        graph->numEdges--;
    }
}

/* ************************************************************************** */

bool graphExistsVertex(GraphObject* graph, uint label)
{
    assert(graph);
    return graph->type->graph_representation->graph_existsVertex(graph->structure, label);
}

/* ************************************************************************** */

bool  graphExistsEdge(GraphObject* graph, uint label1 , uint label2)
{
    assert(graph);
    return graph->type->graph_representation->graph_existsEdge(graph->structure, label1, label2);
}

/* ************************************************************************** */

DataObject* graphGetVertexData(GraphObject* graph, uint label)
{
    assert(graph);
    return graph->type->graph_representation->graph_getVertexData(graph->structure, label);
}

/* ************************************************************************** */

void graphSetVertexData(GraphObject* graph, uint label , DataObject* elem)
{
    assert(graph);
    graph->type->graph_representation->graph_setVertexData(graph->structure, label, elem);
}

/* ************************************************************************** */

uint graphVertexFromPointer(GraphObject* graph, GraphVertex* graphVert)
{
   assert(graphVert);
   return graph->type->graph_representation->graph_vertexFromPointer(graph, graphVert);
}

/* ************************************************************************** */

bool graphEqual(GraphObject* graph, GraphObject* graphx)
{
    assert(graph);
    assert(graphx);

    if((graph->numEdges != graphx->numEdges) || (graph->numVertex != graphx->numVertex)){
        return false;
    }
    return graph->type->graph_equal(graph, graphx);

}

/* ************************************************************************** */

bool graphExistsVertexWithData(GraphObject* graph, DataObject* elem)
{
    assert(graph);
    bool success = false;
    graphBreadthFold(graph, &esisteFold, &success, elem);
    return success;
}

/* ************************************************************************** */

ITRObject* graphVertices(GraphObject* graph)
{
   assert(graph);
   return graph->type->graph_representation->graph_vertices(graph->structure);
}

/* ************************************************************************** */

ITRObject* graphVertexEdges(GraphObject* graph, uint label)
{
    assert(graph);
    return graph->type->graph_representation->graph_vertexEdges(graph->structure, label);
}


/* ************************************************************************** */

int graphShortestPath(GraphObject* graph, uint label1, uint label2)
{
    assert(graph);
    return graph->type->graph_shortestPath(graph,label1, label2);
}

/* ************************************************************************** */

bool graphIsAcyclic(GraphObject* graph)
{
    assert(graph);
    return graph->type->graph_isAcyclic(graph);
}

/* ************************************************************************** */

ITRObject* graphTopologicalOrder(GraphObject* graph)
{
    assert(graph);
    return graph->type->graph_topologicalOrder(graph);
}

/* ************************************************************************** */

GraphObject* graphMaximalReachableSubgraph(GraphObject* graph, uint label)
{
    assert(graph);
    return graph->type->graph_maximalReachableSubgraph(graph, label);
}

/* ************************************************************************** */

GraphObject* graphSCCGraph(GraphObject* graph)
{
    assert(graph);
    return graph->type->graph_SCCGraph(graph);
}

/* ************************************************************************** */

void graphPreOrderMap(GraphObject* graph, MapFun fun, void* par)
{
    assert(graph);
    graph->type->graph_preOrderMap(graph, fun, par);
}

/* ************************************************************************** */

void graphPostOrderMap(GraphObject* graph, MapFun fun, void* par)
{
    assert(graph);
    graph->type->graph_postOrderMap(graph, fun, par);
}

/* ************************************************************************** */

void graphBreadthMap(GraphObject* graph, MapFun fun, void* par)
{
    assert(graph);
    graph->type->graph_breadthMap(graph, fun, par);
}

/* ************************************************************************** */

void graphPreOrderFold(GraphObject* graph, FoldFun fun, void* par, void* parx)
{
    assert(graph);
    graph->type->graph_preOrderFold(graph, fun, par, parx);

}

/* ************************************************************************** */

void graphPostOrderFold(GraphObject* graph, FoldFun fun , void* par, void* parx)
{
    assert(graph);
    graph->type->graph_postOrderFold(graph, fun, par, parx);
}

/* ************************************************************************** */
void graphBreadthFold(GraphObject* graph, FoldFun fun, void* par, void* parx)
{
   assert(graph);
   graph->type->graph_breadthFold(graph, fun, par, parx);
}

/* ************************************************************************** */

void* vertexConstruct(DataType* type)
{
    DataObject* data = adtConstruct(type);
    GraphVertex* vertex = (GraphVertex*)malloc(sizeof(GraphVertex));
    vertex->value = data;
    vertex->label = 0;

    return vertex;
}