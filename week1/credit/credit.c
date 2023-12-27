#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get the credit card number from the user
    long long card_number = get_long_long("Enter your credit card number: ");

    // Initialize variables to store the sum of digits and the number of digits
    int sum_of_digits = 0;
    int num_digits = 0;

    // Iterate through the digits of the credit card number
    while (card_number > 0)
    {
        // Get the last digit of the card number
        int digit = card_number % 10;

        // If it's an even digit position, add the digit to the sum of digits
        if (num_digits % 2 == 0)
        {
            sum_of_digits += digit;
        }
        // If it's an odd digit position, double the digit and add its digits to the sum
        else
        {
            int doubled_digit = digit * 2;
            sum_of_digits += doubled_digit % 10 + doubled_digit / 10;
        }

        // Move to the next digit and increment the digit counter
        card_number /= 10;
        num_digits++;
    }

    // Check if the card number is valid based on the sum of digits modulo 10
    if (sum_of_digits % 10 == 0)
    {
        // Determine the type of credit card based on the number of digits and the first two digits
        if ((num_digits == 13 || num_digits == 16) && (card_number / 10 == 4))
        {
            printf("VISA\n");
        }
        else if (num_digits == 16 && (card_number >= 51 && card_number <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if (num_digits == 15 && (card_number == 34 || card_number == 37))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
