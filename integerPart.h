#ifndef INTEGERPART_H_INCLUDED
#define INTEGERPART_H_INCLUDED

int *transformNumberToDecimal (char *characterToTransform);
int *fromAnyBaseToDecimal(char *number, int *base);
int *getLengthOfNumber(int *number);
void setEquivalentDigit(char *currentDigit, int *reminder);
void reverseString (char *stringToReverse);
char *fromDecimalBaseToAnyBase(char *number, int *base);


#endif // INTEGERPART_H_INCLUDED
