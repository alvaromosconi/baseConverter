#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"

/**
 * Funcion encargada de transformar un caracter ASCII a su entero decimal equivalente.
 * @param characterToTransform
          Puntero a char que apunta al caracter a transformar.
 * @return Puntero a entero que apunta a un entero decimal equivalente al char recibido por parametro.
 *
 */
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

/**
 * Funcion encargada de comparar cadena de caracteres (strings).
 * @param cadenaA
          Puntero a char que apunta al primer caracter de la cadenaA.
   @param cadenaB
          Puntero a char que apunta al primer caracter de la cadenaB.
 * @return Puntero a entero que apunta a un 1 si las cadenas eran iguales y a un 0 en caso contrario.
 */
int *stringCompare(const char *cadenaA, const char *cadenaB) {

   int *toReturn;
   toReturn = malloc(sizeof(int));
   *toReturn = 0;

   while (*cadenaA == *cadenaB) {
      if (*cadenaA == '\0' || *cadenaB == '\0')
         break;

      cadenaA++;
      cadenaB++;
   }

   if (*cadenaA == '\0' && *cadenaB == '\0')
      *toReturn = 1;

    return toReturn;
}

/**
 * Funcion encargada de contar la cantidad de caracteres de una cadena de caracteres.
 * @param string
          Puntero a char que apunta al primer caracter de la cadena ingresada por el usuario.
 * @return Puntero a entero que apunta a un entero que representa la cantidad de caracteres de la cadena recibida.
 */
int *stringLength(char *string) {

    int *length;
    length = malloc(sizeof(int));
    *length = 0;

    while (*string != '\0') {
        string++;
        *length = *length + 1;
    }

    return length;
}

/**
 * Procedimiento encargado de asignar el caracter equivalente al numero recibido por parametro.
 * @param currentDigit
          Puntero a char que almacena la posicion de memoria correspondiente al digito a transformar a base destino.
 * @param reminder
          Puntero a entero que apunta al resto resultante de la division (expresado en base origen)
 */
void setEquivalentDigit(char *currentDigit, int *reminder) {

    char *newDigit;
    newDigit = malloc(sizeof(char));

    if (*reminder >= 0 && *reminder <= 9)
        *newDigit = '0' + *reminder;
    else if (*reminder >= 9 && *reminder <= 15)
        *newDigit = 'A' + (*reminder - 10);

    *currentDigit = *newDigit;
}

/**
 * Funcion encargarda de retornar la cantidad de digitos necesarias para representar el numero ingresado en base destino.
 * @param number
          Puntero a char que apunta al primer caracter del numero ingresado por el usuario (expresado en cadena de caracteres).
 * @param destinationBase
          Puntero a entero que apunta al entero que representa la base numerica destino ingresada por el usuario.
 * @return Puntero a entero que apunta al entero que indica la cantidad de digitos necesarios para representar el numero ingresado en base destino.
 */
int *getRequiredSizeForNumber(char *number, int *destinationBase) {

    int *transformedNumber, *valueToReturn;
    transformedNumber = malloc(sizeof(int));
    valueToReturn = malloc(sizeof(int));

    *transformedNumber = atoi(number);

    *valueToReturn = (int)(log(*transformedNumber)/log(*destinationBase) + 1);

    return valueToReturn;
}

