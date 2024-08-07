#include "nn.h"
#include <stdlib.h>
#include <time.h>

static int SEED_INITIALIZED = 0;

LinearLayer *nn_new_linear_layer(int input_size, int output_size)
{
    LinearLayer *l = malloc(sizeof(LinearLayer));
    l->w = new_mat(input_size, output_size);
    l->b = new_mat(1, output_size);
    l->x = NULL;
    nn_init_weights(l->w);
    nn_init_weights(l->b);
    return l;
}

ReLU *nn_new_relu()
{
    ReLU *r = malloc(sizeof(ReLU));
    r->x = NULL;
    return r;
}

// random value in range [0, 1]
double nn_rand_double()
{
    double value = ((double)rand()) / RAND_MAX;
    return value;
}

void nn_init_weights(Matrix *m)
{
    if (!SEED_INITIALIZED)
    {
        srand(time(NULL));
        SEED_INITIALIZED = 1;
    }
    for (size_t y = 0; y < m->rows; y++)
    {
        for (size_t x = 0; x < m->cols; x++)
        {
            m->data[y][x] = nn_rand_double();
        }
    }
}

Matrix *nn_linear_forward(LinearLayer *l, Matrix *x)
{
    l->x = x;
    Matrix *x_t = transpose(x);
    Matrix *out = mul_mats(x_t, l->w);
    Matrix *out_b = add_mats(out, l->b);
    return out_b;
}

Matrix *nn_relu_forward(ReLU *r, Matrix *m)
{
    r->x = m;
    Matrix *result = new_mat(m->rows, m->cols);
    for (size_t y = 0; y < m->rows; y++)
    {
        for (size_t x = 0; x < m->cols; x++)
        {
            if (m->data[y][x] <= 0)
            {
                result->data[y][x] = 0;
            }
            else
            {
                result->data[y][x] = m->data[y][x];
            }
        }
    }
    return result;
}

Matrix *nn_linear_backward(LinearLayer *l, Matrix *next_grad)
{
    return NULL;
}

Matrix *mean_squared_error(Matrix *y_hat, Matrix *y)
{
    Matrix *result = subtract_mats(y, y_hat);
    result = element_wise_pow(result, 2);
    divide_by_value(result, y->rows);

    return result;
}

void normalize_weights(Matrix *m)
{
    (void)m;
}
