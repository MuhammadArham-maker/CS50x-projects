#include <cs50.h>
#include <stdio.h>

// DEFINED FUNCTIONS
long get_input(void);
int luhn_double_digit_sum(long card_no);
int sum_of_digits(int n);
int sum_untouched_digits(long card_no);
int luhn_total_sum(long card_no);
int count_digit(long card_no);
int is_valid_card(int n);
void identify_cardtype(long card_no);
int get_first_two_digits(long card_no);
int get_first_digit(long card_no);

// MAIN FUNCTION
int main(void)
{
    long card_no = get_input();
    if (card_no == -1)
    {
        printf("INVALID\n");
        return 0;
    }
    int total = luhn_total_sum(card_no);
    int is_valid = is_valid_card(total);
    if (is_valid)
    {
        identify_cardtype(card_no);
    }
    else
    {
        printf("INVALID\n");
    }
}

// RETURN USER INPUT
long get_input(void)
{
    long card_no = get_long("Number: ");
    int digits = count_digit(card_no);
    if (digits < 13 || digits > 16) // "Checks" for wrong entry
    {
        return -1;
    }
    return card_no;
}

// Return the luhn second last digts sum of a card_No
int luhn_double_digit_sum(long card_no)
{
    int position_from_right = 1;
    int digits_sum = 0;
    while (card_no > 0)
    {
        if (position_from_right % 2 == 0) //"checks" digit correct position
        {
            int num = card_no % 10 * 2; // "Multiply" the digit by 2
            if (num > 9)                // Handles 2 digit no.s and add the digits in them
            {
                int sum = sum_of_digits(num);
                digits_sum += sum;
            }
            else
            {
                digits_sum += num; // adds
            }
        }
        card_no /= 10;         // "updates" card no by removing each digit one by one
        position_from_right++; // "updates" position of digits
    }
    return digits_sum;
}

// Returns the "sum of all digits in an integer n".
int sum_of_digits(int n)
{
    int digitsum = 0;
    while (n > 0)
    {
        digitsum += n % 10;
        n /= 10;
    }
    return digitsum;
}

// Return the "left over digits sum."
int sum_untouched_digits(long card_no)
{
    int position_from_right = 1;
    int digit_sum = 0;
    while (card_no > 0)
    {
        if (position_from_right % 2 != 0)
        {
            digit_sum += card_no % 10;
        }
        card_no /= 10;
        position_from_right++;
    }
    return digit_sum;
}

// Return the "total luhns Card_no sum"
int luhn_total_sum(long card_no)
{
    int sum = luhn_double_digit_sum(card_no) + sum_untouched_digits(card_no);
    return sum;
}

// Return the "number of digits"
int count_digit(long card_no)
{
    int count = 0;
    while (card_no > 0)
    {
        card_no /= 10;
        count++;
    }
    return count;
}

// Check for card "validty"
int is_valid_card(int n)
{
    return (n % 10 == 0);
}

// Check for card type and "prints output"
void identify_cardtype(long card_no)
{
    int digits = count_digit(card_no);
    int temp = get_first_two_digits(card_no);
    if ((temp == 34 || temp == 37) && digits == 15)
    {
        printf("AMEX\n");
    }
    else if ((temp >= 51 && temp <= 55) && digits == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((get_first_digit(card_no) == 4) && (digits == 13 || digits == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Return the first 2 digit of the card_no
int get_first_two_digits(long card_no)
{
    while (card_no >= 100)
    {
        card_no /= 10;
    }
    return card_no;
}

// Return first digit of the card_no
int get_first_digit(long card_no)
{
    while (card_no >= 10)
    {
        card_no /= 10;
    }
    return card_no;
}
