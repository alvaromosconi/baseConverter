#ifndef CONVERT_H_INCLUDED


#define CONVERT_H_INCLUDED


int main(int argc, char * argv[]);

int *parseArguments(int nArg, char *argv[]);

void buildNumber(char *integerPart, char *fractionalPart, int *sourceBase, int *destinationBase, short int *detailed);

void help();

int *validateNumber(const char *number, const int *base);

char *getFractionalSide(const char *number, char *destination);

char *getIntegerSide(const char *number, char *destination) ;

int *stringLength(char *string);

#endif // CONVERT_H_INCLUDED
