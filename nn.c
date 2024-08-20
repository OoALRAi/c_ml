#include "nn.h"
#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

LinearLayer *nn_new_linear_layer(int input_size, int output_size) {
  LinearLayer *l = malloc(sizeof(LinearLayer));
  l->w = new_mat(output_size, input_size);
  l->b = new_mat(1, output_size);
  l->x = NULL;
  nn_init_weights(l->w);
  nn_init_weights(l->b);
  return l;
}

ReLU *nn_new_relu() {
  ReLU *r = malloc(sizeof(ReLU));
  r->x = NULL;
  return r;
}

MSE *nn_new_mse() {
  MSE *l = malloc(sizeof(MSE));
  // l->y = NULL;
  l->y_yhat = NULL;
  return l;
}
// random value in range [0, 1]
double nn_rand_double() {
  double value = ((double)rand()) / RAND_MAX;
  return value;
}

double nn_normal_rand_double() {
  double mean = 0.0;
  double var = 1.0;
  static int has_spare = 0;
  static double spare;

  if (has_spare) {
    has_spare = 0;
    return mean + var * spare;
  }

  double u1, u2, z0, z1;

  // Generate two uniform random numbers in the interval (0, 1]
  u1 = ((double)rand() / RAND_MAX);
  u2 = ((double)rand() / RAND_MAX);

  z0 = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
  z1 = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);

  // Cache one of the generated values for the next call
  spare = z1;
  has_spare = 1;

  return mean + var * z0;
}

void nn_init_weights(Matrix *m) {
  static int SEED_INITIALIZED = 0;
  if (!SEED_INITIALIZED) {
    srand(time(NULL));
    SEED_INITIALIZED = 1;
  }
  for (size_t y = 0; y < m->rows; y++) {
    for (size_t x = 0; x < m->cols; x++) {
      m->data[y][x] = nn_normal_rand_double();
    }
  }
}

Matrix *nn_linear_forward(LinearLayer *l, Matrix *x) {
  l->x = x;
  Matrix *w_t = transpose(l->w);
  Matrix *out = mul_mats(x, w_t);
  Matrix *out_biased = add_mats(out, l->b);
  return out_biased;
}

Matrix *nn_relu_forward(ReLU *r, Matrix *m) {
  r->x = m;
  Matrix *result = new_mat(m->rows, m->cols);
  for (size_t y = 0; y < m->rows; y++) {
    for (size_t x = 0; x < m->cols; x++) {
      if (m->data[y * m->cols + x] <= 0) {
        result->data[y * m->cols + x] = 0;
      } else {
        result->data[y][x] = m->data[y][x];
      }
    }
  }
  return result;
}

Matrix *nn_linear_backward(LinearLayer *l, Matrix *next_grad, double lr) {
  Matrix *dx = mul_mats(next_grad, l->w);

  Matrix *next_grad_t = transpose(next_grad);
  Matrix *dw = mul_mats(next_grad_t, l->x);
  dw = multiply_with_value(dw, lr);
  l->w = subtract_mats(l->w, dw);

  Matrix *db = multiply_with_value(next_grad, lr);
  l->b = subtract_mats(l->b, db);

  return dx;
}

Matrix *nn_mse_forward(MSE *l, Matrix *y_hat, Matrix *y) {
  Matrix *sub_y_yhat = subtract_mats(y, y_hat);
  l->y_yhat = sub_y_yhat;

  Matrix *sub_squared = element_wise_pow(sub_y_yhat, 2);
  Matrix *mse_error_value = divide_by_value(sub_squared, 2);
  return mse_error_value;
}

Matrix *nn_relu_backward(ReLU *relu, Matrix *next_grad) {
  Matrix *drelu = new_mat(relu->x->rows, relu->x->cols);
  for (size_t y = 0; y < drelu->rows; y++) {
    for (size_t x = 0; x < drelu->cols; x++) {
      drelu->data[y][x] = relu->x->data[y][x] <= 0 ? 0 : next_grad->data[y][x];
    }
  }
  return drelu;
}

Matrix *nn_mse_grad(MSE *l) { return multiply_with_value(l->y_yhat, -1); }

void normalize_weights(Matrix *m) { (void)m; }
