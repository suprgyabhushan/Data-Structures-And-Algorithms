#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(int argc,char *argv[])
{

	int index,k,string_length,Product,New_product,i,j;
	int number[1001]={0};
	int array1[1001]={0};
	int number1[1001]={0};
	array1[0]=2;
	char string_digit[200];
	int a;
	FILE *f_read;
    	int values[3];
    	index=0;
    	f_read=fopen(argv[1],"r");
	for(i=0;i<3;i++)
	{
		fscanf(f_read,"%d",&values[i]);
	}

    	while(fscanf(f_read,"%s",string_digit)==1)
	{
		string_length=strlen(string_digit);
      	for(k=0;k<string_length;k++)
		{
			number[index]=string_digit[k]-48;
			index++;
		}
    	}
    	fclose(f_read);    
	
	int * unpad_zeroes1(int *array,int length)
	{
		int i = 0;
		int j=0;
		int k;
		int l = length;
		while(array[i] == 0)
		{
			i++;
		}
		k=i;
		for(j=0;j<(length-i);j++)
		{
			array[j] = array[k];
			k++;
		}
		return array;
	}



	int unpad_zeroes(int *array,int length)
	{
		int i = 0;
		int j=0;
		int k;
		int l = length;
		while(array[i] == 0)
		{
			i++;
		}
		return i;
		
	}
      
	int div_by_two(int * array,int i,int length,int remain)
	{
		
		if(i==length)
			return remain;
		array[i]=(remain*10)+array[i];
		remain=array[i]%2;
		array[i]=array[i]/2;
		div_by_two(array,i+1,length,remain);
	}	
	
	void matmult(long long  a[][3],long long  b[][3],long long c[][3],long long M)
	{
		int i,j,k;
		for(i=0;i<3;i++)
	    	{
	      	for(j=0;j<3;j++)
	      	{
	            	c[i][j]=0;
	            	for(k=0;k<3;k++)
	            	{
	            		c[i][j]+=(a[i][k]*b[k][j]);
	                		c[i][j]=c[i][j]%M;
	            	}
	        	}
	    	}
	 
	}	
	
	void matpow(long long Z[][3],int *n,long long ans[][3],long long M,int index)
	{
		 
		long long temp[3][3];
    	
		ans[0][0]=1;
	    	ans[0][2]=0;
	    	ans[1][0]=0;
	    	ans[0][1]=0;
	    	ans[1][1]=1;
	    	ans[1][2]=0;
	    	ans[2][0]=0;
	    	ans[2][1]=0;
	    	ans[2][2]=1;
	    	int i,j;
	    	while(n[0]>0)
	    	{
	      	if(n[index-1]&1)
	            {
	            	matmult(ans,Z,temp,M);
	            	for(i=0;i<3;i++)
		                  for(j=0;j<3;j++)
			                  ans[i][j]=temp[i][j];
	        	}
	        	matmult(Z,Z,temp,M);
	        	for(i=0;i<3;i++)
	            	for(j=0;j<3;j++)
	                		Z[i][j]=temp[i][j];
			int l,m;	
			l=div_by_two(n,0,index,0);
			m=unpad_zeroes(n,index);
			n=unpad_zeroes1(n,index);
			index=index-m;		
	 	}
	    	return;
	}
	
	long long findFibonacci(int *n,long long M,int index)
	{
	     
		long long fib;
		int *d;

		if((n[0]==2)&&(index==1))
	      	fib=values[2];
	      else if((n[0]==1)&&(index==1))
			fib=values[1];
		else if((n[0]==0)&&(index==1))
			fib=values[0];
	      else
	   	{
	      	long long int Z[3][3]={{1,1,1},{1,0,0},{0,1,0}},result[3][3];
			matpow(Z,n,result,M,index);
	      	fib=(result[2][0]*values[2] + result[2][1]*values[1] + result[2][2]*values[0])%1000;    
	    	}	         
	      return fib;
	}
	long long x;
	printf("%lld\n",findFibonacci(number,1000,index));
	return 0;
}
			
