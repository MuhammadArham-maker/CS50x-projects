#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defined Functions
bool is_number(string s);
void plain_to_cypher(string plain_text, int k);

// Main Fuction  accepts a command line argument
int main(int argc, string argv[])
{

    // Checks if the Command Line Argument [1] is interger
    if (argc == 2 && is_number(argv[1]))
    {
        // Gets the plain text
        string plain_text = get_string("plaintext: ");

        // Variable storing the converted string char to int char (key)
        int k = atoi(argv[1]);

        // Function call to print cypher text
        plain_to_cypher(plain_text, k);
        return 0;
    }
    // If the Command line Argument [1] is a noninteger
    else
    {
        printf("Usage: ./caesar key\n");
    }
    return 1;
}

// Fuction to check if a string is number
bool is_number(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Fuction to Prints the Cypher text
void plain_to_cypher(string plain_text, int k)
{
    // Printing beforhand the "Ciphertext"
    printf("ciphertext: ");
    // loop to get through each character in text
    for (int i = 0, len = strlen(plain_text); i < len; i++)
    {
        // Storing the plain text characters as p
        char p = plain_text[i];

        // Check if the character is alphabet and capital
        if (isalpha(p) && isupper(p))
        {
            // Shifting the uppercase letters
            char c = (((p - 'A') + k) % 26) + 'A';
            printf("%c", c);
        }

        // Check if the character is alphabet and lower
        else if (isalpha(p) && islower(p))
        {
            // Shifting the lowercase letters
            char c = (((p - 'a') + k) % 26) + 'a';
            printf("%c", c);
        }
        // Check if the character is nonalphabet
        else
        {
            // Printing the nonalphabet as it is
            printf("%c", p);
        }
    }
    // Printing a new line at the end
    printf("\n");
}
