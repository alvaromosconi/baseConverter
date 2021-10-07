#include "fractionalPart.h"
#include "utilities.h"

float *divisionMethodFractional(char *number, int *base) {

    int* length, *negativePower, *digit, *index;
    float *result;

    length = malloc(sizeof(int));
    index = malloc(sizeof(int));
    digit = malloc(sizeof(int));
    negativePower = malloc(sizeof(int));
    result = malloc(sizeof(float));

    length = stringLength(number);
    *negativePower = -1;
    *digit = 0;
    *result = 0;
    *index = 0;

    while (*index < *length) {

        digit = transformNumberToDecimal(number + *index);
        *result = *result + (*digit * pow(*base, *negativePower));
        *index = *index + 1;
        *negativePower = *negativePower - 1;
    }

    free(length);
    free(index);
    free(digit);
    free(negativePower);

    return result;
}

char *multiplicationMethodFractional(char *number, int *base) {

    int* transformedNumber, *reminder, *index;
    char* result;

    transformedNumber = malloc(sizeof(int));
    reminder = malloc(sizeof(int));
    index = malloc(sizeof(int));
    result = malloc(20*sizeof(char));

    *transformedNumber = atoi(number);
    *index = 0;

    while (*index < 10) {

        *reminder = (*transformedNumber * *base) / 100000;
     //   printf("numero: %i, resto: %i\n",*transformedNumber, *reminder);
        *transformedNumber = (*transformedNumber * *base) % 100000;
        *index = *index + 1;
        setEquivalentDigit((result + *index), reminder);
    }

    *(result + *index) = '\0';

    free(transformedNumber);
    free(reminder);
    free(index);

    return result;
}
