#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    while (i < 25)
    {
        printf("%d ", i);
        i++;
    }

    // Need this to add a new line
    printf("\n");

    int j = 25;

    while (j >= 0)
    {
        printf("%d ", j);
        j--;
    }

    // Need this to add a final new line
    printf("\n");
    
    return 0;
}