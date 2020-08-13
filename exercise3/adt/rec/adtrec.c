
#include "adtrec.h"

/* ************************************************************************** */

DataType* ConstructRecordDataType()
{
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construction = &adtConstructRec;
    type->destruction = &adtDestructRec;
    type->getValue = &adtGetValueRec;
    type->setValue = &adtSetValueRec;
    type->randomValue = &adtRandomValueRec;
    type->readFromKeyboard = &adtReadFromKeyboardRec;
    type->writeToMonitor = &adtWriteToMonitorRec;
    type->clone = &adtCloneRec;
    type->compare = &adtCompareRec;
    return type;
}

/* ************************************************************************** */

void DestructRecordDataType(DataType* type)
{
    free(type);
}

/* ************************************************************************** */

void* adtConstructRec()
{
    Deposito* deposito;
    deposito = (Deposito*)malloc(sizeof(Deposito));
    return deposito;
}

/* ************************************************************************** */

void adtDestructRec(void* val)
{
    free(val);
}

/* ************************************************************************** */

void* adtGetValueRec(void* val)
{
    Deposito* struttura = (Deposito*)val;
    Deposito* clone = (Deposito*)malloc(sizeof(Deposito));
    clone->index2 = struttura->index2;
    clone->index1 = struttura->index1;

    return clone;
}

/* ************************************************************************** */

void adtSetValueRec(void** val, void* valx)
{
    Deposito* record = (Deposito*)*val;
    Deposito* record2 = (Deposito*)valx;
    record->index2 = record2->index2;
    record->index1 = record2->index1;

}

/* ************************************************************************** */

void adtRandomValueRec(void* val)
{
    Deposito* elem = (Deposito*)val;
    // int randQ = rndNum(0,100);
    int randT = rndNum(36,60);

    if(randT%2!=0){
        randT=randT+1;
    }

    elem->index2 = rndNum(0,100);
    elem->index1 = randT;


}

/* ************************************************************************** */

void adtReadFromKeyboardRec(void* val)
{
    Deposito* inDep = (Deposito*)val;

    int inQuant = 0;
    int inTagl = 0;

    printf("inserire quantita'\n");
    scanf("%d", &inQuant);

    do {
        printf("inserire taglia\n");
        scanf("%d", &inTagl);

        if (inTagl % 2 != 0 || inTagl < 36 || inTagl > 60) {
            printf("taglia non valida!\n");

        }
    }while(inTagl % 2 != 0 || inTagl < 36 || inTagl > 60);

    inDep->index2 = inQuant;
    inDep->index1 = inTagl;
}

/* ************************************************************************** */

void adtWriteToMonitorRec(void* val)
{
    Deposito* dep = (Deposito*)val;
    printf("Quantita': %d\n", dep->index2);
    printf("Taglia %d\n", dep->index1);
}

/* ************************************************************************** */

void* adtCloneRec(void* val)
{

    Deposito* str = (Deposito*)val;
    Deposito* clone = (Deposito*)malloc(sizeof(Deposito));
    clone->index1 = str->index1;
    clone->index2 = str->index2;


    return clone;
}

/* ************************************************************************** */

int adtCompareRec(void* val, void* valx)
{
    Deposito* dep1 = (Deposito*)val;
    Deposito* dep2 = (Deposito*)valx;

    if(/*(dep1->index2 == dep2->index2) &&*/ dep1->index1==dep2->index1){
        return 0;
    }
    else
        //return (dep1->index2) - (dep2->index2);
        return (dep1->index1) - (dep2->index1);

}

/* ************************************************************************** */

void* adtInitializeRec(void* struct_t, uint name, uint color)
{
    Deposito* recStruct = (Deposito*)struct_t;

    recStruct->index1 = name;
    recStruct->index2 = color;

    return recStruct;
}