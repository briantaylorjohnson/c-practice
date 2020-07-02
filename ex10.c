#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR: You need one argument.\n");
        return 1; // This is how you abort a program
    }

    int i = 0;

    // Looping through each char in the array of the first argument; loop ends when it reaches the end of the array (or the null byte)
    for (i = 0; argv[1][i] != '\0'; i++)
    {
        char letter = argv[1][i];

        switch (letter)
        {
            // Fallthrough A
            case 'a':
            case 'A':
                printf("%d: 'A'\n", i);
                break;
            
            // Fallthrough E
            case 'e':
            case 'E':
                printf("%d: 'E'\n", i);
                break;

            // Fallthrough I
            case 'i':
            case 'I':
                printf("%d: 'I'\n", i);
                break;
            
            // Fallthrough O
            case 'o':
            case 'O':
                printf("%d: 'O'\n", i);
                break;

            // Fallthrough U
            case 'u':
            case 'U':
                printf("%d: 'U'\n", i);
                break;
            
            // Fallthrough Y
            case 'y':
            case 'Y':
                if (i > 2)
                {
                    // It's only sometimes Y
                    printf("%d: 'Y'\n", i);
                }
                break;

            default:
                printf("%d: %c is not a vowel.\n", i, letter);
        }
    }

    return 0;
}