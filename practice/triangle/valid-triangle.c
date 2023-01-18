#include <stdio.h>
#include <cs50.h>

//create a function that takes input for three side length values
//then checks if the three values can make a valid triangle
//output True or False accordingly

void valid_triangle();

int main(void)
{
    //calling the function
    valid_triangle();
}

void valid_triangle(void)
{
    //set up an array for the three sides
    float sides[3];
    int i = 0;
    //set up a do while loop to take input from the user
    do
    {
        sides[i] = get_float("Side length %i: ", i);
        i++;
    }
    //repeat the loop as long as the input is a positive number
    while (sides[i] >= 0);

    //if two sides are greater than the third then the triangle is valid
    if ((sides[0] + sides[1]) > sides[2])
    {
        printf("True\n");
    }

    else
    {
        printf("False\n");
    }
}