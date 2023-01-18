#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool characters(string arg);
bool alphabetic(string arg_letters);
bool duplicate(string arg_letters);
void cipher(string arg, string plaintext);

int main(int argc, string argv[])
{
    // Check for exaclty 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validating the key

    // Check for exactly 26 characters
    if (characters(argv[1]) == 1)
    {
        return 1;
    }

    // Check for only alphabetic characters
    if (alphabetic(argv[1]) == 1)
    {
        return 1;
    }

    // Check for no duplicates
    if (duplicate(argv[1]) == 1)
    {
        return 1;
    }

    // Get plaintext
    string plaintext = get_string("plaintext: ");


    cipher(argv[1], plaintext);
}

// Check for exactly 26 characters
bool characters(string arg)
{
    if (strlen(arg) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    return 0;
}

// Check for only alphabetic characters
bool alphabetic(string arg_letters)
{
    int i;
    for (i = 0; i < strlen(arg_letters); i++)
    {
        if (isalpha(arg_letters[i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }
    return 0;
}

// Check for no duplicates
bool duplicate(string arg_letters)
{
    int i;
    int j;
    // Two nested loops
    // First loop stores i character of the key
    for (i = 0; i < strlen(arg_letters); i++)
    {
        // Convert i character to uppercase to correctly check for duplicates
        arg_letters[i] = toupper(arg_letters[i]);
        // Second loop compares i character of key with every other character in the key by looping j
        for (j = i + 1; j < strlen(arg_letters); j++)
        {
            // If i character matches with another then return an error message
            if (arg_letters[i] == arg_letters[j])
            {
                printf("Key must not contain duplicate characters.\n");
                return 1;
            }
        }
    }
    return 0;
}

void cipher(string arg, string plaintext)
{
    // Create an alphabet variable in order to match the plaintext to the key
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int length = strlen(plaintext);

    // Declare ciphertext as a char with an identical number of characters as plaintext
    // Ciphertext must be a char instead of a string in order to be easily manipulated when adding characters later in code
    char ciphertext[length];

    // Because ciphertext was not declared as a string it won't appear to have an endpoint later in code in the loops
    // Therefore we must give it an endpoint by declaring the last character to be null character '\0' to prevent errors
    ciphertext[length] = '\0';

    int i;
    int j;
    int k;

    // Similar to the duplicate loop, the outer loop cycles through each character of plaintext
    for (i = 0; i < length; i++)
    {
        // Differentiate between upper and lower case
        if (isupper(plaintext[i]) != 0)
        {
            // Two nested loops that take the character from the outer loop and check if it exists in the alphabet variable
            // If yes the append ciphertext with 'key' character the matches alphabet, in the same position as plaintext
            for (j = 0; j < strlen(arg); j++)
            {
                if (plaintext[i] == alphabet[j])
                {
                    ciphertext[i] = arg[j];
                }
            }
        }
        else if (islower(plaintext[i]) != 0)
        {
            for (k = 0; k < strlen(arg); k++)
            {
                if (plaintext[i] == tolower(alphabet[k]))
                {
                    ciphertext[i] = tolower(arg[k]);
                    break;
                }
            }
        }
        // If the character is not alphabetic then simply append the plaintext character directly to ciphertext
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: %s\n", ciphertext);
}

// Take a command line argument for a 'key'
// - must have exactly 2 arguments

// Validate key
// - case insensitive
// - must contain exactly 26 characters
// - must only contain letters
// - no duplicate characters

// Get plaintext
//

// Encipher
// - for each alphabetic character, determine what letter it maps to
// - the letter case should be preserved
// - numbers, spaces or punctuation should also be preserved

// Print ciphertext