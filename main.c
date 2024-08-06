#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main(void)
{
    Matrix *m1 = new_mat(1, 4);
    fill_matrix_starting_with(m1, 1);

    return 0;
}
