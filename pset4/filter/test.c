#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int test_lrint(int x, int y, int z, int a)
{ 
    int rgbSum = x + y + z + a;
    int result = round((double) rgbSum/4);
    return result; 
}

int main(void)
{
    printf("%i", test_lrint(150,250,140,230));
    return 0;
}


