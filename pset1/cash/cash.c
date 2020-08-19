#include <math.h>
#include <cs50.h>
#include <stdio.h>

// Steps:
// get user input
// count number of coins required
//  - quarters .25
//  - dimes .1
//  - nickels .05
//  - pennies .01


void min_coins(int owed);
int get_owed(void);

int main(void)
{
    min_coins(get_owed());
}

int get_owed(void)
{
    float change;

    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    return round(change * 100);
}


void min_coins(int owed)
{
    int num_coins = 0;
    int coin_types[] = {25, 10, 5, 1};
   
    for (int i = 0; i < 4; i++)
    {
        num_coins += owed / coin_types[i];
        owed = owed % coin_types[i];
    }

    printf("%d\n", num_coins);
}
