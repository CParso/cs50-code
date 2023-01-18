#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = get_int("Choose a number: ");

    if (n % 2 == 0)
    {
        printf("This number is even\n");
    }

    else
    {
        printf("This number is odd\n");
    }
}