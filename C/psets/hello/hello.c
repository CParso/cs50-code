#include <stdio.h>
#include <cs50.h>
//headers to allow for use of functions printf and get_string

int main(void)
{
    string answer = get_string("What's your name? ");
    //retrieves a string from the user
    printf("Hello, %s\n", answer);
    //prints hello + the retrieved string
}