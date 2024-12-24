#include <stdio.h>
#include <stdlib.h>

// 📝: trigger segmentation fault from TWO places

typedef struct {
    int a[2];
    double d;
} struct_t;

double fun(int i) {
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824;  // Potential out-of-bounds access
    return s.d;
}

int main(int argc, char* argv[]){

  int i = atoi(argv[1]);
  printf("fun(%d) → %f\n", i, fun(i));

  return 0;
}