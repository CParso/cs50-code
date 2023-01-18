#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt user for a card number
    long card_number = get_long("Enter your card number: ");

    //calculate the length of the card number
    int count = 0;
    long i = card_number;
    while (i > 0)
    {
        i /= 10;
        count++;
    }

    //check if the card number is a valid length, if not then output INVALID
    if (count != 13 && count != 15 && count != 16)
    {
        printf("INVALID\n");
        return 0;
    }


    long sum = card_number;
    long digit_sum = 0;

    while (sum > 0)  //Luhn's algorithm
    {
        //calculates the last digit
        long last_digit = sum % 10;
        digit_sum += last_digit;

        //subtract the last digit
        long first_sum = sum - last_digit;

        //remove the last digit
        long second_sum = first_sum / 10;

        //calculate the second last digit
        long secondlast_digit = second_sum % 10;

        //subtract the second last digit
        long final_sum = second_sum - secondlast_digit;

        //remove the second last digit
        final_sum /= 10;

        //multiply second last digit
        secondlast_digit *= 2;

        long j;
        //separate each digit from the result of the multiplication and then add them to the total
        while (secondlast_digit > 0)
        {
            j = secondlast_digit % 10;
            secondlast_digit /= 10;
            digit_sum += j;
        }
        //update the loop, reducing the card number by 2 digits each time
        sum = final_sum;
        //loop ends when the card number reaches 0
    }

    long start = card_number;
    do
    {
        start = start / 10;  //loop that reduces the length of card number by a digit each time
    }
    while (start > 100);  //until there are only two digits left

    //if the last number of the total of the calculated digits doesn't equal 0, then it is invalid
    if ((digit_sum % 10) != 0)
    {
        printf("INVALID\n");
    }

    //if the first number is 3 AND the second number is 4 OR 7 --> AMEX
    else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }

    //if the first number is 5 AND the second number is BETWEEN 0 and 6 --> MASTERCARD
    else if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }

    //if the first number is 4 --> VISA
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }

    //if in the rare case the checksum is passed but it doesn't qualify for any of the card types --> INVALID
    else
    {
        printf("INVALID\n");
    }
}