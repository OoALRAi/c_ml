#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "nn.h"

int main(void)
{

    Matrix *x = new_mat(2, 1);
    fill_matrix_starting_with(x, 1);
    printf("input:\n");
    print_matrix(x);
    LinearLayer *l = nn_new_linear_layer(2, 4);
    printf("weights:\n");
    print_matrix(l->w);
    printf("bias:\n");
    print_matrix(l->b);
    Matrix *out = nn_linear_forward(l, x);
    printf("output:\n");
    print_matrix(out);
    out->data[0][0] = -2;
    ReLU *relu = nn_new_relu();
    Matrix *activated = nn_relu_forward(relu, out);
    print_matrix(activated);

    return 0;
}
