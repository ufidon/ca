#include <stdio.h>
#include <stdint.h>

int main()
{
  // Demonstrate MOV
  uint64_t rax = 0x0011223344556677; // MOV rax, 0x0011223344556677
  printf("MOV: rax = 0x%lx\n", rax);

  // Demonstrate MOVZX
  uint8_t dl = 0xAA;    // MOV dl, 0xAA
  uint64_t rax_zx = dl; // MOVZX rax, dl
  printf("MOVZX: rax = 0x%lx\n", rax_zx);

  // Demonstrate MOVSX
  int8_t dl_signed = -86;     // MOV dl, 0xAA (interpreted as -86 in signed 8-bit)
  int64_t rax_sx = dl_signed; // MOVSX rax, dl
  printf("MOVSX: rax = 0x%lx\n", rax_sx);

  // Demonstrate MOV with register-to-register transfer
  uint8_t al = dl;                       // MOV al, dl
  rax = (rax & 0xFFFFFFFFFFFFFF00) | al; // Update lower 8 bits of rax
  printf("MOV (register-to-register): rax = 0x%lx\n", rax);

/** 📝 Try all C integer data type ↔ C integer data type
| **Type**                    | **<stdint.h> Equivalent** | **Size (bytes)** |
|-----------------------------|---------------------------|------------------|
| `signed char`               | `int8_t`                  | 1                |
| `unsigned char`             | `uint8_t`                 | 1                |
| `short` / `signed short`    | `int16_t`                 | 2                |
| `unsigned short`            | `uint16_t`                | 2                |
| `int` / `signed int`        | `int32_t`                 | 4                |
| `unsigned int`              | `uint32_t`                | 4                |
| `long` / `signed long`      | (Platform Dependent)      | 8 (on 64-bit)    |
| `unsigned long`             | (Platform Dependent)      | 8 (on 64-bit)    |
| `long long` / `signed long long` | `int64_t`            | 8                |
| `unsigned long long`        | `uint64_t`                | 8                |

---

### Notes:
1. `<stdint.h>` guarantees exact sizes:
   - `int8_t` is always 1 byte (8 bits).
   - `int16_t`, `int32_t`, and `int64_t` are always 2, 4, and 8 bytes, respectively.
   - For unsigned types, the corresponding `uint8_t`, `uint16_t`, `uint32_t`, and `uint64_t` follow the same size guarantees.
2. **Platform-dependent `long`**:
   - The size of `long` is platform-dependent. On most **64-bit systems**, it's 8 bytes, but on **32-bit systems**, it’s typically 4 bytes. `long` doesn't have a direct `<stdint.h>` equivalent because its size can vary.
3. `<stdint.h>` also defines types like `int_leastN_t` and `int_fastN_t`, which are less strict about size but optimized for speed or minimum size.
*/

  return 0;
}