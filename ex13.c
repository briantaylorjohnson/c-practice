# include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // Go through each string in argv
    // Why am I skipping argv[0]?

    // Loops through all of the arguments entered into the command line, but skips the first argument
    for (i = 1; i < argc; i++)
    {
        printf("arg %d: %s\n", i, argv[i]);
    }

    printf("\n");

    // Let's make our own array of strings using the star syntax
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;

    // Loops through states array and prints out each state
    for (i = 0; i < num_states; i++)
    {
        printf("state %d: %s\n", i, states[i]);
    };

    return 0;
}