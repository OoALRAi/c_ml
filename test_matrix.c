#include "matrix.h"
// #include <stdio.h>

int main() {
  Matrix *m1 = new_mat(2, 3);
  fill_matrix_starting_with(m1, 1);
  Matrix *m2 = transpose(m1);
  print_matrix(m1);
  print_matrix(m2);
  Matrix *r = mul_mats(m1, m2);
  print_matrix(r);
  return 0;
}
