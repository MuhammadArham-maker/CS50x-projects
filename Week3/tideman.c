#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool creates_cycles(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // loop to check for valid name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // storing the index of candidate
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // For [i] in preferences
    for (int i = 0; i < candidate_count; i++)
    {
        // For [j] in preferences
        for (int j = i + 1; j < candidate_count; j++)
        {
            // update the preferences
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // rows
    for (int i = 0; i < candidate_count; i++)
    {
        // columns
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    // Ties are ignored
}

// Bubble Sort
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort by descending set of victory
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength_j = preferences[pairs[j].winner][pairs[j].loser] -
                             preferences[pairs[j].loser][pairs[j].winner];
            int strength_j1 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] -
                              preferences[pairs[j + 1].loser][pairs[j + 1].winner];

            if (strength_j < strength_j1)
            {
                // Swap if current pair is weaker than the next pair
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;

        if (!creates_cycles(w, l))
        {
            locked[w][l] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // loop to all candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Asumming all to be true
        bool is_source = true;

        // loop to all candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // Checking if i is locked by anyone j i.e. every candidate with another
            if (locked[j][i])
            {
                // Correcting the source for losers
                is_source = false;
                break;
            }
        }
        if (is_source == true)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

// Returns true if locking the winner to loser would create a cycle
bool creates_cycles(int winner, int loser)
{
    // Base case
    if (winner == loser)
    {
        return true;
    }

    // loop for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks that if the current one is locked with anyone & and is that one leading to
        // starting
        if (locked[loser][i] && creates_cycles(winner, i))
        {
            return true;
        }
    }
    // Return false if no cycles is created
    return false;
}
