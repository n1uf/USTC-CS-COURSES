// main.c
#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 50
#define MAX_ENTRIES 10

// 声明外部汇编函数
extern void sort_strings(char** strings, int count);

// 定义结构体存储字符串和指针
typedef struct {
    char data[MAX_ENTRIES][MAX_STR_LEN];
    char* ptrs[MAX_ENTRIES];
} StringArray;

int main(void) {
    // 所有变量声明放在函数开始处
    StringArray arr;
    int count = 0;
    int i;
    char temp;
    
    printf("Input strings (name-salary format):\n");
    
    // 读取输入
    while (count < MAX_ENTRIES) {
        // 读取一行输入
        i = 0;
        while (i < MAX_STR_LEN - 1) {
            temp = getchar();
            if (temp == '\n' || temp == EOF) {
                break;
            }
            arr.data[count][i++] = temp;
        }
        arr.data[count][i] = '\0';
        
        // 如果是空行，结束输入
        if (i == 0) {
            break;
        }
        
        arr.ptrs[count] = arr.data[count];
        count++;
        
        // 清除可能的多余输入
        while (temp != '\n' && temp != EOF) {
            temp = getchar();
        }
    }
    
    if (count < 5) {
        printf("Error: Please input at least 5 strings\n");
        return 1;
    }
    
    // 调用汇编排序函数
    sort_strings(arr.ptrs, count);
    
    printf("\nSorted results:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", arr.ptrs[i]);
    }
    
    return 0;
}