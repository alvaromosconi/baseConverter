#ifndef CONVERT_H_INCLUDED


#define CONVERT_H_INCLUDED


int main(int argc, char * argv[]);

void parseArguments(int nArg, char *argv[]);

int *stringCompare(const char *a, const char *b);

void help();

int *validateNumber(const char *number, int *base);

char *getFractionalSide(const char *number, char *destination);

char *getIntegerSide(const char *number, char *destination) ;

int *stringLength(char *string);

#endif // CONVERT_H_INCLUDED
