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

typedef struct Sigmoid
{
    Matrix *x;
    Matrix *out;
} Sigmoid;

typedef struct MSE
{
    Matrix *y_yhat;
} MSE;

LinearLayer *nn_new_linear_layer(int input_size, int output_size);
ReLU *nn_new_relu();
MSE *nn_new_mse();
Sigmoid *nn_new_sigmoid();

Matrix *nn_linear_forward(LinearLayer *l, Matrix *x);
Matrix *nn_relu_forward(ReLU *r, Matrix *x);
Matrix *nn_sigmoid_forward(Sigmoid *s, Matrix *m);

Matrix *nn_linear_backward(LinearLayer *l, Matrix *next_grad, double lr);
Matrix *nn_relu_backward(ReLU *relu, Matrix *next_grad);
Matrix *nn_sigmoid_backward(Sigmoid *s, Matrix *next_grad);

Matrix *nn_mse_grad(MSE *l);

double nn_rand_double();
void nn_init_weights(Matrix *m);
void nn_normalize_weights(Matrix *m);

Matrix *nn_mse_forward(MSE *l, Matrix *y_hat, Matrix *y);
double nn_normal_rand_double();

#endif // NN_H
