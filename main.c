#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "nn.h"

#define INPUT_SIZE 1
#define HIDDEN_SIZE 9
#define OUTPUT_SIZE 1
#define LEARNING_RATE 0.001

#include <math.h>
int main(void)
{

    Matrix *x = new_mat(1, INPUT_SIZE);
    // fill x
    fill_matrix_starting_with(x, 4);
    Matrix *y = element_wise_pow(x, 3);
    print_matrix(y);

    // linear layer with input size and output of 1
    LinearLayer *h = nn_new_linear_layer(INPUT_SIZE, HIDDEN_SIZE);
    LinearLayer *o = nn_new_linear_layer(HIDDEN_SIZE, OUTPUT_SIZE);
    ReLU *relu = nn_new_relu();
    MSE *mse = nn_new_mse();

    for (size_t e = 0; e < 1000; e++)
    {
        Matrix *h_out = nn_linear_forward(h, x);
        Matrix *h_out_activ = nn_relu_forward(relu, h_out);
        Matrix *out = nn_linear_forward(o, h_out_activ);
        printf("out: \n");
        print_matrix(out);
        Matrix *loss = nn_mse_forward(mse, out, y);
        printf("loss: \n");
        print_matrix(loss);

        printf("-------------\n");
        Matrix *grad;
        grad = nn_mse_grad(mse);
        grad = nn_linear_backward(o, grad, LEARNING_RATE);
        grad = nn_relu_backward(relu, grad);
        nn_linear_backward(h, grad, LEARNING_RATE);
    }

    return 0;
}
