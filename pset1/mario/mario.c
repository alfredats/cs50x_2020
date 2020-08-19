#include <cs50.h>
#include <stdio.h>


int get_height(void);
void print_pyramid(int n);
void print_left(int n, int i);
void print_right(int i);



int main(void) 
{
    // Get positive integer from user
    int height = get_height();

    // Print pyramid
    print_pyramid(height);
}


int get_height(void)
{
    int n;
    do
    {
        n = get_int("Positive Integer between 1 and 8: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        print_left(n,i);
        printf("  ");
        print_right(i);
        printf("\n");
    }
}

void print_left(int n, int i)
{
    for (int j = 0; j < n; j++)
    {        
        if (j >= n - i - 1)
        {
            printf("#");
        }
        else
        {
            printf(" ");
        }
    }
}

void print_right(int i)
{
    for (int j = 0; j < i + 1; j++)
    {
        printf("#");
    }
}
