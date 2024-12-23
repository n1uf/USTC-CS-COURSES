#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <termios.h>

#include <unistd.h>



// 初始化非阻塞输入模式

void init_terminal_mode() {

    struct termios newt;

    tcgetattr(STDIN_FILENO, &newt);  // 获取当前终端设置

    newt.c_lflag &= ~(ICANON | ECHO); // 关闭缓冲和回显

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 设置新模式

}



// 恢复默认终端模式

void reset_terminal_mode() {

    struct termios newt;

    tcgetattr(STDIN_FILENO, &newt);

    newt.c_lflag |= ICANON | ECHO; // 恢复缓冲和回显

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

}



#define N 40

int chess[N][N];      // 地图

int display[N][N];  // 显示的地图

int visited[N][N];      // 是否访问过

int queue[N*N][2];  // BFS队列



// 计算显示区域中值为x的块的数量

int count(int n, int m, int x) {

    int sum = 0;

    int i, j;

    for (i = 0; i < n; ++i) {

        for (j = 0; j < m; ++j) {

            if (display[i][j] == x) {

                ++sum;

            }

        }

    }

    return sum;

}



// 获取游戏难度

int get_level() {

    printf("选择难度\n");

    printf("难度一：9 x 9 棋盘，10 颗雷。\n");

    printf("难度二：16 x 16 棋盘，40 颗雷。\n");

    printf("难度三：30 x 30 棋盘，99 颗雷。\n");

    printf("输入1或2或3来选择难度:\n");



    char c;

    while (c = getchar()) {

        if ('1' <= c && c <= '3') {

            return c - '0';

        } else if (c != '\n') {

            printf("Illegal input, please input again.\n");

        }

    }

}



// 绘制地图

void draw(int level, int n, int m, int s, int x, int y) {

    system("clear");



    // 游戏信息

    printf("=====================================\n");

    printf("           扫雷游戏\n");

    printf("=====================================\n");

    printf("难度： Level %d\n", level);

    printf("剩余雷数： %d\n", s - count(n, m, -1));

    printf("=====================================\n");



    // 绘制地图

    int i, j;

    for (i = 0; i < n; ++i) {

        printf("|");  // 添加边框

        for (j = 0; j < m; ++j) {

            if (i == x && j == y) {

                printf(" o ");  // 当前选中的块

            } else if (display[i][j] == 0) {

                printf(" # ");  // 未揭开的块

            } else if (display[i][j] == -1) {

                printf(" ^ ");  // 标记为旗帜的块

            } else if (chess[i][j] > 0) {

                printf(" %c ", (char)(chess[i][j] + '0'));  // 显示数字

            } else {

                printf("   ");  // 空白块

            }

        }

        printf("|\n");  // 每行结束后打印边框

    }



    printf("=====================================\n");



    // 提示信息
    printf("操作说明：\n");
    printf("'o'为当前选择的方块。\n");
    printf("'#'为未揭开的方块。\n");
    printf("'^'为标记为旗帜的方块。\n");
    printf("数字为周围雷的数量。\n");
    printf("按 'w' 'a' 's' 'd' 移动选择。\n");
    printf("按 'y' 挖掘当前选择的方块。\n");
    printf("按 'f' 标记当前选择的方块为旗帜。\n");
    printf("按 'r' 移除当前选择的旗帜。\n");
    printf("=====================================\n");

}



// 获取按键输入

int input(int n, int m, int *x, int *y) {

    char c;

    while (c = getchar()) {

        switch (c) {

            case 'w':

                *x = (*x - 1 + n) % n;

                return 0;

            case 'a':

                *y = (*y - 1 + m) % m;

                return 0;

            case 's':

                *x = (*x + 1) % n;

                return 0;

            case 'd':

                *y = (*y + 1) % m;

                return 0;

            case 'y':

                display[*x][*y] = 1;

                return 1;

            case 'f':

                if (display[*x][*y] == 0) {

                    display[*x][*y] = -1;

                }

                return 0;

            case 'r':

                if (display[*x][*y] == -1) {

                    display[*x][*y] = 0;

                }

                return 0;

            default:

                break;

        }

    }

}



// 初始化地图

void init(int level, int n, int m, int s, int *x, int *y) {

    memset(chess, 0, sizeof(chess));

    memset(display, 0, sizeof(display));



    // 等待用户输入并绘制

    while (!input(n, m, x, y)) {

        draw(level, n, m, s, *x, *y);

    }



    srand(time(NULL));

    int cnt = 0;

    while (cnt < s) {

        int a = rand() % n, b = rand() % m;

        if (chess[a][b] == -1) continue;

        if (a == *x && b == *y) continue;



        chess[a][b] = -1;

        ++cnt;

    }



    // 初始化数字块

    int i, j, dx, dy;

    for (i = 0; i < n; ++i) {

        for (j = 0; j < m; ++j) {

            if (chess[i][j] == -1) continue;

            int sum = 0;

            for (dx = -1; dx <= 1; ++dx) {

                for (dy = -1; dy <= 1; ++dy) {

                    if (dx == 0 && dy == 0) continue;

                    int nx = i + dx, ny = j + dy;

                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

                    if (chess[nx][ny] == -1) ++sum;

                }

            }

            chess[i][j] = sum;

        }

    }

}



// 扩展空白区域

void spread(int n, int m, int x, int y) {

    if (chess[x][y] != 0) return;



    memset(visited, 0, sizeof(visited));

    int head = 0, tail = 0;

    queue[tail][0] = x;

    queue[tail++][1] = y;

    visited[x][y] = 1;



    int i, j, dx, dy;

    while (head < tail) {

        i = queue[head][0];

        j = queue[head++][1];

        for (dx = -1; dx <= 1; ++dx) {

            for (dy = -1; dy <= 1; ++dy) {

                if (dx == 0 && dy == 0) continue;

                int nx = i + dx, ny = j + dy;

                if (nx < 0 || nx >= n || ny < 0 || ny >= m || display[nx][ny] < 0) continue;

                display[nx][ny] = 1;

                if (chess[nx][ny] == 0 && !visited[nx][ny]) {

                    visited[nx][ny] = 1;

                    queue[tail][0] = nx;

                    queue[tail++][1] = ny;

                }

            }

        }

    }

}



// 游戏失败

void fail() {

    printf("\n=====================================\n");

    printf("        游戏结束！你输了。\n");

    printf("=====================================\n");

    printf("按任意键退出游戏。\n");

    getchar();

}



// 游戏胜利

void win() {

    printf("\n=====================================\n");

    printf("           你赢了！恭喜你。\n");

    printf("=====================================\n");

    printf("按任意键退出游戏。\n");

    getchar();

}



// 主程序

int main() {

    init_terminal_mode(); // 启用非阻塞模式

    int level = get_level();



    int n, m, s;

    switch (level) {

        case 1:

            n = 9, m = 9, s = 10;

            break;

        case 2:

            n = 16, m = 16, s = 40;

            break;

        case 3:

            n = 30, m = 30, s = 99;

            break;

        default:

            printf("Illegal level.\n");

            printf("Exit unexpectedly.\n");

            return 1;

    }



    int x = 0, y = 0;

    draw(level, n, m, s, x, y);

    init(level, n, m, s, &x, &y);

    spread(n, m, x, y);

    draw(level, n, m, s, x, y);



    while (1) {

        while (!input(n, m, &x, &y)) {

            draw(level, n, m, s, x, y);

        }

        spread(n, m, x, y);

        draw(level, n, m, s, x, y);



        if (chess[x][y] == -1) {

            fail();

            break;

        }



        if (count(n, m, 0) + count(n, m, -1) == s) {

            win();

            break;

        }

    }



    reset_terminal_mode(); // 恢复终端模式

    return 0;

}

