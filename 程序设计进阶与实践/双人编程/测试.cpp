#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
FILE *fp = fopen("way.out", "r");

int main()
{
	int flag = 0; 
	//���ݴ��� 
	int n = 200;
	char letter[7];
	int sex[200], id[200], group[40], groupscale[40];
	int chinese[200], math[200], english[200], science[200], total[200];
	int i, j = 0;
	for(i = 0; i < 200; i ++)
	{
		sex[i] = -1;
	}
	i = 0;
	while(1)
	{
		groupscale[i] = 0;
		fscanf(fp, "%s", letter);
		group[i] = i + 1;
		while(1)
		{
			fscanf(fp, "%d", &sex[j]);
			if(sex[j] == 0 || sex[j] == 1)
			{
				fscanf(fp, "%d %d %d %d %d %d", &id[j], &chinese[j], &math[j], &english[j], &science[j], &total[j]);
				printf("%d %d %d %d %d %d %d\n", sex[j], id[j], chinese[j], math[j], english[j], science[j], total[j]);
			}
			else
			{
				break;
			}
			j ++;
			groupscale[i] ++;
		}
		if(groupscale[i] == 0)
		{
			break;
		}
		printf("�� %d �����Ա�� %d ��\n\n", group[i], groupscale[i]);
		i ++;
	}
	
	printf("���� %d ���飬һ���� %d λͬѧ\n\n", i, j); 
	//printf("\n%d\n", i);
	
	
	//������Ů�����Ƿ����Ҫ�� 
	float sexrate[40];
	int k, scale = 0;
	j = 0;
	for(k = 0; k < i; k ++)
	{
		scale += groupscale[k];
		for(; j < scale; j ++)
		{
			sexrate[k] += sex[j];
		}
		sexrate[k] /= groupscale[k];
		printf("�� %d �������ռ��Ϊ %.2f%% \n", k + 1, sexrate[k] * 100.0);
		
		//������Ҫ������ 
		if(sexrate[k] >= 0.7 || sexrate[k] <= 0.3)
		{
			printf("��%d����Ů����������Ҫ��\n", k + 1);
			break;
		}
	}
	
	//������Ҫ�� 
	if(k == i)
	{
		flag ++;
		printf("��Ů���������ϣ�������Ҫ��\n\n");
	}
	
	
	//���С������Ƿ����Ҫ��
	float Average = 0;
	for(j = 0; j < 200; j ++)
	{
		Average += total[j];
	}
	Average /= j;
	printf("�ܾ���Ϊ%.2f\n\n", Average);
	float average[40];
	scale = 0, j = 0;
	for(k = 0; k < i; k ++)
	{
		scale += groupscale[k];
		for(; j < scale; j ++)
		{
			average[k] += total[j];
		}
		average[k] /= groupscale[k];
		printf("��%d���ƽ����Ϊ%.2f\n", k + 1, average[k]);
		if(fabs(Average - average[k]) > 35.0)
		{
			printf("��%d���ƽ���ֲ���Ҫ��\n", k + 1);
			break;
		}
	}
	
	//������ 
	if(k == i)
	{
		flag ++;
		printf("����ƽ���ּ����ϣ�������Ҫ��\n\n");
	}
	
	if(flag == 2)
	{
		printf("����������Ҫ��");
	}
}
