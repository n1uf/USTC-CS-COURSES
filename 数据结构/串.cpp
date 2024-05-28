#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 40

#define OVERFLOW -2

typedef int Status;

typedef char SString[MAXSTRLEN+1];

Status StrEmpty(SString S);							// �жϴ��Ƿ�Ϊ�� 
Status StrAssign(SString T,char *chars);			// ����ֵ 
Status StrCopy(SString T,SString S);				// ������ 
Status StrLength(SString T);						// �󴮳��� 
Status StrPrint(SString T);							// ��ӡ�� 
Status StrClear(SString S);							// ��մ� 
Status StrConcat(SString T,SString S1,SString S2);	// ���������� 
Status StrIndex(SString T,SString S,int *pos);		// ������һ��ƥ��Ĵ���λ�� 
Status StrInsert(SString T,SString S,int pos);		// ��posλ�ú���봮 
Status StrDelete(SString T,int pos,int len);		// ɾ��posλ�ú󳤶�Ϊlen�Ĵ� 

int main()
{
	SString ch;
    StrAssign(ch, "abc");
    int length = StrLength(ch);
    printf("%d\n", length);
    StrPrint(ch);
    return 0;
}

/* �ַ�����ֵ,����ֵ�ַ������ȳ�������ֵ�ַ���ʱ��ض�,δ����ʱ�Ƚ����ȴ���T[0],����λ��ֵ */
Status StrAssign(SString T,char *chars)
{
        int i;
        if(strlen(chars)>MAXSTRLEN)
        {
                for(i = 1;i <= MAXSTRLEN;i++)
                {
                        T[i] = *(chars + i - 1);
                }
                T[0] = MAXSTRLEN;  //T[0]����int �����ݣ�%s�޷���ӡ
        }
        else
        {
                T[0] = strlen(chars);  //T[0]�������chars���ַ�����
                for(i = 1;i <= strlen(chars);i++)
                {
                        T[i] = *(chars + i - 1);
                }
        }
        return 1;
}

/* �ַ�������,����ַ�����(���������ȷ�Χ�ڵ�) */
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

/*  �ַ����пգ�S[0] == 0ʱΪ��  */
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

/*  ���ظ��ַ����ĳ���  */
Status StrLength(SString T)
{
        return T[0];
}

/*  ��ӡ�ַ���  */
Status StrPrint(SString T)
{
        int i;
        for(i = 1;i <= T[0];i++)
                printf("%c",T[i]);
        printf("\n");
        return 1;
}
/*  ����ַ�������������� */
Status StrClear(SString S)
{
        S[0] = 0;
        return 1;
}

/*  �ַ�������,ͨ��T���洢���,S2���Ӷ��ɵ��´�,��δ�ض��򷵻�TRUE,�ضϷ���FAlSE,ע���ַ�������Խ������  */
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

/*  �����Ӵ�,���ش�T�е�һ���������봮S��ͬ���Ӵ���λ��  */
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

/*  �ڴ�T�ĵ�pos��λ�ú�����Ӵ�S  */
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
                        T[i + pos] = S[i];  //�������ֱ�ɾ��
                T[0] = MAXSTRLEN;
                return 0;
        }
}

/*  ɾ����T�ĵ�pos��λ���𣬳�Ϊlen���Ӵ�  */
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

