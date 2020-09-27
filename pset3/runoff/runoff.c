#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }

    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Linear search
    for (int n = 0; n < candidate_count; n++)
    {
        if (strcmp(name, candidates[n].name) == 0)
        {
            preferences[voter][rank] = n;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Going through the voters,
    // going through the voter's ranking,
    // if the currently ranked candidate is not eliminated,
    //  add to the candidate's vote count 
    // otherwise,
    //  go to the next

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int curr_vote = preferences[i][j];

            if (!candidates[curr_vote].eliminated)
            {
                candidates[curr_vote].votes += 1;
                //printf("Voter %d votes for %s\n", i, candidates[curr_vote].name);
                break ;
            }
            else
            {
                // printf("%s eliminated\n", candidates[curr_vote].name);
            }
        }
    }
    
    //printf("\n");
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Election is won when a majority is achieved
    int majority_count = (int) ceil(voter_count / 2.0);
    //printf("majority needed: %d\n", majority_count); 

    for (int n = 0; n < candidate_count; n++)
    {
        if (candidates[n].votes > majority_count) 
        {
            printf("%s\n", candidates[n].name);
            // printf("%d\n", candidates[n].votes); 
            return true;
        }
        
        // printf("%s does not have majority\n", candidates[n].name);
    }
    //printf("\n");
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // initialize local min
    int curr_min = voter_count;
    
    for (int n = 0; n < candidate_count; n++)
    {
        if (!candidates[n].eliminated && candidates[n].votes <= curr_min)
        {
            curr_min = candidates[n].votes;
        }
    }

    return curr_min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //
    bool tieBool = true;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            tieBool = tieBool && (candidates[i].votes == min);
        }
    }
    
    //printf("Tie? %s\n", tieBool ? "true" : "false");

    return tieBool;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int n = 0; n < candidate_count; n++)
    {
        if (candidates[n].votes == min)
        {
            candidates[n].eliminated = true;
            //printf("%s eliminated\n", candidates[n].name);
        }
    }
    return;
}
