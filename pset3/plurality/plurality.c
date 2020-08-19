#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Linear search of name (cause no other choice lmao)
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].name == NULL) // strcmp throws segmentation fault if null is passed
        {
            ;
        }
        else if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Not sure what the best way to do this is... 
    
    // Requirements:
    // - Upper bound of votes received = MAX = 9
    // - Candidates must receive at least a single vote

    int _max = 0, _num_winners = 0; // 
    string winner[MAX];

    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].votes == 0) // A candidate that receives no votes is disqualified
        {
            ;
        }
        else if (candidates[i].votes > _max)
        {
            _num_winners = 0;
            winner[_num_winners] = candidates[i].name;
            _max = candidates[i].votes;

            _num_winners += 1;
        }
        else if (candidates[i].votes == _max)
        {
            winner[_num_winners] = candidates[i].name;
            _num_winners += 1;
        }
    }

    for (int i = 0; i < _num_winners; i++)
    {
        printf("%s\n", winner[i]);
    }

    return;
}

