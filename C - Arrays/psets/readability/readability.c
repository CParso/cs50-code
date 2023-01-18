#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void readability(float letters, float words, float sentences);

int main(void)
{
    // Get input from user
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    readability(letters, words, sentences);
}

int count_letters(string text)
{
    // For loop that increases count if the current character is alphabetic
    int i;
    int letters = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    // For loop that increases the count if the current character is a space
    int i;
    int words = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (text[i] == 32)
        {
            words++;
        }
    }
    // Increase count by one because the amount of words will be one more than the amount of spaces
    words++;
    return words;
}

int count_sentences(string text)
{
    // For loop that increases the count if the current character is a full stop, exclaimation mark or question mark
    int i;
    int sentences = 0;
    for (i = 0; i < strlen(text); i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}

void readability(float letters, float words, float sentences)
{
    // Calculations using the formula

    // Calculate average letters
    float average_letters = letters / words * 100;

    // Calculate average sentences
    float average_sentences = sentences / words * 100;

    // Input values into the formula
    float index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;

    // Round the result for a whole number to output
    index = round(index);

    // If statements Grades higher than 15 or lower than 1
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}