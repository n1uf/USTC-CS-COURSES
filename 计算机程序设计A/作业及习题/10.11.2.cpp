#include<stdio.h>
int main()
{
 int year, month, day;
 while (scanf("%d %d %d", &year, &month, &day) != EOF)
 {
  if (month == 1 || month == 2)//??month???1?2 
   year--, month += 12;
  int c = year / 100;
  int y = year - c * 100;
  int week = y + y / 4 + c / 4 - 2 * c + 26 * (month + 1) / 10 + day - 1;
  while (week < 0)
   week += 7;
  week %= 7;
  switch (week)
  {
  case 1:printf("Monday\n"); break;
  case 2:printf("Tuesday\n"); break;
  case 3:printf("Wednesday\n"); break;
  case 4:printf("Thursday\n"); break;
  case 5:printf("Friday\n"); break;
  case 6:printf("Saturday\n"); break;
  case 0:printf("Sunday\n"); break;
  }
 }
 return 0;
}
