#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
FILE *fp = fopen("way.out", "r");

int main()
{
	int flag = 0; 
	//数据处理 
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
		printf("第 %d 组的组员有 %d 个\n\n", group[i], groupscale[i]);
		i ++;
	}
	
	printf("分了 %d 个组，一共有 %d 位同学\n\n", i, j); 
	//printf("\n%d\n", i);
	
	
	//检验男女比例是否符合要求 
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
		printf("第 %d 组的男生占比为 %.2f%% \n", k + 1, sexrate[k] * 100.0);
		
		//不符合要求的情况 
		if(sexrate[k] >= 0.7 || sexrate[k] <= 0.3)
		{
			printf("第%d组男女比例不符合要求\n", k + 1);
			break;
		}
	}
	
	//都符合要求 
	if(k == i)
	{
		flag ++;
		printf("男女比例检查完毕，都符合要求\n\n");
	}
	
	
	//检查小组均分是否符合要求
	float Average = 0;
	for(j = 0; j < 200; j ++)
	{
		Average += total[j];
	}
	Average /= j;
	printf("总均分为%.2f\n\n", Average);
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
		printf("第%d组的平均分为%.2f\n", k + 1, average[k]);
		if(fabs(Average - average[k]) > 35.0)
		{
			printf("第%d组的平均分不合要求\n", k + 1);
			break;
		}
	}
	
	//都符合 
	if(k == i)
	{
		flag ++;
		printf("各组平均分检查完毕，均符合要求\n\n");
	}
	
	if(flag == 2)
	{
		printf("分组程序符合要求");
	}
}
