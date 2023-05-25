#include <stdio.h>

/**
 * A function that calculates the square of a given number.
 *
 * @param num The number to calculate the square of.
 * @return The square of the input number.
 */
int calculateSquare(int num);

int main(void)
{
    int number = 5;
    int result = calculateSquare(number);
    
    printf("The square of %d is: %d\n", number, result);
    
    return 0;
}

int calculateSquare(int num)
{
    return num * num;
}

