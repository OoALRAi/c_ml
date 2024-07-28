#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix
{
    int t;
    int cols;
    int rows;
    double *data;
} Matrix;

Matrix *make_matrix(int cols, int rows);

void fill_matrix_with(Matrix *m, double value);

void print_matirx(Matrix *m);

void transpose(Matrix *m);

#endif // MATRIX_H