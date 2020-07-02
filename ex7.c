#include <stdio.h>

int main(int argc, char*argv[])
{
    // Output header of program to delineate runs in terminal
    printf("\n<------------------------------------------->\nStart Code\n\n");

    // Sets integer value of 100
    int distance = 100;

    // Sets float value of 2.345; floats are smaller than doubles, yet larger than ints in memory
    float power = 2.345f;

    // Sets double value of 56789.4532; doubles are larger than floats and ints in memory
    double super_power = 56789.4532;

    // Sets a primitive char value
    char initial = 'A';

    // Sets a string value; notice that a string is an array of chars in C
    char first_name[] = "Zed";
    char last_name[] = "Shaw";

    printf("You are %d miles away.\n", distance);
    printf("You have %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);

    // Sets integer value of 100
    int bugs = 100;

    // Sets double value of 1.2
    double bug_rate = 1.2;
    printf("You have %d bugs at the imaginery rate of %f.\n", bugs, bug_rate);

    // Sets long integer value based upon a calculation; long is always larger than ints up to 64 bits/8 bytes (ints are up to 32 bits/4 bytes)
    long universe_of_defects = 1L * 1024L * 1024L * 1024L;
    printf("The entire universe has %ld bugs.\n", universe_of_defects);

    // Sets double value base upon a calculation; note that double type is set even though one of the multipliers is an int
    double expected_bugs = bugs * bug_rate;
    printf("You are expected to have %f bugs.\n", expected_bugs);

    // Sets double value base upon a calculation; note that double type is set even though one of the multipliers is an int
    double part_of_universe = expected_bugs / universe_of_defects;
    printf("That is only a %e portion of the universe.\n", part_of_universe);

    // This makes no sense -- just a demo of something weird.
    // Sets char value of null which outputs to zero when multiplied by another type
    char null_byte = '\0';
    int care_percentage = bugs * null_byte;
    printf("Which means you should care %d%%.\n", care_percentage);

    // Output footer of program to delineate runs in terminal
    printf("\nEnd Code\n<------------------------------------------->\n\n");

    return 0;
}