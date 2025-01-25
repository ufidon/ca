#include <stdio.h>
#include "student.h"

int main() {
    Student students[] = {
        {"Alice", 20, 60.5},
        {"Bob", 21, 75.2},
        {"Charlie", 19, 68.0},
    };
    int num_students = sizeof(students) / sizeof(students[0]);

    float average_weight = calculate_average_weight(students, num_students);
    printf("The average weight of the students is: %.2f kg\n", average_weight);

    return 0;
}
