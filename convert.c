#include <stdio.h>
#include <stdlib.h>
#include "convert.h"

void getFractionalSide(char *number, char *destination);

int main(int argc, char * argv[]) {

    parseArguments(argc, argv);
}

// Metodo para analizar los argumentos y derivarlos a otras funciones
void parseArguments(int nArg, char *argv[]) {

    int *baseS, *baseD, *index;

    char * num, *fractionalSide;

    baseS = malloc(sizeof(int));
    baseD = malloc(sizeof(int));
    index = malloc(sizeof(int));
    num = malloc(sizeof(char));

    fractionalSide = malloc(sizeof(char));

    *baseS = 10;
    *baseD = 10;
    *index = 1;
    *num = 0;
    *fractionalSide = 0;

    for (*index = 1; *index < nArg; ++*index) {

        if (nArg < 3 || stringCompare(argv[*index], "-h") == 1)
            help();
       // printf("%s", argv[*index]);
        else if (stringCompare(argv[*index], "-n") == 1)
             num = argv[++*index];
        else if (stringCompare(argv[*index], "-s") == 1)
             *baseS = atoi(argv[++*index]);

        else if (stringCompare(argv[*index], "-d") == 1)
             *baseD = atoi(argv[++*index]);
    }


    getFractionalSide(num, fractionalSide);
    printf("%s", fractionalSide);
    printf("%i", stringLength(fractionalSide));

    if (validateNumber(num, baseS) == 1)
        printf("%s", "Valido");
    else
        printf("%s", "Invalido");


    printf("\nDatos ingresados --> Numero ingresado: %s. Base origen: %i. Base destino: %i", *num++, *baseS, *baseD);

    free(baseS);
    free(baseD);
    free(index);
    free(num);
    free(fractionalSide);

}

// Metodo que compara strings
int stringCompare(char *a, char *b) {

// printf("%i", 'a');
   while(*a == *b) {
      if (*a == '\0' || *b == '\0')
         break;

      a++;
      b++;
   }

   if (*a == '\0' && *b == '\0')
      return 1;
   else
      return 0;

}

 //Metodo que imprime ayuda
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

// Metodo que valida que el numero corresponda a la base
int validateNumber(char *a, int *b) {

    int *flag;
    flag = malloc(sizeof(int));
    *flag = 1;

    int * toReturn;
    toReturn = malloc(sizeof(int));

    if (*b > 16)
        *toReturn = 0;

    else if (*b <= 10) {

        while (*a >= '0' && *a < ('0' + *b) || (*a == '.' && *flag == 1)) {

             if (*a == '.')
                *flag = 0;

             a++;
        }

    }

    else {

        while( (*a >= '0' && *a <= ('0' + *b)) ||
               (*a >= 'A' && *a < ('A' + *b - 10)) ||
               (*a == '.' && *flag == 1)) {
                if (*a == '.')
                    *flag = 0;

                a++;
        }
    }


   if (*a == '\0')
      *toReturn = 1;


   return *toReturn;

//   free(toReturn);
}

// Retorna la cantidad de caracteres del String recibido
int stringLength(char *string) {

    int *length;
    length = malloc(sizeof(int));
    *length = 0;

    while (*string != '\0') {
        string++;
        *length = *length + 1;
    }

    return *length;
}

// Le asigna al puntero destination la parte fraccionaria del numero (si es que la hay)
void getFractionalSide(char *number, char *destination) {

    char *fractionalSide = destination;

    while (*number != '.') {
        number++;
    }

    number++;

    while (*number != '\0') {

        *fractionalSide++ = *number++;
    }


    *fractionalSide = '\0';
}
// Le asigna al puntero destination la parte entera del numero
void getIntegerSide(char *number, char *destination) {

    char *integerSide = destination;

    while (*number != '.' && *number != '\0') {
        *integerSide++ = *number++;
    }

    *integerSide = '\0';
}



