#include <stdio.h>

struct rect
{
  long llx;             // X coordinate of lower-left corner
  long lly;             // Y coordinate of lower-left corner
  unsigned long width;  // Width (in pixels)
  unsigned long height; // Height (in pixels)
  unsigned color;       // Color (in RGB)
};

// Function to compute the area of a rectangle
long area(struct rect *rp)
{
  return rp->width * rp->height; // Access fields using pointer dereferencing
}

// Function to rotate the rectangle 90 degrees clockwise
void rotate_left(struct rect *rp)
{
  long temp = rp->height;
  rp->height = rp->width; // Swap width and height
  rp->width = temp;

  rp->llx -= 1; // Shift the lower-left corner (example)
}

int main()
{
  // Declare and initialize a rectangle
  struct rect r = {0, 0, 10, 20, 0xFF00FF}; // {llx, lly, width, height, color}

  // Print the area of the rectangle
  printf("Area of rectangle: %ld\n", area(&r));

  // Print rectangle details before rotation
  printf("Before rotation: width = %lu, height = %lu\n", r.width, r.height);

  // Rotate the rectangle
  rotate_left(&r);

  // Print rectangle details after rotation
  printf("After rotation: width = %lu, height = %lu\n", r.width, r.height);
  printf("New lower-left corner: (%ld, %ld)\n", r.llx, r.lly);

  return 0;
}
