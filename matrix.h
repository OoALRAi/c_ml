#ifndef MATRIX_H
#define MATRIX_H

// a matrix is represented as (rows X cols)
typedef struct Matrix {
  int cols;
  int rows;
  double **data;
} Matrix;

Matrix *new_mat(int rows, int cols);
void free_mat(Matrix *m);

void fill_matrix_starting_with(Matrix *m, double value);
void fill_matrix_with_constant(Matrix *m, double value);

// void set_mat_data(Matrix *m, double *values);
void set_mat_value(Matrix *m, double value, int x, int y);

void print_matrix(Matrix *m);

Matrix *transpose(Matrix *m);

Matrix *add_mats(Matrix *m1, Matrix *m2);
Matrix *subtract_mats(Matrix *m1, Matrix *m2);
Matrix *mul_mats(Matrix *m1, Matrix *m2);
Matrix *element_wise_pow(Matrix *m, double e);
Matrix *element_wise_mats_product(Matrix *m1, Matrix *m2);
Matrix *multiply_with_value(Matrix *m, double value);

Matrix *divide_by_value(Matrix *m, double value);

int mat_size_equals(Matrix *m1, Matrix *m2);
int mat_equals(Matrix *m1, Matrix *m2);
double find_max(Matrix *m);
double find_min(Matrix *m);

#endif // MATRIX_H
