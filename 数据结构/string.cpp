#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MODE0
// #define MODE1
#define MAX 1000
int next[MAX] = {0};

#define MODE2
#ifdef MODE1
//����˳��ṹ�洢

#define MAXSIZE 200

typedef struct
{	// ���� 
	char ch[MAXSIZE + 1];
	int length;
}SString, *StringList;

SString *initString()
{	//��ʼ����
	SString *str = (SString *)malloc(sizeof(SString));
	if(!str)
	{
        printf("��ʼ������洢�ռ�ʧ�ܣ�\n");
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
{	// ���ٴ�
	free(str);
	puts("���ѱ�����");
}

void StringClear(SString *str)
{	// ��մ� 
	for(int i = 0; i < MAXSIZE + 1; i ++)
	{
		str->ch[i] = '\0';
	}
	str->length = 0;
}

int IsEmpty(SString *str)
{	// �жϴ��Ƿ�Ϊ�� 
	if(str->length == 0)
		return 1;
	else
		return 0;
}

int StringLength(SString *str) 
{	//���ش��ĳ���
	return str->length;
}

void insert (SString *str, int k, char s) 
{	//��ԭ���ĵ�k���ַ�ǰ�����ַ�ch��k=0��1������

	// ����ʧ�� 
	if(k > str->length)
	{
		puts("kԽ�磬����ʧ��");
		exit(0); 
	}
	
	if(str->length > MAXSIZE)
	{
		puts("�������޷�����");
		exit(0);
	}
	
	// kλ�ú���ַ����� 
	int i = 0;
	for(i = str->length; i >= k; i --)
	{
		str->ch[i + 1] = str->ch[i];
	}
	// �����ַ���kλ�� 
	str->ch[k] = s;
	str->length ++;
}

char StringAt (SString *str,int k) 
{	//���ش��ĵ�k���ַ���k=0��1������
	return str->ch[k];
}

void StringPrint(SString *str)
{	// ��ӡ��
	if(IsEmpty(str))
		puts("�ַ���Ϊ��");
	else
		puts(str->ch);
}

void StrConcat(SString *str, SString *S1, SString *S2)
{	// �ַ������� 
	int length1 = S1->length;
	int length2 = S2->length;
	for(int i = 0; i < length1; i ++)
	{	// ǰlength1����ֱ�Ӵ� 
		str->ch[i] = S1->ch[i];
	}
	int temp;
	// �ı�str��length 
	if(length1 + length2 > MAXSIZE)
		str->length = MAXSIZE;
	else
		str->length = length1 + length2;
	for(int i = length1; i < str->length; i ++)
	{	// ����浽str��length���ȣ����ܽضϣ� 
		str->ch[i] = S2->ch[i - length1];
	}
}

#endif

#ifdef MODE2
//�ѷ���洢

//�����ʼ��������������
#define INITSIZE 20
#define INCREASEMENT 5

//���崮���ݽṹ
typedef struct
{
    char *ch;  //������
    int length; //������
}SString, *StringList;

// ��ʼ��һ�������ݽṹ������ָ��
SString* initString()
{
    SString* str = (SString *)malloc(sizeof(SString));
    if (!str) // ����ʧ�� 
    {
        printf("��ʼ������洢�ռ�ʧ�ܣ�\n");
        exit(0);
    }
    str->ch = (char *)malloc(INITSIZE * sizeof(char));
    for(int i = 0; i < INITSIZE + 1; i ++)
	{	// ȫ����ʼ��Ϊ'\0' 
		str->ch[i] = '\0';
	}
    str->length = 0;
    return str;
}


void insert(SString *str, int k, char s)
{	// ԭ���ĵ�k���ַ�ǰ�����ַ�ch��k=0��1������ k�ͳ��������Ϊ��ĩβ����
    if (k > str->length)
    {
        printf("kԽ�磬����ʧ��\n");
        exit(0);
    }
    if (str->length == INITSIZE - 1 ||
        (str->length > INITSIZE - 1 && (str->length - INITSIZE) % INCREASEMENT == INCREASEMENT - 1)) // �������ӿռ�
        str->ch = (char *)realloc(str->ch, (str->length + 1 + INCREASEMENT) * sizeof(char));
    if (!str) //����ʧ��
    {
        printf("����洢�ռ�ʧ�ܣ�\n");
        exit(0);
    }
    for (int i = str->length; i > k; i--) // ��k���Ժ��ַ�����һλ
        str->ch[i] = str->ch[i - 1];
    str->ch[k] = s;	// ����
    str->length++;	// �������� 
    str->ch[str->length] = '\0'; // ��һ���ַ������� 
}

int StringLength(SString *str) 
{	// ���ش��ĳ���
	return str->length;
}


char StringAt(SString *str, int k)
{	// ���ش��ĵ�k���ַ���k=0��1������
    return str->ch[k];
}

void StringClear(SString *str)
{	// ��մ� 
	for(int i = 0; i < str->length; i ++)
	{
		str->ch[i] = '\0';
	}
	str->length = 0;
}

void StringDestroy(SString *str)
{	// ���ٴ�
	free(str);
	puts("���ѱ�����");
}

int IsEmpty(SString *str)
{	// �жϴ��Ƿ�Ϊ�� 
	if(str->length == 0)
		return 1;
	else
		return 0;
}

void StringPrint(SString *str)
{	// ��ӡ��
	if(IsEmpty(str))
		puts("�ַ���Ϊ��");
	else
		puts(str->ch);
}

void StrConcat(SString *str, SString *S1, SString *S2)
{	// �ַ������� 
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
	
    str->ch[str->length] = '\0'; //��'\0'
}

#endif

SString *StringSon(SString *str, SString *son, int k, int len)
{	// kλ�ó�Ϊlen���ִ� 
	for(int i = k; i < k + len; i ++)
	{
		son->ch[i - k] = str->ch[i];
	}
	son->length = len;
	return son;
}

void *initNext()
{	// ��ʼ��next���� 
	for(int i = 0; i < MAX; i ++)
	{
		next[i] = 0;
	}
}

void get_next(SString *str, int *next)
{	// ��next���� 
    next[0] = -1; // next�����next[1]��ʼ��Ч������ֱ�Ӱ�0��ֵΪ-1������� 
    next[1] = 0;
    int k; // ÿһ��next��ֵ�ݴ���k
	int j = 2; // �����Ѿ���ֵ��0��1����next[2]��ʼ��ֵ 
    while (j < str->length)	// û�е���β 
    {
    	// ����j��ǰһλ�Ƚ� 
        k = next[j - 1];
        // ��j-1��k�Ƚ� 
        while (k != 0 && str->ch[k] != str->ch[j - 1])
            k = next[k];
        if (k == 0)
            if (str->ch[0] == str->ch[j - 1])	//��� 
                next[j] = 1;
            else	// û����� 
                next[j] = 0;
        else	// k!= 0 
            next[j] = k + 1;
        j++;	// �Ƚ���һ���ַ� 
    }
}


int Index_KMP(SString *S, SString *T, int pos, int *next)
{	// kmp�㷨 
	int i = pos, j = 0; // i���������j���ģʽ��
    while (i < S->length && j < T->length)	// û�бȽϵ���β 
    {
        if (j == -1 || S->ch[i] == T->ch[j])
        {	// ģʽ��ƥ�䣬�����Ƚ� 
            i++;
            j++;
        }
        else // �������next�ƶ�Ҫ�Ƚϵ�j 
            j = next[j];
    }
    if (j >= T->length) //ƥ��ɹ�
        return i - T->length;
    else //ƥ��ʧ��
        return -1;
}


SString *StrAssign(SString *str, char *chars)	 
{	// ����һ���ַ���������ʼ�����в��ԣ�
	str->length = strlen(chars);
	for(int i = 0; i < str->length; i ++)
	{
		str->ch[i] = chars[i];
	}
	return str;
}

void StrReplace(SString* str, SString* T, SString* P)
{	// �ַ����滻
	initNext();
    get_next(T, next);
    for (int i = 0; str->ch[i] != '\0'; i++)
    {
        int loc = Index_KMP(str, T, i, next);
        if(loc == -1)	// kmp�㷨ƥ��ʧ�� 
        	continue;
		else			// �п����滻��ƥ�� 
		{
			str->length = str->length - T->length;		// �ȸı䴮�� 
			strncpy(str->ch + loc, str->ch + loc + T->length, str->length - loc - T->length + 1);  //���Ӵ�����Ĵ����Ƶ��Ӵ�λ��
			for (int j = P->length - 1; j >= 0; j--)    //locλ�ò��봮P 
    			insert(str, loc, P->ch[j]);
			i = loc + P->length - 1;	// �ƶ���������λ�� 
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
	puts("��ʼ���ַ���Ϊ��");
	StringPrint(str);
	insert(str, 4, 'e');
	insert(str, 4, 'm');
	puts("���������ַ����ַ���Ϊ��");
	StringPrint(str);
	puts("�ַ�������Ϊ��");
	printf("%d\n", StringLength(str));
	
	StringClear(str);
	puts("����ַ������ַ���Ϊ��");
	StringPrint(str);
	
	StrAssign(str, "acabaabaabcacaabc");
	puts("��ʼ�����ַ���Ϊ��");
	StringPrint(str);
	
	StringSon(str, son, 7, 3);
	puts("���ַ����ӵ�7λ��ʼ�������ַ���ɵ��Ӵ�Ϊ��"); 
	StringPrint(son);
	puts("�ִ�����Ϊ��"); 
	printf("%d\n",StringLength(son));
	
	StrConcat(cat, str, son);
	puts("�����������ַ����õ����ַ���Ϊ��"); 
	StringPrint(cat);
	puts("���Ӻ�õ����ַ����ĳ���Ϊ��"); 
	printf("%d\n",StringLength(cat));
	StringClear(cat);
	StringClear(str);
	StringClear(son);
	
	StrAssign(str, "abaabccabcaccc");
	StrAssign(cat, "abc");
	puts("����Ϊ��");
	StringPrint(str);
	puts("ģʽ��Ϊ��"); 
	StringPrint(cat);
	
	get_next(cat, next);
	printf("��KMP�㷨�õ�ģʽ����һ�γ�����������λ��Ϊ��%d\n", Index_KMP(str, cat, 0, next));
	
	StrAssign(str1, "ab");
	StrAssign(str2, "abab");
	puts("����Ϊ��");
	StringPrint(str);
	puts("��Ҫ�滻�Ĵ�Ϊ��");
	StringPrint(str1);
	puts("�滻�ɵĴ���");
	StringPrint(str2);
	StrReplace(str, str1, str2);
	puts("�滻��Ľ��Ϊ��"); 
	StringPrint(str);
	
	StringDestroy(str);
	StringDestroy(son);
	StringDestroy(cat);
	StringDestroy(str1);
	StringDestroy(str2);
}
