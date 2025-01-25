#include <stdio.h>
#include <stdint.h> // For fixed-width integer types

// Function to perform left shift
uint32_t left_shift(uint32_t x, int shift_amount)
{
  return x << shift_amount;
}

// Function to perform right arithmetic shift
int32_t right_arithmetic_shift(int32_t x, int shift_amount)
{
  return x >> shift_amount;
}

// Function to perform right logical shift
uint32_t right_logical_shift(uint32_t x, int shift_amount)
{
  return x >> shift_amount;
}

int main()
{
  // Example values
  uint32_t x = 0x8000000F; // Example value for left and logical shifts
  int32_t y = 0x8000000F;  // Example value for arithmetic shift
  int shift_amount = 4;    // Shift amount

  // Left Shift
  uint32_t left_shift_result = left_shift(x, shift_amount);
  printf("Left Shift (0x%x << %d): 0x%x\n", x, shift_amount, left_shift_result);

  // Right Arithmetic Shift
  int32_t right_arithmetic_result = right_arithmetic_shift(y, shift_amount);
  printf("Right Arithmetic Shift (0x%x >> %d): 0x%x\n", y, shift_amount, right_arithmetic_result);

  // Right Logical Shift
  uint32_t right_logical_result = right_logical_shift(x, shift_amount);
  printf("Right Logical Shift (0x%x >> %d): 0x%x\n", x, shift_amount, right_logical_result);

  return 0;
}