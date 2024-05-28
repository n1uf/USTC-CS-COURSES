#include <iostream>
#include <ctime>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

#define MAX 80000000
int board[MAX];
int pos_diag[2 * MAX - 1]; // ���Խ����ϵĻʺ����
int neg_diag[2 * MAX - 1]; // ���Խ����ϵĻʺ����

// ����[0, n - 1]��һ���������
// int get_randindex(int n) {
//     int sqrt_n = (int)sqrt(n);
//     int high = rand() % sqrt_n, low = rand() % sqrt_n;
//     return high * sqrt_n + low;
// }

// ���õ��������������
unsigned long long int RandSeed = (unsigned)time(NULL);
unsigned long long int get_randindex(long long int n) {
	unsigned long long int x;
	double i;
	
	x = 0x7fffffff;
	x += 1;
	RandSeed *= ((unsigned long long int)134775813);
	RandSeed += 1;
	RandSeed = RandSeed % x;
	i = ((double)RandSeed) / (double)0x7fffffff;
	
	return (unsigned long long int)(n * i);
}

void random_start(int n) {
    // �������һ���½�,ʹÿ�С�ÿ�ж�ֻ��һ���ʺ�
    random_shuffle(board, board + n);
}

int random_start_qs4(int n, int c) {
    int m = n - c;
    for (int i = 0; i < n; ++i) board[i] = i;
    memset(pos_diag, 0, sizeof(int) * (2 * n - 1));
    memset(neg_diag, 0, sizeof(int) * (2 * n - 1));
    int conflicts = 0;
    // �����ڿ��������������m���ʺ�,��֤�޳�ͻ
    for (int i = 0, last = n; i < m; ++i, --last) {
        // ��[i, n)��ѡj,��֤��Ӱ���ѷ��õĻʺ�
        int j = i + get_randindex(last);
        while (pos_diag[i - board[j] + n - 1] > 0 || neg_diag[i + board[j]] > 0) j = i + get_randindex(last);
        swap(board[i], board[j]);
        pos_diag[i - board[i] + n - 1]++;
        neg_diag[i + board[i]]++;
    }
    // ʣ��c���ʺ��ڿ�������������,�����Ƿ������ͻ
    for (int i = m, last = c; i < n; ++i, --last) {
        int j = i + get_randindex(last);
        swap(board[i], board[j]);
        pos_diag[i - board[i] + n - 1]++;
        neg_diag[i + board[i]]++;
    }
    for (int i = 0; i < 2 * n - 1; ++i) {
        conflicts += pos_diag[i] > 1 ? pos_diag[i] - 1 : 0;
        conflicts += neg_diag[i] > 1 ? neg_diag[i] - 1 : 0;
    }
    return conflicts;
}


// ��ʼʱ��ͻ�Ļʺ�����
int get_c(int n) {
    if (n <= 10) return n > 8 ? 8 : n;
    else if (n <= 100) return 30;
    else if (n <= 10000) return 50;
    else if (n <= 100000) return 80;
    return 100;
}

// int get_conflicts(int n) {
//     int ans = 0;
//     // ֻ�жԽ����ϲ��п��ܲ�����ͻ
//     for (int i = 0; i < n - 1; ++i) {
//         for (int j = i + 1; j < n; ++j) {
//             if (j - i == abs(board[i] - board[j])) ans++;
//         }
//     }
//     return ans;
// }

int get_conflicts(int n) {
    int ans = 0;
    memset(pos_diag, 0, sizeof(int) * (2 * n - 1));
    memset(neg_diag, 0, sizeof(int) * (2 * n - 1));
    for (int i = 0; i < n; ++i) {
        pos_diag[i - board[i] + n - 1]++;
        neg_diag[i + board[i]]++;
    }
    for (int i = 0; i < 2 * n - 1; ++i) {
        ans += pos_diag[i] > 1 ? pos_diag[i] - 1 : 0;
        ans += neg_diag[i] > 1 ? neg_diag[i] - 1 : 0;
    }
    return ans;
}

// ������i�͵�j���ʺ�����ĳ�ͻ���仯
int swap_gain(int i, int j, int n) {
    int gain = 0;
    // ԭ��λ�ö�Ӧ�ĶԽ����ϻʺ�����Ҫ��1
    // ���ԭ����Ӧ�ĶԽ������г�ͻ,��gain--
    if (neg_diag[i + board[i]] > 1) gain--;
    if (neg_diag[j + board[j]] > 1) gain--;
    if (pos_diag[i - board[i] + n - 1] > 1) gain--;
    if (pos_diag[j - board[j] + n - 1] > 1) gain--;
    // ͬ���֪�¶�Ӧ�ĶԽ������лʺ�,��gain++
    if (neg_diag[i + board[j]] > 0) gain++;
    if (neg_diag[j + board[i]] > 0) gain++;
    if (pos_diag[i - board[j] + n - 1] > 0) gain++;
    if (pos_diag[j - board[i] + n - 1] > 0) gain++;
    return gain;
}

// ���ڽ��������³�ͻ��ͻʺ�λ��
void update_state(int i, int j, int n) {
    neg_diag[i + board[i]]--;
    neg_diag[j + board[j]]--;
    pos_diag[i - board[i] + n - 1]--;
    pos_diag[j - board[j] + n - 1]--;

    neg_diag[i + board[j]]++;
    neg_diag[j + board[i]]++;
    pos_diag[i - board[j] + n - 1]++;
    pos_diag[j - board[i] + n - 1]++;
    
    swap(board[i], board[j]);
}


void local_search_v0(int n) {
    bool restart = true;
    int curr;
    clock_t start = clock();
    while (true) {
        // ����Ҳ�����С�ĳ�ͻ��,�������������
        if (restart) {
            random_start(n);
            curr = get_conflicts(n);
        }
        if (curr == 0) break;
        restart = true;
        // ѡ����״̬
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(board[i], board[j]);
                int tmp = get_conflicts(n);
                // ����������ͻ������,��������ֽ���
                if (tmp < curr) {
                    curr = tmp;
                    restart = false;
                }
                else swap(board[i], board[j]);
            }
        }
    }
    clock_t end = clock();
    cout << "solved in " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
}

// �Ż�:�����ͻ��,�����ͻ��ֻ��O(1)
void local_search_v1(int n) {
    bool restart = true;
    int curr;
    clock_t start = clock();
    while (true) {
        if (restart) {
            random_start(n);
            curr = get_conflicts(n);
        }
        if (curr == 0) break;
        restart = true;
        // ������������ʺ�,���Դ��������������С
        long long max_iteration = (long long)n * (long long)n / 2;
        for (long long i = 0; i < max_iteration; ++i) {
            int i_index = get_randindex(n), j_index = get_randindex(n);
            int gain = swap_gain(i_index, j_index, n);
            if (gain < 0) {
                update_state(i_index, j_index, n);
                curr += gain;
                restart = false;
                break;
            }
        }
    }
    clock_t end = clock();
    cout << "solved in " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
}

// �Ż�:���õ����ɳ�ʼ��(QS4�㷨)
void local_search_v2(int n, int c) {
    bool restart = true;
    int curr;
    clock_t start = clock();
    int m = n - c;
    while (true) {
        if (restart) curr = random_start_qs4(n, c);
        if (curr <= 0) break;
        restart = true;
        int gain = 0;
        // ������������ʺ�,��һ���Ӳ�����ͻ������ѡȡ,�ڶ�����ȫ���ѡȡ
        for (int i = 0; i < n; ++i) {
            if (pos_diag[i - board[i] + n - 1] > 1 || neg_diag[i + board[i]] > 1) {
                for (int j = 0; j < n; ++j) {
                    if (i != j) {
                        gain = swap_gain(i, j, n);
                        if (gain < 0) {
                            update_state(i, j, n);
                            curr += gain;
                            restart = false;
                            break;
                        }
                    }
                }
                if (restart) break;
            }
        }
    }
    clock_t end = clock();
    cout << "solved in " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
}

int main() {
    srand(unsigned(time(0)));
    int n;
    while (true) {
        cout << "input (pos)num of queens, -1 to quit" << endl;
        cin >> n;
        if (n <= 0 || n > MAX) break;
        for (int run = 0; run < 10; run++) {
            for (int i = 0; i < n; ++i) board[i] = i;
            local_search_v2(n, get_c(n));
            // n��Сʱ��ӡ�����,��֤��ȷ��
            if (n <= 10) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (board[i] == j) cout << "Q";
                        else cout << "+";
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}
