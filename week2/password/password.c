// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool upper = false, lower = false, num = false, sym = false;
    int length = strlen(password);
    for (int i = 0; i < length; i++)
    {
        if (upper == false)
        {
            upper = isupper(password[i]);
        }
        if (lower == false)
        {
            lower = islower(password[i]);
        }
        if (num == false)
        {
            num = isdigit(password[i]);
        }
        if (sym == false)
        {
            sym = !isalnum(password[i]);
        }
    }
    if (upper == true && lower == true && num == true && sym == true)
    {
        return true;
    }

    return false;
}
