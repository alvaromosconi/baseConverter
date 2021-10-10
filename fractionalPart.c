#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fractionalPart.h"
#include "utilities.h"

/**
 * Funcion encargada de llevar a cabo el metodo de la division para la parte fraccional del numero ingresado por el usuario.
 * @param number
          Puntero a char que almacena la parte fraccionaria del numero ingresado por el usuario (expresado en cadena de caracteres).
 * @param base
          Puntero a entero que almacena la base numerica origen ingresada por el usuario.
 * @param detailed
          Puntero a entero corto que almacena un 1 si el usuario ingreso el parametro "-v", 0 si el usuario no ingreso el parametro "-v".
 * @return Puntero a float que almacena el numero fraccional ya convertido a base 10.
 *
 */
float *divisionMethodFractional(char *number, int *base, int *detailed) {

    int *length, *negativePower, *digit, *index, *transformedNumber;
    float *temporaryResult, *result;

    length = malloc(sizeof(int));
    index = malloc(sizeof(int));
    digit = malloc(sizeof(int));
    negativePower = malloc(sizeof(int));
    transformedNumber = malloc(sizeof(int));

    temporaryResult = malloc(sizeof(float));
    result = malloc(sizeof(float));

    length = stringLength(number);
    *negativePower = -1;
    *digit = 0;
    *result = 0;
    *index = 0;
    *temporaryResult = 0;

    *transformedNumber = atoi(number);

    // Si el numero no es 0, entonces llevar a cabo la conversion
    if (*transformedNumber != 0) {

        // IMPRESION DE DATOS ("-v")
        if (*detailed)
            printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE FRACCIONARIA) ---------------------\n");

        while (*index < *length) {

            digit = transformNumberToDecimal(number + *index);        // Transformo el digito actual del numero ingresado a decimal
            *temporaryResult = (*digit * pow(*base, *negativePower)); // Multiplico el digito actual por la base elevado a la potencia negativa (de acuerdo a la posicion)
            *result = *result + *temporaryResult;                     // Adiciono el resultado obtenido en temporaryResult en una variable.

            if (*detailed)
                printf("\n R%i --> %i * %i^%i = %f\n",*negativePower, *digit, *base, *negativePower, *temporaryResult);

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

           printf(" = (%f)b10\n",*result);
           printf("\n ---------------------- FIN DE LA CONVERSION (PARTE FRACCIONARIA) -----------------------");
        }
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
          Puntero a char que almacena la parte fraccionaria del numero ingresado por el usuario (expresado en cadena de caracteres).
 * @param base
          Puntero a entero que almacena la base numerica destino ingresada por el usuario.
 * @param detailed
          Puntero a entero corto que almacena un 1 si el usuario ingreso el parametro "-v", 0 si el usuario no ingreso el parametro "-v".
 * @return Puntero a char que almacena el numero fraccional ya convertido a base destino.
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
    finalResult = malloc(10 * sizeof(char));

    length = stringLength(number);

    *transformedNumber = atof(number) / pow (10, *length); // Se transforma el numero a double y se lo corre 10^(cantidad de digitos) lugares.
    *index = 0;
    *integerPart = 0;
    *finalResult = '0';

    // Si el numero no es 0, entonces llevar a cabo la conversion
    if (*transformedNumber != (double) 0) {
        // IMPRESION DE DATOS ("-v")
        if (*detailed)
            printf("\n\n --------------------- INICIO DE LA CONVERSION (PARTE FRACCIONARIA) ---------------------\n");

        while (*index < 10 && *transformedNumber != (double) 0) {

            *multiplicationResult = (*transformedNumber * *base);                 // Se multiplica el numero actual por la base y se obtiene la parte entera

            // IMPRESION DE DATOS ("-v")
            if (*detailed)
                printf("\nR%i --> %lf * %i = %i\t",(*index), *transformedNumber, *base, (int) *multiplicationResult);

            *transformedNumber = *multiplicationResult - (int) *multiplicationResult;    // Se le resta la parte entera al numero actual
            *integerPart = (int) *multiplicationResult;                                  // Se almacena la parte entera
            setEquivalentDigit((finalResult + *index), integerPart);                    // Se setea el digito equivalente en la base requerida

            // IMPRESION DE DATOS ("-v")
            if (*detailed)
                printf("<==> (%c)b%i", *(finalResult + *index), *base);

            *index = *index + 1;
        }

        *(finalResult + *index) = '\0';

        // IMPRESION DE DATOS ("-v")
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
    }

    else
        *(finalResult + 1) = '\0';

    free(multiplicationResult);
    free(index);
    free(transformedNumber);
    free(integerPart);
    free(length);

    return finalResult;
}
