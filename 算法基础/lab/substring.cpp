#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* computePrefix(const char* pattern) {
    int m = strlen(pattern);
    int* prefix = (int*)malloc(m * sizeof(int));
    int j = 0;

    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefix[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        prefix[i] = j;
    }

    return prefix;
}

int* findSubstringPositions(const char* text, const char* pattern, int* count) {
    int n = strlen(text);
    int m = strlen(pattern);
    int* prefix = computePrefix(pattern);
    int i = 0;  // text中的索引
    int j = 0;  // pattern中的索引
    int* positions = NULL;
    *count = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;

            if (j == m) {
                (*count)++;
                positions = (int*)realloc(positions, (*count) * sizeof(int));
                positions[(*count) - 1] = i - j;
                j = prefix[j - 1];
            }
        } else {
            if (j != 0) {
                j = prefix[j - 1];
            } else {
                i++;
            }
        }
    }

    free(prefix);
    return positions;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char text[n + 1];
    char pattern[m + 1];
    scanf("%s %s", text, pattern);

    int count;
    int* positions = findSubstringPositions(text, pattern, &count);

    printf("%d\n", count);

    for (int i = 0; i < count; i++) {
        printf("%d", positions[i]);

        if (i < count - 1) {
            printf(" ");
        }
    }

    printf("\n");

    free(positions);

    return 0;
}
