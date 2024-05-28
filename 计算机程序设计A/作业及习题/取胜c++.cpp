#include <vector>
#include<iostream>
using namespace std;
class MethodOfWin
{
public:
   MethodOfWin(void);

   static pair<long,long> MaxAndMin(vector<int> M)
   {
    const int size_M = M.size();
    vector< vector<int> > A(size_M);
    vector< vector<int> > B(size_M);
    for(int i=0; i< size_M ; ++i)
    {
     A[i] =   vector<int>(size_M);
     B[i] =   vector<int>(size_M);
    }
    //≥ı ºªØ
    for(int i=0; i<size_M; ++i)
     for(int j=0; j<size_M; ++j)
     {
      A[i][i] = M[i];
      B[i][i] = 0;
     }

    for(int l=2; l<=size_M; ++l)
     for(int i=0;i<size_M-l+1;++i )
     {
      int k=i+l-1; 
      int temp_A1 = B[i][k-1] + M[k];
      int temp_B1 = A[i][k-1];
      int temp_A2 = M[i] + B[i+1][k];
      int temp_B2 = A[i+1][k];
      if(temp_A1>temp_A2)
      {
       A[i][k] = temp_A1;
       B[i][k] = temp_B1;
      }
      else{
         A[i][k] = temp_A2;
        B[i][k] = temp_B2;
          }
      }
    return make_pair(A[0][size_M-1], B[0][size_M-1]);
   }
public:
   virtual ~MethodOfWin(void);
};


int main(void)
{
vector<int> M(6);
M[0] = 4;
M[1] = 7;
M[2] = 2;
M[3] = 9;
M[4] = 5;
M[5] = 2;
pair<long,long> result = MethodOfWin::MaxAndMin(M);
cout<<result.first<<" "<<result.second<<endl;
return 1;
}
