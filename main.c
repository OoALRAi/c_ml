#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main(void)
{
    int matrix[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6}};

    for (int y = 0; y < 2; y++)
    {

        for (int x = 0; x < 3; x++)
        {
            printf("%i ", matrix[x][y]);
        }
        printf("\n");
    }
    return 0;
}