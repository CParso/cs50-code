#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    //prompts the user for a an integer from 1 to 8
    do
    {
        height = get_int("How tall should the pyramids be? ");
    }
    while (height < 1 || height > 8); //until a correct response is given


    for (int row = 0; row < height; row++) //loop row by row until you reach the height
    {
        for (int spaces = row + 1; spaces < height; spaces++) //print spaces until you have one less than row + height
        {
            printf(" ");
        }
        for (int left_hash = height + row + 1; left_hash > height;
             left_hash--) //print hashes + row counting down until you reach the height value
        {
            printf("#");
        }
        printf("  ");
        for (int right_hash = height + row + 1; right_hash > height;
             right_hash--) //print hashes in the same way as left_hash
        {
            printf("#");
        }
        printf("\n"); //then go to new line and repeat the row loop again and adding one
    }
}

//row must be added to spaces and hash so that each count one more time each loop to cause the steps to increase/decrease