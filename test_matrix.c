#include <stdio.h>
#include "matrix.h"

int main()
{
    Matrix *m2 = new_mat(2000, 500);
    Matrix *m1 = new_mat(500, 2000);
    fill_matrix_starting_with(m1, 1);
    fill_matrix_starting_with(m2, 1);
    Matrix *r = mul_mats(m1, m2);

    return 0;
}