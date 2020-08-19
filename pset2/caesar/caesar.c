#include <cs50.h>
#include <stdio.h>
// Honestly, i'm not a fan of using so many libraries... might find a better way to do this?
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool check_key(string key_str);
void caesars_cipher(string text, long int key);


int main(int argc, string argv[])
{
    // If either conditions fail, throw error
    if (argc == 2 && check_key(argv[1]))
    {
        long int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");   
        caesars_cipher(plaintext, key);  

        return 0;
    }
    else
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
}

bool check_key(string key_str)
{
    for (int i = 0; key_str[i] != '\0'; i++)
    {
        // Check if each character is a digit
        if (isdigit(key_str[i]) == 0)
        {
            return false;
        }
        else
        {
            ;
        }
    }
    // if every character is a digit, key is valid
    return true;
}

void caesars_cipher(string text, long int key)
{
    int p, c;
    string cipher_text[strlen(text)];
    
    printf("ciphertext: ");
    // instead of constructing an array of strings, we can just output them to cli character by character
    for (int i = 0; text[i] != '\0'; i++)
    {
        // If the character is uppercase, the ascii number for 'A' is 65
        if (isupper(text[i]))
        {
            p = (int) text[i] - 65;
            c = (p + key) % 26;
            printf("%c", (c + 65));
        }
        // If the character is lowercase, the ascii number for 'a' is 97
        else if (islower(text[i]))
        {
            p = (int) text[i] - 97;
            c = (p + key) % 26;
            printf("%c", (c + 97));
        }
        // If both conditions are not met, we don't have to do anything ;p
        else
        {
            printf("%c", text[i]);
        }
    }
    // For completeness
    printf("\n");
}
