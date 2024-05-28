#include <stdio.h>
int main()
{
    char str1[500] = {0};
    char str2[500] = {0};
    int i = 0,j = 0,flag = 0,pos = -1;
    gets(str1);
    gets(str2);
    for (i = 0;str1[i] != '\0';i++)
    {
        if (str1[i] == str2[0])
        {
            flag = 0;
            for (j = 0;str2[j] != '\0' && str1[i+j] != '\0';j++)
            {
                if (str1[i+j] != str2[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                pos = i;
                break;
            }
        }
    }
    if (pos != -1) printf("%d",pos);
    return 0;
}
