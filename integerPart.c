#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "integerPart.h"
#include "utilities.h"

int *multiplicationMethodInteger(char *number, int *base, short int *detailed) {

    int *length, *power, *result, *index, *digit, *temporaryResult;

    power = malloc(sizeof(int));
    result = malloc(sizeof(int));
    index = malloc(sizeof(int));
    digit = malloc(sizeof(int));
    temporaryResult = malloc(sizeof(int));

    length = stringLength(number);

    *index = *length - 1;
    *power = 0;
    *result = 0;
    *digit = 0;
    *temporaryResult = 0;

    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE ENTERA) ---------------------\n");

    for (*index = *index; *index >= 0; *index = *index - 1) {

        digit = transformNumberToDecimal(number + *index);
        *temporaryResult = (*digit * pow(*base, *power));
        *result = *result + *temporaryResult;

        if (*detailed)
            printf("\n R%i --> %i * %i^%i = %i\n", *power, *digit, *base, *power, *temporaryResult);

        *power = *power + 1;
    }

    if (*detailed) {

        *index = *index +1;
        printf("\n Numero Convertido -->");

        for (*index = *index; *index < *power; *index = *index + 1){

            printf(" R%i ",*index);

            if (*index < *power - 1)
                printf("+");
        }

        printf(" = (%i)b10\n", *result);
        printf("\n ---------------------- FIN DE LA CONVERSION (PARTE ENTERA) -----------------------");
    }

    free(length);
    free(power);
    free(index);
    free(digit);
    free(temporaryResult);;

    return result;
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

    for (*i = *i; *i < *length / 2; ++*i) {
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


    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE ENTERA) ---------------------\n\n");

    while (*transformedNumber != 0) {

        if (*detailed)
            printf("%i.   %i / %i",(*index) + 1, *transformedNumber, *base);

        *reminder = *transformedNumber % *base;
        *transformedNumber /= *base;
        setEquivalentDigit((result + *index), reminder);

        if (*detailed)
            printf(" \t--- Resto%i = %i <=> (%c)b%i --- Cociente: %i\n",(*index)+1, *reminder, *(result + *index), *base,*(transformedNumber));

        *index = *index + 1;
    }

    *(result + *index) = '\0';
    reverseString(result);

    if (*detailed) {

        printf("\nNumero Convertido --> ");

        for (*index = *index; *index > 0; (*index = *index -1)) {

            printf("[Resto%i]",*index);
        }
         printf(" = (%s)b%i", result, *base);
         printf("\n\n ---------------------- FIN DE LA CONVERSION (PARTE ENTERA) -----------------------");
    }


    free(transformedNumber);
    free(reminder);
    free(index);

    return result;
}

