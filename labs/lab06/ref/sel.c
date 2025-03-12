// selectionSort in array indexing
/*
void selectionSort(long long array[], long long size)
{
    long long i, j, min_idx;
    for (i = 0; i < size - 1; i++)
    {
        // Find the minimum element in the right unsorted part
        min_idx = i;
        for (j = i + 1; j < size; j++)
        {
            if (array[j] < array[min_idx])
                min_idx = j;
        }
        // Swap the found minimum element with the first element
        // in the right unsorted part
        if (min_idx != i)  // Only swap if min_idx changed
        {
            long long temp = array[min_idx];
            array[min_idx] = array[i];
            array[i] = temp;
        }
    }
}
*/

// pointer version
void selectionSort(long long* array, long long size)
{
    long long* p_end = array + size - 1; // Pointer to last element
    long long* p = array;                // Pointer to current position
    long long* min_ptr;                  // Pointer to minimum
    long long* q;                        // Pointer to scan unsorted part
    long long temp;

    while (p < p_end)
    {
        // Find the minimum element in the right unsorted part
        min_ptr = p; // Pointer to minimum
        q = p + 1;   // Pointer to scan unsorted part
        while (q <= p_end)
        {
            if (*q < *min_ptr)
                min_ptr = q;
            q++;
        }
        // Swap the found minimum with the current position
        if (min_ptr != p) // Only swap if min_ptr changed
        {
            temp = *min_ptr;
            *min_ptr = *p;
            *p = temp;
        }
        p++; // Move to next position
    }
}

int main()
{
    long long arr1[] = { 3, 1, 2 };
    long long arr2[] = { 4,2,1,3 };

    selectionSort(arr1, 3);
    selectionSort(arr2, 4);

    return 0;
}