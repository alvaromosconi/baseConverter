#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fractionalPart.h"
#include "utilities.h"

/**
 * Funcion encargada de llevar a cabo el metodo de la division para la parte fraccional del numero ingresado por el usuario.
 * @param number
          Puntero a char que apunta al primer caracter de la parte fraccionaria del numero ingresado por el usuario (expresado en cadena de caracteres).
 * @param base
          Puntero a entero que apunta al numero que representa la base numerica origen ingresada por el usuario.
 * @param detailed
          Puntero a entero que apunta al numero 1 si el usuario ingreso el parametro "-v", 0 si el usuario no ingreso el parametro "-v".
 * @return Puntero a double que apunta al numero fraccional ya convertido a base 10.
 *
 */
double *divisionMethodFractional(char *number, int *base, int *detailed) {

    int *length, *negativePower, *digit, *index;
    double *temporaryResult, *result;

    length = malloc(sizeof(int));
    index = malloc(sizeof(int));
    digit = malloc(sizeof(int));
    negativePower = malloc(sizeof(int));

    temporaryResult = malloc(sizeof(double));
    result = malloc(sizeof(double));

    length = stringLength(number);
    *negativePower = -1;
    *digit = 0;
    *result = 0.0;
    *index = 0;
    *temporaryResult = 0.0;

    // IMPRESION DE DATOS ("-v")
    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE FRACCIONARIA) METODO DE LA DIVISION---------------------\n");

    while (*index < *length) {

        digit = transformNumberToDecimal(number + *index);        // Transformo el digito actual del numero ingresado a decimal
        *temporaryResult = (*digit * pow(*base,*negativePower));  // Multiplico el digito actual por la base elevado a la potencia negativa (de acuerdo a la posicion)
        *result = (*result + *temporaryResult);                   // Adiciono el resultado obtenido en temporaryResult en una variable.

        if (*detailed)
            printf("\n R%i --> %i * %i^%i = %.20lf\n",*negativePower, *digit, *base, *negativePower, *temporaryResult);

        *index = *index + 1;                                      // Aumento el indice (variable control)
        *negativePower = *negativePower - 1;                      // Disminuyo la variable que marca la potencia negativa.
    }

    // IMPRESION DE DATOS ("-v")
    if (*detailed) {

        printf("\n Numero Convertido --> ");

        for (*negativePower = *negativePower + 1; *negativePower < 0; *negativePower = *negativePower + 1){

            printf("R%i",*negativePower);

            if (*negativePower < -1)
                printf(" + ");
        }

        printf(" = (%.20lf)b10\n",*result);
        printf("\n ---------------------- FIN DE LA CONVERSION (PARTE FRACCIONARIA) -----------------------");
    }

    free(length);
    free(index);
    free(digit);
    free(negativePower);
    free(temporaryResult);

    return result;
}


/**
 * Funcion encargada de llevar a cabo el metodo de la multiplicacion para la parte fraccional del numero ingresado por el usuario.
 * @param number
          Puntero a char que apunta al primer caracter de la parte fraccionaria del numero ingresado por el usuario (expresado en cadena de caracteres).
 * @param base
          Puntero a entero que apunta al numero que representa la base numerica destino ingresada por el usuario.
 * @param detailed
          Puntero a entero que apunta al numero 1 si el usuario ingreso el parametro "-v", 0 si el usuario no ingreso el parametro "-v".
 * @return Puntero a char que apunta al primer caracter del numero fraccional ya convertido a base destino.
 *
 */
char *multiplicationMethodFractional(char *number, int *base, int *detailed) {

    int *index, *integerPart, *length;
    double *transformedNumber, *multiplicationResult;
    char* finalResult;

    index = malloc(sizeof(int));
    integerPart = malloc(sizeof(int));
    multiplicationResult = malloc(sizeof(double));
    transformedNumber = malloc(sizeof(double));
    finalResult = malloc(20 * sizeof(char));

    length = stringLength(number);
    *transformedNumber = atof(number) / pow (10, *length); // Se transforma el numero a double y se lo corre 10^(cantidad de digitos) lugares.
    *index = 0;
    *integerPart = 0;
    *finalResult = '0';

    // IMPRESION DE DATOS ("-v")
    if (*detailed)
        printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE FRACCIONARIA) METODO DE LA MULTIPLICACION ---------------------\n");

    while (*index < 20) {

        *multiplicationResult = (*transformedNumber * *base);                 // Se multiplica el numero actual por la base y se obtiene la parte entera

        // IMPRESION DE DATOS ("-v")
        if (*detailed)
            printf("\n%i. --> %.20lf * %i = %i\t",(*index), *transformedNumber, *base, (int) *multiplicationResult);

        *transformedNumber = *multiplicationResult - (int) *multiplicationResult;    // Se le resta la parte entera al numero actual
        *integerPart = (int) *multiplicationResult;                                  // Se almacena la parte entera
        setEquivalentDigit((finalResult + *index), integerPart);                    // Se setea el digito equivalente en la base requerida

        // IMPRESION DE DATOS ("-v")
        if (*detailed)
            printf("D%i ==> (%c)b%i", *index,*(finalResult + *index), *base);

        *index = *index + 1;
    }

    *(finalResult + *index) = '\0';

    // IMPRESION DE DATOS ("-v")
    if (*detailed) {

        printf("\n\nNumero Convertido --> ");

        int *temporalIndex;
        temporalIndex = malloc(sizeof(int));

        for (*temporalIndex = 0; *temporalIndex < *index; (*temporalIndex)++)

            printf("[Digito%i]",*temporalIndex);

        printf(" = (%s)b%i\n", finalResult, *base);
        printf("\n ---------------------- FIN DE LA CONVERSION (PARTE FRACCIONARIA) -----------------------\n");

        free(temporalIndex);
    }

    free(multiplicationResult);
    free(index);
    free(transformedNumber);
    free(integerPart);
    free(length);

    return finalResult;
}
