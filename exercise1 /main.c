
#include "utility.h"
#include "stdio.h"

/* ************************************************************************** */

#include "adt/adt.h"
#include "adt/int/adtint.h"
#include "adt/flt/adtflt.h"
#include "adt/str/adtstr.h"
#include "adt/rec/adtrec.h"

#include "stack/stack.h"
#include "stack/vec/stackvec.h"
#include "stack/lst/stacklst.h"

#include "queue/queue.h"
#include "queue/vec/queuevec.h"
#include "queue/lst/queuelst.h"

/* ************************************************************************** */
void mapPosZerNeg(DataObject * dat, void * _)
{
    assert(dat != NULL);
    int elm = *((int *) (adtGetValue(dat)));
    int val = (elm > 0) ? 1 : ((elm == 0) ? 0 : -1);
    adtSetValue(dat, &val);
}

void foldParity(DataObject * dat, void * val, void * _)
{
    assert(dat != NULL);
    assert(val != NULL);
    int elm = *((int *) (adtGetValue(dat)));
    int valx = *((int *) val);
    *((int *) val) = (elm >= 0) ? valx : -valx;
}

void testStack(StackType * stktyp, DataObject * data, DataType* inputDataType, MapFun myMap, FoldFun myFold)
{
    printf("Creazione Oggetto Stack\n\n");
    StackObject * stack = stkConstruct(stktyp);
    DataObject* elemToPrint;
    int numDistr;
    DataObject* wantedElem = adtConstruct(inputDataType);
    int par;
    StackObject *stackx = NULL;
    int numIns;

    int num=0;
    printf("Quanti elementi casuali si vuole inserire?\n");
    scanf("%d", &num);

    for(uint i = 0; i < num; i++)
    {
        adtRandomValue(data);
        stkPush(stack, data);
    }

    int choice;
    do{
        printf("Seleziona l'operazione da eseguire\n");
        printf("1. Stampa valori\n"
               "2. Stampa elemento in cima\n"
               "3. Stampa e distruggi elemento in cima\n"
               "4. Stampa il numero di elementi presenti nella struttura\n"
               "5. Eliminazione n elementi dalla struttura\n"
               "6. Creazione clone della struttura\n"
               "7. Stampa clone della struttura\n"
               "8. Elemento in cima al clone della struttura\n"
               "9. Stampa numero elementi presenti nel clone della struttura\n"
               "10. Controllo di uguaglianza tra la struttura stessa ed il suo clone\n"
               "11. Ricerca di un elemento nella struttura\n"
               "12. Funzione Fold relativa al tipo di dato\n"
               "13. Funzione Map relativa al tipo di dato\n"
               "14. Svuotamento della struttura\n"
               "15. Inserimento n elementi nella struttura\n"
               "16. Distruzione struttura e terminazione del programma\n");
        scanf("%d", &choice);

        switch(choice){

            case 1:
                if(!stkEmpty(stack)) {
                    printf("Gli elementi della struttura sono i seguenti\n");
                    stkMap(stack, &stampaMap, NULL);
                }else{
                    printf("Impossibile effettuare operazione: stack vuoto\n");
                }

                break;

            case 2:
                if(!stkEmpty(stack)) {
                    printf("Elemento in cima\n");
                    elemToPrint = stkTop(stack);
                    adtWriteToMonitor(elemToPrint);
                    adtDestruct(elemToPrint);
                }else{
                    printf("Impossibile effettuare operazione: stack vuoto");
                }

                break;

            case 3:
                if(!stkEmpty(stack)) {
                    printf("Elemento che era in  cima\n");
                    elemToPrint = stkTopNPop(stack);
                    adtWriteToMonitor(elemToPrint);
                    adtDestruct(elemToPrint);
                }else{
                    printf("Impossibile effettuare operazione: stack vuoto");
                }

                break;

            case 4:
                printf("Nella struttura ci sono %d elementi\n", stkSize(stack));

                break;

            case 5:
                if(!stkEmpty(stack)){
                    printf("Quanti elementi si vogliono eliminare dalla pila?\n");
                    scanf("%d", &numDistr);

                    if (numDistr > stkSize(stack)) {
                        printf("Non è possibile eliminare piu' elementi di quanti ne siano stati inseriti!\n");
                    } else {
                        for (uint i = 0; i < numDistr; i++) {
                            stkPop(stack);
                        }
                    }
                } else {
                    printf("Impossibile effettuare operazione: stack vuoto\n");
                }

                break;

            case 6:
                if(stackx != NULL) {
                    int choiceOvewrite = 0;
                    printf("Il clone gia' esiste, vuoi sovrascriverlo?\n1. Sovrascrivi\n2. Annulla\n");
                    scanf("%d", &choiceOvewrite);
                    if (choiceOvewrite == 1) {
                        if (!stkEmpty(stackx)) {
                            stkClear(stackx);
                        }
                        stkDestruct(stackx);
                        stackx = stkClone(stack);
                    }
                } else {
                    if (!stkEmpty(stack)) {
                        printf("Creo il clone della struttura\n");
                        stackx = stkClone(stack);
                        printf("Clone creato\n");
                    } else {
                        printf("Impossibile effettuare operazione: stack vuoto");
                    }
                }

                break;

            case 7:
                if(stackx == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                } else {
                    printf("Gli elementi della struttura sono i seguenti\n");
                    stkMap(stackx, &stampaMap, NULL);
                }

                break;

            case 8:
                if(stackx == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                }else {
                    printf("Elemento in cima\n");
                    elemToPrint = stkTop(stackx);
                    adtWriteToMonitor(elemToPrint);
                    adtDestruct(elemToPrint);
                }

                break;

            case 9:
                if(stackx == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                }else {
                    printf("Nella struttura ci sono %d elementi\n", stkSize(stackx));
                }

                break;

            case 10:
                if(stackx == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                }else {
                    if (!stkEqual(stack, stackx)) {
                        printf("Le pile sono diverse\n");
                    } else {
                        printf("Le pile sono uguali\n");
                    }
                }

                break;

            case 11:
                if(!stkEmpty(stack)) {
                    printf("Inserire elemento che si vuol cercare\n");
                    adtReadFromKeyboard(wantedElem);
                    if (!stkExists(stack, wantedElem)) {
                        printf("Il valore non e' stato trovato\n");
                    } else {
                        printf("Il valore e' stato trovato\n");
                    }
                }else{
                    printf("Impossibile effettuare operazione: stack vuoto");
                }

                break;

            case 12:
                if(myFold == NULL) {
                    printf("Operazione non supportata per il tipo di dato scelto\n");
                } else {
                    printf("Inserire discriminante (numero intero):\n");
                    scanf("%d", &par);
                    printf("In base al tipo di dato scelto sono disponibili le seguenti funzioni:\n"
                           "Dato Intero: somma interi minori del discriminante\n"
                           "Dato Float: prodotto elementi minori del discriminante\n"
                           "Dato Stringhe: concatenazioni stringhe minori del discriminante \n");
                    DataObject *accum = adtConstruct(inputDataType);

                    stkFold(stack, myFold, accum->value, &par);
                    printf("Il risultato e' \n");
                    adtWriteToMonitor(accum);
                    adtDestruct(accum);
                }

                break;

            case 13:
                if(myMap == NULL){
                    printf("Operazione non supportata per il tipo di dato scelto\n");
                } else {
                    printf("In base al tipo di dato scelto sono disponibili le seguenti funzioni:\n"
                           "Dato Intero: ogni elemento sara' raddoppiato\n"
                           "Dato Float: ogni elemento sara' elevato al quadrato\n"
                           "Dato Stringhe: ogni lettera minuscola diventera' maiuscola \n");
                    stkMap(stack, myMap, NULL);
                }

                break;

            case 14:
                if(!stkEmpty(stack)) {
                    printf("Svuotamento della struttura\n");
                    stkClear(stack);
                    printf("Struttura svuotata\n");
                } else {
                    printf("Impossibile effettuare operazione: stack vuoto");
                }

                break;

            case 15:
                printf("Quanti elementi casuali si vogliono inserire?\n");
                scanf("%d", &numIns);

                if(numIns>0){
                    for(uint j=0;j<numIns;j++) {
                        adtRandomValue(data);
                        stkPush(stack, data);
                    }
                } else {
                    printf("Inserire un valore positivo\n");
                }
                break;


            case 16:
                if(!stkEmpty(stack)) {
                    stkClear(stack);
                }
                printf("Distruzione struttura\n");
                stkDestruct(stack);
                printf("Stack distrutto\n");
                break;

            default:
                printf("Scelta non valida\n");
        }
    } while((choice<0) || (choice>16) || (choice!=16));

    // Libero la memoria
    if(stackx != NULL) {
        if(!stkEmpty(stackx)) {
            stkClear(stackx);
        }
        stkDestruct(stackx);
    }

    adtDestruct(wantedElem);
}

void testQueue(QueueType * quetyp, DataObject * data, DataType* inputDataType, MapFun myMap, FoldFun myFold)
{
    printf("Creazione Oggetto Queue\n\n");
    QueueObject * queue = queConstruct(quetyp);
    DataObject* elemToPrint;
    int numDistr;
    DataObject* wantedElem = adtConstruct(inputDataType);
    QueueObject* queuex = NULL;
    int par;
    int numIns;

    int num=0;
    printf("Quanti elementi si vuole inserire?\n");
    scanf("%d", &num);

    for(uint i = 0; i < num; i++)
    {
        adtRandomValue(data);
        queEnqueue(queue, data);
    }

    int choice;
    do{
        printf("1. Stampa valori\n"
               "2. Stampa elemento in cima\n"
               "3. Stampa e distruggi elemento in cima\n"
               "4. Stampa il numero di elementi presenti nella struttura\n"
               "5. Eliminazione n elementi dalla struttura\n"
               "6. Creazione clone della struttura\n"
               "7. Stampa clone della struttura\n"
               "8. Elemento in cima al clone della struttura\n"
               "9. Stampa numero elementi presenti nel clone della struttura\n"
               "10. Controllo di uguaglianza tra la struttura stessa ed il suo clone\n"
               "11. Ricerca di un elemento nella struttura\n"
               "12. Funzione Fold relativa al tipo di dato\n"
               "13. Funzione Map relativa al tipo di dato\n"
               "14. Svuotamento della struttura\n"
               "15. Inserimento n elementi nella struttura\n"
               "16. Distruzione struttura e terminazione del programma\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(!queEmpty(queue)) {
                    printf("Gli elementi della struttura sono i seguenti\n");
                    queMap(queue, &stampaMap, NULL);
                }else{
                    printf("Impossibile effettuare operazione: queue vuota");
                }

                break;

            case 2:
                if(!queEmpty(queue)) {
                    printf("Elemento in cima\n");
                    elemToPrint = queHead(queue);
                    adtWriteToMonitor(elemToPrint);
                    adtDestruct(elemToPrint);
                }else{
                    printf("Impossibile effettuare operazione: queue vuota");
                }

                break;

            case 3:
                if(!queEmpty(queue)) {
                    printf("Elemento che era in  cima\n");
                    elemToPrint = queHeadNDequeue(queue);
                    adtWriteToMonitor(elemToPrint);
                    adtDestruct(elemToPrint);
                }else{
                    printf("Impossibile effettuare operazione: queue vuota");
                }

                break;

            case 4:
                if(!queEmpty(queue)) {
                    printf("Nella struttura ci sono %d elementi\n", queSize(queue));
                }else{
                    printf("Impossibile effettuare operazione: queue vuota");
                }

                break;

            case 5:
                if(!queEmpty(queue)) {
                    printf("Quanti elementi si vogliono eliminare dalla coda?\n");
                    scanf("%d", &numDistr);

                    if (numDistr > queSize(queue)) {
                        printf("Non è possibile eliminare piu' elementi di quanti ne siano stati inseriti!\n");
                    } else {
                        for (uint i = 0; i < numDistr; i++) {
                            queDequeue(queue);
                        }
                    }
                } else {
                    printf("Impossibile effettuare operazione: queue vuota");
                }

                break;

            case 6:
                if(queuex != NULL) {
                    int choiceOvewrite = 0;
                    printf("Il clone gia' esiste, vuoi sovrascriverlo?\n1. Sovrascrivi\n2. Annulla\n");
                    scanf("%d", &choiceOvewrite);
                    if(choiceOvewrite == 1) {
                        if (!queEmpty(queuex)) {
                            queClear(queuex);
                        }
                        queDestruct(queuex);
                        queuex = queClone(queue);
                    }
                } else {
                    if (!queEmpty(queue)) {
                        printf("Creo il clone della struttura\n");
                        queuex = queClone(queue);
                        printf("Clone creato\n");
                    } else {
                        printf("Impossibile effettuare operazione: queue vuota");
                    }
                }

                break;

            case 7:
                if(queuex == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                }else {
                    printf("Gli elementi della struttura sono i seguenti\n");
                    queMap(queuex, &stampaMap, NULL);
                }

                break;

            case 8:
                if(queuex == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                }else {
                    printf("Elemento in cima\n");
                    elemToPrint = queHead(queuex);
                    adtWriteToMonitor(elemToPrint);
                    adtDestruct(elemToPrint);
                }

                break;

            case 9:
                if(queuex == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                }else {
                    printf("Nella struttura ci sono %d elementi\n", queSize(queuex));
                }

                break;

            case 10:
                if(queuex == NULL){
                    printf("Clone non esistente, prova a creare prima il clone!\n");
                }else {
                    if (!queEqual(queue, queuex)) {
                        printf("Le code sono diverse\n");
                    } else {
                        printf("Le code sono uguali\n");
                    }
                }

                break;

            case 11:
                if(!queEmpty(queue)) {
                    printf("Inserire elemento che si vuol cercare\n");
                    adtReadFromKeyboard(wantedElem);
                    if (!queExists(queue, wantedElem)) {
                        printf("Il valore non e' stato trovato\n");
                    } else {
                        printf("Il valore e' stato trovato\n");
                    }
                }else{
                    printf("Impossibile effettuare operazione: queue vuota");
                }

                break;

            case 12:
                if(myFold == NULL)
                    printf("Operazione non supportata per il tipo di dato scelto\n");
                else {
                    printf("Inserire discriminante (numero intero):\n");
                    scanf("%d", &par);
                    printf("In base al tipo di dato scelto sono disponibili le seguenti funzioni:\n"
                           "Dato Intero: somma interi minori del discriminante\n"
                           "Dato Float: prodotto elementi minori del discriminante\n"
                           "Dato Stringhe: concatenazioni stringhe minori del discriminante \n");
                    DataObject *accum = adtConstruct(inputDataType);

                    queFold(queue, myFold, accum->value, &par);
                    printf("Il risultato e' \n");
                    adtWriteToMonitor(accum);
                    adtDestruct(accum);
                }

                break;

            case 13:
                if(myMap== NULL){
                    printf("Operazione non supportata per il tipo di dato scelto\n");
                }else {
                    printf("In base al tipo di dato scelto sono disponibili le seguenti funzioni:\n"
                           "Dato Intero: ogni elemento sara' raddoppiato\n"
                           "Dato Float: ogni elemento sara' elevato al quadrato\n1"
                           "Dato Stringhe: ogni lettera minuscola diventera' maiuscola \n");
                    queMap(queue, myMap, NULL);
                }

                break;

            case 14:
                if(!queEmpty(queue)) {
                    printf("Svuotamento della struttura\n");
                    queClear(queue);
                    printf("Struttura svuotata\n");
                } else {
                    printf("Impossibile effettuare operazione: queue vuota");
                }

                break;

            case 15:
                    printf("Quanti elementi casuali si vogliono inserire?\n");
                    scanf("%d", &numIns);

                    if(numIns>0){
                        for(uint j=0;j<numIns;j++) {
                            adtRandomValue(data);
                            queEnqueue(queue, data);
                        }
                    } else {
                        printf("Inserire un valore positivo\n");
                    }

                break;

            case 16:
                if(!queEmpty(queue)) {
                    queClear(queue);
                }
                printf("Distruzione struttura\n");
                queDestruct(queue);
                printf("Queue distrutto\n");
                break;

            default:
                printf("Scelta non valida\n");
        }

    } while((choice<0) || (choice>16) || (choice!=16));

    // Libero la memoria
    if(queuex != NULL) {
        if(!queEmpty(queuex)) {
            queClear(queuex);
        }
        queDestruct(queuex);
    }

    adtDestruct(wantedElem);
}

int main() {
    srand(time(NULL));
    setbuf(stdout, NULL);

    int choiceStruct=0;
    int choiceData;
    int choiceTyp=0;

    DataObject *inputData = NULL;
    DataType *inputDatatype = NULL;
    MapFun myMap = NULL;
    FoldFun myFold = NULL;

    do {
        printf("Selezionare il tipo di dato che si vuole utilizzare:\n"
               "1 - per gli interi\n2 - per i float\n3 - per le stringhe\n4 - per i record\n");

        scanf("%d", &choiceData);

        switch (choiceData) {
            case 1:
                printf("Creazione ADT per Intero\n\n");
                inputDatatype = ConstructIntDataType();
                myMap = raddoppiaMap;
                myFold = sommaFold;
                break;

            case 2:
                printf("Creazione ADT per Float\n\n");
                inputDatatype = ConstructFloatDataType();
                myMap = quadratoMap;
                myFold = prodottoFold;
                break;

            case 3:
                printf("Creazione ADT per Stringhe\n\n");
                inputDatatype = ConstructStringDataType();
                myMap = mapUppercase;
                myFold = concatenazioneFold;
                break;

            case 4:
                printf("Creazione ADT per Record\n\n");
                inputDatatype = ConstructRecordDataType();
                break;

            default:
                printf("Scelta non valida!\n");
        } //fine switch

    }while((choiceData<1) || (choiceData>4));

    printf("Creazione Oggetto Dato\n\n");
    inputData = adtConstruct(inputDatatype);

    StackType * stkChosenType = NULL;
    QueueType * queChosenType = NULL;

    printf("Scegliere il tipo di struttura:\n1-Pile\n2-Code\n");
    scanf("%d", &choiceStruct);
    if(choiceStruct == 1){
        printf("Creazione Pila:\n");
        printf("Scegliere il tipo di implementazione:\n1-Array\n2-Liste\n");
        scanf("%d", &choiceTyp);
        if(choiceTyp == 1){
            stkChosenType = ConstructStackVecType();
            testStack(stkChosenType, inputData, inputDatatype, myMap, myFold);
            DestructStackVecType(stkChosenType);

        }else if(choiceTyp == 2){
            stkChosenType = ConstructStackLstType();
            testStack(stkChosenType, inputData, inputDatatype, myMap, myFold);
            DestructStackLstType(stkChosenType);
        }else{
            printf("Scelta non valida\n");
            return -1;
        }
    }else if(choiceStruct == 2){
        printf("Creazione Coda\n");
        printf("Scegliere il tipo di implementazione:\n1-Array\n2-Liste\n");
        scanf("%d", &choiceTyp);
        if(choiceTyp == 1){
            queChosenType = ConstructQueueVecType();
            testQueue(queChosenType, inputData, inputDatatype, myMap, myFold);
            DestructQueueVecType(queChosenType);
        }else if(choiceTyp == 2){
            queChosenType = ConstructQueueLstType();
            testQueue(queChosenType, inputData, inputDatatype, myMap, myFold);
            DestructQueueLstType(queChosenType);
        }else{
            printf("Scelta non valida\n");
            return -1;
        }
    }

    //Libero la memoria
    adtDestruct(inputData);
    switch (choiceData) {
        case 1:
            DestructIntDataType(inputDatatype);
            break;

        case 2:
            DestructFloatDataType(inputDatatype);
            break;

        case 3:
            DestructStringDataType(inputDatatype);
            break;

        case 4:
            DestructRecordDataType(inputDatatype);
            break;

        default:
            printf("Scelta non valida!\n");
    }
}