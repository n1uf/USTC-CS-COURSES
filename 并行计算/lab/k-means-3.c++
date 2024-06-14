#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>
#include <numeric>
#include <iomanip>

#define EPOCH_NUM 100

int main(int argc, char *argv[]) {
    int rank, size;
    int N, M, K;

    std::vector<double> data, center, local_data, new_center;
    std::vector<int> belong, count, local_belong, local_count;
    std::vector<int> displs, sendcounts, displs1, sendcounts1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        std::cin >> N >> M >> K;
        data.resize(N * M);
        for (int i = 0; i < N * M; ++i) {
            std::cin >> data[i];
        }
        center.resize(K * M);
        for (int i = 0; i < K; ++i) {
            std::copy(data.begin() + i * M, data.begin() + (i + 1) * M, center.begin() + i * M);
        }
        belong.resize(N);
        count.resize(K, 0);
    }

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&K, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        center.resize(K * M);
    }
    MPI_Bcast(center.data(), K * M, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int local_N = N / size + (rank < N % size ? 1 : 0);
    local_data.resize(local_N * M);

    if (rank == 0) {
        displs.resize(size);
        sendcounts.resize(size);
        int pos = 0;
        for (int i = 0; i < size; ++i) {
            int tmp_N = N / size + (i < N % size ? 1 : 0);
            sendcounts[i] = tmp_N * M;
            displs[i] = pos;
            pos += tmp_N * M;
        }
        displs1 = displs;
        for (auto &d : displs1) d /= M;
        sendcounts1 = sendcounts;
        for (auto &s : sendcounts1) s /= M;
    }

    MPI_Scatterv(data.data(), sendcounts.data(), displs.data(), MPI_DOUBLE, local_data.data(), local_N * M, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    local_belong.resize(local_N);
    local_count.resize(K, 0);
    new_center.resize(K * M, 0.0);

    for (int epoch = 0; epoch < EPOCH_NUM; ++epoch) {
        for (int i = 0; i < local_N; ++i) {
            double min_dist = std::numeric_limits<double>::max();
            for (int j = 0; j < K; ++j) {
                double dist = 0.0;
                for (int k = 0; k < M; ++k) {
                    dist += std::pow(local_data[i * M + k] - center[j * M + k], 2);
                }
                if (dist < min_dist) {
                    min_dist = dist;
                    local_belong[i] = j;
                }
            }
        }

        MPI_Gatherv(local_belong.data(), local_N, MPI_INT, belong.data(), sendcounts1.data(), displs1.data(), MPI_INT, 0, MPI_COMM_WORLD);

        std::fill(local_count.begin(), local_count.end(), 0);
        std::fill(new_center.begin(), new_center.end(), 0.0);

        for (int i = 0; i < local_N; ++i) {
            int cluster_id = local_belong[i];
            for (int j = 0; j < M; ++j) {
                new_center[cluster_id * M + j] += local_data[i * M + j];
            }
            local_count[cluster_id]++;
        }

        MPI_Reduce(new_center.data(), center.data(), K * M, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(local_count.data(), count.data(), K, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            for (int i = 0; i < K; ++i) {
                if (count[i] > 0) {
                    for (int j = 0; j < M; ++j) {
                        center[i * M + j] /= count[i];
                    }
                }
            }
        }

        MPI_Bcast(center.data(), K * M, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        double sum_dist = 0.0;
        for (int i = 0; i < N; ++i) {
            double single_dist = 0.0;
            for (int j = 0; j < M; ++j) {
                single_dist += std::pow(data[i * M + j] - center[belong[i] * M + j], 2);
            }
            sum_dist += std::sqrt(single_dist);
        }
        std::cout << std::fixed << std::setprecision(2) << sum_dist << std::endl;
    }

    MPI_Finalize();
    return 0;
}
