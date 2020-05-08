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

    //print blocks
    for (int i = 1; i <= input; i++)
    {
        for (int x = 0; x < input; x++)
        {
            //return space if x(colum) is less than input - row
            printf(x < input - i ? " " : "#");
        }
        printf("\n"); //print new line at the end of the row
    }

}
