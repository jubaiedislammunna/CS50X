#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start Size: ");
    }
    while (start < 9);
    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End Size ");
    }
    while (start > end);
    // TODO: Calculate number of years until we reach threshold
    int year = 0;
    for (int n = start; n < end; n = n + (n / 3) - (n / 4))
    {
        year++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", year);
}
