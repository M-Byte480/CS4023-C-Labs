// 21308128: Milan Kovacs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "utils.h"
#include <sys/time.h>

int main(int argc, char* argv[])
{
    float ref, range;
    int position = -1;
    // Check if 5 args are passed
    if(argc <= 6){
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
            }else if(strcmp(argv[i], "-v") == 0){
                position = 1;
            }
        }
    }else{
        printf("Please use the format:\n./findvals -r [Value] -t [Tolerance]\n");
        printf( "The number of args passed: %d\n", argc);
        exit(1);
    }



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

    // This is from the lab sheet
    struct timeval tim;
    gettimeofday(&tim, NULL);
    double t1=tim.tv_sec+(tim.tv_usec/1000000.0);

    // Counter for the number of values
    int count = 0;
    // Iterate through the array(s) and check if they are within the tolerance range
#pragma omp parallel for collapse(2)
    for (int row = 0; row < rct; ++row) {
        for (int column = 0; column < cct; ++column) {
            if(approxEquals(rows[row][column], ref, range) == 1){
                if(position != -1) {
                    fprintf(stdout, "r=%d, c=%d: %.6f (thread = %d) \n", row, column, rows[row][column], omp_get_thread_num());
                }
#pragma omp atomic
                count++;
            }
        }
    }

    gettimeofday(&tim, NULL);
    double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
    printf("%.6lf seconds elapsed\n", t2-t1);
    printf("There were %d matches\n", count);

    for(int row = 0; row < rct; ++row){
        free(rows[row]);
    }

    free(rows);
    exit(0);
}


