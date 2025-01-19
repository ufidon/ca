#include <iostream>
#include <bitset>

int main()
{
  int a = 10, b = 4;
  int result;
  unsigned int c = 0b1010; // Binary 1010 (10 in decimal)
  unsigned int d = 0b1100; // Binary 1100 (12 in decimal)

  // Arithmetic Operations
  std::cout << "=== Arithmetic Operations ===\n";
  std::cout << "a = " << a << ", b = " << b << "\n";

  // Addition
  __asm {
        mov eax, a
        add eax, b
        mov result, eax
  }
  std::cout << "a + b = " << result << "\n";

  // Subtraction
  __asm {
        mov eax, a
        sub eax, b
        mov result, eax
  }
  std::cout << "a - b = " << result << "\n";

  // Multiplication (unsigned)
  __asm {
        mov eax, a
        mul b
        mov result, eax
  }
  std::cout << "a * b (unsigned) = " << result << "\n";

  // Multiplication (signed)
  __asm {
        mov eax, a
        imul eax, b
        mov result, eax
  }
  std::cout << "a * b (signed) = " << result << "\n";

  // Division (unsigned)
  __asm {
        mov eax, a
        xor edx, edx
        div b
        mov result, eax
  }
  std::cout << "a / b (unsigned) = " << result << "\n";

  // Division (signed)
  __asm {
        mov eax, a
        cdq
        idiv b
        mov result, eax
  }
  std::cout << "a / b (signed) = " << result << "\n";

  // Modulus (unsigned)
  __asm {
        mov eax, a
        xor edx, edx
        div b
        mov result, edx
  }
  std::cout << "a % b (unsigned) = " << result << "\n";

  // Modulus (signed)
  __asm {
        mov eax, a
        cdq
        idiv b
        mov result, edx
  }
  std::cout << "a % b (signed) = " << result << "\n";

  // Increment
  __asm {
        mov eax, a
        inc eax
        mov result, eax
  }
  std::cout << "++a = " << result << "\n";

  // Decrement
  __asm {
        mov eax, b
        dec eax
        mov result, eax
  }
  std::cout << "--b = " << result << "\n";

  // Negation
  __asm {
        mov eax, a
        neg eax
        mov result, eax
  }
  std::cout << "-a = " << result << "\n";

  // Logical Operations
  std::cout << "\n=== Logical Operations ===\n";
  std::cout << "c = " << std::bitset<8>(c) << " (" << c << "), d = " << std::bitset<8>(d) << " (" << d << ")\n";

  // Bitwise AND
  __asm {
        mov eax, c
        and eax, d
        mov result, eax
  }
  std::cout << "c & d = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bitwise OR
  __asm {
        mov eax, c
        or eax, d
        mov result, eax
  }
  std::cout << "c | d = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bitwise XOR
  __asm {
        mov eax, c
        xor eax, d
        mov result, eax
  }
  std::cout << "c ^ d = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bitwise NOT
  __asm {
        mov eax, c
        not eax
        mov result, eax
  }
  std::cout << "~c = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bitwise Shift Left
  __asm {
        mov eax, c
        shl eax, 2
        mov result, eax
  }
  std::cout << "c << 2 = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bitwise Shift Right
  __asm {
        mov eax, d
        shr eax, 1
        mov result, eax
  }
  std::cout << "d >> 1 = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bitwise Rotate Left
  __asm {
        mov eax, c
        rol eax, 1
        mov result, eax
  }
  std::cout << "c <<< 1 = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bitwise Rotate Right
  __asm {
        mov eax, d
        ror eax, 1
        mov result, eax
  }
  std::cout << "d >>> 1 = " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bit Test and Set (bts)
  __asm {
        mov eax, c
        bts eax, 2
        mov result, eax
  }
  std::cout << "Set bit 2 of c: " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bit Test and Reset (btr)
  __asm {
        mov eax, d
        btr eax, 3
        mov result, eax
  }
  std::cout << "Clear bit 3 of d: " << std::bitset<8>(result) << " (" << result << ")\n";

  // Bit Test and Complement (btc)
  __asm {
        mov eax, c
        btc eax, 1
        mov result, eax
  }
  std::cout << "Toggle bit 1 of c: " << std::bitset<8>(result) << " (" << result << ")\n";

  return 0;
}