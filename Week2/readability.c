#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Defined Functions
int letter_count(string text);
int words_count(string text);
int sentence_count(string text);
void cal_grade(int index);

// Main function
int main(void)
{
    // get text from the user
    string text = get_string("Text: ");

    // no. of letters
    int letters = letter_count(text);

    // number of words
    int words = words_count(text);

    // number of sentences
    int sentence = sentence_count(text);

    // Finding L and S
    float L = ((float) letters / words) * 100;
    float S = ((float) sentence / words) * 100;

    // Applying the Coleman liau Index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Calculating grade
    cal_grade(index);
    return 0;
}

// Returns number of letters in the text
int letter_count(string text)
{
    int count = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Returns number of words in the text
int words_count(string text)
{
    int count = 0;
    bool in_word = false;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (!isspace(text[i]) && !in_word)
        {
            in_word = true;
            count++;
        }
        else if (isspace(text[i]))
        {
            in_word = false;
        }
    }
    return count;
}

// Returns number of sentences in the text
int sentence_count(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

// Grade calculator
void cal_grade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
