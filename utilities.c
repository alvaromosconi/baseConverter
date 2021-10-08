#include "utilities.h"

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
 * @param a
          Cadena de caracteres.
 * @param b
          Cadena de caracteres.
 * @return 1 si las cadenas son iguales, 0 si son distintas.
 *
 */
int *stringCompare(const char *a, const char *b) {

   int *toReturn;
   toReturn = malloc(sizeof(int));
   *toReturn = 0;

   while (*a == *b) {
      if (*a == '\0' || *b == '\0')
         break;

      a++;
      b++;
   }

   if (*a == '\0' && *b == '\0')
      *toReturn = 1;

    return toReturn;
}

/**
 * Funcion encargada de contar la cantidad de caracteres de una cadena de caracteres.
 * @param string
          Cadena de caracteres ingresada por el usuario.
 * @return Cantidad de caracteres de la cadena recibida.
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

void setEquivalentDigit(char *currentDigit, int *reminder) {

    char *newDigit;
    newDigit = malloc(sizeof(char));

    if (*reminder >= 0 && *reminder <= 9)
        *newDigit = '0' + *reminder;
    else
        *newDigit = 'A' + (*reminder - 10);

    *currentDigit = *newDigit;
}

