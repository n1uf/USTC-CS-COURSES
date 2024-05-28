#include <stdio.h>
#include <stdlib.h>
#include <time.h>
FILE *fp = fopen("test.out", "r");
FILE *fp2 = fopen("way.out", "w");
int n, people[50], number[300], sex[300], chinese[300], math[300];
int english[300], science[300], total[300], group[50][7], used[300], groupnum;
void create()
{
    int i, j, num;
    for (i = 0; i < groupnum; i++)
    {
        j = 0;
        while (j < 2)
        {
            num = 1 + rand() % n;
            if (used[num] == 0 && sex[num] == 1)
            {
                group[i][j] = num;
                used[num] = 1;
                j++;
            }
        }
        while (j < 4)
        {
            num = 1 + rand() % n;
            if (used[num] == 0 && sex[num] == 0)
            {
                group[i][j] = num;
                used[num] = 1;
                j++;
            }
        }
        while (j < 5)
        {
            num = 1 + rand() % n;
            if (used[num] == 0)
            {
                group[i][j] = num;
                used[num] = 1;
                j++;
            }
        }
    }
    for (i = 0; i < groupnum; i++)
    {
        people[i] = 5;
    }
    i = 0;
    for (j = 0; j < n; j++)
    {
        if (used[j + 1] == 0)
        {
            group[i][5] = j;
            people[i]++;
            i++;
        }
    }
}
void aver(int round)
{
    int i, j, totalscore[50], mark[50], k1, k2;
    double average;
    average = 0;
    for (i = 1; i <= n; i++)
    {
        average = average + total[i];
    }
    average = average / n;
    for (i = 0; i < groupnum; i++)
    {
        j = 0;
        totalscore[i] = 0;
        mark[i] = 0;
        while (group[i][j] != 0)
        {
            totalscore[i] = totalscore[i] + total[group[i][j]];
            j++;
        }
        if (totalscore[i] / j > average + 20)
        {
            mark[i] = 1;
        }
        if (totalscore[i] / j < average - 20)
        {
            mark[i] = 2;
        }
    }
    for (i = 1; i < groupnum - 1; i++)
    {
        for (j = 1; j < groupnum; j++)
        {
            if (mark[i] == 1 && mark[j] == 2)
            {
                for (k1 = 0; k1 < people[i]; k1++)
                {
                    int nummax = 0, nummaxk = 0;
                    if (nummax < total[group[i][k1]])
                    {
                        nummax = total[group[i][k1]];
                        nummaxk = k1;
                    }
                }
                for (k2 = 0; k2 < people[j]; k2++)
                {
                    int nummin = 0, nummink = 0;
                    if (nummin > total[group[j][k2]])
                    {
                        nummin = total[group[j][k2]];
                        nummink = k2;
                    }
                }
                int temp;
                temp = group[i][k1];
                group[i][k1] = group[j][k2];
                group[j][k2] = temp;
                totalscore[i] = totalscore[i] + total[group[i][k1]] - total[group[j][k2]];
                totalscore[j] = totalscore[j] - total[group[i][k1]] + total[group[j][k2]];
                mark[i] = 0;
                mark[j] = 0;
            }
            if (mark[i] == 2 && mark[j] == 1)
            {
                for (k1 = 0; k1 < people[j]; k1++)
                {
                    int nummax = 0, nummaxk = 0;
                    if (nummax < total[group[j][k1]])
                    {
                        nummax = total[group[j][k1]];
                        nummaxk = k1;
                    }
                }
                for (k2 = 0; k2 < people[i]; k2++)
                {
                    int nummin = 0, nummink = 0;
                    if (nummin > total[group[i][k2]])
                    {
                        nummin = total[group[i][k2]];
                        nummink = k2;
                    }
                }
                int temp;
                temp = group[j][k1];
                group[j][k1] = group[i][k2];
                group[i][k2] = temp;
                totalscore[i] = totalscore[i] + total[group[i][k2]] - total[group[j][k1]];
                totalscore[j] = totalscore[j] - total[group[i][k2]] + total[group[j][k1]];
                mark[i] = 0;
                mark[j] = 0;
            }
        }
    }
}
int main()
{
    int i, j, num;
    srand((unsigned)time(NULL));
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; i++)
    {
        used[i + 1] = 0;
        fscanf(fp, "%d", &number[i]);
        num = number[i] % 1000;
        fscanf(fp, "%d %d %d %d %d %d", &sex[num], &chinese[num], &math[num], &english[num], &science[num], &total[num]);
    }
    groupnum = n / 5 - 2;
    create();
    aver(10);
    num = number[0] / 1000;
    for (i = 0; i < groupnum; i++)
    {
        fprintf(fp2, "group%d\n", i);
        for (j = 0; j < people[i]; j++)
        {
            fprintf(fp2, "%d    ", sex[group[i][j]]);
            fprintf(fp2, "%d    ", num * 1000 + group[i][j]);
            fprintf(fp2, "%d    ", chinese[group[i][j]]);
            fprintf(fp2, "%d    ", math[group[i][j]]);
            fprintf(fp2, "%d    ", english[group[i][j]]);
            fprintf(fp2, "%d    ", science[group[i][j]]);
            fprintf(fp2, "%d", total[group[i][j]]);
            fprintf(fp2, "\n");
        }
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}