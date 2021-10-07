#include "integerPart.h"
#include "utilities.h"

int *multiplicationMethodInteger(char *number, int *base, short int *detailed) {

    int *length, *power, *result, *index, *digit, *instanceResult;

    length = malloc(sizeof(int));
    power = malloc(sizeof(int));
    result = malloc(sizeof(int));
    index = malloc(sizeof(int));
    digit = malloc(sizeof(int));
    instanceResult = malloc(sizeof(int));

    length = stringLength(number);

    *index = *length - 1;
    *power = 0;
    *result = 0;
    *digit = 0;
    *instanceResult = 0;

    if (*detailed)
        printf("\n --------------------- Inicio del proceso de conversion ---------------------");

    for (*index; *index >= 0; *index = *index - 1) {

        digit = transformNumberToDecimal(number + *index);
        *instanceResult = (*digit * pow(*base, *power));
        *result = *result + *instanceResult;

        if (*detailed)
            printf("\n R%i --> %i * %i^%i = %i\n",*power, *digit, *base, *power, *instanceResult);

        *power = *power + 1;
    }

    if (*detailed) {
        *index = *index +1;
        printf("\n Numero Convertido -->");
        for (*index; *index < *power; *index = *index + 1){
            printf(" R%i ",*index);
            if (*index < *power - 1)
                printf("+");
       }

       printf(" = %i",*result);
       printf("\n ---------------------- Fin del proceso de conversion -----------------------");
    }

    free(length);
    free(power);
    free(index);
    free(digit);
    free(instanceResult);

    return result;
}

int *getLengthOfNumber(int* number) {

    int *length;
    length = malloc(sizeof(int));
    *length = 0;

    while (*number != 0) {

        *number /= 10;
        *length = *length + 1;
    }

     return length;
}

void setEquivalentDigit(char *currentDigit, int *reminder) {

    char *newDigit;
    newDigit = malloc(sizeof(char));

    if (*reminder >= 0 && *reminder <= 9)
        *newDigit = '0' + *reminder;
    else
        *newDigit = 'A' + (*reminder - 10);

    *currentDigit = *newDigit;
}

//MODIFICAR PARA PUNTEROS
void reverseString (char *stringToReverse) {

    int *i, *length;
    char *temporalChar;

    i = malloc(sizeof(int));
    length = malloc(sizeof(int));
    temporalChar = malloc(sizeof(char));

    *i = 0;
    length = stringLength(stringToReverse);
    *temporalChar = '0';

    for (*i; *i < *length / 2; ++*i) {
        *temporalChar = *(stringToReverse + *i);
        *(stringToReverse + *i) = *(stringToReverse + (*length - *i - 1));
        *(stringToReverse + (*length - *i - 1)) = *temporalChar;
    }

    free(i);
    free(length);
    free(temporalChar);

}

char *divisionMethodInteger(char *number, int *base, short int *detailed) {

    int *transformedNumber, *reminder, *index;
    char *result;

    transformedNumber = malloc(sizeof(int));
    reminder = malloc(sizeof(int));
    index = malloc(sizeof(int));
    result = malloc(20 * sizeof(char));

    *transformedNumber = atoi(number);
    *reminder = 0;
    *index = 0;

    while (*transformedNumber != 0) {

        *reminder = *transformedNumber % *base;
        // printf("numero: %i, resto: %i\n",*transformedNumber, *reminder);
        *transformedNumber /= *base;
        *index = *index + 1;
        setEquivalentDigit((result + *index), reminder);
    }

    reverseString(result);

    *(result + *index) = '\0';

    free(transformedNumber);
    free(reminder);
    free(index);

    return result;
}

