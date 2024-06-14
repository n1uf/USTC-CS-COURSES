#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265358979323846

double buffon_laplace(double l, double a, double b) {
    return (2 * l * (a + b) - l * l) / (PI * a * b);
}

int main() {
    srand(time(NULL)); // 初始化随机数种子

    int needle_count = 1000000; // 针的数量
    double l = 1.0; // 针的长度
    double a = 2.0; // 网格的宽度
    double b = 2.0; // 网格的间距

    int crosses = 0; // 落在线上的次数

    clock_t start_time = clock();
    // 模拟投针
    for (int i = 0; i < needle_count; i++) {
        double x = (double)rand() / RAND_MAX * a; // 随机生成针的x坐标
        double angle = (double)rand() / RAND_MAX * PI; // 随机生成针的角度
        double y = (double)rand() / RAND_MAX * b / 2; // 随机生成针的y坐标

        if (x <= l * cos(angle)) // 如果针与线相交
            crosses++;
    }

    double estimated_pi = (double)needle_count / crosses * buffon_laplace(l, a, b);
    clock_t end_time = clock();

    double running_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Estimated value of pi: %f\n", estimated_pi);
    printf("Running time: %f seconds\n", running_time);
    
    return 0;
}
