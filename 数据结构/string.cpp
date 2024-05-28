#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MODE0
// #define MODE1
#define MAX 1000
int next[MAX] = {0};

#define MODE2
#ifdef MODE1
//定长顺序结构存储

#define MAXSIZE 200

typedef struct
{	// 定长 
	char ch[MAXSIZE + 1];
	int length;
}SString, *StringList;

SString *initString()
{	//初始化串
	SString *str = (SString *)malloc(sizeof(SString));
	if(!str)
	{
        printf("初始化分配存储空间失败！\n");
        exit(0);
    }
	for(int i = 0; i < MAXSIZE + 1; i ++)
	{
		str->ch[i] = '\0';
	}
	str->length = 0;
	return str;
}

void StringDestroy(SString *str)
{	// 销毁串
	free(str);
	puts("串已被销毁");
}

void StringClear(SString *str)
{	// 清空串 
	for(int i = 0; i < MAXSIZE + 1; i ++)
	{
		str->ch[i] = '\0';
	}
	str->length = 0;
}

int IsEmpty(SString *str)
{	// 判断串是否为空 
	if(str->length == 0)
		return 1;
	else
		return 0;
}

int StringLength(SString *str) 
{	//返回串的长度
	return str->length;
}

void insert (SString *str, int k, char s) 
{	//在原串的第k个字符前插入字符ch，k=0，1，……

	// 插入失败 
	if(k > str->length)
	{
		puts("k越界，插入失败");
		exit(0); 
	}
	
	if(str->length > MAXSIZE)
	{
		puts("串满，无法插入");
		exit(0);
	}
	
	// k位置后的字符后移 
	int i = 0;
	for(i = str->length; i >= k; i --)
	{
		str->ch[i + 1] = str->ch[i];
	}
	// 插入字符在k位置 
	str->ch[k] = s;
	str->length ++;
}

char StringAt (SString *str,int k) 
{	//返回串的第k个字符，k=0，1，……
	return str->ch[k];
}

void StringPrint(SString *str)
{	// 打印串
	if(IsEmpty(str))
		puts("字符串为空");
	else
		puts(str->ch);
}

void StrConcat(SString *str, SString *S1, SString *S2)
{	// 字符串连接 
	int length1 = S1->length;
	int length2 = S2->length;
	for(int i = 0; i < length1; i ++)
	{	// 前length1长度直接存 
		str->ch[i] = S1->ch[i];
	}
	int temp;
	// 改变str的length 
	if(length1 + length2 > MAXSIZE)
		str->length = MAXSIZE;
	else
		str->length = length1 + length2;
	for(int i = length1; i < str->length; i ++)
	{	// 后面存到str的length长度（可能截断） 
		str->ch[i] = S2->ch[i - length1];
	}
}

#endif

#ifdef MODE2
//堆分配存储

//定义初始容量和增加容量
#define INITSIZE 20
#define INCREASEMENT 5

//定义串数据结构
typedef struct
{
    char *ch;  //数据域
    int length; //串长度
}SString, *StringList;

// 初始化一个串数据结构并返回指针
SString* initString()
{
    SString* str = (SString *)malloc(sizeof(SString));
    if (!str) // 分配失败 
    {
        printf("初始化分配存储空间失败！\n");
        exit(0);
    }
    str->ch = (char *)malloc(INITSIZE * sizeof(char));
    for(int i = 0; i < INITSIZE + 1; i ++)
	{	// 全部初始化为'\0' 
		str->ch[i] = '\0';
	}
    str->length = 0;
    return str;
}


void insert(SString *str, int k, char s)
{	// 原串的第k个字符前插入字符ch，k=0，1，…… k和长度相等认为在末尾插入
    if (k > str->length)
    {
        printf("k越界，插入失败\n");
        exit(0);
    }
    if (str->length == INITSIZE - 1 ||
        (str->length > INITSIZE - 1 && (str->length - INITSIZE) % INCREASEMENT == INCREASEMENT - 1)) // 串满增加空间
        str->ch = (char *)realloc(str->ch, (str->length + 1 + INCREASEMENT) * sizeof(char));
    if (!str) //分配失败
    {
        printf("分配存储空间失败！\n");
        exit(0);
    }
    for (int i = str->length; i > k; i--) // 第k及以后字符后移一位
        str->ch[i] = str->ch[i - 1];
    str->ch[k] = s;	// 插入
    str->length++;	// 长度增加 
    str->ch[str->length] = '\0'; // 补一个字符串结束 
}

int StringLength(SString *str) 
{	// 返回串的长度
	return str->length;
}


char StringAt(SString *str, int k)
{	// 返回串的第k个字符，k=0，1，……
    return str->ch[k];
}

void StringClear(SString *str)
{	// 清空串 
	for(int i = 0; i < str->length; i ++)
	{
		str->ch[i] = '\0';
	}
	str->length = 0;
}

void StringDestroy(SString *str)
{	// 销毁串
	free(str);
	puts("串已被销毁");
}

int IsEmpty(SString *str)
{	// 判断串是否为空 
	if(str->length == 0)
		return 1;
	else
		return 0;
}

void StringPrint(SString *str)
{	// 打印串
	if(IsEmpty(str))
		puts("字符串为空");
	else
		puts(str->ch);
}

void StrConcat(SString *str, SString *S1, SString *S2)
{	// 字符串连接 
	int length1 = S1->length;
	int length2 = S2->length;
	for(int i = 0; i < length1; i ++)
	{
		str->ch[i] = S1->ch[i];
	}
	str->length = length1 + length2;
	for(int i = length1; i < str->length; i ++)
	{
		str->ch[i] = S2->ch[i - length1];
	}
	
    str->ch[str->length] = '\0'; //补'\0'
}

#endif

SString *StringSon(SString *str, SString *son, int k, int len)
{	// k位置长为len的字串 
	for(int i = k; i < k + len; i ++)
	{
		son->ch[i - k] = str->ch[i];
	}
	son->length = len;
	return son;
}

void *initNext()
{	// 初始化next数组 
	for(int i = 0; i < MAX; i ++)
	{
		next[i] = 0;
	}
}

void get_next(SString *str, int *next)
{	// 求next数组 
    next[0] = -1; // next数组从next[1]开始有效，所以直接把0赋值为-1避免错误 
    next[1] = 0;
    int k; // 每一个next的值暂存在k
	int j = 2; // 由于已经赋值了0和1，从next[2]开始赋值 
    while (j < str->length)	// 没有到串尾 
    {
    	// 根据j的前一位比较 
        k = next[j - 1];
        // 将j-1与k比较 
        while (k != 0 && str->ch[k] != str->ch[j - 1])
            k = next[k];
        if (k == 0)
            if (str->ch[0] == str->ch[j - 1])	//相等 
                next[j] = 1;
            else	// 没有相等 
                next[j] = 0;
        else	// k!= 0 
            next[j] = k + 1;
        j++;	// 比较下一个字符 
    }
}


int Index_KMP(SString *S, SString *T, int pos, int *next)
{	// kmp算法 
	int i = pos, j = 0; // i标记主串，j标记模式串
    while (i < S->length && j < T->length)	// 没有比较到串尾 
    {
        if (j == -1 || S->ch[i] == T->ch[j])
        {	// 模式串匹配，继续比较 
            i++;
            j++;
        }
        else // 否则调用next移动要比较的j 
            j = next[j];
    }
    if (j >= T->length) //匹配成功
        return i - T->length;
    else //匹配失败
        return -1;
}


SString *StrAssign(SString *str, char *chars)	 
{	// 插入一组字符（仅供初始化进行测试）
	str->length = strlen(chars);
	for(int i = 0; i < str->length; i ++)
	{
		str->ch[i] = chars[i];
	}
	return str;
}

void StrReplace(SString* str, SString* T, SString* P)
{	// 字符串替换
	initNext();
    get_next(T, next);
    for (int i = 0; str->ch[i] != '\0'; i++)
    {
        int loc = Index_KMP(str, T, i, next);
        if(loc == -1)	// kmp算法匹配失败 
        	continue;
		else			// 有可以替换的匹配 
		{
			str->length = str->length - T->length;		// 先改变串长 
			strncpy(str->ch + loc, str->ch + loc + T->length, str->length - loc - T->length + 1);  //将子串后面的串复制到子串位置
			for (int j = P->length - 1; j >= 0; j--)    //loc位置插入串P 
    			insert(str, loc, P->ch[j]);
			i = loc + P->length - 1;	// 移动到插入后的位置 
		}
    }
}

int main(void)
{
	SString *str = initString();
	SString *son = initString();
	SString *cat = initString();
	SString *str1 = initString();
	SString *str2 = initString();
	
	insert(str, 0, '0');
	insert(str, 0, '5');
	insert(str, 0, 'v');
	insert(str, 0, 'c');
	insert(str, 0, 'f');
	insert(str, 0, 'k');
	puts("初始的字符串为：");
	StringPrint(str);
	insert(str, 4, 'e');
	insert(str, 4, 'm');
	puts("插入两个字符后字符串为：");
	StringPrint(str);
	puts("字符串长度为：");
	printf("%d\n", StringLength(str));
	
	StringClear(str);
	puts("清除字符串后字符串为：");
	StringPrint(str);
	
	StrAssign(str, "acabaabaabcacaabc");
	puts("初始设置字符串为：");
	StringPrint(str);
	
	StringSon(str, son, 7, 3);
	puts("该字符串从第7位开始的三个字符组成的子串为："); 
	StringPrint(son);
	puts("字串长度为："); 
	printf("%d\n",StringLength(son));
	
	StrConcat(cat, str, son);
	puts("连接这两个字符串得到的字符串为："); 
	StringPrint(cat);
	puts("连接后得到的字符串的长度为："); 
	printf("%d\n",StringLength(cat));
	StringClear(cat);
	StringClear(str);
	StringClear(son);
	
	StrAssign(str, "abaabccabcaccc");
	StrAssign(cat, "abc");
	puts("主串为：");
	StringPrint(str);
	puts("模式串为："); 
	StringPrint(cat);
	
	get_next(cat, next);
	printf("由KMP算法得到模式串第一次出现在主串的位置为：%d\n", Index_KMP(str, cat, 0, next));
	
	StrAssign(str1, "ab");
	StrAssign(str2, "abab");
	puts("主串为：");
	StringPrint(str);
	puts("需要替换的串为：");
	StringPrint(str1);
	puts("替换成的串：");
	StringPrint(str2);
	StrReplace(str, str1, str2);
	puts("替换后的结果为："); 
	StringPrint(str);
	
	StringDestroy(str);
	StringDestroy(son);
	StringDestroy(cat);
	StringDestroy(str1);
	StringDestroy(str2);
}
