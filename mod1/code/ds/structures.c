#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct rec
{
  int a[4];
  size_t i;
  struct rec *next;
};

// Generating pointer to array element
int *get_ap(struct rec *r, size_t idx)
{
  return &r->a[idx];
}

// Following linked list and modifying structure fields
void set_val(struct rec *r, int val)
{
  while (r)
  {
    int i = r->i;
    r->a[i] = val;
    r = r->next;
  }
}

// Structure with alignment constraints
struct S1
{
  char c;
  int i[2];
  double v;
};

struct S2
{
  double v;
  int i[2];
  char c;
};

// Accessing array of structures
struct S3
{
  short i;
  float v;
  short j;
} a[10];

short get_j(int idx)
{
  return a[idx].j;
}

// Structs demonstrating space optimization
struct S4
{
  char c;
  int i;
  char d;
};

struct S5
{
  int i;
  char c;
  char d;
};

int main()
{
  struct rec node1 = {{1, 2, 3, 4}, 2, NULL};
  struct rec node2 = {{5, 6, 7, 8}, 1, &node1};

  printf("Original value at node2.a[1]: %d\n", node2.a[1]);
  set_val(&node2, 99);
  printf("Modified value at node2.a[1]: %d\n", node2.a[1]);

  struct S1 s1;
  struct S2 s2;
  struct S4 s4;
  struct S5 s5;
  printf("Size of S1: %zu, Size of S2: %zu\n", sizeof(s1), sizeof(s2));
  printf("Size of S4: %zu, Size of S5: %zu\n", sizeof(s4), sizeof(s5));

  a[3].j = 42;
  printf("Value of a[3].j: %d\n", get_j(3));

  return 0;
}
