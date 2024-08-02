#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix *new_mat(int cols, int rows)
{
    if (cols <= 0 || rows <= 0)
    {
        fprintf(
            stderr,
            "cannot allocate a matrix of size (%ix%i), smallest matrix to be allocated (1x1)!",
            cols, rows);
        return NULL;
    }
    Matrix *m = malloc(sizeof(Matrix));
    m->cols = cols;
    m->rows = rows;
    m->data = malloc(sizeof(double *) * rows);
    for (size_t i = 0; i < rows; i++)
    {
        m->data[i] = malloc(sizeof(double) * cols);
    }
    return m;
}

void free_mat(Matrix *m)
{
    if (m == NULL)
    {
        return;
    }
    for (size_t y = 0; y < m->rows; y++)
    {
        free(m->data[y]);
    }
    free(m->data);
    free(m);
}

void fill_matrix_with(Matrix *m, double value)
{
    for (int y = 0; y < m->rows; y++)
    {
        for (int x = 0; x < m->cols; x++)
        {
            m->data[y][x] = ++value;
        }
    }
}

void print_matrix(Matrix *m)
{
    for (int y = 0; y < m->rows; y++)
    {
        for (int x = 0; x < m->cols; x++)
        {
            printf("%2.2f ", m->data[y][x]);
        }
        printf("\n");
    }
}

Matrix *transpose(Matrix *m)
{
    int old_cols = m->cols;
    int old_rows = m->rows;
    Matrix *new_matrix = new_mat(old_rows, old_cols);
    for (size_t y = 0; y < old_rows; y++)
    {
        for (size_t x = 0; x < old_cols; x++)
        {
            new_matrix->data[x][y] = m->data[y][x];
        }
    }
    return new_matrix;
}

Matrix *add_mats(Matrix *m1, Matrix *m2)
{
    Matrix *result_mat = new_mat(m1->cols, m1->rows);
    for (size_t y = 0; y < m1->rows; y++)
    {
        for (size_t x = 0; x < m1->cols; x++)
        {
            result_mat->data[y][x] = m1->data[y][x] + m2->data[y][x];
        }
    }
    return result_mat;
}
Matrix *subtract_mats(Matrix *m1, Matrix *m2)
{
    Matrix *result_mat = new_mat(m1->cols, m1->rows);
    for (size_t y = 0; y < m1->rows; y++)
    {
        for (size_t x = 0; x < m1->cols; x++)
        {
            result_mat->data[y][x] = m1->data[y][x] - m2->data[y][x];
        }
    }
    return result_mat;
}

Matrix *mul_mats(Matrix *m1, Matrix *m2)
{
    return NULL;
}

int mat_size_equals(Matrix *m1, Matrix *m2)
{
    if (
        m1 == NULL ||
        m2 == NULL ||
        m1->cols != m2->cols ||
        m1->rows != m2->rows)
    {
        return 0;
    }
    return 1;
}

int mat_equals(Matrix *m1, Matrix *m2)
{
    if (mat_size_equals(m1, m2))
        return 0;
    Matrix *result_mat = new_mat(m1->cols, m1->rows);
    for (size_t y = 0; y < m1->rows; y++)
    {
        for (size_t x = 0; x < m1->cols; x++)
        {
            result_mat->data[y][x] = m1->data[y][x] + m2->data[y][x];
        }
    }
    return 1;
}