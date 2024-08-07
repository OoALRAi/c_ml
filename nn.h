#include "matrix.h"
#ifndef NN_H
#define NN_H

typedef struct LinearLayer
{
    Matrix *w;
    Matrix *b;
    Matrix *x;
} LinearLayer;

typedef struct ReLU
{
    Matrix *x;
} ReLU;

LinearLayer *nn_new_linear_layer(int input_size, int output_size);
ReLU *nn_new_relu();

Matrix *nn_linear_forward(LinearLayer *l, Matrix *x);
Matrix *nn_relu_forward(ReLU *r, Matrix *x);

Matrix *nn_linear_backward(LinearLayer *l, Matrix *next_grad);

double nn_rand_double();
void nn_init_weights(Matrix *m);
void nn_normalize_weights(Matrix *m);

Matrix *mean_squared_error(Matrix *y_hat, Matrix *y);

#endif // NN_H