#include "matrix.h"
#include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_SIZE 1
#define HIDDEN_SIZE 20
#define OUTPUT_SIZE 1
#define LEARNING_RATE 0.00001
#define EPOOCHS 1000
#define NUM_SAMPLES 1000

typedef struct LossList
{
  double value;
  struct LossList *next;
} LossList;

LossList *losses = NULL;

void loss_add_value(LossList *list, double value)
{
  LossList *new_node = malloc(sizeof(LossList));
  new_node->value = value;
  new_node->next = list;
  losses = new_node;
}

void print_losses(LossList *list)
{
  while (list)
  {
    printf("loss=%f\n", list->value);
    list = list->next;
  }
}

void write_to_file(LossList *list)
{
  FILE *file = fopen("./test.txt", "w");
  while (list)
  {
    fprintf(file, "%f\n", list->value);
    list = list->next;
  }
  fclose(file);
}

int main(void)
{

  // linear layer with input size and output of 1
  LinearLayer *h = nn_new_linear_layer(INPUT_SIZE, HIDDEN_SIZE);
  LinearLayer *o = nn_new_linear_layer(HIDDEN_SIZE, OUTPUT_SIZE);
  ReLU *relu = nn_new_relu();
  MSE *mse = nn_new_mse();
  printf("hello world!\n");

  Matrix *samples[NUM_SAMPLES];
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    samples[i] = new_mat(1, INPUT_SIZE);
    double random_value = (nn_rand_double() * 10);
    fill_matrix_with_constant(samples[i], random_value);
  }

  for (size_t e = 0; e < EPOOCHS; e++)
  {
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
      Matrix *x = samples[i];
      Matrix *y = element_wise_pow(x, 2);
      // print_matrix(x);
      // print_matrix(y);

      Matrix *h_out = nn_linear_forward(h, x);
      // printf("hidden out=\n");
      // print_matrix(h_out);
      Matrix *h_out_activ = nn_relu_forward(relu, h_out);
      // printf("hidden activated=\n");
      // print_matrix(h_out_activ);
      Matrix *out = nn_linear_forward(o, h_out_activ);
      // printf("out=\n");
      // print_matrix(out);
      Matrix *loss = nn_mse_forward(mse, out, y);
      loss_add_value(losses, loss->data[0][0]);
      printf("loss:\n");
      print_matrix(loss);

      Matrix *grad;
      grad = nn_mse_grad(mse);
      grad = nn_linear_backward(o, grad, LEARNING_RATE);
      // printf("grad mse:\n");
      // print_matrix(grad);
      // return 0;
      grad = nn_relu_backward(relu, grad);
      nn_linear_backward(h, grad, LEARNING_RATE);
    }
  }
  // return 0;
  write_to_file(losses);
  int c = 0;
  int end = 100;

  while (c < end)
  {
    // double a = (c % 5) == 0 ? c : end - c;
    Matrix *x = new_mat(1, 1);
    double random_value = nn_rand_double() * 10;
    fill_matrix_with_constant(x, random_value);
    Matrix *y = element_wise_pow(x, 2);
    Matrix *h_out = nn_linear_forward(h, x);
    Matrix *h_out_activ = nn_relu_forward(relu, h_out);
    Matrix *out = nn_linear_forward(o, h_out_activ);
    printf("x = %f, expected = %f, actual = %f\n", x->data[0][0], y->data[0][0],
           out->data[0][0]);
    c++;
  }

  return 0;
}
