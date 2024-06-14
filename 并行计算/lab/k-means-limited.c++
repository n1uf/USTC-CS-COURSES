#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>
#include <numeric>
#include <iomanip>
#include <limits>

#define EPOCHS 100

int main(int argc, char *argv[]) {
    int rank, size;
    int numData, dim, numCenters;

    std::vector<double> data, centers, localData, newCenters;
    std::vector<int> assignments, counts, localAssign, localCounts;
    std::vector<int> displs, sendCnts, displsInt, sendCntsInt;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 设定参与计算的进程数
    int active_procs = std::min(size, 4); // 设定最多4个进程参与计算

    if (rank == 0) {
        std::cin >> numData >> dim >> numCenters;
        data.resize(numData * dim);
        for (int i = 0; i < numData * dim; ++i) {
            std::cin >> data[i];
        }
        centers.resize(numCenters * dim);
        for (int i = 0; i < numCenters; ++i) {
            std::copy(data.begin() + i * dim, data.begin() + (i + 1) * dim, centers.begin() + i * dim);
        }
        assignments.resize(numData);
        counts.resize(numCenters, 0);
    }

    MPI_Bcast(&numData, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&dim, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numCenters, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0 && rank < active_procs) {
        centers.resize(numCenters * dim);
    }
    MPI_Bcast(centers.data(), numCenters * dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int localNumData = numData / active_procs + (rank < numData % active_procs ? 1 : 0);
    localData.resize(localNumData * dim);

    if (rank == 0) {
        displs.resize(active_procs);
        sendCnts.resize(active_procs);
        int pos = 0;
        for (int i = 0; i < active_procs; ++i) {
            int tmpNumData = numData / active_procs + (i < numData % active_procs ? 1 : 0);
            sendCnts[i] = tmpNumData * dim;
            displs[i] = pos;
            pos += tmpNumData * dim;
        }
        displsInt = displs;
        sendCntsInt = sendCnts;
        for (auto &d : displsInt) d /= dim;
        for (auto &s : sendCntsInt) s /= dim;
    }

    if (rank < active_procs) {
        MPI_Scatterv(data.data(), sendCnts.data(), displs.data(), MPI_DOUBLE, localData.data(), localNumData * dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        localAssign.resize(localNumData);
        localCounts.resize(numCenters, 0);
        newCenters.resize(numCenters * dim, 0.0);

        for (int epoch = 0; epoch < EPOCHS; ++epoch) {
            for (int i = 0; i < localNumData; ++i) {
                double minDist = std::numeric_limits<double>::max();
                int centerId = -1;
                for (int j = 0; j < numCenters; ++j) {
                    double dist = 0.0;
                    for (int k = 0; k < dim; ++k) {
                        dist += std::pow(localData[i * dim + k] - centers[j * dim + k], 2);
                    }
                    if (dist < minDist) {
                        minDist = dist;
                        centerId = j;
                    }
                }
                localAssign[i] = centerId;
            }

            MPI_Gatherv(localAssign.data(), localNumData, MPI_INT, assignments.data(), sendCntsInt.data(), displsInt.data(), MPI_INT, 0, MPI_COMM_WORLD);

            std::fill(localCounts.begin(), localCounts.end(), 0);
            std::fill(newCenters.begin(), newCenters.end(), 0.0);

            for (int i = 0; i < localNumData; ++i) {
                int centerId = localAssign[i];
                for (int j = 0; j < dim; ++j) {
                    newCenters[centerId * dim + j] += localData[i * dim + j];
                }
                localCounts[centerId]++;
            }

            MPI_Reduce(newCenters.data(), centers.data(), numCenters * dim, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(localCounts.data(), counts.data(), numCenters, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

            if (rank == 0) {
                for (int i = 0; i < numCenters; ++i) {
                    if (counts[i] > 0) {
                        for (int j = 0; j < dim; ++j) {
                            centers[i * dim + j] /= counts[i];
                        }
                    }
                }
            }

            MPI_Bcast(centers.data(), numCenters * dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        double totalDist = 0.0;
        for (int i = 0; i < numData; ++i) {
            double pointDist = 0.0;
            for (int j = 0; j < dim; ++j) {
                pointDist += std::pow(data[i * dim + j] - centers[assignments[i] * dim + j], 2);
            }
            totalDist += std::sqrt(pointDist);
        }
        std::cout << std::fixed << std::setprecision(2) << totalDist << std::endl;
    }

    MPI_Finalize();
    return 0;
}
