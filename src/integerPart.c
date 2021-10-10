#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "integerPart.h"
#include "utilities.h"

/**
 * Procedimiento encargado de invertir una cadena de caracteres.
 * @param stringToReverse
          Puntero a char que apunta a el primer caracter de la parte entera del numero ingresado por el usuario ya convertido a base destino(expresado en cadena de caracteres).
 *
 */
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

/**
 * Funcion encargada de llevar a cabo el metodo de la division para la parte entera del numero ingresado por el usuario.
 * @param number
          Puntero a char que apunta al primer caracter de la parte entera del numero ingresado por el usuario (expresado en cadena de caracteres).
 * @param base
          Puntero a entero que apunta al entero que representa la base numerica destino ingresada por el usuario.
 * @param detailed
          Puntero a entero que apunta al numero 1 si el usuario ingreso el parametro "-v", 0 si el usuario no ingreso el parametro "-v".
 * @return Puntero a char que apunta al primer caracter del numero entero ya convertido a base destino.
 *
 */
char *divisionMethodInteger(char *number, int *base, int *detailed) {

    int *transformedNumber, *reminder, *index;
    char *result;

    transformedNumber = malloc(sizeof(int));
    reminder = malloc(sizeof(int));
    index = malloc(sizeof(int));
    result = malloc(*getRequiredSizeForNumber(number, base) * sizeof(char));         // Se obtendra la cantidad de digitos necesarios para representar el numero en la base destino

    *transformedNumber = atoi(number);
    *reminder = 0;
    *index = 0;
    *result = '0';

    // IMPRESION DE DATOS ("-v")
    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE ENTERA) ---------------------\n\n");

    while (*transformedNumber != 0) {

        // IMPRESION DE DATOS ("-v")
        if (*detailed)
            printf("%i.   %i / %i",(*index) + 1, *transformedNumber, *base);

        *reminder = *transformedNumber % *base;             // Se almacena el resto de la division
        *transformedNumber /= *base;                        // Se divide el numero por la base
        setEquivalentDigit((result + *index), reminder);    // Se obtiene el digito transformado en la base correspondiente

        // IMPRESION DE DATOS ("-v")
        if (*detailed)
            printf(" \t--- Resto%i = %i <=> (%c)b%i --- Cociente: %i\n",(*index)+1, *reminder, *(result + *index), *base,*(transformedNumber));

        *index = *index + 1;
    }

    *(result + *index) = '\0';
    reverseString(result);

    // IMPRESION DE DATOS ("-v")
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

/**
 * Funcion encargada de llevar a cabo el metodo de la multiplicacion para la parte entera del numero ingresado por el usuario.
 * @param number
          Puntero a char que apunta al primer caracter de la parte entera del numero ingresado por el usuario (expresado en cadena de caracteres).
 * @param base
          Puntero a entero que apunta al entero que representa la base numerica origen ingresada por el usuario.
 * @param detailed
          Puntero a entero que apunta al numero 1 si el usuario ingreso el parametro "-v", 0 si el usuario no ingreso el parametro "-v".
 * @return Puntero a char que almacena el numero fraccional ya convertido a base 10.
 *
 */
int *multiplicationMethodInteger(char *number, int *base, int *detailed) {

    int *length, *power, *result, *index, *digit, *temporaryResult, *transformedNumber;

    power = malloc(sizeof(int));
    result = malloc(sizeof(int));
    index = malloc(sizeof(int));
    digit = malloc(sizeof(int));
    temporaryResult = malloc(sizeof(int));
    transformedNumber = malloc(sizeof(int));

    length = stringLength(number);

    *index = *length - 1;
    *power = 0;
    *result = 0;
    *digit = 0;
    *temporaryResult = 0;
    *transformedNumber = atoi(number);

    // IMPRESION DE DATOS ("-v")
    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE ENTERA) ---------------------\n");

    for (*index = *index; *index >= 0; *index = *index - 1) {

        digit = transformNumberToDecimal(number + *index);      // Transformo el digito actual del numero ingresado a decimal
        *temporaryResult = (*digit * pow(*base, *power));       // Multiplico el digito actual por la base elevado a la potencia (de acuerdo a la posicion)
        *result = *result + *temporaryResult;                   // Adiciono el resultado obtenido en temporaryResult en una variable.

        // IMPRESION DE DATOS ("-v")
        if (*detailed)
            printf("\n R%i --> %i * %i^%i = %i\n", *power, *digit, *base, *power, *temporaryResult);

        *power = *power + 1;                                    // Aumento la potencia
    }

    // IMPRESION DE DATOS ("-v")
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
    free(temporaryResult);
    free(transformedNumber);

    return result;
}

