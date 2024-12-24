#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// 📝: profile functions by changing the size N and stride S

#define N 2048
#define S 1

int src[N][N], dst[N][N];

void copyji(int src[N][N], int dst[N][N]) {
    for (int j = 0; j < N; j+=S)
        for (int i = 0; i < N; i+=S)
            dst[i][j] = src[i][j];
}

void copyij(int src[N][N], int dst[N][N]) {
    for (int i = 0; i < N; i+=S)
        for (int j = 0; j < N; j+=S)
            dst[i][j] = src[i][j];
}

// Function to calculate time difference in nanoseconds
double time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
}

int main() {
    struct timespec start, end;

    // Initialize the source array with random data
    for (int i = 0; i < N; i+=S) {
        for (int j = 0; j < N; j+=S) {
            src[i][j] = rand() % 100;
        }
    }

    // Time copyij (row-major order)
    clock_gettime(CLOCK_MONOTONIC, &start);
    copyij(src, dst);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("copyij time: %.2f ms\n", time_diff(start, end) / 1e6);

    // Time copyji (column-major order)
    clock_gettime(CLOCK_MONOTONIC, &start);
    copyji(src, dst);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("copyji time: %.2f ms\n", time_diff(start, end) / 1e6);

    return 0;
}
