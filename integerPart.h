#ifndef INTEGERPART_H_INCLUDED
#define INTEGERPART_H_INCLUDED


int *transformNumberToDecimal (char *characterToTransform);

int *multiplicationMethodInteger(char *number, int *base, short int *detailed);

void setEquivalentDigit(char *currentDigit, int *reminder);

void reverseString (char *stringToReverse);

char *divisionMethodInteger(char *number, int *base, short int *detailed);


#endif // INTEGERPART_H_INCLUDED
