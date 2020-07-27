#include <stdio.h>

int main(int argc, char *argv[])
{
    // Create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Francisco", "Frank",
        "Mary", "Alan", "Lisa"
    };

    // Safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // First way of using indexing
    for (i = 0; i < count; i++)
    {
        printf("\n%s has %d years alive.", names[i], ages[i]);
    }

    printf("\n\n---\n");

    // Set up the pointers at the start of the array
    int *cur_age = ages;
    char **cur_name = names;

    // Second way using pointers
    for (i = 0; i < count; i++)
    {
        printf("\n%s is %d years old.", 
            *(cur_name + i), *(cur_age + i));
    }

    printf("\n\n---\n");

    // Third way where pointers are just arrays
    for (i = 0; i < count; i++)
    {
        printf("\n%s is %d years old again.", cur_name[i], cur_age[i]);
    }

    printf("\n\n---\n");

    printf("Address of names: %p\n", names);
    printf("\nAddress of ages: %p\n", ages);

    // Fourth with pointers in a stupid complex way
    for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++)
    {
        printf("\n%s lived %d years so far.", *cur_name, *cur_age);
        printf("\ncur_name: %p || cur_age: %p\n", cur_name, cur_age);
    }

    printf("\n\n");

    return 0;
}