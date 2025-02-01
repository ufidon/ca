#include <stdio.h>
#include <string.h>
/*
### **Steps to Demonstrate Exploitation**:

- **Crafting the Input**: The attacker needs to input a string that fills the `buffer[64]` with arbitrary data and then overwrite the return address with the address of the `exploit()` function.
- **In a Real Attack**: The attacker's input would include:
  - A series of characters to fill the `buffer` (64 bytes).
  - The address of the `exploit()` function to overwrite the return address.
*/
// gcc -fno-stack-protector -z execstack -o bf bf.c
// Vulnerable function with buffer overflow
void vulnerable_function() {
    char buffer[64];  // Small buffer to hold user input
    printf("Enter some text: ");
    gets(buffer);  // Dangerous: does not check for buffer overflow
    printf("You entered: %s\n", buffer);
}

// Exploit function to simulate an attack (would normally be in separate code)
void exploit() {
    printf("Exploit successful! You've hijacked control flow.\n");
}

int main() {
    // Normal execution
    printf("Program started\n");
    vulnerable_function();
    printf("Program ended\n");

    return 0;
}
