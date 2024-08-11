#include <stdio.h>
#include "matrix.h"

int main()
{
    Matrix *m1 = new_mat(4, 3);
    fill_matrix_starting_with(m1, 1);
    Matrix *r = multiply_with_value(m1, 10.0);
    print_matrix(r);

    return 0;
}