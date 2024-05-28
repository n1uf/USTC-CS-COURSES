#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *solution; 		// solution[col]=row,��ʾ��col�еĻʺ���row��
int len;			// ���̴�С���� 

int initSolution();
void restart();
void swap(int, int);
int traverseNeighbors();
int evaluate();

int main()
{
	srand(int(time(0)));	// ��ʱ����Ϊ������� 

	printf("������ʺ������");
	scanf("%d",&len);     	// ���̴�С 
	
	initSolution();			// ��ʼ��
	
	int flag = traverseNeighbors();
	
	while(flag != 0)		// ��ͻ����Ϊ0�����²����������� 
	{
		restart();
		flag = traverseNeighbors();
		if(flag)
			printf("��ͻ��Ϊ��%d����������\n",flag);
	}
	
	// �ҵ��⣬��ӡ�� 
	printf("�ҵ�һ��⣬��Ϊ��\n");
	for(int i = 0; i < len; i ++)
		printf("%d ",solution[i] + 1);
		
	free(solution);
	return 0;
}

// �������̵ĵ�i�к͵�j��
void swap(int i, int j)
{
	int temp = solution[i];
	solution[i] = solution[j];
	solution[j] = temp;
}


// ��ʼ������
int initSolution()
{
	solution = (int *)malloc(sizeof(int)*len);	// ����ռ�  
	if (!solution)  return 0; 
	// �������ʼ���ֻ����ĳ����ʼ����
	for(int i = 0; i < len; i ++)    
		solution[i]=i;
	for(int i = 0; i < len; i ++)	// �����̽����������
		swap(rand()%len, rand()%len);
}

// ��ǰ���̵ĳ�ͻ��value 
int evaluate()
{
	int value=0;
	for(int i = 0; i < len; i ++)
		for(int j = i + 1; j < len; j ++)
			if(solution[i] == solution[j] || abs(solution[i] - solution[j]) == abs(i - j))
				value ++;
	return value;
}



// ����ھ����̳�ͻ�����������滻
int traverseNeighbors()
{
	int min_value = evaluate();     // ��ǰ���̵������ھӵ���С���ۺ���ֵ 
	int col1 = -1, col2 = -1;		// ����ǰ�����±�ͽ���������±�  
	
    //�����ھӣ�����ÿ���ھӳ�ͻ�ʺ�Եĸ������ҵ���С��ͻ�������ھ�
	int i, j, value;
	for(i = 0; i < len; i ++)
	{
		for(j = i + 1; j < len; j ++)
		{
			swap(i, j);				// �õ��ھ� 
			value = evaluate();		// �ھӵĳ�ͻ�� 
			swap(i, j);				// ������ 
			if(value < min_value)	// ���������  
			{
				min_value = value;
				col1 = i; 
				col2 = j;
			}
		}
	}
	
    if (col1 == -1) 
	{  //������������е��ھӽڵ㣬Ҳ�Ҳ������õ��ƶ���ʽ����ô����Ҫ���������㷨����ʼ��ָı�һ��
    	printf("�Ҳ����⣬��������\n");
    	return -1;
    }
    swap(col1, col2);	// �ҵ����õ��ƶ���ʽ����ô��������ھӽ�����һ����ɽ
    return min_value;
}

void restart()
{	// ��������У��������� 
	int times = 10; 
	for(int i = 0; i < times; i ++)
		swap(rand()%len, rand()%len);
	printf("restart()������\n");
}

