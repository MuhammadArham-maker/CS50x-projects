#include <cs50.h>
#include <stdio.h>

// Defined Functions
int get_height(void);
void print_space(int n);
void print_brick(int n);
void print_row(int space, int brick);
void print_pyramid(int n);

// Main function
int main(void)
{
    int times = get_height();
    print_pyramid(times);
}

// Get's Pyramid height(INPUT)
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Enter the pyramid's height ");
    }
    while (n <= 0 || n > 100);
    return n;
}

// Prints Space
void print_space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// Prints Brick
void print_brick(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

// Prints each Row
void print_row(int space, int brick)
{
    print_space(space);
    print_brick(brick);
    printf("\n");
}

// Prints the Pyramid
void print_pyramid(int n)
{
    for (int rw = 1; rw <= n; rw++)
    {
        print_row(n - rw, rw);
    }
}
