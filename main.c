#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main(void)
{
    Matrix *m = new_mat(2, 2);
    fill_matrix_with(m, 0);
    print_matrix(m);
    free_mat(m);
    print_matrix(m);

    return 0;
}