#include <stdio.h>
#include <cs50.h>

float saving(float price, float reduction);

int main (void)
{
    float full = get_float("What is the full price?: ");

    float discount = get_float("What is the discount percentage?: ");

    float sale = saving(full, discount);

    printf("You are saving £%.2f\n", sale);
}

float saving(float price, float reduction)
{
    reduction /= 100;
    return price * reduction;
}