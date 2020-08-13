
#include "adtstr.h"

/* ************************************************************************** */

DataType* ConstructStringDataType()
{
  DataType* type = (DataType*)malloc(sizeof(DataType));
  type->construction = &adtConstructString;
  type->destruction = &adtDestructString;
  type->getValue = &adtGetValueString;
  type->setValue = &adtSetValueString;
  type->randomValue = &adtRandomValueString;
  type->readFromKeyboard = &adtReadFromKeyboardString;
  type->writeToMonitor = &adtWriteToMonitorString;
  type->clone = &adtCloneString;
  type->compare = &adtCompareString;
  return type;

}

/* ************************************************************************** */

void DestructStringDataType(DataType* type)
{
  free(type);
}

/* ************************************************************************** */

void* adtConstructString()
{
  char* string = (char*)malloc(sizeof(char)*MaxStrLen+1);
  return (void*)string;

}

/* ************************************************************************** */

void adtDestructString(void* val)
{
  free(val);
}

/* ************************************************************************** */

void* adtGetValueString(void* val)
{

  char* string = (char*)val;
  int len = strlen(string);
  char* clone = (char*)malloc(sizeof(char)*len+1);
  strcpy(clone, string);
  return (void*)clone;
}

/* ************************************************************************** */

void adtSetValueString(void* val , void* valx)
{

  char* str = (char*)val;
  char* strx = (char*)valx;

  strcpy(str,strx);

}

/* ************************************************************************** */

void adtRandomValueString(void* val)
{
      char* rndString = (char*)malloc(sizeof(char)*MaxStrLen+1);

      uint i = 0;

        while(i<MaxStrLen) {
            uint rndElem = (uint) rndNum(65, 122);


            if ((rndElem <= 90) || (rndElem >= 97)) {
                rndString[i++] = (char) rndElem;

            }
        }

        rndString[i]='\0';
        strcpy((char*)val, rndString);
        free(rndString);


}

/* ************************************************************************** */

void adtReadFromKeyboardString(void* val)
{
    //chiedi all'utente una grandezza compresa tra 1 e maxlen
    //presa la lunghezza chiamo il metodo getstr
    //in input passo puntatore void castato a char e la lunghezza

  int dim;
  printf("Inserire grandezza stringa\n");
  scanf("%d", &dim);
  if(dim>1 && dim<MaxStrLen) {
      getStr((char *)val , dim); //non entra nel for della get char
  }
  else {
      printf("errore\n");

  }

}

/* ************************************************************************** */

void adtWriteToMonitorString(void* val)
{
  char* string = (char*)val;
  printf("Stringa: %s\n", string);

}

/* ************************************************************************** */

void* adtCloneString(void* val)
{

    char* string = (char*)val; //casto a char stringa in ingresso
    int len = strlen(string);//calcolo la lunghezza
    char* clone = (char*)malloc(sizeof(char)*len+1); //alloco spazio necessario
    strcpy(clone, string); //copio

    return clone;
}

/* ************************************************************************** */

int adtCompareString(void* val, void* valx)
{
    return strcmp((char*)val , (char*)valx);
}

/* ************************************************************************** */
