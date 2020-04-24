#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "scanner.h"
#include "funct.h"

int main(int argc,char **argv)
    {
    char *a;
    printf("Cryptography Project\nMath237\nAndrew Duerr Jr.\n\n");
    printf("What would you like to do? encode/decode: ");
    a = readToken(stdin);
    while (strcmp(a,"encode") != 0 && strcmp(a,"decode") != 0)
        {
        printf("Please enter either \"decode\" or \"encode\": ");
        a = readToken(stdin);
        }

    if (strcmp(a,"encode") == 0)
        encode();
    if (strcmp(a,"decode") == 0)
        decode();

    return 0;
    }
