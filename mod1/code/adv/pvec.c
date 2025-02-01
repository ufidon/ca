/*
A **packed vector** is a data format used in **SIMD (Single Instruction, Multiple Data)** processing, where multiple values (usually of the same data type) are stored in a single CPU register and processed simultaneously. This is in contrast to **scalar** operations, which process only one value at a time.

### **Packed vs. Scalar Operations**
- **Scalar Operations**: Operate on a single value at a time (e.g., `vmulsd` for double-precision multiplication).  
- **Packed Vector Operations**: Operate on multiple values in parallel (e.g., `vmulpd` for packed double-precision multiplication).  

### **Example in AVX (Advanced Vector Extensions)**
Modern CPUs support **vector registers** like **XMM (128-bit)** and **YMM (256-bit)** registers, which can hold multiple floating-point or integer values.

| **Register**  | **Size** | **Data Type (Packed)** | **Example** |
|--------------|---------|----------------------|-------------|
| XMM (SSE)   | 128-bit | 4 floats / 2 doubles | `vmulps` (4 floats at once) |
| YMM (AVX)   | 256-bit | 8 floats / 4 doubles | `vmulpd` (4 doubles at once) |

gcc -mavx pvec.c -o pvec
gcc -mavx2 pvec.c -o pvec

*/
#include <stdio.h>
#include <immintrin.h>  // AVX header

int main() {
    __m256d a = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
    __m256d b = _mm256_set_pd(5.0, 6.0, 7.0, 8.0);
    __m256d result = _mm256_mul_pd(a, b);  // Packed multiplication

    double res[4];
    _mm256_storeu_pd(res, result);

    for (int i = 0; i < 4; i++)
        printf("%f ", res[i]);  // Output: 5.0 12.0 21.0 32.0

    return 0;
}