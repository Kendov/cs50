#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get input
    int input;
    do
    {
        input = get_int("Height: ");
    }
    while (input < 1 || input > 8);


    for (int i = 1; i <= input; i++)
    {
        for (int x = 0; x < input + 2 + i; x++)
        {
            
            if (x < input - i) ////checks for space at the beginning
            {
                printf(" ");
            }
            else if (x == input || x == input + 1)//checks if is a gap
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }

        }
        printf("\n");//print a new line at the end of each row
    }
}
