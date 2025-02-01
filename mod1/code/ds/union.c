#include <stdio.h>

union U3
{
  char c;
  int i[2];
  double v;
};

union node_u
{
  struct
  {
    union node_u *left;
    union node_u *right;
  } internal;
  double data[2];
};

typedef enum
{
  N_LEAF,
  N_INTERNAL
} nodetype_t;

struct node_t
{
  nodetype_t type;
  union
  {
    struct
    {
      struct node_t *left;
      struct node_t *right;
    } internal;
    double data[2];
  } info;
};

// Function to convert double to bitwise representation (unsigned long)
unsigned long double2bits(double d)
{
  union
  {
    double d;
    unsigned long u;
  } temp;
  temp.d = d;
  return temp.u;
}

// Function to convert two unsigned words into a double
double uu2double(unsigned word0, unsigned word1)
{
  union
  {
    double d;
    unsigned u[2];
  } temp;
  temp.u[0] = word0;
  temp.u[1] = word1;
  return temp.d;
}

int main()
{
  // Example of using the union U3
  union U3 u3;
  u3.v = 3.14;
  printf("Union U3 (double value): %.2f\n", u3.v);

  // Example of using the node_t structure
  struct node_t node;
  node.type = N_INTERNAL;
  node.info.internal.left = NULL;
  node.info.internal.right = NULL;

  printf("Node type: %d\n", node.type);

  // Example of converting a double to unsigned long
  double d = 3.14159;
  unsigned long bits = double2bits(d);
  printf("Double %.5f as bits: %lx\n", d, bits);

  // Example of reconstructing a double from two unsigned words
  unsigned word0 = 0x400921fb; // Upper part of the double
  unsigned word1 = 0x54442d18; // Lower part of the double
  double reconstructed = uu2double(word0, word1);
  printf("Reconstructed double: %.5f\n", reconstructed);

  return 0;
}
