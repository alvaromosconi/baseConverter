#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {

    int *i;
    *i = 0;

    for (*i; --argc > 1; *i++) {
        printf("%s", argv[*i]);
    }

    return 0;
}
