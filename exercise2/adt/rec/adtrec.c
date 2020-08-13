
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
    clone->quantita = struttura->quantita;
    clone->taglia = struttura->taglia;

    return clone;
}

/* ************************************************************************** */

void adtSetValueRec(void** val, void* valx)
{
    Deposito* record = (Deposito*)*val;
    Deposito* record2 = (Deposito*)valx;
    record->quantita = record2->quantita;
    record->taglia = record2->taglia;

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

    elem->quantita = rndNum(0,100);
    elem->taglia = randT;


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

    inDep->quantita = inQuant;
    inDep->taglia = inTagl;
}

/* ************************************************************************** */

void adtWriteToMonitorRec(void* val)
{
    Deposito* dep = (Deposito*)val;
    printf("Quantita': %d\n", dep->quantita);
    printf("Taglia %d\n", dep->taglia);
}

/* ************************************************************************** */

void* adtCloneRec(void* val)
{

    Deposito* str = (Deposito*)val;
    Deposito* clone = (Deposito*)malloc(sizeof(Deposito));
    clone->taglia = str->taglia;
    clone->quantita = str->quantita;


    return clone;
}

/* ************************************************************************** */

int adtCompareRec(void* val, void* valx)
{
    Deposito* dep1 = (Deposito*)val;
    Deposito* dep2 = (Deposito*)valx;

    if((dep1->quantita == dep2->quantita) && (dep1->taglia==dep2->taglia)){
        printf("Sono uguali\n");
        return 0;
    }
    else
        return (dep1->quantita) - (dep2->quantita);

}
