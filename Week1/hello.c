#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? "); // Initializing variable "name"
    printf("hello, %s\n", name);                    // Printing "hello, name"
}
