#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    scanf("%d", &N);

    int courage_need[N];
    int courage_get[N];

    for(int i = 0; i < N; i ++)
    {
        int dragon_num = 0;
        scanf("%d", &dragon_num);
        int beatable = 0;
        int hp = 0;
        for(int j = 0; j < dragon_num; j ++)
        {
            scanf("%d", &hp);
            if(hp > beatable + j)
                beatable = hp - j + 1;
        }
        courage_need[i] = beatable;
        courage_get[i] = dragon_num;
    }
    
    // 排出所需勇气值最小的山洞顺序
    int pres = 0;
    for(int i = 1; i < N; i ++)
    {
        int need = courage_need[i];
        int get = courage_get[i];
        for(pres = i - 1; (pres >= 0) && (courage_need[pres] > need); pres --)
        {
            courage_need[pres + 1] = courage_need[pres];
            courage_get[pres + 1] = courage_get[pres];
        }
        courage_need[pres + 1] = need;
        courage_get[pres + 1] = get;
    }

    int courage_now = courage_need[0];
    int ans = courage_now;
    int lack = 0;

    // 按照顺序探索山洞，失败记录缺少的勇气值重新探索，成功则继续探索
    int j = 0;
    while(j < N)
    {
        for(j = 0; j < N; j ++)
        {
            if(courage_now >= courage_need[j])
                courage_now += courage_get[j];
            else
            {
                lack = courage_need[j]- courage_now ;
                if(j < N)
                {
                    courage_now = ans + lack;
                    ans = courage_now;
                }
                break;
            }
        }
    }
    
    printf("%d", ans);
    return 0;
}
