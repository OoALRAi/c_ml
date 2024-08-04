#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int main(void)
{
    Matrix *m1 = new_mat(3, 2);
    Matrix *m2 = new_mat(2, 3);
    fill_matrix_with(m1, 0);
    fill_matrix_with(m2, 4);
    printf("m1:\n");
    print_matrix(m1);
    printf("------------------\n");
    printf("m2:\n");
    print_matrix(m2);
    Matrix *m1xm2 = mul_mats(m1, m2);
    printf("------------------\n");
    printf("m1 x m2:\n");
    print_matrix(m1xm2);

    free_mat(m1);
    free_mat(m2);
    free_mat(m1xm2);
    return 0;
}