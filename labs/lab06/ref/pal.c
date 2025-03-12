// Test if an array is a palindrome using array indexing
// If it is then flip each of its symmetrical components
long long flippalindrome_a(long long array[], long long size)
{
    long long i;
    // Compare elements from start and end moving inward
    for (i = 0; i < size / 2; i++)
    {
        if (array[i] != array[size - 1 - i])
        {
            return 0; // Not a palindrome if any pair doesn't match
        }
    }

    // It is, flip each of its symmetrical components
    // e.g. 1,2,3,2,1 → 2,1,3,1,2
    long long left_end, right_begin, mid;
    mid = size / 2;
    if (size % 2 == 0)
    {
        right_begin = size / 2;
        left_end = right_begin - 1;
    }
    else
    {
        left_end = mid - 1;
        right_begin = mid + 1;
    }

    for (i = 0; i < mid / 2; i++)
    {
        // Reverse left part
        long long temp1 = array[i];
        array[i] = array[left_end - i];
        array[left_end - i] = temp1;

        // Reverse right part
        long long temp2 = array[right_begin + i];
        array[right_begin + i] = array[size - 1 - i];
        array[size - 1 - i] = temp2;
    }

    return 1; // Palindrome if all pairs match
}

// Test if an array is a palindrome using pointer referencing
// If it is then flip each of its symmetrical components
long long flippalindrome_p(long long* data, long long size)
{
    long long* p = data;                 // Start pointer
    long long* p_end = data + size - 1;  // End pointer

    // Check if it’s a palindrome
    while (p < p_end)
    {
        if (*p != *p_end)
        {
            return 0; // Not a palindrome if elements don't match
        }
        p++;
        p_end--;
    }

    // It is, flip each of its symmetrical components
    long long mid = size / 2;
    long long* left_end;
    long long* right_begin;

    if (size % 2 == 0)
    {
        right_begin = data + size / 2;
        left_end = right_begin - 1;
    }
    else
    {
        left_end = data + mid - 1;
        right_begin = data + mid + 1;
    }

    p = data;                  // Reset to start of left half
    p_end = data + size - 1;    // Reset to end of the array

    long long* p_right = right_begin;  // Start of right half
    while (p < left_end)       // Loop until middle of left half
    {
        // Reverse left part
        long long temp1 = *p;
        *p = *left_end;
        *left_end = temp1;

        // Reverse right part
        long long temp2 = *p_right;
        *p_right = *p_end;
        *p_end = temp2;

        p++;           // Move inward in left half
        left_end--;    // Move inward in left half
        p_right++;     // Move inward in right half
        p_end--;       // Move inward in right half
    }

    return 1; // Palindrome if all pairs match
}

int main()
{
    long long arr1[] = { 1, 2, 3, 2, 1 };
    long long arr2[] = { 1, 2, 4, 4, 2, 1 };

    long long ispal1 = flippalindrome_a(arr1, 5);
    long long ispal2 = flippalindrome_a(arr2, 6);

    ispal1 = flippalindrome_p(arr1, 5);
    ispal2 = flippalindrome_p(arr2, 6);

    return 0;
}