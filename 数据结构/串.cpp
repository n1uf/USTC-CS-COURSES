#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 40

#define OVERFLOW -2

typedef int Status;

typedef char SString[MAXSTRLEN+1];

Status StrEmpty(SString S);							// 判断串是否为空 
Status StrAssign(SString T,char *chars);			// 串赋值 
Status StrCopy(SString T,SString S);				// 串复制 
Status StrLength(SString T);						// 求串长度 
Status StrPrint(SString T);							// 打印串 
Status StrClear(SString S);							// 清空串 
Status StrConcat(SString T,SString S1,SString S2);	// 连接两个串 
Status StrIndex(SString T,SString S,int *pos);		// 索引第一个匹配的串的位置 
Status StrInsert(SString T,SString S,int pos);		// 在pos位置后插入串 
Status StrDelete(SString T,int pos,int len);		// 删除pos位置后长度为len的串 

int main()
{
	SString ch;
    StrAssign(ch, "abc");
    int length = StrLength(ch);
    printf("%d\n", length);
    StrPrint(ch);
    return 0;
}

/* 字符串赋值,当赋值字符串长度超过被赋值字符串时候截断,未超过时先将长度存入T[0],再逐位赋值 */
Status StrAssign(SString T,char *chars)
{
        int i;
        if(strlen(chars)>MAXSTRLEN)
        {
                for(i = 1;i <= MAXSTRLEN;i++)
                {
                        T[i] = *(chars + i - 1);
                }
                T[0] = MAXSTRLEN;  //T[0]存入int 型数据，%s无法打印
        }
        else
        {
                T[0] = strlen(chars);  //T[0]存入的是chars的字符长度
                for(i = 1;i <= strlen(chars);i++)
                {
                        T[i] = *(chars + i - 1);
                }
        }
        return 1;
}

/* 字符串拷贝,逐个字符拷贝(仅拷贝长度范围内的) */
Status StrCopy(SString T,SString S)
{
        int i;
        for(i = 1;i <= S[0];i++)
        {
                T[i] = S[i];
        }
        T[0] = S[0];
        return 1;
}

/*  字符串判空，S[0] == 0时为空  */
Status StrEmpty(SString T)
{
        if(T[0] == 0)
        {
                printf("The string is empty!\n");
                return 1;
        }
        else
        {
                printf("The string is NOT empty!\n");
                return 0;
        }
}

/*  返回该字符串的长度  */
Status StrLength(SString T)
{
        return T[0];
}

/*  打印字符串  */
Status StrPrint(SString T)
{
        int i;
        for(i = 1;i <= T[0];i++)
                printf("%c",T[i]);
        printf("\n");
        return 1;
}
/*  清除字符串，即长度清空 */
Status StrClear(SString S)
{
        S[0] = 0;
        return 1;
}

/*  字符串联接,通过T来存储结果,S2连接而成的新串,若未截断则返回TRUE,截断返回FAlSE,注意字符串数组越界问题  */
Status StrConcat(SString T,SString S1,SString S2)
{
        int i;
        if(S1[0]+S2[0] <= MAXSTRLEN)
        {
                for(i = 1;i <= S1[0];i++)
                {
                        T[i] = S1[i];
                }
                for(i = 1;i <= S2[0];i++)
                {
                        T[S1[0]+i] = S2[i];
                }
                T[0] = S1[0] + S2[0];
                return 1;
        }
        else
        {
                for(i = 1;i <= S1[0];i++)
                {
                        T[i] = S1[i];
                }
                for(i = 1;i <= (MAXSTRLEN-S1[0]);i++)
                {
                        T[S1[0]+i] = S2[i];
                }
                T[0] = MAXSTRLEN;
                return 0;
        }
}

/*  索引子串,返回串T中第一个索引到与串S相同的子串的位置  */
Status StrIndex(SString T,SString S,int *pos)
{
        int i=1,j=1;
        while((i <= T[0]) && (j <= S[0]))
        {
                if(T[i] == S[j])
                {
                        i++;
                        j++;
                }
                else
                {
                        i = i - j + 2;
                        j = 1;
                }
        }
        if(j > S[0])
        {
                *pos = i - j + 1;
                printf("Found,position is %d\n",*pos);
                return 1;
        }
        else
        {
                printf("NOT find child string yet.\n");
                return 0;
        }
}

/*  在串T的第pos个位置后插入子串S  */
Status StrInsert(SString T,SString S,int pos)
{
        int i;
        if(pos > T[0])
        {
                pos = T[0] +1;
        }
        if(T[0] + S[0] <= MAXSTRLEN)
        {
                for(i = 1; i <= pos;i++)
                        T[T[0] + S[0] - i +1] = T[T[0] + S[0] - i -pos];
                for(i = 1;i <= S[0];i++)
                        T[pos + i] = S[i];
                T[0] = T[0] + S[0];
                return 1;
        }
        if(T[0] + S[0] > MAXSTRLEN)
        {
                for(i = 1;i <= (MAXSTRLEN - pos);i++)
                        T[i + pos] = S[i];  //超出部分被删除
                T[0] = MAXSTRLEN;
                return 0;
        }
}

/*  删除串T的第pos个位置起，长为len的子串  */
Status StrDelete(SString T,int pos,int len)
{
        int i;
        if(pos > T[0])
                return 0;
        if(len > T[0])
                len = T[0] - pos + 1;
        for(i = len + pos;i <= T[0];i++)
                T[i - len] =T[i];
        T[0] = T[0] - len;
        return 1;
}

