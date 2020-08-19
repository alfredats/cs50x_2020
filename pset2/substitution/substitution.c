#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Requirements:
//  - key should be case-insensitive
//  - an valid key is defined as follows
//      > contains 26 characters
//      > contains ONLY alphabetic characters
//      > contains each alphabetic character only once
//  - if key is invalid, print error msg & return 1 from main
//  - program takes input "plaintext: " and outputs "ciphertext: "
//  - program must preserve case
//  - once complete, print newline and exit by returning 0 from main


bool key_valid(string key); // helper function to check key validity
void substitution_cipher(string plntxt, string key);


int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (key_valid(argv[1]) == false)
        {
            return 1;
        }
        else 
        { 
            string plaintext = get_string("plaintext: ");
            substitution_cipher(plaintext, argv[1]);
        }
        
    }
    else 
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

bool key_valid(string key)
{
    if (strlen(key) < 26) // check key length
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    int _memo[26] = {0}; // memoization of character counts using array indices as character proxies
    int _ind;

    for (int i = 0; key[i] != '\0'; i++) // parsing through characters
    {
        if (isalpha(key[i]) == 0) // check if alphabet
        {
            printf("Key must contain alphabetic characters only\n");
            return false;
        }
        
        // check if there are duplicate characters
        _ind = (int) tolower(key[i]) - 97;
        _memo[_ind] += 1;
        
        if (_memo[_ind] > 1)
        {
            printf("Duplicate letter in key: %c\n", key[i]);
            return false;
        }
    }
    // if it passes everything
    return true;
}

void substitution_cipher(string plntxt, string key)
{
    // approach:
    //  - parsing through plntxt, substitute characters accordingly (accounting for upper/lower case)
    //  - print substituted character

    printf("ciphertext: ");

    for (int i = 0; plntxt[i] != '\0'; i++)
    {
        if isalpha(plntxt[i])
        {
            int _ascii_base = 97;
            int _is_upper = 0;
    
            if (isupper(plntxt[i]))
            {
                _ascii_base = 65;
                _is_upper = 1;
            }
            
            int _key_ind = (int) plntxt[i] - _ascii_base;
            
            if (_is_upper)
            {
                printf("%c", toupper(key[_key_ind]));
            }
            else
            {
                printf("%c", tolower(key[_key_ind]));
            }
        }
        else 
        {
            printf("%c", plntxt[i]);
        }
    }

    printf("\n");
    
}

