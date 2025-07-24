#include <cs50.h>
#include <stdio.h>

// Defined Fuctions
void print_space(int n);
void print_bricks(int n);
void print_row(int space, int bricks);
void print_pyramid(int n);
int get_input(void);

// Main Fuction
int main(void)
{
    int times = get_input();
    print_pyramid(times);
}

// Print Spaces
void print_space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// Print Bricks
void print_bricks(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

// Print Each Rows
void print_row(int space, int bricks)
{
    print_space(space);
    print_bricks(bricks);
    print_space(2);
    print_bricks(bricks);
    printf("\n");
}

// Print Pyramid
void print_pyramid(int n)
{
    for (int rw = 1; rw <= n; rw++)
    {
        print_row(n - rw, rw);
    }
}

// Get's user input
int get_input(void)
{
    int i;
    do
    {
        i = get_int("Height: ");
    }
    while (i <= 0 || i > 8);
    return i;
}
