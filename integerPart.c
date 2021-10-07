#include "integerPart.h"

int *transformNumberToDecimal (char *characterToTransform) {

    int *digitToReturn;
    digitToReturn = malloc(sizeof(int));
    *digitToReturn = 0;

    if (*characterToTransform >= '0' && *characterToTransform <= '9')
        *digitToReturn = (int) *characterToTransform - 48;

    else if ( (*characterToTransform >= 'a' && *characterToTransform <= 'f'))
         *digitToReturn = (int) *characterToTransform - 87;

    else if (*characterToTransform >= 'A' && *characterToTransform <= 'F')
         *digitToReturn = (int) *characterToTransform - 55;

    return digitToReturn;
}


int *fromAnyBaseToDecimal(char *number, int *base) {

    int *length, *power, *result, *index;
    length = power = result = index = malloc(sizeof(int));

    length = strlen(number);

    *index = *length - 1;
    *power = 1;
    *result = 0;

    for (*index; *index >= 0; --*index) {
        *result = *result + *transformNumberToDecimal(number + *index) * *power;
        *power = *power * *base;
    }

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

    i = length = malloc(sizeof(int));
    temporalChar = malloc(sizeof(char));

    *i = 0;
    *length = strlen(stringToReverse);
    *temporalChar = '0';

    for (*i; *i < *length / 2; ++*i) {
        *temporalChar = *(stringToReverse + *i);
        *(stringToReverse + *i) = *(stringToReverse + (*length - *i - 1));
        *(stringToReverse + (*length - *i - 1)) = *temporalChar;
    }
}

char *fromDecimalBaseToAnyBase(char *number, int *base) {

    int *transformedNumber, *reminder, *index;
    char* result;

    transformedNumber = reminder = index = malloc(sizeof(int));
    result = malloc(20 * sizeof(char));

    *transformedNumber = atoi(number);
    *reminder = *index = 0;

    while (*transformedNumber != 0) {

        *reminder = *transformedNumber % *base;
        printf("numero: %i, resto: %i\n",*transformedNumber, *reminder);
        *transformedNumber /= *base;
        *index = *index + 1;
        setEquivalentDigit((result + *index), reminder);
    }

    reverseString(result);

    *(result + *index) = '\0';

    return result;
}

