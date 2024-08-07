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
    init_weights(l->w);
    init_weights(l->b);
    return l;
}

// random value in range [0, 1]
double rand_double()
{
    double value = ((double)rand()) / RAND_MAX;
    return value;
}

void init_weights(Matrix *m)
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
            m->data[y][x] = rand_double();
        }
    }
}

Matrix *nn_linear_forward(LinearLayer *l, Matrix *x)
{
    Matrix *x_t = transpose(x);
    Matrix *out = mul_mats(x_t, l->w);
    Matrix *out_b = add_mats(out, l->b);
    return out_b;
}
