
#include "adtvert.h"

/* ************************************************************************** */

DataType* ConstructVertDataType()
{
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construction = &adtConstructVert;
    type->destruction = &adtDestructVert;
    type->writeToMonitor = &adtWriteToMonitorVert;
    type->clone = &adtCloneVert;
    type->compare = &adtCompareLabel;

    return type;
}

/* ************************************************************************** */

void DestructVertDataType(DataType* type)
{
    free(type);
}

/* ************************************************************************** */

void* adtConstructVert()
{
    VertStruct* vert = (VertStruct*)malloc(sizeof(VertStruct));
    vert->label = -1;
    vert->ArrayPos = -1;
    vert->data = NULL;

    return vert;
}

/* ************************************************************************** */

void* adtInitializeVertex(uint label, DataObject* data)
{
    VertStruct* vert = adtConstructVert();
    if(data != NULL) {
        vert->data = adtClone(data);
    } else {
        vert->data = NULL;
    }

    vert->label = label;

    return vert;
}

/* ************************************************************************** */

void adtDestructVert(void* val)
{
   VertStruct* vert = (VertStruct*)val;

   adtDestruct(vert->data);
   free(vert);
}

/* ************************************************************************** */

void adtWriteToMonitorVert(void* val)
{
    VertStruct* graph = (VertStruct*)val;
        printf("\nL'etichetta e' %d\n", graph->label);
        printf("Il dato e': ");
        adtWriteToMonitor(graph->data);
    if(graph->ArrayPos != -1) {
        printf("La map e' %d\n", graph->ArrayPos);
    }
}

/* ************************************************************************** */

void* adtCloneVert(void* val)
{
    VertStruct* graph = (VertStruct*)val;

    VertStruct* CloneGraph = (VertStruct*)malloc(sizeof(VertStruct));
    CloneGraph->label = graph->label;
    CloneGraph->ArrayPos = graph->ArrayPos;
    CloneGraph->data = adtClone(graph->data);

    return CloneGraph;
}

/* ************************************************************************** */

int adtCompareLabel(void* val, void* valx)
{
   VertStruct* graph = (VertStruct*)val;
   VertStruct* graphx = (VertStruct*)valx;

   if(graph->label < graphx->label){
       return -1;
   } else if(graph->label > graphx->label){
       return 1;
   } else return 0;

}

/* ************************************************************************** */
//ho tolto questa funzione dal construct visto che ora mi è inutile
int adtCompareVert(void* val, void* valx){

    VertStruct* vert = (VertStruct*)val;
    VertStruct* vertx = (VertStruct*)valx;

    //if(vert->ArrayPos == -1 || vertx->ArrayPos == -1){
        return adtCompareLabel(vert, vertx);
    //} else {
        //return adtCompareMapIndex(vert, vertx);
    //}
}

/* ************************************************************************** */

/*int adtCompareMapIndex(void* val, void* valx)
{
    VertStruct* vert = (VertStruct*)val;
    VertStruct* vertx = (VertStruct*)valx;

    if(vert->ArrayPos < vertx->ArrayPos){
        return -1;
    } else if(vert->ArrayPos > vertx->ArrayPos){
        return 1;
    } else return 0;
}*/

/* ************************************************************************** */

uint adtGetVertexId(void* val)
{
    VertStruct* vert = (VertStruct*)val;
    return vert->label;
}

/* ************************************************************************** */

uint adtGetVertexArrayPos(void* val)
{
    VertStruct* vert = (VertStruct*)val;
    return vert->ArrayPos;
}

/* ************************************************************************** */

void * adtSetValueVert(DataObject* val, DataObject* valx)
{
    int id = adtGetVertexId(val->value);
    val->value = adtInitializeVertex(id, valx);
    return val;
}

/* ************************************************************************** */

void* adtGetVertexData(void* vert)
{
    VertStruct* vrt = (VertStruct*)vert;
    return vrt->data;
}