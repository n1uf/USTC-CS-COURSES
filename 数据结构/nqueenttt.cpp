#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
#define SIZE 20000
#define swap(a,b) {int t = a; a = b; b = t;}
 
int s[SIZE]={0};
//int row[1000]={0};//row[i]��ʾ��i���м����ʺ�
int row[SIZE]={0};
int col[SIZE]={0};//col[i]��ʾ��i���м����ʺ� 
//pdiag[i]��ʾ��i�����Խ��ߣ�principal diagonal���ʺ�����������ϵ����µ��ߣ� 
int pdiag[SIZE*2-1]={0};
//pdiag[i]��ʾ��i�����Խ��ߣ�counter diagonal���ʺ�����������ϵ����µ��ߣ� 
int cdiag[SIZE*2-1]={0};

//��ӡ����
void  print(int s[])
  {  
      printf("\n");
      for(int i=0;i<SIZE;i++) {
          for (int j = 0; j < SIZE; j++)
              if(s[i]==j) printf("�� ");
              else printf("�� ");
          printf("\n");
      }
  }
//�������һ����start��end��������end��������x��������� 
int myRandom(int start=0,int end=100,int x=0)
{
	srand((unsigned)time(NULL)+x);
	return rand()%(end-start); 
}
  //������ɻʺ�,�������ɵĳ�ͻֵ�Ƚ�С��x�������ɲ�ͬ������
 void randomQueen(int s[],unsigned x=0)
  {
  	  for(int i=0;i<SIZE;i++)
           s[i]=myRandom(0,SIZE,i+x);
  }
  
   int  heuristic(int s[])
  {
  	 //���¶��С��������Խ�����0
	  memset(row,0,sizeof(col)); 
  	  memset(col,0,sizeof(col));
  	  memset(pdiag,0,sizeof(pdiag));
  	  memset(cdiag,0,sizeof(cdiag));
      int h=0;
      int s2=2*SIZE;
	  for(int i=0;i<SIZE;i++)  
	  {
	  	 col[s[i]]++;
	  	// row[i]++;
	  	 //��(��)�Խ���������2*size,sizeΪ�ʺ��ܸ���
		 //���Խ��߱�ţ������Ͻ�Ϊ0�������½�Ϊ2*size-1
		 //����֤���Խ����ϵ�����pֵ����һ������Ϊ���涨��ı�� 
	  	 //int p=i - s[i] + SIZE - 1; 
	  	 pdiag[i - s[i] + SIZE - 1]++;
	  	 //pΪ���Խ��߱�� 
	  	 //p=i+s[i];
	  	 cdiag[i+s[i]]++; 
	  }  
	  for(int i=0;i<s2;i++)
	  {
	    if(i<SIZE)	
		{
	    	h+=(col[i]-1)*col[i]*0.5;
	    	//h+=(row[i]-1)*row[i]*0.5;
		}
		h+=pdiag[i]*(pdiag[i]-1)*0.5;
		h+=cdiag[i]*(cdiag[i]-1)*0.5;
	 }
      return  h;
   }
   
   //����row1���е����лʺ��������col1�У�Ȼ�����������ֵ
//hΪ��������ֵ 
int adjust(int s[],int row1,int col1,int h)
{
	//��������ֵ 
	int nowCol=s[row1];//���ڵ�row1�лʺ�������λ�� 
	h+=(col[col1]-col[nowCol]+1);
	//���Խ���������ֵ 
	h+=(pdiag[row1-col1+SIZE-1]-pdiag[row1-nowCol+SIZE-1]+1);
	//���Խ���������ֵ  
	h+=(cdiag[row1+col1]-cdiag[row1+nowCol]+1); 
	return h;
}

//���ܵ�row1�еĻʺ��ƶ���col1��
void accept(int s[],int row1,int col1)
{
	col[s[row1]]--;
	pdiag[row1-s[row1]+SIZE-1]--;
	cdiag[row1+s[row1]]--;
	s[row1]=col1;
	col[col1]++;
	pdiag[row1-col1+SIZE-1]++;
	cdiag[row1+col1]++;
}

int findTwo(int s[])
{
    int col0,col2,flag=0;
    int row0,row2;
    for(int i=0;i<SIZE;i++)
    {
    	//Ϊ0��ʾĳ��û�лʺ� 
    	if(col[i]==0) {col0=i;flag++;}
    	//Ϊ2��ʾĳ����2���ʺ� 
    	if(col[i]==2) {col2=i;flag++;}
    	if(flag==2) break;
	}
	flag=0; 
    for(int i=0;i<SIZE;i++)
      if(s[i]==col2) 
	  {
		flag++;
		//���Ž�2���ʺ������һ���ʺ������û�лʺ���У�col0�� 
		//������ʱ��������i�У�col0��,����Խ�����1���ʺ���Ȼ���� 
		if(pdiag[i-col0+SIZE-1]==0 && cdiag[i+col0]==0)
		{
		   s[i]=col0;
		   printf("\n�ɹ���\n");
		   return 1;
		}
		if(flag==2) return 0;
	} 	
	return 0;
}

void exchange(int s[],int c)
{
   int r1,r2,r3,r4,k1=0,k2=1;
   do
   {
   	 srand((unsigned)time(NULL)+k1);
   	 r1=rand()%(SIZE);
   	 r2=rand()%(SIZE);
   	 k1++;
   }while(r1==r2);
   swap(s[r1],r2);
   do
   {
   	 srand((unsigned)time(NULL)+c+k2);
   	 r3=rand()%(SIZE);
   	 r4=rand()%(SIZE);
   	 k2++;
   }while(r3==r4);
   swap(s[r3],r4);
}

int hillClimbing(int s[])
   {
       int h=heuristic(s);
       int curr=h;//��ǰ��������
       int min=h;//��С����
       int lastMin=h;//��һ����С����
       //�����⼸�����Ǽ�����
       //int counter=0;//��������ѡ��һ�����ڵ�ǰ��״̬�ĺ��
       int c=0;//�����ִ�
       int cc=0;//��������
       int k=0;//û����
       while (1)
       {
       	   //counter=0;
       	   c++;
       	   int flag=0;
           int minValue=s[0],minLine=0;//�ֱ�Ϊ��������Сʱ�Ļʺ���кš��к�
           for(int i=0;i<SIZE;i++) //��i�� 
           {
              for(int j=0;j<SIZE;j++)//��i�лʺ�ŵ�j���� 
              {
                 if(j!=s[i]) //s[i]Ϊ��i�лʺ���к� 
                 {
                   //��ʱ����������i�еĻʺ���ڵ�j���ϣ���������ֵ 
                    h=adjust(s,i,j,curr);
                    //counter++;
                    if(h<=min)
                     {
                       minLine=i;
                       minValue=j;
                       accept(s,i,j);
                       min=h;
                     } 
                    if(h==0 || h==1) //���⴦��
                    {
                    	flag=1;
                    	break;
					}
                 }
             }  
             if(flag==1) break;
           }
           //printf("%d ",min);
           if(min==0)  //����Ϊ0����ʾ���ҵ�һ��N�ʺ������
		   {  
		    	printf("\n����������%d\n",c);
		    	printf("\n�������������%d\n",cc); 
		 	    s[minLine]=minValue;
		 	    return c;
		    }
		   else if(min==1) //��findTwo�����ֹ�����
		   {
		 	   accept(s,minLine,minValue); 	
               if(findTwo(s)) 
               {
            	 printf("\n����������%d\n",c);
		 	     printf("\n�������������%d\n",cc); 
		 	     return c;
			   }
			   else //����ʧ�ܣ���������������󷨣�����
			   {
				  cc++;
				  exchange(s,c);
		 	      curr=heuristic(s);
		 	      lastMin=curr;
		 	      min=curr;
			   }
		    }
            else if(min==lastMin) //����ֲ�ɽ�壬�޷�ǰ����ֻ�����������
		    {
		 	   s[minLine]=minValue;
		 	   if(k==1) //������
		 	   {
		 	     cc++;
		 	     exchange(s,c);
		 	     curr=heuristic(s);
		 	     lastMin=curr;
		 	     min=curr;
				 k=0;	
			   }
			   k++;
		    }
		    else
		    {
              accept(s,minLine,minValue);
		      curr=min;
		      lastMin=min;
		    } 
	  }
  }
  
  //��ǰ���и����ų���SIZE��ʾ�ʺ�ĸ��������޸���������ͬ�ʺ�������ѵ�ʱ��
 int main(int argc,char *argv[]) {
        //int s[SIZE]={4,5,6,3,4,5,6,5};
        //int s[SIZE]={2,0,6,3,1,4,7,5};
	    randomQueen(s,SIZE);
	    printf("��ʼ��С:%d\n",heuristic(s));
        printf("\n������%d\n",hillClimbing(s));
        printf("������С��%d\n",heuristic(s));    
        return 0; 
    }
