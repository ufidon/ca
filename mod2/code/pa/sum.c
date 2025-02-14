// gcc -c -fno-stack-protector -fcf-protection=none -o sum.o sum.c
// objdump -d sum.o

long sum(long *start, long count) {
  long sum = 0;
  while (count) {
      sum += *start;
      start++;
      count--;
  }
  return sum;
}
