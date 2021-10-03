#ifndef CONVERT_H_INCLUDED

#define ARGUMENTOS_INSUFICIENTES 0


#define CONVERT_H_INCLUDED


int main(int argc, char * argv[]);

void parseArguments(int nArg, char *argv[]);

int stringCompare(char *a, char *b);

void help();

int validateNumber(char *a, int *b);

#endif // CONVERT_H_INCLUDED
