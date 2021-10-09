#include <stdio.h>
#include <stdlib.h>
#include "convert.h"
#include "integerPart.h"
#include "fractionalPart.h"
#include "utilities.h"

/**
 * Procedimiento encargado de analizar los argumentos e invocar a otros/as procedimientos y funciones.
 * @param argc
          Indica el numero de argumentos ingresados por el usuario.
 * @param argv
          Puntero a arreglo de punteros (Contiene los argumentos ingresados por el usuario).
 * @return 0 Si la ejecución fue exitosa, 1 si se produjo algun error.
 */
int main(int argc, char * argv[]) {

                                            // Si ingreso solo el nombre del programa
    if (argc == 1)
        help();                             // Imprimir la ayuda
    else
        exit(*parseArguments(argc, argv));
}

/**
 * Funcion encargada de analizar los argumentos e invocar a otros/as procedimientos y funciones.
 * @param nArg
          Indica el numero de argumentos ingresados por el usuario.
 * @param argv
          Puntero a arreglo de punteros (Contiene los argumentos ingresados por el usuario).
 * @return Puntero a entero que almacena un 0 si la ejecución fue exitosa, 1 si se produjo algun error.
 */
int *parseArguments(int nArg, char *argv[]) {

    int *baseS, *baseD, *index, *detailed, *valueToReturn;
    char *num, *integerPart, *fractionalPart;;

    baseS = malloc(sizeof(int));
    baseD = malloc(sizeof(int));
    index = malloc(sizeof(int));
    detailed = malloc(sizeof(int));
    num = malloc(sizeof(char));
    valueToReturn = malloc(sizeof(int));

    integerPart = malloc(10 * sizeof(char));
    fractionalPart = malloc(5 * sizeof(char));

    *baseS = 10;
    *baseD = 10;
    *index = 1;
    *detailed = 0;
    *num = 0;

    // Bucle encargado de analizar los argumentos ingresados por consola para luego almacenarlos.
    for (*index = 1; *index < nArg; ++*index) {
        // Precedencia del help.
        if (nArg < 3 || *stringCompare(argv[*index], "-h") == 1)
            help();
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

    // Verificacion de las bases

    if (*baseD < 2 || *baseS < 2 || *baseD > 16 || *baseS > 16) {
        printf("\n DATOS INGRESADOS INCORRECTOS :: La base de origen y/o destino deben estar en el rango [2,16].\n");
        *valueToReturn = EXIT_FAILURE;
    } // Verificacion del largo de la parte entera
    else if (*stringLength(integerPart) > 10) {
        printf("\n DATOS INGRESADOS INCORRECTOS :: El maximo de digitos para la parte entera es 10.\n");
        *valueToReturn = EXIT_FAILURE;
    } // Verificacion del largo de la parte fraccionaria
    else if (*stringLength(fractionalPart) > 5) {
        printf("\n DATOS INGRESADOS INCORRECTOS :: El maximo de digitos para la parte fraccionaria es 5.\n");
        *valueToReturn = EXIT_FAILURE;
    } // Verificacion de que el numero ingresado pertenezca a la base
    else if (*validateNumber(num, baseS) == 1) {
        buildNumber(integerPart, fractionalPart, baseS, baseD, detailed);
        *valueToReturn = EXIT_SUCCESS;
    }
    else {
        printf("\n DATOS INGRESADOS INCORRECTOS :: El numero y/o la base origen ingresados son incorrectos.\n");
        *valueToReturn = EXIT_FAILURE;
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

/**
 * Procedimiento encargado de hacer los llamados a las funciones y/o procedimientos que conviertenes los numeros expresados en base origen a
   el numero equivalente en base destino.
 * @param integerPart
          Puntero a char que almacena la parte entera del numero ingresado por el usuario.
 * @param fractionalPart
          Puntero a char que almacena la parte fraccionaria del numero ingresado por el usuario.
 * @param sourceBase
          Puntero a entero que almacena la base origen ingresada por el usuario.
 * @param destinationBase
          Puntero a entero que almacena la base destino ingresada por el usuario.
 * @param detailed
          Puntero a entero corto que almacena un 1 si el usuario ingreso el parametro "-v", 0 si el usuario no ingreso el parametro "-v".
 *
 */
void buildNumber(char *integerPart, char *fractionalPart, int *sourceBase, int *destinationBase, int *detailed) {

    char *fromDecimal_integerPart, *fromDecimal_fractionalPart;
    int *fromAnyBase_integerPart;
    float *fromAnyBase_fractionalPart;
    // Si la base de origen es 10 y la de destino es cualquiera:
    if (*sourceBase == 10 && *destinationBase != 10) {

        // Se producen los llamados para convertir la parte entera y la parte fraccionaria
        fromDecimal_integerPart = divisionMethodInteger(integerPart, destinationBase, detailed);                                                              // Caso contrario --> Se efectua la conversion correspondiente.
        fromDecimal_fractionalPart = multiplicationMethodFractional(fractionalPart, destinationBase, detailed);

        printf("\n\n NUMERO OBTENIDO: (%s.%s)b%i \n", fromDecimal_integerPart, fromDecimal_fractionalPart, *destinationBase);
    }
    // Si la base de origen es cualquiera y la de destino es 10
    else if (*sourceBase != 10 && *destinationBase == 10) {

        // Se producen los llamados para convertir la parte entera y la parte fraccionaria
        fromAnyBase_integerPart = multiplicationMethodInteger(integerPart, sourceBase, detailed);
        fromAnyBase_fractionalPart = divisionMethodFractional(fractionalPart, sourceBase, detailed);

        printf("\n\n NUMERO OBTENIDO: (%f)b%i\n", *fromAnyBase_integerPart + *fromAnyBase_fractionalPart, *destinationBase);
    }
    // De cualquier base origen a cualquier base destino [2,16]
    else {

        fromDecimal_integerPart = malloc(20*sizeof(char));
        fromDecimal_fractionalPart = malloc(10*sizeof(char));
        // Primero convertimos a decimal
        fromAnyBase_integerPart = multiplicationMethodInteger(integerPart, sourceBase, detailed);
        fromAnyBase_fractionalPart = divisionMethodFractional(fractionalPart, sourceBase, detailed);
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
    printf("\t-n numero a convertir :: Indica el numero al que se le hara el cambio de base. Maxima cantidad de digitos enteros: 10. Maxima cantidad de digitos fraccionarios: 5.\n");
    printf("\t-s base origen :: Especifica la base a la que pertence el numero ingresado. Bases permitidas: [2,16]. \n");
    printf("\t-d base destino ::  Especifica la base a la que pertence el numero ingresado. Bases permitidas: [2,16]. \n");
    printf("\t-v computos intermedios :: Permite visualizar en forma secuencial y ordenada los computos realizados para representar el numero ingresado en base destino. \n");
    printf("\t-h ayuda :: Provee informacion para poder utilizar el programa de forma correcta. \n");
    exit(EXIT_SUCCESS);
}

/**
 * Funcion encargada de verificar si el numero recibido por parametro corresponde a la base recibida por parametro.
 * @param number
          Puntero a entero que almacena el numero ingresado por el usuario (cadena de caracteres).
 * @param base
          Puntero a entero que almacena la base numerica origen ingresada por el usuario.
 * @return Puntero a entero que almacena 1 si el numero corresponde a la base, 0 en caso contrario.
 *
 */
int *validateNumber(const char *number, const int *base) {

    int *flag;
    int *toReturn;

    toReturn = malloc(sizeof(int));
    flag = malloc(sizeof(int));
    *flag = 1; // Variable para denotar si ya se encontro un punto.
               // (Solo se admite un punto para separar la parte entera de la fraccional, en caso de encontrar mas de 1 se denotara el numero ingresado como invalido)

    // Control para chequear numeros pertenecientes a bases <=10
    if (*base <= 10)

        while ( (*number >= '0' && *number < ('0' + *base)) || (*number == '.' && *flag == 1)) {

             if (*number == '.')
                *flag = 0;

             number++;
        }

    else
    // Verifica la posicion ASCII (en decimal) del caracter en relacion a la base ingresada.
        while( (*number >= '0' && *number <= ('0' + *base)) ||
               (*number >= 'a' && *number < ('a' + *base - 10)) ||
               (*number >= 'A' && *number < ('A' + *base - 10)) ||
               (*number == '.' && *flag == 1)) {

                if (*number == '.')
                    *flag = 0;

                number++;
        }

   if (*number == '\0')
      *toReturn = 1;

   free(flag);

   return toReturn;
}

/**
 * Funcion encargada de extraer la parte fraccionaria del numero ingresado.
 * @param number
          Puntero a char que apunta al primer caracter del numero ingresado por el usuario (cadena de caracteres).
 * @param destination
          Puntero auxiliar para ubicar el inicio de la cadena a retornar.
 * @return Puntero a char que apunta al primer caracter de la parte fraccionaria.
 */
char *getFractionalSide(const char *number, char *destination) {

    char *fractionalSide = destination;
    int *flag;
    flag = malloc(sizeof(short int));
    *flag = 1; // Puntero para verificar si el numero tiene parte fraccionaria.

    while (*number != '.' && *flag == 1) {
        number++;
        if (*number == '\0')
            *flag = 0;
    }

    number++;

    // Comienzo de la lectura de la parte fraccionaria.
    while (*number != '\0' && *flag == 1)
        *fractionalSide++ = *number++;

    *fractionalSide = '\0';

    if (*flag == 0)
        *destination = '\0';

    free(flag);

    return destination;
}

/**
 * Funcion encargada de extraer la parte entera del numero ingresado.
 * @param number
          Puntero a char que apunta al primer caracter del numero ingresado por el usuario (cadena de caracteres).
 * @param destination
          Puntero auxiliar para ubicar el inicio de la cadena a retornar.
 * @return Puntero a char que apunta al primer caracter de la parte entera.
 */
char *getIntegerSide(const char *number, char *destination) {

    char *integerSide = destination;

    // Lectura de la parte entera del numero
    while (*number != '.' && *number != '\0')
        *integerSide++ = *number++;

    *integerSide = '\0';

    return destination;
}
