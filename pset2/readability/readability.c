#include <cs50.h>
#include <stdio.h>
#include <math.h>

void text_counter(string txt, long num_array[]);
void coleman_liau(long num_array[]);

int main(void)
{
    string text = get_string("Text: ");

    long text_counts[3];
    text_counter(text, text_counts);

    coleman_liau(text_counts);
}


void text_counter(string txt, long num_array[])
{
    num_array[0] = 0, num_array[1] = 0, num_array[2] = 0;

    for (int i = 0; txt[i] != '\0'; i++)
    {
        if (((int) txt[i] > 96) && ((int) txt[i] < 123))
        {
            num_array[0] += 1;
        }
        else if (((int) txt[i] > 64) && ((int) txt[i] < 91))
        {
            num_array[0] += 1;
        }
        else if ((int) txt[i] == 32)
        {
            num_array[1] += 1;
        }
        else if ((int) txt[i] == 46 || (int) txt[i] == 33 || (int) txt[i] == 63)
        {
            num_array[2] += 1;
        }
        else
        {
            ;
        }
    }

    num_array[1] += 1;

    //printf("%ld letter(s)\n", num_array[0]);
    //printf("%ld word(s)\n", num_array[1]);
    //printf("%ld sentence(s)\n", num_array[2]);
}

void coleman_liau(long num_array[])
{
    // Coleman-Liau Formula
    //
    // Params:
    // float::avg_letters -> letters per 100 words
    // float::avg_sentences -> sentences per 100 words
    //
    // Prints:
    // string::readability -> Readability (grade level) as determined by Coleman-Liau Formula


    float avg_letters = (float)num_array[0] * 100 / (float)num_array[1];
    float avg_sentences = (float)num_array[2] * 100 / (float)num_array[1];
    float index_score = round((0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8);

    //printf("%f l/100w\n", avg_letters);
    //printf("%f s/100w\n", avg_sentences);
    //printf("%f score\n", index_score);

    if (index_score > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index_score < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", (int) index_score);
    }
}

