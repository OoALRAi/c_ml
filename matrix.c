#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix *make_matrix(int cols, int rows)
{
    Matrix *m = malloc(sizeof(Matrix));
    m->cols = cols;
    m->rows = rows;
    m->data = malloc(sizeof(double) * cols * rows);
    m->t = 0;
    return m;
}

void fill_matrix_with(Matrix *m, double value)
{
    for (int y = 0; y < m->rows; y++)
    {
        for (int x = 0; x < m->cols; x++)
        {
            m->data[y * m->cols + x] = ++value;
        }
    }
}

void print_matirx(Matrix *m)
{
    int rows = m->t == 0 ? m->rows : m->cols;
    int cols = m->t == 1 ? m->rows : m->cols;
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            printf("%2.2f ", m->data[x * cols + y]);
        }
        printf("\n");
    }
}

void transpose(Matrix *m)
{
    if (m->t == 1)
    {
        m->t = 0;
    }
    else
    {
        m->t = 1;
    }
}