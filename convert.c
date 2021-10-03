#include <stdio.h>
#include <stdlib.h>
#include "convert.h"

//char base_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7','8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int main(int argc, char * argv[]) {

    parseArguments(argc, argv);
}

// Metodo para analizar los argumentos y derivarlas a otras funciones
void parseArguments(int nArg, char *argv[]) {

    int *baseS, *baseD, *index;

    char * num;


    baseS = malloc(sizeof(int));
    baseD = malloc(sizeof(int));
    index = malloc(sizeof(int));
    num = malloc(sizeof(char));

    *baseS = 10;
    *baseD = 10;
    *index = 1;
    *num = 0;

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


    if (validateNumber(num, baseS) == 1)
        printf("%s", "Valido");
    else
        printf("%s", "Invalido");



    printf("\nDatos ingresados --> Numero ingresado: %s. Base origen: %i. Base destino: %i", num, *baseS, *baseD);

    free(baseS);
    free(baseD);
    free(index);
    free(num);

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


 //   printf("%c:  . %i", *a, *b);
 //   printf("%i",(*b));

    int * toReturn;
    toReturn = malloc(sizeof(int));

    if (*b > 16)
        *toReturn = 0;

    else if (*b <= 10) {

        while(*a >= '0' && *a < ('0' + *b))
            a++;

    }

    else {
        while( (*a >= '0' && *a <= ('0' + *b)) ||
               (*a >= 'A' && *a < ('A' + *b - 10)))
            a++;
    }


   if (*a == '\0' )
      *toReturn = 1;


   return *toReturn;

   free(toReturn);
}



