#include "integerPart.h"
#include "commonMethods.h"


int *multiplicationMethodInteger(char *number, int *base) {

    int *length, *power, *result, *index;
    length = malloc(sizeof(int));
    power = malloc(sizeof(int));
    result = malloc(sizeof(int));
    index = malloc(sizeof(int));

    length = stringLength(number);

    *index = *length - 1;
    *power = 1;
    *result = 0;

    for (*index; *index >= 0; *index = *index - 1) {
        *result = *result + (*transformNumberToDecimal(number + *index) * *power);
        *power = *power * *base;
    }

    free(length);
    free(power);
    free(index);

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

char *divisionMethodInteger(char *number, int *base) {

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

