#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void lu_decomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, int n) {
    #pragma omp parallel
    {
        // LU分解过程
        for (int k = 0; k < n; k++) {
            // 除法步骤
            #pragma omp for
            for (int i = k + 1; i < n; i++) {
                A[i][k] /= A[k][k];
            }
            
            // 消去步骤
            #pragma omp for collapse(2)
            for (int i = k + 1; i < n; i++) {
                for (int j = k + 1; j < n; j++) {
                    A[i][j] -= A[i][k] * A[k][j];
                }
            }
        }
        
        // 提取L和U矩阵
        #pragma omp for collapse(2)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i > j) {
                    L[i][j] = A[i][j];
                    U[i][j] = 0.0;
                } else if (i == j) {
                    L[i][j] = 1.0;
                    U[i][j] = A[i][j];
                } else {
                    L[i][j] = 0.0;
                    U[i][j] = A[i][j];
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));
    
    // 设置线程数
    int num_threads = 4; // 线程数量
    omp_set_num_threads(num_threads);

    // 输入矩阵A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    
    lu_decomposition(A, L, U, n);
    
    // 输出矩阵L
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }
    
    // 输出矩阵U
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
