#include <stdio.h>

int main(int argc, char *argv[])
{
    // ** An array is a fixed block of memory **

    // Creates an array of ints
    int areas[] = { 10, 12, 13 ,14 ,20 };

    // Creates an array of chars in condensed syntax
    char name[] = "Zed";

    // Creates an array of chars by specifying each char (note the null pointer to end the array)
    char full_name[] = {
        'Z', 'e', 'd',
        ' ', 'A', '.',
        ' ', 'S', 'h',
        'a', 'w', '\0'
    };

    // WARNING: On some systems you may have to change the
    // %ld in this code a %u since it will be unsigned ints

    printf("\n");

    // Size of int on the machine running the code
    printf("The size of an int: %ld.\n", sizeof(int));
    
    // Size of the block of memory for the areas array
    printf("The size of areas (int[]): %ld.\n", sizeof(areas));

    // Calculates the number of elements in the areas array
    printf("The number of ints in areas: %ld.\n", sizeof(areas) / sizeof(int));

    // Prints the elements in the first and second indices for the areas array
    printf("The first area is %d, the second is %d.\n", areas[0], areas[1]);

    printf("\n");

    // Size of char on the machine running the code
    printf("The size of a char: %ld.\n", sizeof(char));
    
    // Size of the block of memory for the name array
    printf("The size of name (char[]): %ld.\n", sizeof(name));

    // Calculates the number of elements in the name array
    printf("The number of chars in name: %ld.\n", sizeof(name) / sizeof(char));
    
    printf("\n");

    // Size of the block of memory for the full_name array
    printf("The size of full_name (char[]): %ld.\n", sizeof(full_name));

    // Calculates the number of elements in the full_name array
    printf("The number of chars: %ld.\n", sizeof(full_name) / sizeof(char));
    
    // Prints the name and full_name arrays as strings
    printf("\nname=\"%s\" and full_name=\"%s\"\n\n", name, full_name);

    return 0;
}