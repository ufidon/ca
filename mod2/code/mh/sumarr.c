#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// 📝: Profile functions by changing the size N and stride S
#define N 2048
#define S 1

int arr[N][N];

// Function to sum array elements in row-major order
// The `sumarrayrows` function sums a 2D array in `row-major` order, matching C’s memory layout, 
// achieving excellent spatial locality with a stride-1 pattern.
int sumarrayrows(int a[N][N])
{
  int sum = 0;
  for (int i = 0; i < N; i += S)
  {
    for (int j = 0; j < N; j += S)
    {
      sum += a[i][j];
    }
  }
  return sum;
}

// Function to sum array elements in column-major order
// The `sumarraycols` function, despite computing the same result as `sumarrayrows`, 
// scans column-wise, creating a `stride-N pattern` and poor spatial locality.
int sumarraycols(int a[N][N])
{
  int sum = 0;
  for (int j = 0; j < N; j += S)
  {
    for (int i = 0; i < N; i += S)
    {
      sum += a[i][j];
    }
  }
  return sum;
}

// Function to calculate time difference in nanoseconds
double time_diff(struct timespec start, struct timespec end)
{
  return (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
}

int main()
{
  struct timespec start, end;
  int result;

  // Initialize the array with random data
  for (int i = 0; i < N; i += S)
  {
    for (int j = 0; j < N; j += S)
    {
      arr[i][j] = rand() % 100;
    }
  }

  // Time sumarrayrows (row-major order)
  clock_gettime(CLOCK_MONOTONIC, &start);
  result = sumarrayrows(arr);
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("sumarrayrows time: %.2f ms (result: %d)\n", time_diff(start, end) / 1e6, result);

  // Time sumarraycols (column-major order)
  clock_gettime(CLOCK_MONOTONIC, &start);
  result = sumarraycols(arr);
  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("sumarraycols time: %.2f ms (result: %d)\n", time_diff(start, end) / 1e6, result);

  return 0;
}


// 📝 1️⃣ profile all index permutations of a[k][i][j]
int sumarray3d(int a[N][N][N]) {
  int i, j, k, sum = 0;
  for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
          for (k = 0; k < N; k++) {
              sum += a[k][i][j];
          }
      }
  }
  return sum;
}

// 📝 2️⃣ profile the 3 functions below
// The key to solving this problem is to visualize
// how the array is laid put in memory and then analyze the reference patterns.

#define N 1000

typedef struct {
    int vel[3];
    int acc[3];
} point;

point p[N];

void clear1(point *p, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
      for (j = 0; j < 3; j++) {
          p[i].vel[j] = 0;
      }
      for (j = 0; j < 3; j++) {
          p[i].acc[j] = 0;
      }
  }
}

void clear2(point *p, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
      for (j = 0; j < 3; j++) {
          p[i].vel[j] = 0;
          p[i].acc[j] = 0;
      }
  }
}

void clear3(point *p, int n) {
  int i, j;
  for (j = 0; j < 3; j++) {
      for (i = 0; i < n; i++) {
          p[i].vel[j] = 0;
      }
      for (i = 0; i < n; i++) {
          p[i].acc[j] = 0;
      }
  }
}