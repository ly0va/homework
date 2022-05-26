#include <bits/stdc++.h>

typedef std::vector<std::vector<int>> Matrix;

int mul_row_col(Matrix& A, Matrix& B, Matrix& C, int row, int col) {
    int result = 0;
    for (int k = 0; k < A[row].size(); k++) {
        result += A[row][k] * B[k][col];
    }
    printf("Computed matrix C at row %2d column %2d: %d\n", row, col, result);
    return C[row][col] = result;
}

Matrix mul_matrix(Matrix& A, Matrix &B) {
    int n = A.size(), m = B.size(), k = B[0].size();
    assert(A[0].size() == m);
    Matrix C(n, std::vector<int>(k));
    std::vector<std::thread> threads;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            threads.push_back(std::thread(
                mul_row_col, 
                std::ref(A),
                std::ref(B),
                std::ref(C),
                i, j
            ));
        }
    }
    for (std::thread& t: threads) {
        t.join();
    }
    return C;
}

Matrix rand_matrix(int n, int m) {
    Matrix A(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = rand() % 1000;
        }
    }
    return A;
}


int main(int argc, char **argv) {
    Matrix A = rand_matrix(30, 10);
    Matrix B = rand_matrix(10, 15);
    Matrix C = mul_matrix(A, B);

    for (int i = 0; i < C.size(); i++) {
        printf("[ ");
        for (int j = 0; j < C[i].size(); j++) {
            printf("%9d ", C[i][j]);
        }
        printf("]\n");
    }

    return 0;
}

