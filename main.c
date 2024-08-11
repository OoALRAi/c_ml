#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix.h"
#include "nn.h"

#define INPUT_SIZE 1
#define HIDDEN_SIZE 50
#define OUTPUT_SIZE 1
#define LEARNING_RATE 0.00001
#define EPOOCHS 1000
#define NUM_SAMPLES 1000

#include <math.h>

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

    Matrix *samples[NUM_SAMPLES];
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        samples[i] = new_mat(1, INPUT_SIZE);
        double random_value = (nn_normal_rand_double() * 10);
        fill_matrix_with_constant(samples[i], random_value);
    }

    for (size_t e = 0; e < EPOOCHS; e++)
    {
        for (int i = 0; i < NUM_SAMPLES; i++)
        {
            Matrix *x = samples[i];
            Matrix *y = element_wise_pow(x, 2);

            Matrix *h_out = nn_linear_forward(h, x);
            Matrix *h_out_activ = nn_relu_forward(relu, h_out);
            Matrix *out = nn_linear_forward(o, h_out_activ);
            Matrix *loss = nn_mse_forward(mse, out, y);
            loss_add_value(losses, loss->data[0]);

            Matrix *grad;
            grad = nn_mse_grad(mse);
            grad = nn_linear_backward(o, grad, LEARNING_RATE);
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
        fill_matrix_with_constant(x, c);
        Matrix *h_out = nn_linear_forward(h, x);
        Matrix *h_out_activ = nn_relu_forward(relu, h_out);
        Matrix *out = nn_linear_forward(o, h_out_activ);
        printf("x = %f, expected = %f, actual = %f\n", x->data[0], x->data[0] * x->data[0], out->data[0]);
        c++;
    }

    return 0;
}
