#include <stdio.h>
void array_swap(int a[], int n, int k) {
int t[30],i;
for (i=0; i<k; i++) t[i]=a[i];
for (i=k; i<n; i++) a[i-k]=a[i];
for (i=0; i<k; i++) a[n-k+i]=t[k];
}
int main() {
int a[]={1,2,3,4,5,6,7,8,9};
int i, n=9, k=3;
for (i=0; i<n; i++) printf("%3d",a[i]);
printf("\n");
array_swap(a,n,k);
for (i=0; i<n; i++) printf("%3d",a[i]);
printf("\n");
return 0;
}
