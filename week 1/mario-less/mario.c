#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int row = 0; row < height; row++)
    {
        for (int space = 0; row < height - space - 1; space++)
        {
            printf(" ");
        }

        for (int c = 0; c <= row; c++)
            printf("#");
        printf("\n");
    }
}