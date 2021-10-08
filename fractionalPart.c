#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fractionalPart.h"
#include "utilities.h"

float *divisionMethodFractional(char *number, int *base, short int *detailed) {

    int *length, *negativePower, *digit, *index;
    float *temporaryResult, *result;

    length = malloc(sizeof(int));
    index = malloc(sizeof(int));
    digit = malloc(sizeof(int));
    negativePower = malloc(sizeof(int));

    temporaryResult = malloc(sizeof(float));
    result = malloc(sizeof(float));

    length = stringLength(number);
    *negativePower = -1;
    *digit = 0;
    *result = 0;
    *index = 0;
    *temporaryResult = 0;

    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE FRACCIONARIA) ---------------------\n");

    while (*index < *length) {

        digit = transformNumberToDecimal(number + *index);
        *temporaryResult = (*digit * pow(*base, *negativePower));
        *result = *result + *temporaryResult;

        if (*detailed)
            printf("\n R%i --> %i * %i^%i = %f\n",*negativePower, *digit, *base, *negativePower, *temporaryResult);

        *index = *index + 1;
        *negativePower = *negativePower - 1;
    }

    if (*detailed) {


        printf("\n Numero Convertido --> ");

        for (*negativePower = *negativePower + 1; *negativePower < 0; *negativePower = *negativePower + 1){

            printf("R%i",*negativePower);

            if (*negativePower < -1)
                printf(" + ");
       }

       printf(" = (%f)b10\n",*result);
       printf("\n ---------------------- FIN DE LA CONVERSION (PARTE FRACCIONARIA) -----------------------");
    }

    free(length);
    free(index);
    free(digit);
    free(negativePower);
    free(temporaryResult);

    return result;
}

char *multiplicationMethodFractional(char *number, int *base, short int *detailed) {

    int *index, *integerPart, *length;
    double *transformedNumber, *multiplicationResult;
    char* finalResult;

    index = malloc(sizeof(int));
    integerPart = malloc(sizeof(int));
    multiplicationResult = malloc(sizeof(double));
    transformedNumber = malloc(sizeof(double));
    finalResult = malloc(11 * sizeof(char));

    length = stringLength(number);

    *transformedNumber = (double) atoi(number) / pow (10, *length);
    *index = 0;
    *integerPart = 0;

    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE FRACCIONARIA) ---------------------\n");

    while (*index < 11) {

        *multiplicationResult = (int) (*transformedNumber * *base);

        if (*detailed)
            printf("\nR%i --> %lf * %i = %i\t",(*index), *transformedNumber, *base, (int) *multiplicationResult);

        *transformedNumber = (*transformedNumber * *base) - *multiplicationResult;
        *integerPart = *multiplicationResult;
        setEquivalentDigit((finalResult + *index), integerPart);

        if (*detailed)
            printf("<==> (%c)b%i", *(finalResult + *index), *base);

        *index = *index + 1;
    }

    if (*detailed) {

        printf("\n\nNumero Convertido --> ");

        int *temporalIndex;
        temporalIndex = malloc(sizeof(int));

        for (*temporalIndex = 0; *temporalIndex < *index; (*temporalIndex)++)

            printf("[Resto%i]",*temporalIndex);

         printf(" = (%s)b%i\n", finalResult, *base);
         printf("\n ---------------------- FIN DE LA CONVERSION (PARTE FRACCIONARIA) -----------------------\n");

        free(temporalIndex);
    }

    *(finalResult + *index - 1) = '\0';

    free(multiplicationResult);
    free(index);
    free(transformedNumber);
    free(integerPart);
    free(length);

    return finalResult;
}
