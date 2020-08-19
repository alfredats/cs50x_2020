#include <math.h>
#include <cs50.h>
#include <stdio.h>


string check_type(long n);
int get_digit(long n, int pwr);
bool luhns_algorithm(long n, int nD);



int main(void) 
{
    long int ccnum = get_long("Number: ");
    
    //printf("%d", luhns_algorithm(ccnum, floor(log10(ccnum))));
    
    printf("%s", check_type(ccnum));
}



int get_digit(long n, int pwr)
{
    long int r;

    r = n / pow(10, pwr);

    return r % 10;
}


bool luhns_algorithm(long n, int nD)
{
    // assume card number is invalid first
    bool is_valid = false;
    int cum_sum = 0;
    int temp = 0;
    
    for (int i = 1; i <= nD; i += 2)
    {
        temp = 2 * get_digit(n, i);
        cum_sum += get_digit(temp, 0);
        cum_sum += get_digit(temp, 1);
    }

    for (int i = 0; i <= nD; i += 2)
    {
        cum_sum += get_digit(n, i);
    }
    
    if (cum_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}      


string check_type(long n)
{
    // Assume card is initially invalid
    string cctype = "INVALID\n";
    
    if (n == 0)
    {
        return cctype;
    }
    
    // calculate length of cc number
    int numDigits = floor(log10(n));
    
    if (luhns_algorithm(n, numDigits) == true)
    {
        int rAM, rMC, rV1, rV2;
        
        rAM = n / pow(10, 13);
        rMC = n / pow(10, 14);
        rV1 = n / pow(10, 12);
        rV2 = n / pow(10, 15);
    
        // various conditions
        if (rV1 == 4 || rV2 == 4)
        {
            cctype = "VISA\n";
        }
        else if (rMC == 51 || rMC == 52 || rMC == 53 || rMC == 54 || rMC == 55)
        {
            cctype = "MASTERCARD\n";
        }
        else if (rAM == 34 || rAM == 37)
        {
            cctype = "AMEX\n";
        }
    }
    return cctype;
}
