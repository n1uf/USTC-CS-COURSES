#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 在字符串中插入特殊字符，用于处理奇偶长度的回文串
char* preprocessString(const char *s, int *outLength)
{
    int n = strlen(s);
    *outLength = 2 * n + 1;

    char *processedStr = (char*)malloc((*outLength + 1) * sizeof(char));  // +1 为了存放字符串结束符 '\0'
    if (processedStr == NULL) {
        // 处理内存分配失败
        return NULL;
    }

    int j = 0;
    processedStr[j++] = '#';

    for (int i = 0; i < n; i++)
    {
        processedStr[j++] = s[i];
        processedStr[j++] = '#';
    }

    processedStr[j] = '\0';  // 添加字符串结束符

    return processedStr;
}

int findLongestPalindromicSubstring(const char *s)
{
    int n = strlen(s);
    int processedLength;
    char *processedStr = preprocessString(s, &processedLength);

    if (processedStr == NULL) {
        // 处理内存分配失败
        return -1;
    }

    int *palindromeLengths = (int*)malloc(processedLength * sizeof(int));
    if (palindromeLengths == NULL) {
        // 处理内存分配失败
        free(processedStr);
        return -1;
    }

    memset(palindromeLengths, 0, processedLength * sizeof(int));

    int center = 0;    // 当前回文串的中心位置
    int right = 0;     // 当前回文串的右边界

    for (int i = 0; i < processedLength; i++)
    {
        int mirror = 2 * center - i; // 计算当前字符关于center的对称位置

        // 判断当前字符是否在当前回文串的右边界内
        if (i < right)
        {
            palindromeLengths[i] = (right - i) < palindromeLengths[mirror] ? (right - i) : palindromeLengths[mirror];
        }

        // 尝试扩展当前回文串
        while (i - 1 - palindromeLengths[i] >= 0 && i + 1 + palindromeLengths[i] < processedLength &&
               processedStr[i + 1 + palindromeLengths[i]] == processedStr[i - 1 - palindromeLengths[i]])
        {
            palindromeLengths[i]++;
        }

        // 更新当前回文串的右边界和中心位置
        if (i + palindromeLengths[i] > right)
        {
            center = i;
            right = i + palindromeLengths[i];
        }
    }

    // 找到最长回文子串的长度
    int maxLength = 0;
    for (int i = 0; i < processedLength; i++)
    {
        maxLength = (maxLength < palindromeLengths[i]) ? palindromeLengths[i] : maxLength;
    }

    free(processedStr);
    free(palindromeLengths);

    return maxLength;
}

int main()
{
    int n;
    scanf("%d", &n);

    char *s = (char*)malloc((n + 1) * sizeof(char));  // +1 为了存放字符串结束符 '\0'
    if (s == NULL) {
        // 处理内存分配失败
        return -1;
    }

    scanf("%s", s);

    int maxLength = findLongestPalindromicSubstring(s);
    printf("%d\n", maxLength);

    free(s);

    return 0;
}
