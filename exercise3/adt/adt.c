
#include "adt.h"

/* ************************************************************************** */

DataObject* adtConstruct(DataType* type) {
    DataObject *obj = (DataObject*)malloc(sizeof(DataObject));
    obj->type = type;
    obj->value = type->construction();
    return obj;
}

/* ************************************************************************** */

void adtDestruct(DataObject* obj) {

    if(obj != NULL && obj->value!=NULL) {
        obj->type->destruction(obj->value);
        free(obj);
    }
}

/* ************************************************************************** */

void* adtGetValue(DataObject* obj)
{
    assert(obj);
    assert(obj->value);
    return obj->type->getValue(obj->value);
}

/* ************************************************************************** */

void adtSetValue(DataObject* obj, void* x)
{

    obj->type->setValue(&obj->value,x);
}

/* ************************************************************************** */

void adtRandomValue(DataObject* obj)
{
    obj->type->randomValue(obj->value);
}

/* ************************************************************************** */

void adtReadFromKeyboard(DataObject* obj)
{
    obj->type->readFromKeyboard(obj->value);
}

/* ************************************************************************** */

void adtWriteToMonitor(DataObject* obj)
{
    obj->type->writeToMonitor(obj->value);
}

/* ************************************************************************** */

DataObject* adtClone(DataObject *obj)
{
    DataObject* objx = (DataObject*)malloc(sizeof(DataObject));
    objx->type = obj->type;
    objx->value = obj->type->clone(obj->value);
    return objx;
}

/* ************************************************************************** */

int adtCompare(DataObject* obj, DataObject* objx)
{
   // assert(obj->type==objx->type);
    return obj->type->compare(obj->value,objx->value);
}

/* ************************************************************************** */

void stampaMap(DataObject* obj, void* par) {

    if(obj != NULL) {
        adtWriteToMonitor(obj);
    }
}

/* ************************************************************************** */

void raddoppiaMap(DataObject* obj, void* par){

    int * val = ((int*)obj->value);
    *val = *val*2;
}

/* ************************************************************************** */

void cuboMap(DataObject* obj, void* par){

    float* val = ((float*)obj->value);
    *val = (*val) * (*val) * (*val);

}

/* ************************************************************************** */

void concatenazioneMap(DataObject* obj, void* par){

    char* head = par;
    int len1 = strlen(obj->value);
    int len2 = strlen(head)+1;

    char* newStr = (char*)malloc(sizeof(char*)*(len1+len2));
    strcat((char*) newStr, (char*)head);
    strcat((char*) newStr, (char*) obj->value);

  //  adtDestruct(obj->value);
    obj->value = newStr;
}

/* ************************************************************************** */

void sommaFold(DataObject* obj, void* par, void* parx)
{
    int val = *((int*)parx);
    void* elem = obj->value;
    if(*((float*)elem)>val) {
        *((float *) par) = (*((float *) par)) + (*((float *) elem));
    }
}

/* ************************************************************************** */

void prodottoFold(DataObject* obj, void* par, void* parx){

    if(*((int*)par) == 0 ){
        *((int*)par) =1;
    }
    int val = *((int*)parx);
    void* elem = obj->value;
    if(*((int *)elem)<val) {
        *((int *) par) = *((int *) par) * *((int *) elem);
    }

}

/* ************************************************************************** */

void concatenazioneFold(DataObject* obj, void* Str, void* par)
{
    assert(obj);
    assert(Str);

// Se la grandezza della stringa e' minore di quella richiesta, la concateno
    if(strlen((char*) obj->value) <= *((uint*) par)) {
        Str = (char*) realloc(Str, (strlen((char*) Str) + strlen((char*) obj->value) + 1) * sizeof(char));
        strcat((char*) Str, (char*) obj->value);
    }
}

/* ************************************************************************** */

void esisteFold(DataObject* obj, void* accum, void* ElemToFind)
{
    DataObject* elem = (DataObject*)ElemToFind;
    bool* flag = (bool*)accum;

    if(!*(flag)){
        if(adtCompare(obj, elem)==0){
            *flag=true;
        }
    }
}

/* ************************************************************************** */

void contaFold(DataObject* obj, void* accum, void* par)
{
    int count = *((int*)accum);
    count++;
    *((int*)accum) = count;
}

void quadratoMap(DataObject* obj, void* par){

    float* val = ((float*)obj->value);
    *val = (*val) * (*val);

}

void mapUppercase(DataObject* obj, void* par){
    char* string = ((char*)obj->value);
    uint i = 0;


    while(string[i]!='\0')
    {
        if(string[i]>='a' && string[i]<='z'){
            string[i]=string[i]-32;
        }
        i=i+1;
    }
}
