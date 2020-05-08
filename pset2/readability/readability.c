#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float get_index(float letters, float words, float sentences);

int main(void)
{
    //prompts for input
    string input = get_string("Text: ");

    //gets the amount of letters, words and sentences
    int letters = count_letters(input);
    int words = count_words(input);
    int sentences = count_sentences(input);

    //gets the rounded Coleman–Liau index
    int index = round(get_index(letters, words, sentences));


    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }


}



//returns the amount of letters in a text
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }

    }
    return letters;
}

//returns the amount of words in a text
int count_words(string text)
{
    int words = 0;
    int size = strlen(text);
    for (int i = 0; i < size; i++)
    {
        if (text[i] != ' ')
        {
            //keeps incrementing i until find a space or reach the end of the text
            while (text[i] != ' ' && i < size)
            {
                i++;
            }
            words++;
        }
    }
    return words;
}

//returns the amount of sentences in a text
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

//calculates Coleman–Liau index
float get_index(float letters, float words, float sentences)
{
    //l is the average number of letters per 100 words
    //s is the average number of sentences per 100 words
    float l = letters / words * 100;
    float s = sentences / words * 100;

    return 0.0588 * l - 0.296 * s - 15.8;

}
