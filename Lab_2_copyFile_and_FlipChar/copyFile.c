#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int main(int argc, char* argv[])
{
    if(argc <= 2){
        exit(1);
    }

    int flipping = (strcmp(argv[1], "-f") == 0);
    char c;
    FILE *srcFile;
    FILE *destFile;


    if(flipping) {
        srcFile = fopen(argv[2], "r");
        destFile = fopen(argv[3], "w");
    }else{
        srcFile = fopen(argv[1], "r");
        destFile = fopen(argv[2], "w");
    }

    if (srcFile == NULL)
    {
        printf("Source file not found\n");
        exit(1);
    }

    /* We don't need destFile check if copy.txt exists, because the
       'w' write argument will create it if it doesn't exist */


    /* file exists, so start reading */
    while ((c = getc(srcFile)) != EOF) {
        if(flipping){
        putc(flipCharacter(c), destFile);
    }else{
        putc(c, destFile);
        }
    }
    printf("Successful copy\n"); /* Let us know it worked */

    fclose(srcFile);
    fclose(destFile);

    exit(0);
}

