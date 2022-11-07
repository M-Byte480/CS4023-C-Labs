// 21308128: Milan Kovacs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

int main(int argc, char* argv[])
{
    float ref, range;

    // Check if 5 args are passed
    if(argc == 5){
        // Make the input possible in any order.
        for (int i = 1; i < argc; ++i) {
            // Handles the reference
            if(strcmp(argv[i], "-r") == 0){
                ref = strtof(argv[i+1], NULL);
                i++;
            // Handles the tolerance
            }else if(strcmp(argv[i], "-t") == 0){
                range = strtof(argv[i+1], NULL);
                i++;
            }
       }
    }else{
        printf("Please use the format:\n./findvals -r [Value] -t [Tolerance]\n");
        printf( "The number of args passed: %d\n", argc);
        exit(1);
    }

    // This is from the lab sheet
    struct tm *local1, *local2;
    time_t start, end;
    time(&start); // read and record clock
    local1 = localtime(&start);

    int rct, cct;
    scanf("%d", &rct);
    scanf("%d", &cct);


    // Allocate array of arrays in memory, also from the lab sheet
    float** rows = (float **) malloc(rct * sizeof(float *));
    if (rows == 0)
    {
        fprintf(stderr, "Couldn’t alocate sufficient space.\n");
        exit(1);
    }
    int i;
    for (i = 0; i < rct; i++)
    {
        float* row = (float *) malloc(cct * sizeof(float));
        if (row == 0)
        {
            fprintf(stderr, "Couldn’t alocate sufficient row space.\n");
            exit(1);
        }
        rows[i] = row;
    }

    // Populate the array
    for (int row = 0; row < rct; ++row) {
        for (int column = 0; column < cct; ++column) {
            scanf("%f", &rows[row][column]);
        }
    }

    // Counter for the number of values
    int count = 0;

    // Iterate through the array(s) and check if they are within the tolerance range
    for (int row = 0; row < rct; ++row) {
        for (int column = 0; column < cct; ++column) {
            if(approxEquals(rows[row][column], ref, range) == 1){
                count++;
                fprintf(stdout, "r=%d, c=%d: %.6f\n", row, column, rows[row][column]);
            }
        }
    }

    time(&end); // read and record now
    local2 = localtime(&end);
    printf("# Start time and date: %s", asctime(local1));
    printf("# End time and date: %s", asctime(local2));
    printf("It took: %.3f seconds to execute\n", difftime(end, start));
    printf("There was %d counts of numbers within the tolerance range\n", count);

    for(int row = 0; row < rct; ++row){
        free(rows[row]);
    }

    free(rows);
    exit(0);
}