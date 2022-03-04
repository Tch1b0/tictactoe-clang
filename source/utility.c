#include <utility.h>
#include <stdio.h>

char int_to_sign(int num)
{
    return num == 0 ? ' ' : (num == 1 ? 'X' : 'O');
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