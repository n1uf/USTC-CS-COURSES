//�Ҳ���ʲô����
#include <conio.h>
#include <iostream>
#include <iomanip>
int main()
{
using namespace std;
float f;
cin>>f;
cout<<setiosflags(ios::uppercase)<<hex<<reinterpret_cast<int&>(f);
getch();
}
