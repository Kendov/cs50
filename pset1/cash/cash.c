#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float input;
    int coinsAmount = 0;
    
    //asks for input
    do
    {
        input = get_float("Change owed: ");

    }
    while (input <= 0);//checks if the number is positive
    
    //calculates the amount of coins
    for (int remaining = round(input * 100); remaining > 0; coinsAmount++)
    {
        if (remaining >= 25)
        {
            remaining -= 25;
        }
        else if (remaining >= 10)
        {
            remaining -= 10;
        }
        else if (remaining >= 5)
        {
            remaining -= 5;
        }
        else
        {
            remaining--;
        }
    }

    //prints the number of coins
    printf("%i\n", coinsAmount);
}
