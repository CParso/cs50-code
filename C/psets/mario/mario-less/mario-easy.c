#include <cs50.h>
#include <stdio.h>

void hash(void);

int main(void)
{
    int height;
    //prompts the user for a an integer from 1 to 8
    do
    {
        height = get_int("How tall should the pyramids be? ");
    }
    while (height < 1 || height > 8); //until a correct response is given


    for (int row = 0; row < height; row++)
    {
        for (int spaces = row + 1; spaces < height; spaces++)
        {
            printf(" ");
        }
        for (int hash = height + row + 1; hash > height; hash--)
        {
            printf("#");
        }
        printf("\n");
    }
}

// spaces working
//