#include<iostream>
#include<algorithm>
using namespace std;
 
int get_pos(const int* a, int x, int n)
{
    for(int i=x;i<n;i++)    
    {
        if( a[i] == n - x ) return i;
    }
}
 
int run(const int * array, int n)
{
    int a[200]={0};
    for(int i=0;i<n;i++)
        a[i] = array[i];
    int count = 0;
    int pos = 0;
    
    for( int i=0;i<n;i++ )    
    {
        //????????????? 
        if( i+1 == a[i] )  continue;
        else
        {
            //???????????????(??) 
            pos = get_pos(a,i+1,n);
            swap( a[i],a[pos] );
            count++;
        }      
    }
    return count;
}
 
int main()
{
	int i,n;
	scanf("%d",&n);
	int a[n];
    for(i = 0; i < n; i ++)
    {
    	scanf("%f", &a[i]);
	}
	int b = run(a, n);
	printf("%d",b);
	return 0;
}
