#include "matrix.h"
#ifndef NN_H
#define NN_H

typedef struct LinearLayer
{
    Matrix *w;
    Matrix *b;
    Matrix *x;
} LinearLayer;

LinearLayer *nn_new_linear_layer(int input_size, int output_size);

Matrix *nn_linear_forward(LinearLayer *l, Matrix *x);

#endif // NN_H