#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defined Functions
bool isvalid(int count, string key);
bool is_alphabet(string key);
bool is_repeating(string key);
void plain_to_cipher(string plaintext, string key);
void print_ciphertext(char p, string key);

// Main Function: Validates the key and calls the encryption function
int main(int argc, string argv[])
{
    // Checks the key validation
    if (!isvalid(argc, argv[1]))
    {
        return 1;
    }

    // Storing the checked key
    string key = argv[1];

    // Getting the plaintext
    string plaintext = get_string("plaintext: ");

    // Converting and then printing the plaintext to cyphertext
    printf("ciphertext: ");
    plain_to_cipher(plaintext, key);

    // Returns 0
    return 0;
}

// Function that converts plaintext to cyphertext
void plain_to_cipher(string plaintext, string key)
{
    // looping through the text to get each character
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // Variable to store character of plaintext
        char p = plaintext[i];
        // Checks for alphabets
        if (isalpha(p))
        {
            // Prints the cyphertext
            print_ciphertext(p, key);
        }
        // Checks for nonalphabets
        else
        {
            // Prints as it is
            printf("%c", p);
        }
    }
    // Prints new line at the end
    printf("\n");
}

// Function that takes plain char and print cypher char
void print_ciphertext(char p, string key)
{
    // Checks for uppercase
    if (isupper(p))
    {
        // Stores index number
        int index = p - 'A';
        // Stores character from the key
        char c = toupper(key[index]);
        // Prins the cypher character
        printf("%c", c);
    }
    // Checks for lowercase
    else if (islower(p))
    {
        // Stores index number
        int index = p - 'a';
        // Stores character from the key
        char c = tolower(key[index]);
        // Prints the cypher character
        printf("%c", c);
    }
}

// Function that checks the key validation
bool isvalid(int count, string key)
{
    // 1st Checks for argument count and
    // 2nd Checks for alphabets in the key
    if (count != 2 || !is_alphabet(key))
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    // 3rd Checks if the key has 26 letters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    // 4th Checks for repeated characters
    if (is_repeating(key))
    {
        printf("Key must not contain repeated characters.\n");
        return false;
    }
    // Returns true if the key is correct
    return true;
}

// Returns true if all character is alphabet
bool is_alphabet(string key)
{
    // Getting each characters
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // Check for non alpha
        if (!isalpha(key[i]))
        {
            // Returns false
            return false;
        }
    }
    // Returns true if all alpha
    return true;
}

// Function Checking any repeated characters
bool is_repeating(string key)
{
    // Gets the first character
    for (int i = 0; i < 26; i++)
    {
        // Match the first character to every characters in key
        for (int j = i + 1; j < 26; j++)
        {
            // if matched
            if (tolower(key[i]) == tolower(key[j]))
            {
                // Returns true if repeated
                return true;
            }
        }
    }
    // return false if not repeated
    return false;
}
