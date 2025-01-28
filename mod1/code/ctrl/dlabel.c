#include <stdio.h>

/* GNU c extension
void *label_ptr = &&my_label; // Store the address of the label
goto *label_ptr;              // Jump to the label

// state machine
void *state = &&start;
while (1) {
    goto *state;
start:
    printf("Starting...\n");
    state = &&middle;
    continue;
middle:
    printf("In the middle...\n");
    state = &&end;
    continue;
end:
    printf("Ending...\n");
    break;
}
*/

int main()
{
  void *label_ptr = NULL;

  int choice;
  printf("Enter 1 or 2: ");
  scanf("%d", &choice);

  // Store the address of a label based on user input
  if (choice == 1)
  {
    label_ptr = &&label1;
  }
  else if (choice == 2)
  {
    label_ptr = &&label2;
  }
  else
  {
    printf("Invalid choice!\n");
    return 1;
  }

  // Jump to the selected label
  goto *label_ptr;

label1:
  printf("You chose label 1.\n");
  return 0;

label2:
  printf("You chose label 2.\n");
  return 0;
}