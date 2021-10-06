#include <stdio.h>
#include <stdlib.h>
#include "convert.h"


int main(int argc, char * argv[]) {

    parseArguments(argc, argv);

    return EXIT_SUCCESS;
}

/**
 * Procedimiento encargado de analizar los argumentos e invocar a otros/as procedimientos y funciones.
 * @param nArg
          Indica el numero de argumentos ingresados por el usuario.
 * @param argv
          Contiene los argumentos ingresados por el usuario.
 */
void parseArguments(int nArg, char *argv[]) {

    int *baseS, *baseD, *index;

    char * num, *integerSide, *fractionalSide;

    baseS = malloc(sizeof(int));
    baseD = malloc(sizeof(int));
    index = malloc(sizeof(int));
    num = malloc(sizeof(char));
    fractionalSide = malloc(6 * sizeof(char));
    integerSide = malloc(11 * sizeof(char));

    *baseS = 10;
    *baseD = 10;
    *index = 1;
    *num = 0;
    *fractionalSide = '0';
    *integerSide = '0';

    for (*index = 1; *index < nArg; ++*index) {

        if (nArg < 3 || *stringCompare(argv[*index], "-h") == 1)
            help();
       // printf("%s", argv[*index]);
        else if (*stringCompare(argv[*index], "-n") == 1)
             num = argv[++*index];
        else if (*stringCompare(argv[*index], "-s") == 1)
             *baseS = atoi(argv[++*index]);
        else if (*stringCompare(argv[*index], "-d") == 1)
             *baseD = atoi(argv[++*index]);
    }


    printf("Parte Fraccionaria: %s \n", getFractionalSide(num, fractionalSide));
    //printf("Largo de la parte fraccionaria: %i\n", *stringLength(getFractionalSide(num, fractionalSide)));
    printf("Parte Entera: %s \n", getIntegerSide(num, integerSide));

    if (*validateNumber(num, baseS) == 1)
        printf("%s", "Valido");
    else
        printf("%s", "Invalido");


    printf("\nDatos ingresados --> Numero ingresado: %s. Base origen: %i. Base destino: %i", num, *baseS, *baseD);

    free(baseS);
    free(baseD);
    free(index);
    free(num);
    free(integerSide);
    free(fractionalSide);
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
 * Procedimiento encargado de proveer la correcta sintaxis y semantica al usuario.
 */
void help() {

    printf("\n Bienvenido al convertidor de bases programado en C.\n");
    printf("\n A continuacion se indican las opciones de invocacion del programa:\n\n\t");
    printf("-n numero real :: Indica el numero al que se le hara el cambio de base. Maxima cantidad de digitos enteros: 10. Maxima cantidad de digitos fraccionarios: 5.\n\t");
    printf("-s base origen :: Especifica la base a la que pertence el numero ingresado. Bases permitidas: [2,16]. \n\t");
    printf("-d base destino ::  Especifica la base a la que pertence el numero ingresado. Bases permitidas: [2,16]. \n\t");
    printf("-v computos intermedios :: Permite visualizar en forma secuencial y ordenada los computos realizados para cambiar el numero ingresado de la base origen a la base destino. \n\t");
    printf("-h ayuda :: Provee informacion para poder utilizar el programa de forma correcta. \n\t");
    exit(0);
}

/**
 * Funcion encargada de verificar si el numero recibido por parametro corresponde a la base recibida por parametro.
 * @param number
          Numero ingresado por el usuario (cadena de caracteres).
 * @param base
          Base numerica ingresada por el usuario.
 * @return 1 si el numero corresponde a la base, 0 en caso contrario.
 *
 */
int *validateNumber(const char *number, int *base) {

    int *flag;
    int * toReturn;

    toReturn = malloc(sizeof(int));
    flag = malloc(sizeof(int));
    *flag = 1;

    if (*base > 16)
        *toReturn = 0;

    else if (*base <= 10)

        while (*number >= '0' && *number < ('0' + *base) || (*number == '.' && *flag == 1)) {

             if (*number == '.')
                *flag = 0;

             number++;
        }

    else

        while( (*number >= '0' && *number <= ('0' + *base)) ||
               (*number >= 'A' && *number < ('A' + *base - 10)) ||
               (*number == '.' && *flag == 1)) {
                if (*number == '.')
                    *flag = 0;

                number++;
        }

   if (*number == '\0')
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

/**
 * Funcion encargada de extraer la parte fraccionaria del numero ingresado.
 * @param number
          Numero ingresado por el usuario (cadena de caracteres).
 * @param destination
          Puntero auxiliar para ubicar el inicio de la cadena a retornar.
 * @return Parte fraccionaria del numero ingresado.
 */
char *getFractionalSide(const char *number, char *destination) {

    char *fractionalSide = destination;
    int *flag;
    flag = malloc(sizeof(short int));
    *flag = 1;

    while (*number != '.' && *flag == 1) {
        number++;
        if (*number == '\0')
            *flag = 0;
    }

    number++;

    while (*number != '\0' && *flag == 1)
        *fractionalSide++ = *number++;

    *fractionalSide = '\0';

    if (*flag == 0)
        *destination = '\0';

    return destination;
}

/**
 * Funcion encargada de extraer la parte entera del numero ingresado.
 * @param number
          Numero ingresado por el usuario (cadena de caracteres).
 * @param destination
          Puntero auxiliar para ubicar el inicio de la cadena a retornar.
 * @return Parte entera del numero ingresado.
 */
char *getIntegerSide(const char *number, char *destination) {

    char *integerSide = destination;

    while (*number != '.' && *number != '\0')
        *integerSide++ = *number++;

    *integerSide = '\0';

    return destination;
}



