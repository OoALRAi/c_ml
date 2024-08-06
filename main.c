#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main(void)
{
    Matrix *m1 = new_mat(1, 2);
    fill_matrix_starting_with(m1, 1);
    print_matrix(m1);
    Matrix *w = new_mat(2, 2);
    fill_matrix_starting_with(w, 1);
    print_matrix(w);
    Matrix *b = new_mat(1, 2);
    fill_matrix_with_constant(b, 1);
    print_matrix(b);
    printf("x * w + b = \n");
    Matrix *m1_2 = mul_mats(m1, w);
    Matrix *m1_2_b = add_mats(m1_2, b);
    print_matrix(m1_2_b);

    return 0;
}
