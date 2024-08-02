#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main(void)
{
    Matrix *m = new_mat(2, 3);
    fill_matrix_with(m, 1);
    print_matrix(m);
    Matrix *m_t = transpose(m);
    printf("transposed: \n");
    print_matrix(m_t);

    Matrix *result = add_mats(m, m);
    printf("m1 + m1: \n");

    print_matrix(result);
    return 0;
}