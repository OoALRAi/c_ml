#include "matrix.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Matrix *new_mat(int rows, int cols)
{
	if (cols <= 0 || rows <= 0)
	{
		fprintf(stderr,
				"cannot allocate a matrix of size (%ix%i), smallest matrix to be "
				"allocated (1x1)!",
				cols, rows);
		return NULL;
	}
	Matrix *m = malloc(sizeof(Matrix));
	m->cols = cols;
	m->rows = rows;
	m->data = malloc(sizeof(double *) * rows);
	for (size_t row = 0; row <= rows; row++)
	{
		m->data[row] = malloc(sizeof(double) * cols);
	}
	return m;
}
Matrix *ones(int rows, int cols)
{
	Matrix *result = new_mat(rows, cols);
	fill_matrix_with_constant(result, 1);
	return result;
}

void free_mat(Matrix *m)
{
	if (m == NULL)
	{
		return;
	}
	free(m->data);
	free(m);
}

void fill_matrix_starting_with(Matrix *m, double value)
{
	for (int y = 0; y < m->rows; y++)
	{
		for (int x = 0; x < m->cols; x++)
		{
			m->data[y][x] = value++;
		}
	}
}

void fill_matrix_with_constant(Matrix *m, double value)
{
	for (int y = 0; y < m->rows; y++)
	{
		for (int x = 0; x < m->cols; x++)
		{
			m->data[y][x] = value;
		}
	}
}
/*
void set_mat_data(Matrix *m, double **values) {
  for (size_t y = 0; y < m->rows; y++) {
																																for (size_t x =
0; x < m->cols; x++) { m->data = values;
																																}
  }
}

 * */
void set_mat_value(Matrix *m, double value, int x, int y)
{
	if (x < 0 || y < 0 || x > +m->cols || y > +m->rows)
	{
		fprintf(stderr, "coordinates outside the matrix boundaries!\n");
		fprintf(stderr, "matrix size = (%ix%i), position: y=%i, x=%i\n", m->rows,
				m->cols, y, x);
		exit(-1);
	}
	m->data[y][x] = value;
}

void print_matrix(Matrix *m)
{
	if (m == NULL)
	{
		printf("null\n");
		return;
	}
	printf("(%i, %i) matrix:\n", m->rows, m->cols);
	for (int y = 0; y < m->rows; y++)
	{
		for (int x = 0; x < m->cols; x++)
		{
			printf("%f ", m->data[y][x]);
		}
		printf("\n");
	}
}

Matrix *transpose(Matrix *m)
{
	Matrix *new_matrix = new_mat(m->cols, m->rows);
	for (size_t y = 0; y < m->rows; y++)
	{
		for (size_t x = 0; x < m->cols; x++)
		{
			new_matrix->data[x][y] = m->data[y][x];
		}
	}

	return new_matrix;
}

Matrix *add_mats(Matrix *m1, Matrix *m2)
{
	if (!mat_size_equals(m1, m2))
	{
		return NULL;
	}
	Matrix *result = new_mat(m1->rows, m1->cols);
	for (size_t y = 0; y < m1->rows; y++)
	{
		for (size_t x = 0; x < m1->cols; x++)
		{
			result->data[y][x] = m1->data[y][x] + m2->data[y][x];
		}
	}
	return result;
}
Matrix *element_wise_mats_product(Matrix *m1, Matrix *m2)
{
	if (m1->cols != m2->cols || m1->rows != m2->rows)
	{
		fprintf(
			stderr,
			"cannot apply element wise product to (%ix%i) with (%ix%i) matrices!\n",
			m1->rows, m1->cols, m2->rows, m2->cols);
		exit(-1);
	}
	Matrix *result = new_mat(m1->rows, m1->cols);
	for (size_t y = 0; y < m1->rows; y++)
	{
		for (size_t x = 0; x < m1->cols; x++)
		{
			result->data[y][x] = m1->data[y][x] * m2->data[y][x];
		}
	}
	return result;
}

Matrix *subtract_mats(Matrix *m1, Matrix *m2)
{
	if (!mat_size_equals(m1, m2))
	{
		return NULL;
	}
	Matrix *result = new_mat(m1->rows, m1->cols);
	for (size_t y = 0; y < m1->rows; y++)
	{
		for (size_t x = 0; x < m1->cols; x++)
		{
			result->data[y][x] = m1->data[y][x] - m2->data[y][x];
		}
	}
	return result;
}

Matrix *mul_mats(Matrix *m1, Matrix *m2)
{
	// (rows_1 X cols_1) * (rows_2 X cols_2)
	// applicable for cols_1 = rows_2
	if (m1->cols != m2->rows)
	{
		fprintf(stderr, "cannot multiply (%ix%i) with (%ix%i) matrices!\n",
				m1->rows, m1->cols, m2->rows, m2->cols);
		exit(-1);
	}

	size_t rows = m1->rows;
	size_t cols = m2->cols;
	size_t inners = m1->cols;
	Matrix *result = new_mat(rows, cols);

	// for each row in m1,
	for (size_t row = 0; row < rows; row++)
	{
		for (size_t i = 0; i < inners; i++)
		{
			for (size_t col = 0; col < cols; col++)
			{
				result->data[row][col] += m1->data[row][i] * m2->data[i][col];
			}
		}
	}
	return result;
}

Matrix *element_wise_pow(Matrix *m, double e)
{
	Matrix *result = new_mat(m->rows, m->cols);
	for (size_t y = 0; y < m->rows; y++)
	{
		// for each col in m2:
		for (size_t x = 0; x < m->cols; x++)
		{
			result->data[y][x] = pow(m->data[y][x], e);
		}
	}
	return result;
}

Matrix *divide_by_value(Matrix *m, double value)
{
	Matrix *result = new_mat(m->rows, m->cols);
	for (size_t y = 0; y < m->rows; y++)
	{
		for (size_t x = 0; x < m->cols; x++)
		{
			result->data[y][x] = m->data[y][x] / value;
		}
	}
	return result;
}
Matrix *multiply_with_value(Matrix *m, double value)
{
	Matrix *result = new_mat(m->rows, m->cols);
	for (size_t y = 0; y < m->rows; y++)
	{
		for (size_t x = 0; x < m->cols; x++)
		{
			result->data[y][x] = m->data[y][x] * value;
		}
	}
	return result;
}

int mat_size_equals(Matrix *m1, Matrix *m2)
{
	if (m1 == NULL || m2 == NULL || m1->cols != m2->cols ||
		m1->rows != m2->rows)
	{
		return 0;
	}
	return 1;
}

int mat_equals(Matrix *m1, Matrix *m2)
{
	if (!mat_size_equals(m1, m2))
		return 0;
	for (size_t y = 0; y < m1->rows; y++)
	{
		for (size_t x = 0; x < m1->cols; x++)
		{
			if (m1->data[y][x] != m2->data[y][x])
			{
				printf("%lu, %lu", y, x);
				return 0;
			}
		}
	}
	return 1;
}

double find_max(Matrix *m)
{
	double max = INT_MIN;
	for (size_t y = 0; y < m->rows; y++)
	{
		for (size_t x = 0; x < m->cols; x++)
		{
			if (m->data[y][x] > max)
			{
				max = m->data[y][x];
			}
		}
	}
	return max;
}
double find_min(Matrix *m)
{

	double min = INT_MAX;
	for (size_t y = 0; y < m->rows; y++)
	{
		for (size_t x = 0; x < m->cols; x++)
		{
			if (m->data[y][x] < min)
			{
				min = m->data[y][x];
			}
		}
	}
	return min;
}
