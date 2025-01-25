#include "student.h"

float calculate_average_weight(Student students[], int size) {
    if (size == 0) return 0;

    float total_weight = 0;
    for (int i = 0; i < size; i++) {
        total_weight += students[i].weight;
    }
    return total_weight / size;
}
