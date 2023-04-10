#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n, int m);
double det_2x2(double **matrix);
int input(double **matrix, int *n, int *m);
void scan_matrix(double **matrix, int n, int m, int col, double **new_matrix);
void output(double det);
void output_matrix(double **matrix, int n, int m);

int main() {
    double **matrix;
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n == 0 || m == 0 || n != m) {
        printf("n/a");
        exit(0);
    }
    matrix = malloc(n * m * sizeof(double) + n * sizeof(double *));
    double *ptr = (double *)(matrix + n);
    for (int i = 0; i < n; i++) {
        matrix[i] = ptr + m * i;
    }
    if (input(matrix, &n, &m)) {
        printf("n/a");
        free(matrix);
        exit(0);
    }
    output(det(matrix, n, m));
    free(matrix);
    return 0;
}
int input(double **matrix, int *n, int *m) {
    int flag = 0;
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) flag = 1;
        }
    }
    return flag;
}
double det(double **matrix, int n, int m) {
    // формула для j от 0 элемента до m (deter += pow*matrix[0][j]*минор для преобразованной 2х2 матрицы)
    double deter = 0;  //переменная для определителя
    double pow = 1;    //степень
    if (n == 1 && m == 1)
        return matrix[0][0];
    else if (n == 2 && m == 2)
        return det_2x2(matrix);  //выход из рекурсии
    else {
        double **new_matrix = malloc((n - 1) * sizeof(double *));  // создаем матрицу на одну строку меньше
        for (int i = 0; i < n - 1; i++) {
            new_matrix[i] = malloc((m - 1) * sizeof(double));  // и на один столбец меньше
        }
        for (int j = 0; j < m; j++) {
            scan_matrix(matrix, n, m, j, new_matrix);
            deter = deter + (pow * matrix[0][j] * det(new_matrix, n - 1, m - 1));  // рекурсия
            pow *= (-1);  //для изменения степени
        }
        for (int i = 0; i < n - 1; i++) {
            free(new_matrix[i]);
        }
        free(new_matrix);
    }
    return deter;
}
double det_2x2(double **matrix) { return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]; }
void scan_matrix(double **matrix, int n, int m, int col, double **new_matrix) {
    int row_shift = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (j == col) {
                row_shift = 1;
            }
            new_matrix[i][j] = matrix[i + 1][j + row_shift];
        }
        row_shift = 0;
    }
}
void output_matrix(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1)
                printf("%.1lf", matrix[i][j]);
            else
                printf("%.1lf ", matrix[i][j]);
        }
        printf("\n");
    }
}
void output(double det) { printf("%.6lf", det); }