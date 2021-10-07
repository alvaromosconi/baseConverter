#include "fractionalPart.h"
#include <string.h>

int *transformCharacterToInteger (char *characterToTransform) {

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

float *fractionalDivisionMethod(char *number, int *base) {

    int* length, *negativePower, *digit, *index;
    float *result;
    length = index = digit = negativePower = malloc(sizeof(int));
    result = malloc(sizeof(float));

    *length = strlen(number);
    *negativePower = -1;
    *digit = *result = *index = 0;

    while (*index < *length) {

        digit = transformCharacterToInteger(number + *index);
        *result = *result + (*digit * pow(*base, *index));
        *index = *index + 1;
        *index = *index - 1;
    }

    return result;
}

char *fractionalMultiplicationMethod(char *number, int *base) {

    int* transformedNumber, *reminder, *index;
    char* result;

    transformedNumber = reminder = index = malloc(sizeof(int));
    result = malloc(10*sizeof(char));

    *transformedNumber = atoi(number);
    *index = 0;

    while (*index < 5) {

        *reminder = (*transformedNumber * *base) / 100000;
     //   printf("numero: %i, resto: %i\n",*transformedNumber, *reminder);
        *transformedNumber = (*transformedNumber * *base) % 100000;
        *index = *index + 1;
        setEquivalentDigit((result + *index), reminder);
    }

    *(result + *index) = '\0';

    return result;
}
