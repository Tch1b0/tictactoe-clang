#include <utility.h>
#include <stdio.h>

char int_to_sign(int num)
{
    //            SPACE                X    O
    //                |                |    |
    return num == 0 ? 32 : (num == 1 ? 88 : 79);
}

// Prompt the User to enter a number
int prompt(char *question)
{
    printf("%s", question);
    int answer;
    scanf("%d", &answer);
    return answer;
}

int bounds_valid(int value, int lower_bound, int upper_bound)
{
    return (value >= lower_bound && value <= upper_bound)
               ? 1
               : 0;
}