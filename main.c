#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "nn.h"

#include <math.h>
int main(void)
{

    printf("value = %f, value^(2) = %f\n", 3.0, pow(3.0, 2));

    Matrix *x = new_mat(2, 1);
    fill_matrix_starting_with(x, 1);
    printf("input:\n");
    print_matrix(x);
    LinearLayer *l = nn_new_linear_layer(2, 2);
    printf("weights:\n");
    print_matrix(l->w);
    printf("bias:\n");
    print_matrix(l->b);
    Matrix *out = nn_linear_forward(l, x);
    printf("output:\n");
    print_matrix(out);
    ReLU *relu = nn_new_relu();
    Matrix *activated = nn_relu_forward(relu, out);
    print_matrix(activated);
    Matrix *error = mean_squared_error(activated, new_mat(1, 2));
    printf("error=\n");
    print_matrix(error);

    return 0;
}
