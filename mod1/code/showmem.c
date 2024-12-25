#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union Data
{
  char c;
  short s;
  int i;
  long l;
  long long ll;
  float f;
  double d;
  long double ld;
  void *p;
};

int check_endian()
{
  unsigned int x = 1;
  char *c = (char *)&x;

  if (*c)
  {
    printf("CPU is running in Little-endian\n");
    return 1;
  }
  else
  {
    printf("CPU is running in Big-endian\n");
    return 0;
  }
}

void print_bytes(void *ptr, int size, int endian)
{
  unsigned char *bytes = (unsigned char *)ptr;
  if (endian) // CPU is running in Little-endian
  {
    printf("Little-Endian Layout: ");
    for (int i = 0; i < size; i++)
    {
      printf("%02x ", bytes[i]);
    }
    printf("\n");

    printf("Big-Endian Layout:    ");
    for (int i = size - 1; i >= 0; i--)
    {
      printf("%02x ", bytes[i]);
    }
    printf("\n");
  }
  else
  {
    printf("Big-Endian Layout:    ");
    for (int i = 0; i < size; i++)
    {
      printf("%02x ", bytes[i]);
    }
    printf("\n");

    printf("Little-Endian Layout: ");
    for (int i = size - 1; i >= 0; i--)
    {
      printf("%02x ", bytes[i]);
    }
    printf("\n");    
  }
}

void print_layout(union Data *data, const char *type, int endian)
{
  if (strcmp(type, "char") == 0)
  {
    print_bytes(&data->c, sizeof(data->c), endian);
  }
  else if (strcmp(type, "short") == 0)
  {
    print_bytes(&data->s, sizeof(data->s), endian);
  }
  else if (strcmp(type, "int") == 0)
  {
    print_bytes(&data->i, sizeof(data->i), endian);
  }
  else if (strcmp(type, "long") == 0)
  {
    print_bytes(&data->l, sizeof(data->l), endian);
  }
  else if (strcmp(type, "long long") == 0)
  {
    print_bytes(&data->ll, sizeof(data->ll), endian);
  }
  else if (strcmp(type, "float") == 0)
  {
    print_bytes(&data->f, sizeof(data->f), endian);
  }
  else if (strcmp(type, "double") == 0)
  {
    print_bytes(&data->d, sizeof(data->d), endian);
  }
  else if (strcmp(type, "long double") == 0)
  {
    print_bytes(&data->ld, sizeof(data->ld), endian);
  }
  else if (strcmp(type, "pointer") == 0)
  {
    print_bytes(&data->p, sizeof(data->p), endian);
  }
  else
  {
    printf("Unknown type.\n");
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <value> <type>\n", argv[0]);
    fprintf(stderr, "Supported types: char, short, int, long, long long, \
        \n\tfloat, double, long double, pointer\n");
    return 1;
  }

  union Data data;
  const char *type = argv[2];
  int endian = check_endian();

  if (strcmp(type, "char") == 0)
  {
    data.c = (char)atoi(argv[1]);
  }
  else if (strcmp(type, "short") == 0)
  {
    data.s = (short)atoi(argv[1]);
  }
  else if (strcmp(type, "int") == 0)
  {
    data.i = atoi(argv[1]);
  }
  else if (strcmp(type, "long") == 0)
  {
    data.l = atol(argv[1]);
  }
  else if (strcmp(type, "long long") == 0)
  {
    data.ll = atoll(argv[1]);
  }
  else if (strcmp(type, "float") == 0)
  {
    data.f = atof(argv[1]);
  }
  else if (strcmp(type, "double") == 0)
  {
    data.d = atof(argv[1]);
  }
  else if (strcmp(type, "long double") == 0)
  {
    data.ld = strtold(argv[1], NULL);
  }
  else if (strcmp(type, "pointer") == 0)
  {
    data.p = (void *)strtoll(argv[1], NULL, 16);
  }
  else
  {
    fprintf(stderr, "Unknown type: %s\n", type);
    return 1;
  }

  printf("Value (%s): %s\n", type, argv[1]);
  print_layout(&data, type, endian);

  return 0;
}
