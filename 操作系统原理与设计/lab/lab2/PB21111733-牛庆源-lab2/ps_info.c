#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<stdlib.h>

int main(void)
{
	int pid_ls[100];
	long long lstime[100];	// 上一任务的开始时刻
	long long stime[100];	// 当前任务的开始时刻
	char comm[1600];		// 指令
	int isrun[100];			// 运行与否
	double cpuo[100];		// cpu占用率
	double nstime[100];		// 持续时间
	int i;
	int k;
	while (1)
	{
		syscall(333, pid_ls, comm, isrun, stime);// 系统调用，传参
		printf("PID\tCOMM\t\tISRUNNING\t%%CPU\tTIME\n");
		for (i = 0; i < 100; i++)	// init
		{
			nstime[i] = (double)stime[i]/(double)10000000;
			cpuo[i] = (double)(stime[i]-lstime[i])/(double)10000000;	// ns为10的-9次，cpu按照百分比计算所以10的-7次
			lstime[i] = stime[i];
		}
		for (i = 0; i < 100; i++)
		{	// 排序
			int j;
			for (j = i+1; j < 100; j++)
			{
				if (cpuo[i]<cpuo[j])
				{
					double temp1;
					int temp2;
					char temp3;
				
					temp2 = pid_ls[i];
					pid_ls[i] = pid_ls[j];
					pid_ls[j] = temp2;
				
					temp2 = lstime[i];
					lstime[i] = lstime[j];
					lstime[j] = temp2;
				
					temp2 = isrun[i];
					isrun[i] = isrun[j];
					isrun[j] = temp2;
				
					temp1 = cpuo[i];
					cpuo[i] = cpuo[j];
					cpuo[j] = temp1;
					
					temp1 = nstime[i];
					nstime[i] = nstime[j];
					nstime[j] = temp1;
				
					int k;
					for (k = 0;k < 16;k++)
					{
						temp3 = comm[16*i+k];
						comm[16*i+k] = comm[16*j+k];
						comm[16*j+k] = temp3;
					}
				}
			}
		}
		k = 20;
		for (i = 0; i < k; i++)
		{	// 排除自己
			if(pid_ls[i] == 1)
			{
				k = 21;
				continue;
			}
			else
			{	// 输出
				int j;
				printf("%d\t",pid_ls[i]);
				for (j = 0; j < 16; j++)
				{
					printf("%c",comm[i * 16 + j]);
				}
				printf("%d\t\t",isrun[i]);
				printf("%.2lf\t%.2lf",cpuo[i],nstime[i]);
				printf("\n");
			}
		}
		sleep(1);	// 等待1s再刷新
		system("clear");
	}
	return 0;
}