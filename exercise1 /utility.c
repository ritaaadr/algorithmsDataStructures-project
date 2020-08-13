
#include "utility.h"

#include "adt/adt.h"


/* ************************************************************************** */

int rndNum(int a, int b)
{
  assert(a <= b);
  return (a + (rand() % (b - a + 1)));
}

/* ************************************************************************** */

void getStr(char * str, uint len)
{

  assert(str != NULL);
  uint i;
  char c;
  char x;
  x= getchar(); //dopo la lunghezza rimane un \n
  for(i = 0; (i < len) && ( (c = getchar() ) != '\n') && (c != EOF); ++i)
    {
      str[i] = c;
    }
  str[i] = '\0';

}

/* ************************************************************************** */

void stampaMap(DataObject* obj, void* par) {

    //printf("Stampo valori\n");
    adtWriteToMonitor(obj);
    //printf("\n");
}

/* ************************************************************************** */

void sommaFold(DataObject* obj, void* par, void* parx){

  int val = *((int*)parx);
  void* elem = obj->value;
  if(*((int *)elem)<val) {
      *((int *) par) = *((int *) par) + *((int *) elem);
  }

}

/* ************************************************************************** */

void prodottoFold(DataObject* obj, void* par, void* parx)
{
    int val = *((int*)parx);
    void* elem = obj->value;
    if(*((float*)elem)>val) {
        *((float *) par) = (*((float *) par)) * (*((float *) elem));
    }
}

/* ************************************************************************** */

void concatenazioneFold(DataObject* element, void* Str, void* par)
{
    assert(element);
    assert(Str);

// Se la grandezza della stringa e' minore di quella richiesta, la concateno
    if(strlen((char*) element->value) <= *((uint*) par)) {
        Str = (char*) realloc(Str, (strlen((char*) Str) + strlen((char*) element->value) + 1) * sizeof(char));
        strcat((char*) Str, (char*) element->value);
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

void raddoppiaMap(DataObject* obj, void* par){

    int * val = ((int*)obj->value);
    *val = *val*2;
}

/* ************************************************************************** */

void quadratoMap(DataObject* obj, void* par){

    float* val = ((float*)obj->value);
    *val = (*val) * (*val);

}


/* ************************************************************************** */

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