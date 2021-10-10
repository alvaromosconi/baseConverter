#ifndef COMMONMETHODS_H_INCLUDED
#define COMMONMETHODS_H_INCLUDED

int *transformNumberToDecimal (char *characterToTransform);

int *stringCompare(const char *a, const char *b);

int *stringLength(char *string);

void setEquivalentDigit(char *currentDigit, int *reminder);

int *getRequiredSizeForNumber(char *number, int *destinationBase);

#endif // COMMONMETHODS_H_INCLUDED
