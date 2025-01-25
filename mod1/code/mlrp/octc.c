#include <stdio.h>
#include <stdint.h>

void store_tprod(__int128_t *d, __int128 a, __int128 b){
  *d = a * b;
}

int main()
{
  // 64-bit signed and unsigned integers
  int64_t signed_a = 1234567890123456789LL;
  int64_t signed_b = 987654321098765432LL;
  uint64_t unsigned_a = 12345678901234567890ULL;
  uint64_t unsigned_b = 9876543210987654321ULL;

  // 128-bit signed and unsigned integers
  __int128 signed_128_a = (__int128)signed_a * signed_b; // 64-bit to 128-bit
  __int128 signed_128_b = (__int128)signed_b * signed_a;
  unsigned __int128 unsigned_128_a = (unsigned __int128)unsigned_a * unsigned_b;
  unsigned __int128 unsigned_128_b = (unsigned __int128)unsigned_b * unsigned_a;

  // 64-bit multiplication (signed and unsigned)
  int64_t signed_mul_64 = signed_a * signed_b;
  uint64_t unsigned_mul_64 = unsigned_a * unsigned_b;

  // 128-bit multiplication (signed and unsigned)
  __int128 signed_mul_128 = signed_128_a * signed_128_b;
  __int128_t d = 0LL;
  store_tprod(&d, signed_128_a, signed_128_b);
  
  unsigned __int128 unsigned_mul_128 = unsigned_128_a * unsigned_128_b;

  // 64-bit division and modulus (signed and unsigned)
  int64_t signed_div_64 = signed_a / signed_b;
  int64_t signed_mod_64 = signed_a % signed_b;
  uint64_t unsigned_div_64 = unsigned_a / unsigned_b;
  uint64_t unsigned_mod_64 = unsigned_a % unsigned_b;

  // 128-bit division and modulus (signed and unsigned)
  __int128 signed_div_128 = signed_128_a / signed_128_b;
  __int128 signed_mod_128 = signed_128_a % signed_128_b;
  unsigned __int128 unsigned_div_128 = unsigned_128_a / unsigned_128_b;
  unsigned __int128 unsigned_mod_128 = unsigned_128_a % unsigned_128_b;

  // Print 64-bit results
  printf("64-bit Signed Multiplication: %ld * %ld = %ld\n", signed_a, signed_b, signed_mul_64);
  printf("64-bit Unsigned Multiplication: %lu * %lu = %lu\n", unsigned_a, unsigned_b, unsigned_mul_64);
  printf("64-bit Signed Division: %ld / %ld = %ld\n", signed_a, signed_b, signed_div_64);
  printf("64-bit Signed Modulus: %ld %% %ld = %ld\n", signed_a, signed_b, signed_mod_64);
  printf("64-bit Unsigned Division: %lu / %lu = %lu\n", unsigned_a, unsigned_b, unsigned_div_64);
  printf("64-bit Unsigned Modulus: %lu %% %lu = %lu\n", unsigned_a, unsigned_b, unsigned_mod_64);

  // Print 128-bit results
  printf("\n128-bit Signed Multiplication: ");
  printf("%lld * %lld = %lld (high) %lld (low)\n",
         (long long)(signed_128_a >> 64), (long long)signed_128_a,
         (long long)(signed_mul_128 >> 64), (long long)signed_mul_128);
  printf("\n128-bit signed product stored: ");
  printf("%lld (high) %lld (low)\n", (long long)(d >> 64), (long long)d);

  printf("128-bit Unsigned Multiplication: ");
  printf("%llu * %llu = %llu (high) %llu (low)\n",
         (unsigned long long)(unsigned_128_a >> 64), (unsigned long long)unsigned_128_a,
         (unsigned long long)(unsigned_mul_128 >> 64), (unsigned long long)unsigned_mul_128);

  printf("128-bit Signed Division: ");
  printf("%lld / %lld = %lld\n",
         (long long)(signed_128_a >> 64), (long long)signed_128_a,
         (long long)signed_div_128);

  printf("128-bit Signed Modulus: ");
  printf("%lld %% %lld = %lld\n",
         (long long)(signed_128_a >> 64), (long long)signed_128_a,
         (long long)signed_mod_128);

  printf("128-bit Unsigned Division: ");
  printf("%llu / %llu = %llu\n",
         (unsigned long long)(unsigned_128_a >> 64), (unsigned long long)unsigned_128_a,
         (unsigned long long)unsigned_div_128);

  printf("128-bit Unsigned Modulus: ");
  printf("%llu %% %llu = %llu\n",
         (unsigned long long)(unsigned_128_a >> 64), (unsigned long long)unsigned_128_a,
         (unsigned long long)unsigned_mod_128);

  return 0;
}