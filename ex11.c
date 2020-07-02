#include <stdio.h>

int main(int argc, char *argv[])
{
    int numbers[4] = { 0 }; // Sets all elements to 0 -- this is a shortcut
    char name[4] = { 'a' }; // Sets the first element to 'a' and all others to null byte ('\0')

    // First, print them out raw
    printf("Numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
    printf("Name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

    printf("Name: %s\n", name);

    // Set up the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    // Set up the name
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0'; // Must end string with a null byte so program knows when the string terminates

    // Then print them out initialized
    printf("Numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
    printf("Name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

    // Print the name like a string
    printf("Name: %s\n", name);

    // Another way to use name -- This is the preferred way to make string literals!
    char *another = "Zed";
    
    printf("Another: %s\n", another);
    printf("Name each: %c %c %c %c\n", another[0], another[1], another[2], another[3]);

    return 0;
}