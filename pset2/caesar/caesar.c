#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool isnumber(string text);
void encrypt(int key, string text);
bool isArgValid(int argc, string args[]);

int main(int argc, string argv[])
{
    int key;
    string input;

    //checks if has 2 arguments and if can be a number
    if (!isArgValid(argc, argv))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //gets key and convert to int
    key = atoi(argv[1]);

    //gets text input
    input = get_string("plaintext: ");

    //calculates the output
    encrypt(key, input);


    return 0;
}

//checks if the argument is valid
bool isArgValid(int argc, string args[])
{
    //checks if has only two arguments
    if (argc != 2)
    {
        return false;
    }
    //checks if is a number
    if (!isnumber(args[1]))
    {
        return false;
    }
    return true;
}

//checks if a string can be a valid number
bool isnumber(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (!isdigit(text[i]))
        {
            return false;
        }
    }
    return true;
}

//calculates the caesar cipher
void encrypt(int key, string text)
{
    printf("ciphertext: ");

    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", (text[i] - 65 + key) % 26 + 65);
        }
        else if (islower(text[i]))
        {
            printf("%c", (text[i] - 97 + key) % 26 + 97);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");

}

