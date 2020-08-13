#include "utility.h"

/* ************************************************************************** */

#include "adt/adt.h"
#include "adt/int/adtint.h"
#include "adt/flt/adtflt.h"
#include "adt/str/adtstr.h"
#include "adt/rec/adtrec.h"
#include "adt/ptr/adtptr.h"

#include "stack/stack.h"
#include "stack/vec/stackvec.h"
#include "stack/lst/stacklst.h"

#include "queue/queue.h"
#include "queue/vec/queuevec.h"
#include "queue/lst/queuelst.h"

#include "bst/bst.h"
#include "bst/rec/bstrec.h"
#include "bst/itr/bstitr.h"


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

/* ************************************************************************ */

void testBST(BSTType* bstChosenType, DataObject * data, DataType* inputDataType, MapFun myMap, FoldFun myFold, int ChoiceMap) {
    printf("Creazione Oggetto Tree\n\n");
    BSTObject* tree = bstConstruct(bstChosenType);
    int numDistr;
    int par;
    BSTObject* treex = NULL;
    int numIns;
    int PrintChoice = 0;

    DataObject* dataObj = adtConstruct(inputDataType);
    DataObject* tmpDataObj = NULL;

    int num=0;
    printf("Quanti elementi casuali si vuole inserire?\n");
    scanf("%d", &num);

    for(uint i = 0; i < num; i++) {
        adtRandomValue(dataObj);
        bstInsert(tree, dataObj);
    }

    int choice;

    do {
        printf("Seleziona l'operazione da eseguire\n");
        printf("1. Stampare i valori\n"
               "2. Stampa numero di elementi presenti nella struttura\n"
               "3. Inserimento di un dato elemento\n"
               "4. Eliminazione di un dato elemento\n"
               "5. Lettura e rimozione del massimo\n"
               "6. Lettura e rimozione del minimo\n"
               "7. Lettura e rimozione del predecessore di un dato elemento\n"
               "8. Lettura e rimozione del successore di un dato elemento\n"
               "9. Rimozione del massimo\n"
               "10. Rimozione del minimo\n"
               "11. Rimozione del predecessore di un dato elemento\n"
               "12. Rimozione del successore di un dato elemento\n"
               "13: Lettura del minimo\n"
               "14. Lettura del massimo\n"
               "15. Lettura del predecessore\n"
               "16. Lettura del successore\n"
               "17. Controllo di vuotezza della struttura\n"
               "18. Svuotamento della struttura\n"
               "19. Controllo di esistenza di un dato elemento nella struttura\n"
               "20. Funzione Map relativa al tipo di dato\n"
               "21  Funzione Fold relativa al tipo di dato\n"
               "22. Chiudi il programma\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(!bstEmpty(tree)){
                    printf("1. Per stampare in Pre Order\n"
                           "2. Per stampare in Post Order\n"
                           "3. Per stampare in In Order\n"
                           "4. Per stampare in ampiezza\n");
                    scanf("%d", &PrintChoice);

                    if(PrintChoice == 1){
                        printf("Stampo in Pre Order\n");
                        bstPreOrderMap(tree, &stampaMap , NULL);
                    } else if(PrintChoice == 2){
                        printf("Stampo in Post Order\n");
                        bstPostOrderMap(tree, &stampaMap, NULL);
                    } else if(PrintChoice == 3){
                        printf("stampo In Order\n");
                        bstInOrderMap(tree, &stampaMap, NULL);
                    } else if(PrintChoice == 4){
                        printf("stampo in ampiezza\n");
                        bstBreadthMap(tree, &stampaMap, NULL);
                    } else {
                        printf("Scelta non valida\n");
                    }
                }
                break;

            case 2:
                if(!bstEmpty(tree)) {
                    printf("La struttura ha %d elementi\n", tree->size);
                } else printf("La struttura e' vuota\n");

                break;

            case 3:
                    printf("Digitare l'elemento da inserire: ");
                    adtReadFromKeyboard(dataObj);
                    bstInsert(tree, dataObj);

                break;
            case 4:
                if(!bstEmpty(tree)) {
                    printf("Digitare l'elemento da eliminare: ");
                    adtReadFromKeyboard(dataObj);
                    bstRemove(tree, dataObj);
                } else printf("La struttura e' vuota\n");


                break;
            case 5:
                if(!bstEmpty(tree)) {
                    printf("Elimino massimo\n");
                    tmpDataObj = bstGetNRemoveMax(tree);
                    adtWriteToMonitor(tmpDataObj);
                    adtDestruct(tmpDataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 6:
                if(!bstEmpty(tree)) {
                    printf("Elimino minimo\n");
                    tmpDataObj = bstGetNRemoveMin(tree);
                    adtWriteToMonitor(tmpDataObj);
                    adtDestruct(tmpDataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 7:
                if(!bstEmpty(tree)) {
                    printf("Inserire il valore di cui si vuole il predecessore\n");
                    adtReadFromKeyboard(dataObj);
                    tmpDataObj = bstGetNRemovePredecessor(tree, dataObj);
                    if (tmpDataObj == NULL) {
                        printf("Elemento non trovato\n");
                    } else {
                        printf("L'elemento e': ");
                        adtWriteToMonitor(tmpDataObj);
                    }
                    adtDestruct(tmpDataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 8:
                if(!bstEmpty(tree)) {
                    printf("Inserire il valore di cui si vuole il successore\n");
                    adtReadFromKeyboard(dataObj);
                    tmpDataObj = bstGetNRemoveSuccessor(tree, dataObj);
                    if (tmpDataObj == NULL) {
                        printf("Elemento non trovato\n");
                    } else {
                        printf("L'elemento e': ");
                        adtWriteToMonitor(tmpDataObj);
                    }
                    adtDestruct(tmpDataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 9:
                if(!bstEmpty(tree)) {
                    printf("Rimuovo massimo\n");
                    bstRemoveMax(tree);
                } else printf("La struttura e' vuota\n");

                break;

            case 10:
                if(!bstEmpty(tree)) {
                    printf("Rimuovo minimo\n");
                    bstRemoveMin(tree);
                } else printf("La struttura e' vuota\n");

                break;

            case 11:
                if(!bstEmpty(tree)) {
                    printf("Inserire il valore di cui si rimuovere il predecessore\n");
                    adtReadFromKeyboard(dataObj);
                    bstRemovePredecessor(tree, dataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 12:
                if(!bstEmpty(tree)) {
                    printf("Inserire il valore di cui si rimuovere il successore\n");
                    adtReadFromKeyboard(dataObj);
                    bstRemoveSuccessor(tree, dataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 13:
                if(!bstEmpty(tree)) {
                    printf("Stampo il minimo\n");
                    tmpDataObj = bstGetMin(tree);
                    adtWriteToMonitor(tmpDataObj);
                    adtDestruct(tmpDataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 14:
                if(!bstEmpty(tree)) {
                    printf("Stampo il massimo\n");
                    tmpDataObj = bstGetMax(tree);
                    adtWriteToMonitor(tmpDataObj);
                    adtDestruct(tmpDataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 15:
                if(!bstEmpty(tree)) {
                    printf("Inserire il valore di cui si trovare il predecessore\n");
                    adtReadFromKeyboard(dataObj);
                    tmpDataObj = (DataObject *) bstGetPredecessor(tree, dataObj);
                    if(tmpDataObj != NULL){
                        adtWriteToMonitor(tmpDataObj);
                    } else printf("Elemento non esistente\n");
                    adtDestruct(tmpDataObj);
                } else printf("La struttura e' vuota\n");

                break;

            case 16:
                if(!bstEmpty(tree)) {
                    printf("Inserire il valore di cui si trovare il sucessore\n");
                    adtReadFromKeyboard(dataObj);
                    tmpDataObj = (DataObject *) bstGetSuccessor(tree, dataObj);
                    if(tmpDataObj != NULL){
                        adtWriteToMonitor(tmpDataObj);
                        adtDestruct(tmpDataObj);
                    } else printf("Elemento non esistente\n");

                } else printf("La struttura e' vuota\n");

                break;

            case 17:
                if(!bstEmpty(tree)){
                    printf("La struttura non e' vuota\n");
                } else {
                    printf("La struttura e' vuota\n");
                }

                break;

            case 18:
                if(!bstEmpty(tree)) {
                    printf("Svuotamento della struttura\n");
                    bstClear(tree);
                } else printf("La struttura e' gia' vuota\n");

                break;

            case 19:
                if(!bstEmpty(tree)) {
                    printf("Inserire l'emento da cercare\n");
                    adtReadFromKeyboard(dataObj);
                    if(bstExists(tree, dataObj)){
                        printf("L'elemento e' presente all'interno della struttura\n");
                    } else printf("Elemento non presente nella struttura");
                } else printf("La struttura e' vuota\n");

                break;

            case 20:
                if(!bstEmpty(tree)) {
                    if(myMap == NULL){
                        printf("Operazione non supportata per il tipo di dato scelto\n");
                    } else {
                        if(ChoiceMap == 1){
                            printf("Per il tipo di dato scelto (interi) e' disponibile\n"
                                   "la seguente funzione: raddoppiamento");
                            bstPreOrderMap(tree, myMap, NULL);
                        } else if(ChoiceMap == 2){
                            printf("Per il tipo di dato scelto (float) e' disponibile\n"
                                   "la seguente funzione: elevazione al cubo");
                            bstPreOrderMap(tree, myMap, NULL);
                        } else if(ChoiceMap == 3){
                            printf("Per il tipo di dato scelto (stringhe) e' disponibile\n"
                                   "la seguente funzione: concatenazione di una stringa arbritraria");
                            char* par = (char*)malloc(sizeof(char)*50);
                            printf("Inserire stringa da concatenare\n");
                            scanf("%s", par);
                            bstPreOrderMap(tree, myMap, par);
                            free(par);
                        } else printf("Scelta non valida\n");
                    }
                } else printf("La struttura e' vuota\n");
                break;

            case 21:
                if(!bstEmpty(tree)) {
                    if (myFold == NULL) {
                        printf("Operazione non supportata per il tipo di dato scelto\n");
                    } else {
                        printf("Inserire discriminante (numero intero):\n");
                        scanf("%d", &par);
                        DataObject* accum = adtConstruct(inputDataType);

                        bstPreOrderFold(tree, myFold, accum->value, &par);
                        printf("Il risultato e' \n");
                        adtWriteToMonitor(accum);
                        adtDestruct(accum);
                    }
                } else printf("La struttura e' vuota\n");
                break;

            case 22:
                if(!bstEmpty(tree)) {
                    bstClear(tree);
                }
                printf("Distruzione struttura\n");
                bstDestruct(tree);
                printf("Albero distrutto\n");
                exit(0);
                break;

            default:
                printf("Scelta non valida\n");
        }
    } while((choice<0) || (choice>21) || (choice!=22));
}

/* ************************************************************************ */

int main() {
    srand(time(NULL));
    setbuf(stdout, NULL);

    int choiceData;
    int choiceMap = 0;

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
                myFold = prodottoFold;
                choiceMap = 1;
                break;

            case 2:
                printf("Creazione ADT per Float\n\n");
                inputDatatype = ConstructFloatDataType();
                myMap = cuboMap;
                myFold = sommaFold;
                choiceMap = 2;
                break;

            case 3:
                printf("Creazione ADT per Stringhe\n\n");
                inputDatatype = ConstructStringDataType();
                myMap = concatenazioneMap;
                myFold = concatenazioneFold;
                choiceMap = 3;
                break;

            case 4:
                printf("Creazione ADT per Record\n\n");
                inputDatatype = ConstructRecordDataType();
                break;

            default:
                printf("Scelta non valida!\n");
        } //fine switch

    } while ((choiceData < 1) || (choiceData > 4));

    printf("Creazione Oggetto Dato\n\n");
    inputData = adtConstruct(inputDatatype);

    BSTType* bstChosenType = NULL;
    int choiceImplementation;

    printf("Scegliere il tipo di implementazione per la creazione"
           "dell'oggetto albero:\n1-Iterativa\n2-Ricorsiva\n");
    scanf("%d", &choiceImplementation);
    if(choiceImplementation == 1){
        bstChosenType = ConstructBSTIterative();
        testBST(bstChosenType, inputData, inputDatatype, myMap, myFold, choiceMap);
        DestructBSTIterative(bstChosenType);
    } else if(choiceImplementation == 2){
        bstChosenType = ConstructBSTRecursive();
        testBST(bstChosenType, inputData, inputDatatype, myMap, myFold, choiceMap);
        DestructBSTRecursive(bstChosenType);
    } else {
        printf("Scelta non valida\n");
        return -1;
    }

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
} // fine main