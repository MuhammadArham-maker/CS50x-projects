#include <cs50.h>
#include <stdio.h>

// Defined Fuctions
int get_input(void);
int calculate_quarter(int n);
int calculate_dimes(int n);
int calculate_nickel(int n);
void calculate_coins(int n);

// Main Fuction
int main(void)
{
    int n = get_input();
    calculate_coins(n);
}

// Get's user Input
int get_input(void)
{
    int i;
    do
    {
        i = get_int("Change owed: ");
    }
    while (i < 0);
    return i;
}

// Quarters
int calculate_quarter(int cents)
{
    return cents / 25;
}

// Dimes
int calculate_dimes(int cents)
{
    return cents / 10;
}

// Nickle
int calculate_nickel(int cents)
{
    return cents / 5;
}

// Coins
void calculate_coins(int cents)
{
    if (cents == 0) // Handles 0 input
    {
        printf("0\n");
        return;
    }
    int quarters = calculate_quarter(cents);            // Calculate quarters
    cents %= 25;                                        // Update cent value
    int dimes = calculate_dimes(cents);                 // Calculate dimes
    cents %= 10;                                        // Update cent value
    int nickel = calculate_nickel(cents);               // Calculate nickle
    cents %= 5;                                         // Update cent value
    int pennie = cents;                                 // Calculate pennie
    printf("%i\n", quarters + dimes + nickel + pennie); // Total number of coins
}
