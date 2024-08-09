#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "nn.h"

#define INPUT_SIZE 3
#define HIDDEN_SIZE 3
#define OUTPUT_SIZE 2
#define LEARNING_RATE 0.001

#include <math.h>
int main(void)
{

    Matrix *x = new_mat(1, INPUT_SIZE);
    // fill x
    fill_matrix_starting_with(x, 1);

    // linear layer with input size and output of 1
    LinearLayer *h = nn_new_linear_layer(INPUT_SIZE, HIDDEN_SIZE);
    LinearLayer *o = nn_new_linear_layer(HIDDEN_SIZE, OUTPUT_SIZE);
    ReLU *relu = nn_new_relu();
    MSE *mse = nn_new_mse();

    Matrix *h_out = nn_linear_forward(h, x);
    Matrix *h_out_activ = nn_relu_forward(relu, h_out);
    Matrix *out = nn_linear_forward(o, h_out);
    Matrix *loss = nn_mse_forward(mse, out, new_mat(1, 2));
    printf("loss: \n");
    print_matrix(loss);

    Matrix *grad;
    grad = nn_mse_grad(mse);

    grad = nn_linear_backward(o, grad, LEARNING_RATE);
    grad = nn_relu_backward(relu, grad);
    nn_linear_backward(h, grad, LEARNING_RATE);

    return 0;
}
