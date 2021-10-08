#include <stdio.h>
#include <stdlib.h>
#include "convert.h"
#include "integerPart.h"
#include "fractionalPart.h"
#include "utilities.h"

int main(int argc, char * argv[]) {

    exit(*parseArguments(argc, argv));
}

/**
 * Procedimiento encargado de analizar los argumentos e invocar a otros/as procedimientos y funciones.
 * @param nArg
          Indica el numero de argumentos ingresados por el usuario.
 * @param argv
          Contiene los argumentos ingresados por el usuario.
 * @return
 */
short int *parseArguments(int nArg, char *argv[]) {

    int *baseS, *baseD, *index;
    short int *detailed, *valueToReturn;
    char *num, *integerPart, *fractionalPart;;

    baseS = malloc(sizeof(int));
    baseD = malloc(sizeof(int));
    index = malloc(sizeof(int));
    detailed = malloc(sizeof(short int));
    num = malloc(sizeof(char));
    valueToReturn = malloc(sizeof(short int));

    integerPart = malloc(10 * sizeof(char));
    fractionalPart = malloc(5 * sizeof(char));

    *baseS = 10;
    *baseD = 10;
    *index = 1;
    *detailed = 0;
    *num = 0;

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
        else if (*stringCompare(argv[*index], "-v") == 1)
             *detailed = 1;
        else
            help();
    }

    integerPart = getIntegerSide(num, integerPart);
    fractionalPart = getFractionalSide(num, fractionalPart);

    if (nArg > 1) {
        if (*baseD < 2 || *baseD > 16) {
            printf("\n DATOS INGRESADOS INCORRECTOS :: La base de destino debe estar en el rango [2,16].\n");
            *valueToReturn = EXIT_FAILURE;
        }
        else if (*stringLength(integerPart) > 10) {
            printf("\n DATOS INGRESADOS INCORRECTOS :: El maximo de digitos para la parte entera es 10.\n");
            *valueToReturn = EXIT_FAILURE;
        }
        else if (*stringLength(fractionalPart) > 5) {
            printf("\n DATOS INGRESADOS INCORRECTOS :: El maximo de digitos para la parte fraccionaria es 5.\n");
            *valueToReturn = EXIT_FAILURE;
        }
        else if (*validateNumber(num, baseS) == 1)
            buildNumber(integerPart, fractionalPart, baseS, baseD, detailed);
        else {
            printf("\n DATOS INGRESADOS INCORRECTOS :: El numero y/o la base origen ingresados son incorrectos.\n");
            *valueToReturn = EXIT_FAILURE;
        }
    }

    free(baseS);
    free(baseD);
    free(detailed);
    free(index);
    free(num);
    free(integerPart);
    free(fractionalPart);

    return valueToReturn;
}

void buildNumber(char *integerPart, char *fractionalPart, int *sourceBase, int *destinationBase, short int *detailed) {

    char *fromDecimal_integerPart, *fromDecimal_fractionalPart;
    int *fromAnyBase_integerPart;
    float *fromAnyBase_fractionalPart;
    // Si la base de origen es 10 y la de destino es cualquiera:
    if (*sourceBase == 10 && *destinationBase != 10) {

        if (*integerPart == '0')        // Si el numero es 0 --> No hay nada que hacer.
            fromDecimal_integerPart = integerPart;
        else                            // Caso contrario --> Se efectua la conversion correspondiente.
            fromDecimal_integerPart = divisionMethodInteger(integerPart, destinationBase, detailed);

        fromDecimal_fractionalPart = multiplicationMethodFractional(fractionalPart, destinationBase, detailed);
        printf("\n\n NUMERO OBTENIDO: (%s.%s)b%i \n", fromDecimal_integerPart, fromDecimal_fractionalPart, *destinationBase);
    }
    // Si la base de origen es cualquiera y la de destino es 10
    else if (*sourceBase != 10 && *destinationBase == 10) {
        fromAnyBase_integerPart = multiplicationMethodInteger(integerPart, sourceBase, detailed);
        fromAnyBase_fractionalPart = divisionMethodFractional(fractionalPart, sourceBase, detailed);
        printf("\n\n NUMERO OBTENIDO: (%f)b%i\n", *fromAnyBase_integerPart + *fromAnyBase_fractionalPart, *destinationBase);
    }
    // De cualquier base origen a cualquier base destino [2,16]
    else {
        // Primero convertimos a decimal
        fromAnyBase_integerPart = multiplicationMethodInteger(integerPart, sourceBase, detailed);
        fromAnyBase_fractionalPart = divisionMethodFractional(fractionalPart, sourceBase, detailed);
        fromDecimal_integerPart = malloc(20*sizeof(char));
        fromDecimal_fractionalPart = malloc(10*sizeof(char));
        // Transformamos la parte entera y la parte fraccionaria a un puntero char
        itoa(*fromAnyBase_integerPart, fromDecimal_integerPart, 10);
        gcvt(*fromAnyBase_fractionalPart, 10, fromDecimal_fractionalPart);
        // Formateamos la parte fraccionaria (cortamos el digito entero y el .)
        getFractionalSide(fromDecimal_fractionalPart, fromDecimal_fractionalPart);

        // Printeamos utilizando los metodos de conversion de base decimal a base destino
        printf("\n\n NUMERO OBTENIDO: (%s.%s)b%i \n",  divisionMethodInteger(fromDecimal_integerPart, destinationBase, detailed),
                                                       multiplicationMethodFractional(fromDecimal_fractionalPart, destinationBase, detailed),
                                                      *destinationBase);
    }

    free(fromDecimal_integerPart);
    free(fromDecimal_fractionalPart);
    free(fromAnyBase_integerPart);
    free(fromAnyBase_fractionalPart);
}

/**
 * Procedimiento encargado de proveer la correcta sintaxis y semantica al usuario.
 */
void help() {

    printf("\n Bienvenido al convertidor de bases programado en C.\n");
    printf("\n A continuacion se indican las opciones de invocacion del programa:\n\n");
    printf("\t-n numero real :: Indica el numero al que se le hara el cambio de base. Maxima cantidad de digitos enteros: 10. Maxima cantidad de digitos fraccionarios: 5.\n");
    printf("\t-s base origen :: Especifica la base a la que pertence el numero ingresado. Bases permitidas: [2,16]. \n");
    printf("\t-d base destino ::  Especifica la base a la que pertence el numero ingresado. Bases permitidas: [2,16]. \n");
    printf("\t-v computos intermedios :: Permite visualizar en forma secuencial y ordenada los computos realizados para cambiar el numero ingresado de la base origen a la base destino. \n");
    printf("\t-h ayuda :: Provee informacion para poder utilizar el programa de forma correcta. \n");
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

        while ( (*number >= '0' && *number < ('0' + *base)) || (*number == '.' && *flag == 1)) {

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



