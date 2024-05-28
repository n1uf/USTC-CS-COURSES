#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct num
{	// �߾������Ĵ洢�ṹ 
	int negative;	// ��������Ϊ0����Ϊ1 
	int inte[MAX];	// ����ֵ�µ���������
	int deci[MAX];	// ����ֵ�µ�С������
	int base;
	int length1;	// �������� 
	int length2;	// С������ 
}num;

num* initNUM()
{	// ��ʼ���ṹ�� 
	num* tmp = (num*)malloc(sizeof(num));
	tmp->base = 0;
	tmp->negative = 0;
	tmp->length1 = 0; 
	tmp->length2 = 0;
	for(int i = 0; i < MAX; i ++)
	{
		tmp->inte[i] = 0;
		tmp->deci[i] = 0;
	}
	return tmp;
}

char *initCHAR(char *str)
{	// ��ʼ���ַ����� 
	for(int i = 0; i < MAX; i ++)
		str[i] = '\0';
	return str;
}

int *initINT(int *p)
{	// ��ʼ���������� 
	for(int i = 0; i < MAX; i ++)
		p[i] = 0;
	return p;
}

num* Copy(num *IN, num *OUT)
{	// ���Ƹ߾�������ÿ���ṹ���ڶ���ı��������ƹ�ȥ 
	OUT->base = IN->base;
	OUT->length1 = IN->length1;
	OUT->length2 = IN->length2;
	OUT->negative = IN->negative;
	for(int i = 0; i < MAX; i ++)
	{
		OUT->inte[i] = IN->inte[i];
		OUT->deci[i] = IN->deci[i];
	}
	return OUT;
}

num* ReadFromString(char *str, int base)
{	// ��ȡ�ַ�������base�����µĸ߾����� 
	num* tmp = initNUM();		// ��ʼ�� 
	tmp->base = base;			// ����һ�� 
	int i;
	if(str[0] == '-')
	{	// �������� 
		tmp->negative = 1;
		for(i = 0; i < MAX; i ++)
		{	// ֮���ǰ��һλ 
			str[i] = str[i + 1];
		}
	}
	for(i = 0; str[i] != '.' && str[i] != '\0'; i ++);		// �Ƶ����λ 
	int j = i - 1;
	int k = 0;
	for(; j >= 0; j --, k ++)
	{	// ���ζ�ȡ�������֣��������������ֳ��� 
		tmp->inte[k] = str[j] - 48;
		tmp->length1 ++;
	}
	if(i != MAX)
	{	// û���꣬����С�� 
		k ++;
		int l = 0;
		for(; str[k] != '\0'; k ++, l ++)
		{	// ���ζ�ȡС�����֣�������С�����ֳ��� 
			tmp->deci[l] = str[k] - 48;
			tmp->length2 ++;
		}
	}
	return tmp;
}

num* baseConversion(num *N, int base)
{	// ���߾�����ת��Ϊbase������ 
	num* tmp = initNUM();
	tmp->base = base;				// ����
	tmp->negative = N->negative;	// ����һ�� 
	// ��������
	for(int i = 0; i < MAX; i ++)
	{
		for(int j = 0; j < MAX; j ++)
			tmp->inte[j] *= N->base;			// Ԥ����base���Ƶ����� 

		tmp->inte[0] += N->inte[MAX - 1 - i];

		for(int j = 0; j < MAX - 1; j ++)
		{	// ������������ 
			if(tmp->inte[j] >= base)
			{	// �г���base���������ȡbase���ƵĽ�λ 
				tmp->inte[j + 1] += tmp->inte[j] / base;
				tmp->inte[j] = tmp->inte[j] % base;
			}
		}		
	}
	// С������
	int i, j, k = 0;
	int tmpp[MAX];
	for(i = 0; i < MAX; i ++)
	{	// tmpp��tmp��С������ 
		tmpp[i] = N->deci[i];
		tmp->deci[i] = 0;
	}
	for(k = 0; k < MAX; k ++)
	{	// ���ÿһλ 
		for(i = MAX - 1; tmpp[i] == 0; i --);	// �ƶ���С�������λ��ȥ�����0�� 
		for(; i >= 0; i --)
		{	// ��С�������һλ��ʼ���Ӻ���ǰ���а�λ�Ĳ��� 
			int temp = tmpp[i] * base + j;		// Ԥ�����Ϊbase���� 
			for(j = 0; j <= base; j ++)
			{	// �ҵ�temp/��ʼ���Ƶ��������֣�����¼���� 
				if(temp - j * N->base < 0)
				{
					j --;
					tmpp[i] = temp - j * N->base;
					break;
				}
			}
		}
		tmp->deci[k] = j;						// ���������ּ�Ϊת�����ƺ��λ������ 
		j = 0;									// ����j 
	}
}

void printnum(num *N)
{	// ��ӡ���ṹ��洢���� 
	int flag = 0;
	int i;
	if(N->negative == 1)
		printf("-");		// ��ӡ���� 
	for(i = MAX - 1;! N->inte[i] && i >= 0; i --);		//�ƶ��������������λ 
	if(i < 0)
		printf("0");		// û�������������������ִ�ӡ0 
	for(; i >= 0; i --)
	{	// �����ӡ 
		if(N->inte[i] < 10)
			printf("%d", N->inte[i]);
		else if(N->inte[i] < 36)
			printf("%c", 'a' + N->inte[i] - 10);
	}
		
	for(i = 0; i < MAX; i ++)				 
	{	// �ж��Ƿ���С��
		if(N->deci[i] != 0)
			flag = 1;
	}
	if(flag)
	{	// ��С������ 
		printf(".");
		for(i = MAX - 1;! N->deci[i]; i --);			// �ƶ���С���������λ��ȥ�����0�� 
		int j;
		for(j = 0; j <= i; j ++)
		{	// �����ӡ 
			if(N->deci[j] < 10) 	 printf("%d",N->deci[j]);
			else if(N->deci[j] < 36) printf("%c",'a' + N->deci[j] - 10);
		}
	}
	printf("\n");
}

int max(int a, int b)
{	// ���������ֵĽϴ�ֵ 
    return (a > b ? a : b);
}

int CompareAbs(num *A, num *B) 
{	// �ȽϾ���ֵ��С��A���򷵻�1������Ϊ0 
    if (A->length1 > B->length1)
        return 1;							// A�������ֳ���A�� 
    if (A->length1 == B->length1)
    {	// �������ֳ���һ�� 
        for (int i = A->length1 - 1; i >= 0; i--)
        {	// �����ж��������ִ�С 
            if (A->inte[i] > B->inte[i])
                return 1;
            if (A->inte[i] < B->inte[i])
                return 0;
        }
        for (int i = 0; i < max(A->length2, B->length2) - 1; i++)
        {	// �����ж�С�����ִ�С 
            if (A->deci[i] > B->deci[i])
                return 1;
            if (A->deci[i] < B->deci[i])
                return 0;
        }
    }
    return 0;
}

num *AddAbs(num *A, num *B) 
{	// ���о���ֵA + B
    num *C = initNUM();
    int k = 0;				// k�����λ 
    for (int i = max(A->length2, B->length2) - 1; i >= 0; i--) 
    {	// С�����ּӷ� 
        C->deci[i] = (A->deci[i] + B->deci[i] + k) % A->base;		// ������Ӳ��ӽ�λ�ٶԽ���ȡ��õ���λ 
        k = (A->deci[i] + B->deci[i] + k) / A->base;				// ��λ 
    }
    for (int i = 0; i <= max(A->length1, B->length1); i++)  
    {	// �������ּӷ�
        C->inte[i] = (A->inte[i] + B->inte[i] + k) % A->base;		// ������Ӳ��ӽ�λ�ٶԽ���ȡ��õ���λ 
        k = (A->inte[i] + B->inte[i] + k) / A->base;				// ��λ 
    }
    
    k = MAX - 1;
    for (; C->inte[k] == 0 && k > 0;)
        k--;					// kΪ�������λ 
    C->length1 = k + 1; 		// �������ֳ���
    k = MAX - 1;
    for (; C->deci[k] == 0 && k > 0;)
        k--;					// kΪС�����λ��ȥ�����0�� 
    C->length2 = k + 1; 		// С�����ֳ���
	C->negative = A->negative;	// �������� 
    return C;
}

num *SubAbs(num *A, num *B) 
{	// ���о���ֵA - B
    num *C = initNUM();
    int k = 0;				// k�����λ 
    for (int i = max(A->length2, B->length2) - 1; i >= 0; i--) 
    {	// С�����ּ�����һλһλ�� 
        if (A->deci[i] + k >= B->deci[i])
        {	// ����������Ϊ���� ��ֱ�Ӽ� 
            C->deci[i] = A->deci[i] + k - B->deci[i];
            k = 0;
        }
        else
        {	// �����λ������λ��ʶΪ-1 
            C->deci[i] = A->deci[i] + k + A->base - B->deci[i];
            k = -1;
        }
    }

    for (int i = 0; i <= max(A->length1, B->length1) - 1; i++) 
    {	// �������ּ�����һλһλ�� 
        if (A->inte[i] + k >= B->inte[i])
        {	// ����������Ϊ���� ��ֱ�Ӽ� 
            C->inte[i] = A->inte[i] + k - B->inte[i];
            k = 0;
        }
        else
        {	// �����λ������λ��ʶΪ-1 
            C->inte[i] = A->inte[i] + k + A->base - B->inte[i];
            k = -1;
        }
    }

    k = MAX - 1;
    for (; C->inte[k] == 0 && k > 0;)
        k--;					// �ƶ�k��λ�õ��������λ 
    C->length1 = k + 1;			// ��ֵ�������� 
    k = MAX - 1;
    for (; C->deci[k] == 0 && k > 0;)
        k--;					// �ƶ�k��λ�õ�С�����λ��ȥ�����0�� 
    C->length2 = k + 1;			// ��ֵС������ 
    C->negative = A->negative;	// ��������һ�� 
    return C;
}

num *SubOrder(num *A, num *B) 
{	// �ı�Ӽ�˳��ʹ�������ȷ��� 
    if (CompareAbs(A, B)) // ��A����ֵ����B ��A-B
        return SubAbs(A, B);
    else
        return SubAbs(B, A); // ����B-A
}

num *Add(num *A, num *B) 
{	// �ӷ� 
	num *C = initNUM();				// ��ʼ�� 
	
    if (A->negative == B->negative)
    {	// ������ͬ 
    	C = AddAbs(A, B);			// ����ֵ�ӷ� 
    	C->base = 10;				// ����Ϊ10 
    	return C;
	}

    else
    {	// ���Ų�ͬ 
    	C = SubOrder(A, B);			// ����ֵ���� 
    	C->base = 10;				// ����Ϊ10 
    	return C;
	}
}

num *Sub(num *A, num *B) 
{	// ���� 
	num *C = initNUM();				// ��ʼ�� 
	C = SubOrder(A, B);				// ��ȷ˳��ļ��� 
	
    if (A->negative != B->negative)
    {	// ���Ų�ͬ����þ���ֵ�ӷ� 
    	C = AddAbs(A, B);			// ����ֵ�ӷ� 
    	C->base = 10;				// ע����Ҫ�ѽ���Ҳ������� 
    	return C;
	}
    else if(!CompareAbs(A, B))
    {	// ����Ǹ��� 
    	C->negative = 1;			// ����Ϊ�� 
    	C->base = 10;				// ���Ʊ���10 
    	return C;
	}
    else
    {	// ��������� 
    	C->base = 10;				// ���Ʊ���10 
    	return C;
	}
}

// �洢��ʽΪ a[0]:���ֳ���len��a[MAX-1]:����λ��a[MAX-2]:����λ��
// ���ִӸ�λ����λ���洢��len..1 
char *output(int a[], int M, char str[])
{	// �����δ洢�ĸ߾�����ת��Ϊ�ַ��ʹ洢����� 
	int i, j, k = 0;		
	int strp = 0;			// str�ַ����ĵڼ����ַ� 
	if(a[M - 1] < 0)
	{	// ����λ���ж� 
		str[strp] = '-';
		strp ++;
	}
	 
	for(i = 1; i < a[0] - a[M - 2]; i ++)
	{	// ����С������û���õ�0
		if(a[i] == 0)
		{
			for(j = i + 1; j <= a[0]; j ++)
				a[j - 1] = a[j];
			a[0] --;
			i --; 			// ��ֹ�ƶ�������Ҳ��0 
		}
		else
			break;
	}
	
	for(i = a[0]; i > 1; i --)
	{	// ��������������Ч0 
		if(a[i] == 0 && a[M - 2] > 1)
		{
			a[0] --;
			a[M - 2] --;
		}		
		else
			break;
	}	
	
	for(i = a[0]; i >= 1; i --)
	{
		// k��¼�Ѿ������λ��
		if(k == a[M - 2])
		{	// �����С���㣬��¼��С���� 
			str[strp] = '.';
			strp ++;
		}
		str[strp] = a[i] + '0';			// ¼������ 
		strp ++;
		k ++;		
	}
	return str;
}

int allDigit(char *s) 
{	// �ж��ַ����Ƿ���Ա���ȷ��ȡ 
	int flag = 1;// ��־��ȡ���Ƿ��һ���ַ� 
	int pointFlag = 1; // ��־��ȡ����һ��С���� 
	while(*s) 
	{
		if(flag) 
		{	// ����ǵ�һ���ַ���������+����-
			flag = 0; 
			if(*s == '+' || *s == '-')
			{
				s ++;
				continue;
			}								
		}
		
		if(! (*s >= '0' && *s <= '9'))
		{	// ���������ַ��Ҳ��ǵ�һ��С���㣬return 0;
			if(*s == '.' && pointFlag == 1)
			{	// ֻ����һ��С����
				pointFlag = 0;				
			}
			else
				return 0;
		}
		s ++;		// �ж���һ���ַ� 
	}
	return 1;
}

void input(char s[],int p[])
{	// ���ַ������ŵĸ߾����������������������ڼ���˷� 
	int sign = 1;// ����λ 
	int len = strlen(s), i = 0, j, k;	// len��s�ĳ��� 
	 
	// ���s�е�һ���Ƿ��Ƿ��� 
	if(s[0] == '+')
	{
		i = 1;
		len --;			
	}
	if(s[0] == '-')
	{
		i = 1;
		len --;
		sign = -1;
	}		
	
	
	if(s[i] == '.')
	{	// ����С�����ڵ�һλ�����λ֮������
		// �磺+.12345��.12345 
		for(j = len + 1; j >= i; j --)		// ���� 
			s[j + 1] = s[j];

		s[i] = '0';							// ��.ǰ��0 
		len ++;
	} 
	
	j = i;
	
	while(s[j] && s[j] != '.')
		j ++;
	if(s[j])
		// ��С���� 
		len --;	 	
	p[MAX - 2] = j - i; // ����λ��
	
	while(s[i] == '0' && len > 1 && p[MAX - 2] > 1)
	{	// ��������λ֮������е���Ч0������Ҫ����С����ǰ��һ��0 
		i ++;
		len --;
		p[MAX - 2] --; 
	}	// ��ʱiΪ��һ����0�ַ����±꣬�ر�������Ϊ0����iΪ���һ��0���±� 
	 
	j = 0;
	
	for(; j < len; j ++)
	{	// ���������ַ�����洢��Ϊ��������洢 
		if(s[i] == '.')						// ����С���� 
			j --;
		else								//�洢 
			p[len - j] = s[i] - '0';
		i ++;		
	}
	
	p[0] = len;								// ��¼���� 
	p[MAX - 1] = sign;						// ��¼����λ 
} 

void multiply(int a[],int b[],int c[]) 
{	// c = a * b
	int i, j, k;
	
	// a,b�е�С��λ�� 
	int len1 = a[0] - a[MAX - 2];
	int len2 = b[0] - b[MAX - 2];
	
	// a,b�ķ���
	int signa = a[MAX - 1];      
	int signb = b[MAX - 1];	 
	
	c[0] = a[0] + b[0]; 					// ���ĳ��� 
	for(j = 1; j <= b[0]; j ++)
	{
		for(i = 1; i <= a[0]; i ++)			
			c[i + j - 1] += a[i] * b[j];	// �ȳ��꣬�ٴ����λ
		
		for(k = 1; k <= c[0]; k ++) 
			if(c[k] >= 10)
			{	// �����λ������������ 
				c[k + 1] += c[k] / 10;
				c[k] = c[k] % 10;
			}				
	}
	
	// ���������m + n - 1λ 
	if(c[c[0]] == 0) 
		c[0] --;
		
	// ������ķ���
	if(signa > 0 && signb > 0 || signa < 0 && signb < 0) 
		c[MAX - 1] = 1;
	else
		c[MAX - 1] = -1;
		 
	// ��������λ�� 
	c[MAX - 2] = c[0] - len1 - len2;
}

int main()
{
P:	printf("---------------------------------\n");
	printf("0.�˳�\n1.����ת������\n2.10����ת2����\n3.2����ת10����\n4.10����תN����\n");
	printf("5.10�������߾������Ӽ������㲢���10���ƺ�N���ƽ��\n6.����������ʽ\n");
	int flag;
	
	// ѡ���� 
	printf("��������ѡ���ܣ�");
	scanf("%d", &flag);
	printf("---------------------------------\n");
	
	// ��ʼ�������õ��Ľṹ��  
	num *A = initNUM();
	num *B = initNUM();
	num *C = initNUM();
	num *D = initNUM();
	num *E = initNUM();
	num *F = initNUM();
	
	switch(flag)
	{
		case(0):
		{
			break; 
		}
		case(1):
		{	// ����ת������ 
			int baseM, baseN;				// ��ʼ������������� 
			char str1[MAX];
			initCHAR(str1);					// ��ʼ���ַ��� 
			printf("�����ʼ���ƣ�");
			scanf("%d", &baseM);			// ��ʼ���� 
			
			printf("�����ʼ���֣�");
			scanf("%s", str1);				// ��ʼ���� 
			
			A = ReadFromString(str1, baseM);			// ��ʼ����д��ṹ�� 
			printf("�����%d��������Ϊ��", baseM);
			printnum(A);					// �����������ּ���ǰ���Ƿ����� 
			
			printf("������Ҫת���Ľ��ƣ�"); 
			scanf("%d", &baseN);			// ������� 
			printnum(baseConversion(A, baseN));			// ���ת�����ƺ������ 
			goto P;
		}
		
		case(2):
		{	// ʮ����ת������ 
			char str2[MAX];
			initCHAR(str2);					// ��ʼ���ַ��� 
			printf("����10�������֣�");
			scanf("%s", str2);				// ��ʼ���� 
			
			A = ReadFromString(str2, 10);	// д��ṹ�� 
			printf("�����10��������Ϊ��");
			printnum(A);					// ������������ 
			printf("ת��Ϊ2��������Ϊ��");
			printnum(baseConversion(A, 2));	// ���ת��Ϊ�����ƺ������ 
			goto P;
		}
		
		case(3):
		{	// ������תʮ���� 
			char str3[MAX];
			initCHAR(str3);					// ��ʼ���ַ��� 
			printf("����2�������֣�");
			scanf("%s", str3);				// ��ʼ���� 
			
			A = ReadFromString(str3, 2);	// д��ṹ�� 
			printf("�����2��������Ϊ��");
			printnum(A);					// ������������ 
			printf("ת��Ϊ10��������Ϊ��");
			printnum(baseConversion(A, 10));// ���ת��Ϊʮ���ƺ������ 
			goto P;
		}
		
		case(4):
		{	// ʮ����תN���� 
			char str4[MAX];
			initCHAR(str4);					// ��ʼ���ַ��� 
			int N;
			printf("����10�������֣�");
			scanf("%s", str4);				// ��ʼ���� 
			
			A = ReadFromString(str4, 10);	// д��ṹ�� 
			printf("�����10��������Ϊ��");
			printnum(A);					// ������������
			printf("������Ҫת�����Ľ��ƣ�");
			scanf("%d", &N); 				// ����ת����Ľ��� 
			printf("ת��Ϊ%d��������Ϊ��", N);
			printnum(baseConversion(A, N)); // ���ת��ΪN���ƺ������ 
			goto P;
		}
		
		case(5):
		{	// �߾������Ӽ���������������ת�� 
			char str5[MAX], str6[MAX], mulres[MAX];
			initCHAR(str5);
			initCHAR(str6);
			initCHAR(mulres);				// ��ʼ���ַ��� 
			
			int a[MAX] = {0}, b[MAX] = {0}, c[2 * MAX] = {0};
			
			int N;
			
			printf("��������a��\n");
			scanf("%s", str5);
			printf("��������b��\n");
			scanf("%s", str6);
			printf("�������N��\n");
			scanf("%d", &N);				// �������ֺͽ��� 
			
			// �˷�����
			input(str5, a);
			input(str6, b);					// �ַ���ת�������飬���ڳ˷� 
			multiply(a, b, c);				// �˷��������������c 
			printf("a * b���Ϊ��");
			output(c, MAX, mulres);			// �����ת��Ϊ�ַ��� 
			printf("%s\n", mulres);			// ������ 
			E = ReadFromString(mulres, 10);	// ���д��ṹ�� 
			 
			printf("%d���ƽ��Ϊ��", N); 
			printnum(baseConversion(E, N));	// N���ƽ�� 
			
			// �Ӽ����� 
			A = ReadFromString(str5, 10);
			B = ReadFromString(str6, 10);	//д��ṹ�� 
			
			C = Add(A, B);					// �ӷ����� 
			printf("a + b���Ϊ��");
			printnum(C);					// ������ 
			printf("%d���ƽ��Ϊ��", N);
			printnum(baseConversion(C, N));	// ���N���ƽ�� 
			
			D = Sub(A, B);					// �������� 
			printf("a - b���Ϊ��");
			printnum(D);					// ������ 
			printf("%d���ƽ��Ϊ��", N);
			printnum(baseConversion(D, N));	// ���N���ƽ�� 
			
			goto P;
		}
		
		case(6):
		{	// ����������ʽ���� 
			int term = 0, i, j;
			printf("����������");
			scanf("%d", &term);				// �������� 
			
			// ���ñ���������ĳ�ʼ�� 
			char coe[10][MAX];
			int coeint[10][MAX];
			int ind[10] = {0}, restmp[10][MAX] = {0}, res[10][MAX] = {0};
			char x[MAX], reschar[10][MAX];
			int xint[MAX] = {0}; 
			for(i = 0; i < 10; i ++)
			{
				initCHAR(coe[i]);
				initCHAR(reschar[i]);
			}
			initCHAR(x);
			
			// ����ʽ�Ķ��� 
			printf("����x��ֵ��"); 
			scanf("%s", x);					// ����x
			input(x, restmp[0]);
			input(x, xint); 				// xת��Ϊ��������洢 
			
			for(i = 0; i < term; i ++)
			{	// ����ϵ�� 
				printf("�����%d���ϵ����", i + 1);
				scanf("%s", coe[i]);
				input(coe[i], coeint[i]);
			}
				
			for(i = 0; i < term; i ++)
			{	//����ָ�� 
				printf("�����%d���ָ����", i + 1);
				scanf("%d", &ind[i]);
			}
			
			// ÿһ��ļ��� 
			for(i = 0; i < term; i ++)
			{	// ÿһ��ֱ���� 
				for(int k = 0; k < 10; k ++)
					initINT(restmp[k]);		// ÿһ�μ��㶼Ҫ���³�ʼ������������ 
				input(x, restmp[0]);		// ��xд����Ҫ���������� 
				if(ind[i] == 0)				
				{	// ���ָ����0��ֱ�����ϵ������ 
					output(coeint[i], MAX, reschar[i]);
				}
				else
				{	// ���� 
					for(j = 0; j < ind[i] - 1; j ++)
					{	// ��ͨ��ѭ������x���ݴ� 
						multiply(restmp[j], xint, restmp[j + 1]);
					}
					multiply(restmp[j], coeint[i], res[i]);		// ����ϵ����x�ݴεĳ˻� 
					output(res[i], MAX, reschar[i]);			// ���ÿһ��ļ����� 
				}
				printf("��%d����Ϊ��%s\n",i + 1, reschar[i]);
			}
			
			// ��������� 
			num *A = initNUM();
			num *RES = initNUM();
			num *TMP = initNUM();			// ��ʼ���ṹ�� 
			TMP = ReadFromString(reschar[0], 10);				// ���� 
			Copy(TMP, RES);					// ���ֻ��һ����ֱ������Ϳ� 
			for(i = 1; i < term; i ++)
			{	// �������һ�����ѭ�����мӷ� 
				RES = initNUM();
				A = initNUM();				// ÿһ�β�������Ҫ���³�ʼ���ϴβ����иı����ʧȥ���õı��� 
				A = ReadFromString(reschar[i], 10);
				RES = Add(TMP, A);			// ѭ�����ڵļӷ� 
				TMP = initNUM();			// ����ù����Ѿ����ʹ����TMP 
				Copy(RES, TMP);				// �ٰ�TMP��ֵΪ��һ�μӷ�����Ľ�� 
			}
			
			printf("����ʽ������Ϊ��");
			printnum(RES);					// ������ 

			goto P;
		}
	}
}
