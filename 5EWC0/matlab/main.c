#include <stdio.h>
#include <stdlib.h>

#define MAXROWS 10

// grade 6.19/10.00

typedef struct {
    int rows, columns;
    float *elements[MAXROWS];
} matrix_t;

matrix_t newMatrix(int rows, int columns, char zeroOrRead) {
    matrix_t m = { -1, -1, { NULL, } };
    if (rows < 1 || rows > MAXROWS || columns < 1) {
        printf("Rows must be 1 to 10, and columns must be at least 1\n");
        return m;
    }

    m.rows = rows;
    m.columns = columns;

    for (int i = 0; i < rows; ++i) {
        m.elements[i] = (float *)malloc(columns * sizeof(float));
        if (zeroOrRead == '0') {
            for (int j = 0; j < columns; ++j) {
                m.elements[i][j] = 0.0;
            }
        } else if (zeroOrRead == 'A') {
            printf("Row %d: ", i);
            for (int j = 0; j < columns; ++j) {
                scanf("%f", &m.elements[i][j]);
            }
        }
    }

    return m;
}

void printMatrix(matrix_t m, char name) {
    if (m.rows == -1 || m.columns == -1) {
        printf("Matrix %c is empty\n", name);
        return;
    }
    printf("Matrix %c (%d X %d):\n", name, m.rows, m.columns);
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.columns; ++j) {
            printf("%8.2f", m.elements[i][j]);
        }
        printf("\n");
    }
}

void freeMatrixElements(matrix_t *m) {
    for (int i = 0; i < m->rows; ++i) {
        free(m->elements[i]);
    }
    m->rows = -1;
    m->columns = -1;
} 

void copyMatrix(matrix_t *src, matrix_t *dest) {
    freeMatrixElements(dest);
    *dest = newMatrix(src->rows, src->columns, '0');
    for (int i = 0; i < src->rows; ++i) {
        for (int j = 0; j < src->columns; ++j) {
            dest->elements[i][j] = src->elements[i][j];
        }
    }
} 

void addMatrices(matrix_t ma, matrix_t mb) {
    for (int i = 0; i < ma.rows; ++i) {
        for (int j = 0; j < ma.columns; ++j) {
            mb.elements[i][j] += ma.elements[i][j];
        }
    }
} 


void multiplyMatrices(matrix_t ma, matrix_t mb, matrix_t *mc) {
    for (int i = 0; i < ma.rows; ++i) {
        for (int j = 0; j < mb.columns; ++j) {
            mc->elements[i][j] = 0;
            for (int k = 0; k < ma.columns; ++k) {
                mc->elements[i][j] += ma.elements[i][k] * mb.elements[k][j];
            }
        }
    }
} 

void transposeMatrix(matrix_t *m) {
    int originalRows = m->rows;
    int originalColumns = m->columns;
    // Allocate new memory for transposed matrix
    float *transposed[MAXROWS];
    for (int i = 0; i < originalColumns; ++i) {
        transposed[i] = (float *)malloc(originalRows * sizeof(float));
    }
    // Transpose the matrix
    for (int i = 0; i < originalRows; ++i) {
        for (int j = 0; j < originalColumns; ++j) {
            transposed[j][i] = m->elements[i][j];
        }
    }
    // Free the original memory
    freeMatrixElements(m);
    // Update matrix dimensions and elements
    m->rows = originalColumns;
    m->columns = originalRows;
    for (int i = 0; i < originalColumns; ++i) {
        m->elements[i] = transposed[i];
    }
}

int main(void) {
    char cmd;
    matrix_t ma = { -1, -1, { NULL, } };
    matrix_t mb = { -1, -1, { NULL, } };
    matrix_t mc = { -1, -1, { NULL, } };

    do {
        printf("Command? ");
        scanf(" %c", &cmd);

        switch(cmd) {
            case 'q':
                printf("Bye!\n");
                freeMatrixElements(&ma);
                freeMatrixElements(&mb);
                freeMatrixElements(&mc);
                break;

            case 'a':
                printMatrix(ma, 'A');
                break;

            case 'b':
                printMatrix(mb, 'B');
                break;

            case 'c':
                printMatrix(mc, 'C');
                break;

            case '0':
                printf("Size of matrix A (rows columns)? ");
                int rows, columns;
                scanf("%d %d", &rows, &columns);
                freeMatrixElements(&ma);
                ma = newMatrix(rows, columns, '0');
                break;

            case 'A':
                printf("Size of matrix A (rows columns)? ");
                int rows_A, columns_A;
                scanf("%d %d", &rows_A, &columns_A);
                freeMatrixElements(&ma);
                ma = newMatrix(rows_A, columns_A, 'A');
                break;
                
            case 'B': 
                copyMatrix(&ma, &mb); 
                break; 
                
            case '+':
                if (ma.rows == -1 || mb.rows == -1) {
                    printf("Matrices cannot be empty\n");
                } else if (ma.rows != mb.rows || ma.columns != mb.columns) {
                    printf("Matrix dimensions don't agree\n");
                } else {
                    addMatrices(ma, mb);
                }
                break;
                
            case '*':
                if (ma.rows == -1 || mb.rows == -1) {
                    printf("Matrices cannot be empty\n");
                } else if (ma.columns != mb.rows) {
                    printf("Matrix dimensions don't agree\n");
                } else {
                    mc = newMatrix(ma.rows, mb.columns, '0');
                    multiplyMatrices(ma, mb, &mc);
                }
                break; 
                
            case 't':
                if (ma.rows == -1) {
                    printf("Matrix cannot be empty\n");
                } else {
                    transposeMatrix(&ma);
                }
                break;

            default:
                printf("Unknown command '%c'\n", cmd);
                break;
        }
    } while (cmd != 'q');

    return 0;
}
