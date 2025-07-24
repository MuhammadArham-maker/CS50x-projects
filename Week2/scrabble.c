#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Defined Functions
int cal_points(string word);

// Constant Points of each letter
const int letter_values[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                             1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Main Function
int main(void)
{
    // Prompting for input
    string word_1 = get_string("Player 1: ");
    string word_2 = get_string("Player 2: ");

    // Function call to get points of each words
    int points_1 = cal_points(word_1);
    int points_2 = cal_points(word_2);

    // Checking who Wins
    if (points_1 > points_2)
    {
        printf("Player 1 wins!\n");
    }
    else if (points_1 < points_2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return 0;
}

// Return the sum of all points of letters
int cal_points(string word)
{
    // Variable for calculating the total sum of points of characters
    int sum = 0;

    // Loop through each letter to calculate points
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Storing each characters in variable letter
        char letter = word[i];

        // Checking for letters and non letters
        if (isalpha(letter))
        {
            // Converts the letters to uppercase if in lower, and assign them there correct index
            int index = toupper(letter) - 'A';

            // Adds the letter's scores using its alphabet index
            sum += letter_values[index];
        }
    }
    return sum;
}
