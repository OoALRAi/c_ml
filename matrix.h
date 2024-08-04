#ifndef MATRIX_H
#define MATRIX_H

// a matrix is represented as (rows X cols)
typedef struct Matrix
{
    int cols;
    int rows;
    double **data;
} Matrix;

Matrix *new_mat(int cols, int rows);
void free_mat(Matrix *m);

void fill_matrix_with(Matrix *m, double value);

void print_matrix(Matrix *m);

Matrix *transpose(Matrix *m);

Matrix *add_mats(Matrix *m1, Matrix *m2);
Matrix *subtract_mats(Matrix *m1, Matrix *m2);
Matrix *mul_mats(Matrix *m1, Matrix *m2);

int mat_size_equals(Matrix *m1, Matrix *m2);
int mat_equals(Matrix *m1, Matrix *m2);

#endif // MATRIX_H