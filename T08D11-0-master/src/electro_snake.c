#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);
int input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);
int compare(const void *first_number, const void *second_number) {
    return (*(int *)first_number - *(int *)second_number);
}

int main() {
    int **matrix, **result;
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n == 0 || m == 0) {
        printf("n/a");
        exit(0);
    }
    matrix = malloc(n * m * sizeof(int) + n * sizeof(int *));
    int *ptr = (int *)(matrix + n);
    for (int i = 0; i < n; i++) {
        matrix[i] = ptr + m * i;
    }
    if (input(matrix, &n, &m)) {
        printf("n/a");
        free(matrix);
        exit(0);
    }
    result = malloc(n * m * sizeof(int) + n * sizeof(int *));
    ptr = (int *)(result + n);
    for (int i = 0; i < n; i++) {
        result[i] = ptr + m * i;
    }
    sort_vertical(matrix, n, m, result);
    output(result, n, m);
    printf("\n");
    sort_horizontal(matrix, n, m, result);
    output(result, n, m);
    free(matrix);
    free(result);
    return 0;
}

int input(int **matrix, int *n, int *m) {
    int flag = 0;
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) flag = 1;
        }
    }
    return flag;
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int temp[n * m];
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[k] = matrix[i][j];
            k++;
        }
    }
    k = 0;
    qsort(temp, n * m, sizeof(int), compare);
    for (int j = 0; j < m; j++) {
        if (j % 2 == 0)
            for (int i = 0; i < n; i++) {
                result_matrix[i][j] = temp[k];
                k++;
            }
        else
            for (int i = n - 1; i >= 0; i--) {
                result_matrix[i][j] = temp[k];
                k++;
            }
    }
}

void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int temp[n * m];
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[k] = matrix[i][j];
            k++;
        }
    }
    k = 0;
    qsort(temp, n * m, sizeof(int), compare);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            for (int j = 0; j < m; j++) {
                result_matrix[i][j] = temp[k];
                k++;
            }
        else
            for (int j = m - 1; j >= 0; j--) {
                result_matrix[i][j] = temp[k];
                k++;
            }
    }
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1)
                printf("%d", matrix[i][j]);
            else
                printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
