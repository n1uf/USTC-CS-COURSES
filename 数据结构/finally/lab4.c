#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODE0
// #define MODE1
// #define MODE2

#ifdef MODE0
//定长顺序结构存储

#define MAXSIZE 200

typedef struct stringType{
    int length;
    char stringValue[MAXSIZE];
}* StringType;

StringType initString () {
    StringType str = malloc(sizeof(struct stringType));
    str->length = 0;
    return str;
}
//初始化串

void insert (StringType str, int k, char ch) {
    if (str->length == MAXSIZE) exit(-1);
    for (int i = str->length; i > k; i--)
        str->stringValue[i] = str->stringValue[i - 1];
    str->stringValue[k] = ch;
    str->length++;
}
//在原串的第k个字符前插入字符ch，k=0，1，……

char StringAt (StringType str,int k) {
    return str->stringValue[k];
}
//返回串的第k个字符，k=0，1，……

int length(StringType str) {
    return str->length;
}
//返回串的长度

void StringClear (StringType str) {
    str->length = 0;
}
//清空字符串

void StringDestroy (StringType str) {
    free(str);
}
//销毁字符串

#endif

#ifdef MODE1
//堆分配存储

#define INITSIZE 20
#define INCREASEMENT 5

typedef struct stringType{
    int length;
    int space;
    char *stringValue;
}* StringType;

StringType initString () {
    StringType temp = malloc(sizeof(struct stringType));
    temp->length = 0;
    temp->space = INITSIZE;
    temp->stringValue = malloc(INITSIZE*sizeof(char));
    return temp;
}
//初始化串

void insert (StringType str, int k, char ch) {
    if (str->length == str->space) {
        str->stringValue = realloc(str->stringValue, str->space + INCREASEMENT);
        str->space += INCREASEMENT;
    }
    for (int i = str->length; i > k; i--) {
        str->stringValue[i] = str->stringValue[i - 1];
    }
    str->stringValue[k] = ch;
    str->length++;
}
//在原串的第k个字符前插入字符ch，k=0，1，……

char StringAt (StringType str,int n) {
    return str->stringValue[n];
}
//返回串的第k个字符，k=0，1，……

int length(StringType str) {
    return str->length;
}
//返回串的长度

void StringClear (StringType str) {
    free(str->stringValue);
    str->space = INITSIZE;
    str->length = 0;
    str->stringValue = malloc(INITSIZE*sizeof(char));
}
//清空字符串

void StringDestroy (StringType str) {
    free(str->stringValue);
    free(str);
}
//销毁字符串

#endif

#ifdef MODE2

#define NODESIZE 4

typedef struct node {
    char ch[NODESIZE];
    struct node *next;
}Node;

typedef struct {
    int length;
    Node *stringValue;
}* StringType;

StringType initString () {
    StringType temp = malloc(sizeof(StringType));
    temp->length = 0;
    temp->stringValue = malloc(sizeof(Node));
    temp->stringValue->next = NULL;
    return temp;
}
//初始化串

void insert (StringType str, int k, char ch) {
    int nodeN = k / NODESIZE, offset = k % NODESIZE;
    Node *p = str->stringValue;
    for (int i = 0; i < nodeN; i++)
        p = p->next;
    int is_overflow = 0;
    char overflow;
    if (k == str->length) {
        overflow = ch;
        is_overflow = 1;
    }
    while (p != NULL) {
        if (str->length >= (nodeN + 1) * NODESIZE) {
            overflow = p->ch[NODESIZE - 1];
            is_overflow = 1;
        } else {
            is_overflow = 0;
        }
        for (int i = NODESIZE - 1; i > offset; i--) {
            p->ch[i] = p->ch[i - 1];
        }
        if (nodeN * NODESIZE + offset == k) p->ch[offset] = ch;
        else p->ch[offset] = overflow;
        p = p->next;
        nodeN += 1;
        offset = 0;
    }
    if (is_overflow) {
        for (p = str->stringValue; p->next != NULL; p = p->next) ;
        p->next = (Node *)malloc(sizeof(Node));
        p->next->ch[0] = overflow;
        p->next->next = NULL;
    }
    str->length++;
}
//在原串的第k个字符前插入字符ch，k=0，1，……

char StringAt (StringType str,int n) {
    Node *q = str->stringValue;
    while (n >= NODESIZE) {
        q = q->next;
        n -= NODESIZE;
    }
    return q->ch[n];
}
//返回串的第k个字符，k=0，1，……

int length(StringType str) {
    return str->length;
}
//返回串的长度

void StringClear (StringType str) {
    Node *p,*q;
    p = q = str->stringValue;
    while (p->next != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    str->stringValue = malloc(sizeof(Node));
    str->stringValue->next = NULL;
    str->length = 0;
}
//清空字符串

void StringDestroy (StringType str) {
    StringClear(str);
    free(str->stringValue);
    free(str);
}
//销毁字符串

#endif

//以下操作仅需要使用上面封装好的函数，而不关注串的具体存储方式。

void StringPrint (StringType str) {
    for (int i = 0; i < length(str); i++)
        printf("%c", StringAt(str, i));
    printf("\n");
}
//打印串中所有元素

void StringConcat (StringType ans,StringType str) {
    for (int i = 0; i < str->length; i++) {
        insert(ans, length(ans), StringAt(str, i));
    }
}
//串的拼接，将串str拼接在串ans的末尾。

void Next (StringType pat, int *next) {
    memset(next, 0, length(pat) * sizeof(int));
    int M = length(pat);
    next[0] = -1;
    next[1] = 0;
    int k = 2,j = 2;
    while (j < M) {
        k = next[j - 1];
        while (k > 0 && StringAt(pat, j - 1) != StringAt(pat, k))
            k = next[k];
        if (k <= 0) {
            if (StringAt(pat, 0) == StringAt(pat, j - 1)) next[j] = 1;
            else next[j] = 0;
        } else next[j] = k + 1;
        j++;
    }
}
//KMP算法中求解next数组

int KMP (StringType txt,StringType pat) {
    int * next = malloc(length(pat) * sizeof(int));
    Next(pat, next);
    int i = 0, j = 0;
    int M = length(pat);
    int N = length(txt);
    while (i<N && j<M) {
        if (j==-1 || StringAt(txt,i)==StringAt(pat,j)) {
            ++i;
            ++j;
        } else j = next[j];
    }
    free(next);
    if (j>=M) return i-M;
    else return -1;
}
//串的模式匹配，txt为主串，pat为模式串，返回值为模式串在主串中第一次出现的位置。
/*
    StringPrint(txt);   //abaabcab
    StringPrint(pat);   //abc
    KMP(txt, pat);      //3
*/

StringType SubString (StringType str,int begin,int size) {
    StringType res = initString();
    for (int i = 0; i < size; i++) {
        insert(res, length(res), StringAt(str, begin + i));
    }
    return res;
}
//求子串，结果为主串中从第begin个字符开始后的size个字符，begin=0，1，……
/*
    StringPrint(txt);       //abaabcab
    SubString(txt, 1, 2);   //ba
*/

void StringReplace (StringType *str,StringType T,StringType P) {
    int pos = KMP(*str, T);
    StringType temp = initString();
    while (pos != -1) {
        StringConcat(temp, SubString(*str, 0, pos));
        StringConcat(temp, P);
        StringType p = SubString(*str, pos + length(T), length(*str) - pos - length(T));
        StringDestroy(*str);
        *str = p;
        pos = KMP(*str, T);
    }
    StringConcat(temp, *str);
    StringDestroy(*str);
    *str = temp;
}
//字符串替换，将主串str中每个与串T相同的子串替换为串P

int main () {
    //测试样例
    StringType txt = initString();
    insert(txt, 0, 'b');
    insert(txt, 0, 'c');
    insert(txt, 0, 'b');
    insert(txt, 0, 'a');
    insert(txt, 0, 'a');
    insert(txt, 0, 'c');
    insert(txt, 0, 'b');
    insert(txt, 0, 'a');
    insert(txt, 0, 'a');
    insert(txt, 0, 'b');
    insert(txt, 0, 'a');
    StringPrint(txt);
    //abaabcaabcb

    StringType pat = initString();
    insert(pat, 0, 'c');
    insert(pat, 0, 'b');
    printf("%d\n", KMP(txt, pat));
    //4

    StringConcat(txt, pat);
    StringPrint(txt);

    StringClear(pat);
    insert(pat, 0, 'b');

    StringType str = initString();
    insert(str, 0, 'b');
    insert(str, 0, 'b');
    StringReplace(&txt, pat, str);
    StringPrint(txt);
    //abbaabbcaabbcbb
    StringDestroy(str);
    StringDestroy(txt);
    StringDestroy(pat);
    return 0;
}