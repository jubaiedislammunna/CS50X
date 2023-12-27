#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int name;
    {
        string user_name = get_string("Whats Your Name? ");
        printf("hello, %s\n", user_name);
    }
}