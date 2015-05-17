#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(int argc,char *argv[])
{

	int index,k,string_length,Product,New_product,i,j;
	int number[1001]={0};
	char string_digit[200];
	int a;
	FILE *f_read;
    	int values[3];
    	index=0;
    	f_read=fopen(argv[1],"r");
	for(i=0;i<3;i++)
	{
		fscanf(f_read,"%d",&values[i]);
		printf("%d\n",values[i]);
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

    
	for(i=0;i<index;i++)
	{
		printf("%d",number[i]);
	}
	
	printf("\n");
	printf("%d\n",index);




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
	                		//c[i][j]=c[i][j]%M;
	            	}
				c[i][j]=c[i][j]%M;
	        	}
	    	}
	 
	}
	
	
	void matpow(long long Z[][3],int n,long long ans[][3],long long M)
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
	    	while(n>0)
	    	{
	      	if(n&1)
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
	 
	 
		      n=n/2;
	    	}
	    	return;
	}
	
	long long findFibonacci(long long n,long long M)
	{
	     
		long long fib;
	      if(n>2)
	   	{
	      	long long int Z[3][3]={{1,1,1},{1,0,0},{0,1,0}},result[3][3];
	            matpow(Z,n-2,result,M);
	      	fib=(result[0][0]*values[2] + result[0][1]*values[1] + result[0][2]*values[0])%1000;    
	    	}	
	    	else if(n==2)
	      	fib=values[2];
	      else if(n==1)
			fib=values[1];
	      else
			fib=values[0];
	         
	      return fib;
	}
	//long long x;
	//scanf("%lld",&x);
	printf("%lld\n",findFibonacci(4,1000));
	return 0;
}
			
