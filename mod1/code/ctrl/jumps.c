#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
- **Labels**: Jump targets use symbolic labels; 
  - assembler and linker handle encoding.  
- **Encodings**: Targets are PC-relative (1/2/4 bytes) or absolute (4 bytes); 
  - assembler selects the method.
📝 Analyze the encoding of `jump` instructions
- PC-Relative Addressing: PC points to the next instruction, not the jump. 
  - both before and after link
- Early processors updated PC first.
*/

int main()
{
  int randomNumber, guess;
  srand(time(NULL));          // Seed the random number generator
  randomNumber = rand() % 10; // Generate a random number between 0 and 9

  printf("Welcome to the Number Guessing Game!\n");
  printf("Guess a number between 0 and 9: ");

// Using goto to implement a while loop
start_loop:
  scanf("%d", &guess);

  // Judge the answer
  if (guess == randomNumber)
  {
    printf("Congratulations! You guessed the correct number: %d\n", randomNumber);
  }
  else if (guess < 0 || guess > 9)
  {
    printf("Invalid guess! Please enter a number between 0 and 9: ");
    goto start_loop; // Restart the loop
  }
  else if (guess < randomNumber)
  {
    printf("Too low! Try again: ");
    goto start_loop; // Restart the loop
  }
  else
  {
    printf("Too high! Try again: ");
    goto start_loop; // Restart the loop
  }

  return 0;
}