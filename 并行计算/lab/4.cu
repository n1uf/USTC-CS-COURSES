#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cuda_runtime.h>

using namespace std;

// 函数原型：用于按列索引排序稀疏矩阵
void sortSparseMatrix(vector<int>& sparse_rows, vector<int>& sparse_cols, vector<int>& sparse_vals, vector<int>& idx);

__global__ void sparseDenseMatMult(int M, int N, int P, int K,
                                   int *dense, int *sparse_rows, int *sparse_col_ptr, int *sparse_col_idx, int *sparse_vals,
                                   int *result) {
    int row = blockIdx.y * blockDim.y + threadIdx.y; // 计算当前线程处理的行索引
    int col = blockIdx.x * blockDim.x + threadIdx.x; // 计算当前线程处理的列索引

    if (row < M && col < P) {
        int value = 0;
        int start = sparse_col_ptr[col];    // 当前列的起始索引
        int end = sparse_col_ptr[col + 1];  // 当前列的结束索引

        for (int k = start; k < end; ++k) {
            if (sparse_col_idx[k] == col) { // 检查当前非零元素是否在当前列
                int idx = sparse_rows[k];   // 获取稀疏矩阵行索引
                value += dense[row * N + idx] * sparse_vals[k]; // 计算乘积并累加到结果值
            }
        }
        result[row * P + col] = value; // 将结果存入结果矩阵中
    }
}

int main() {
    int M, N, P, K;
    cin >> M >> N >> P >> K; // 输入稠密矩阵的维度和稀疏矩阵的非零元素个数

    // 输入稠密矩阵
    vector<int> dense_matrix(M * N);
    for (int i = 0; i < M * N; ++i) {
        cin >> dense_matrix[i];
    }

    // 输入稀疏矩阵的非零元素
    vector<int> sparse_rows(K), sparse_cols(K);
    vector<int> sparse_vals(K);
    for (int i = 0; i < K; ++i) {
        cin >> sparse_rows[i] >> sparse_cols[i] >> sparse_vals[i];
    }

    // 调用排序函数对稀疏矩阵进行排序
    vector<int> idx(K);
    sortSparseMatrix(sparse_rows, sparse_cols, sparse_vals, idx);

    // 创建稀疏矩阵的压缩稀疏列（CSC）格式所需的 sparse_col_ptr 和 sparse_col_idx 数组
    vector<int> sparse_col_ptr(P + 1, 0);
    vector<int> sparse_col_idx(K);

    for (int k = 0; k < K; ++k) {
        sparse_col_ptr[sparse_cols[k] + 1]++;
        sparse_col_idx[k] = sparse_cols[k];
    }

    // 计算 sparse_col_ptr 数组中的偏移量
    for (int j = 1; j <= P; ++j) {
        sparse_col_ptr[j] += sparse_col_ptr[j - 1];
    }

    // 在设备上分配内存
    int *d_dense, *d_sparse_vals, *d_result;
    int *d_sparse_rows, *d_sparse_col_ptr, *d_sparse_col_idx;

    cudaMalloc(&d_dense, M * N * sizeof(int));
    cudaMalloc(&d_sparse_rows, K * sizeof(int));
    cudaMalloc(&d_sparse_col_ptr, (P + 1) * sizeof(int));
    cudaMalloc(&d_sparse_col_idx, K * sizeof(int));
    cudaMalloc(&d_sparse_vals, K * sizeof(int));
    cudaMalloc(&d_result, M * P * sizeof(int));

    // 将数据从主机内存复制到设备内存
    cudaMemcpy(d_dense, dense_matrix.data(), M * N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_sparse_rows, sparse_rows.data(), K * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_sparse_col_ptr, sparse_col_ptr.data(), (P + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_sparse_col_idx, sparse_col_idx.data(), K * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_sparse_vals, sparse_vals.data(), K * sizeof(int), cudaMemcpyHostToDevice);

    // 定义 CUDA kernel 的线程块和网格
    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((P + 15) / 16, (M + 15) / 16);

    // 调用 CUDA kernel
    sparseDenseMatMult<<<numBlocks, threadsPerBlock>>>(M, N, P, K, d_dense, d_sparse_rows, d_sparse_col_ptr, d_sparse_col_idx, d_sparse_vals, d_result);

    // 将结果从设备内存复制回主机内存
    vector<int> result_matrix(M * P);
    cudaMemcpy(result_matrix.data(), d_result, M * P * sizeof(int), cudaMemcpyDeviceToHost);

    // 输出结果矩阵
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < P; ++j) {
            cout << result_matrix[i * P + j] << " ";
        }
        cout << endl;
    }

    // 释放设备内存
    cudaFree(d_dense);
    cudaFree(d_sparse_rows);
    cudaFree(d_sparse_col_ptr);
    cudaFree(d_sparse_col_idx);
    cudaFree(d_sparse_vals);
    cudaFree(d_result);

    return 0;
}

// 定义排序稀疏矩阵的函数
void sortSparseMatrix(vector<int>& sparse_rows, vector<int>& sparse_cols, vector<int>& sparse_vals, vector<int>& idx) {
    iota(idx.begin(), idx.end(), 0); // 初始化索引数组
    sort(idx.begin(), idx.end(), [&sparse_cols](int i1, int i2) { return sparse_cols[i1] < sparse_cols[i2]; });

    vector<int> sorted_sparse_cols(sparse_cols.size());
    vector<int> sorted_sparse_rows(sparse_rows.size());
    vector<int> sorted_sparse_vals(sparse_vals.size());

    for (size_t i = 0; i < idx.size(); ++i) {
        sorted_sparse_cols[i] = sparse_cols[idx[i]];
        sorted_sparse_rows[i] = sparse_rows[idx[i]];
        sorted_sparse_vals[i] = sparse_vals[idx[i]];
    }

    sparse_cols = sorted_sparse_cols;
    sparse_rows = sorted_sparse_rows;
    sparse_vals = sorted_sparse_vals;
}
