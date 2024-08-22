
#include "matrix.h"
#include "nn.h"
#include <stdio.h>

#define INPUT_SIZE 1
#define HIDDEN_SIZE1 10
#define HIDDEN_SIZE2 20
#define OUTPUT_SIZE 1
#define LEARNING_RATE 0.00001
#define EPOOCHS 500
#define NUM_SAMPLES 1000

int main(void)
{

	printf("<INIT MODEL>\n");
	printf("input > linear1 > relu1 > linear2 > relu2 > out\n");

	// linear layer with input size and output of 1
	LinearLayer *h1 = nn_new_linear_layer(INPUT_SIZE, HIDDEN_SIZE1);
	LinearLayer *h2 = nn_new_linear_layer(HIDDEN_SIZE1, HIDDEN_SIZE2);
	LinearLayer *o = nn_new_linear_layer(HIDDEN_SIZE2, OUTPUT_SIZE);
	ReLU *relu1 = nn_new_relu();
	ReLU *relu2 = nn_new_relu();
	MSE *mse = nn_new_mse();

	printf("<INIT SAMPLES>\n");
	Matrix *samples[NUM_SAMPLES];
	for (int i = 0; i < NUM_SAMPLES; i++)
	{
		samples[i] = new_mat(1, INPUT_SIZE);
		double random_value = (nn_normal_rand_double() * 10);
		fill_matrix_with_constant(samples[i], random_value);
	}

	printf("<TRAINING>\n");

	for (size_t e = 0; e < EPOOCHS; e++)
	{
		for (int i = 0; i < NUM_SAMPLES; i++)
		{
			printf("<EPOCH = %zu>\n", e);
			printf("<FORWARD>\n");
			Matrix *x = samples[i];
			Matrix *y = element_wise_pow(x, 2);

			Matrix *h1_out = nn_linear_forward(h1, x);
			Matrix *h1_out_activ = nn_relu_forward(relu1, h1_out);

			Matrix *h2_out = nn_linear_forward(h2, h1_out_activ);
			Matrix *h2_out_activ = nn_relu_forward(relu2, h2_out);

			Matrix *out = nn_linear_forward(o, h2_out_activ);
			Matrix *loss = nn_mse_forward(mse, out, y);
			printf("MSE=\n");
			print_matrix(loss);

			printf("<BACKPROPAGATION>\n");

			Matrix *grad;
			grad = nn_mse_grad(mse);
			grad = nn_linear_backward(o, grad, LEARNING_RATE);
			grad = nn_relu_backward(relu2, grad);
			grad = nn_linear_backward(h2, grad, LEARNING_RATE);
			grad = nn_relu_backward(relu1, grad);
			nn_linear_backward(h1, grad, LEARNING_RATE);
		}
	}
	printf("<TESTING>\n");
	int c = 0;
	int end = 100;

	while (c < end)
	{
		// double a = (c % 5) == 0 ? c : end - c;
		Matrix *x = new_mat(1, 1);
		double random_value = nn_normal_rand_double() * 10;
		fill_matrix_with_constant(x, random_value);
		Matrix *y = element_wise_pow(x, 2);
		Matrix *h1_out = nn_linear_forward(h1, x);
		Matrix *h1_out_activ = nn_relu_forward(relu1, h1_out);

		Matrix *h2_out = nn_linear_forward(h2, h1_out_activ);
		Matrix *h2_out_activ = nn_relu_forward(relu2, h2_out);

		Matrix *out = nn_linear_forward(o, h2_out_activ);
		printf("x = %f, expected = %f, actual = %f\n", x->data[0][0], y->data[0][0],
			   out->data[0][0]);
		c++;
	}
	return 0;
}
