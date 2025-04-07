#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // For file operations
#include <unistd.h>   // For close()
#include <string.h>   // For strlen()
#include <sys/mman.h> // For memory mapping

void demonstrate_system_calls() {
    // 1. System Call Demonstration
    printf("\n=== System Call Demonstration ===\n");
    
    // Open file (system call: open)
    int fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }
    
    // Write to file (system call: write)
    char *data = "Hello, System Calls!\n";
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return;
    }
    
    printf("Wrote %zd bytes to file\n", bytes_written);
    
    // Close file (system call: close)
    if (close(fd) == -1) {
        perror("Error closing file");
    } else {
        printf("File closed successfully\n");
    }
}

void demonstrate_page_fault() {
    // 2. Page Fault Demonstration
    printf("\n=== Page Fault Demonstration ===\n");
    
    // Allocate a large chunk of memory
    size_t size = 10 * 1024 * 1024; // 10MB
    char *memory = mmap(NULL, size, PROT_READ | PROT_WRITE, 
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (memory == MAP_FAILED) {
        perror("Memory mapping failed");
        return;
    }
    
    printf("Memory allocated at %p\n", memory);
    printf("Writing to memory - this will cause page faults...\n");
    
    // Writing to this memory will cause page faults as pages are
    // brought in from swap/disk on demand
    for (size_t i = 0; i < size; i += 4096) { // 4KB page size
        memory[i] = 'A';
    }
    
    printf("Memory write completed\n");
    munmap(memory, size);
}

void demonstrate_segmentation_fault() {
    // 3. Segmentation Fault Demonstration
    printf("\n=== Segmentation Fault Demonstration ===\n");
    
    printf("Attempting to write to invalid memory location...\n");
    
    // This will cause a segmentation fault
    // Uncomment the line below to see it in action
    // WARNING: This will crash the program!
    
    // char *invalid_ptr = (char *)0x1;  // Invalid memory address
    // *invalid_ptr = 'X';              // Attempt to write
    
    // Alternative demonstration using NULL pointer
    char *null_ptr = NULL;
    printf("This line will print\n");
    *null_ptr = 'Y';  // This will cause segmentation fault
    printf("This line won't print\n");
}

int main() {
    // Run each demonstration
    demonstrate_system_calls();
    demonstrate_page_fault();
    demonstrate_segmentation_fault();
    
    return 0;
}
