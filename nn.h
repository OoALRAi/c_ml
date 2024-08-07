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

double rand_double();
void init_weights(Matrix *m);
void normalize_weights(Matrix *m);

#endif // NN_H