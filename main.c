#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// generates a random n*n matrix
int** genRandomMatrix(int n, int max) {
    int i,j;
    int** mat = malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        mat[i] = malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            mat[i][j] = 1 + rand() % max;
        }
    }
    return mat;
}

// Release the allocated memory
void free_all(int **mat, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

// compute the average value of the elements in the matrix in row-major order
float averageMat_rowMajor(int **mat, int n) {
    int i, j, total = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            total += mat[i][j];
        }
    }
    return (float)total/(n*n);
}

// compute the average value of the elements in the matrix in the column-major order
float averageMat_colMajor(int **mat, int n) {
    int i, j, total = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            total += mat[j][i];
        }
    }
    return (float)total/(n*n);
}


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "where <n> is the dimension of the matrix\n");
        return 1;
    }

    int i;
    int n = strtol(argv[1], NULL, 10);
    srand(time(NULL));

    struct timeval tstart, tend;
    int **matrix = genRandomMatrix(n, 100);
    gettimeofday(&tstart, NULL);
    float res = averageMat_rowMajor(matrix, n);
    gettimeofday(&tend, NULL);
    double run_time = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
    printf("row major average is: %.2f; time is %g\n", res, run_time);

    gettimeofday(&tstart, NULL);
    res = averageMat_colMajor(matrix, n);
    gettimeofday(&tend, NULL);
    run_time = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
    printf("column major average is: %.2f; time is %g\n", res, run_time);

    free_all(matrix, n);
    return 0;
}

