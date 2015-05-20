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
		//printf("%d\n",values[i]);
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

    
	
	//printf("\n");
	/*printf("%d\n",index);
	for(i=0;i<index;i++)
	{
		printf("%d",number[i]);
	}

	printf("\n");*/

	/*This function removes all valueless 0s from the starting of the string*/
	int * unpad_zeroes1(int *array,int length)
	{
		int i = 0;
		int j=0;
		int k;
		int l = length;
		//string zero("0");
		while(array[i] == 0)
		{
			i++;
		}
		//printf("%d\n",i);
		k=i;
		for(j=0;j<(length-i);j++)
		{
			array[j] = array[k];
			//printf("%d",array[j]);
			k++;
		}
		//printf("\n");
		return array;
		//if(a.length() == 0)
		//{
		//	a = zero;
		//}
	}



	int unpad_zeroes(int *array,int length)
	{
		int i = 0;
		int j=0;
		int k;
		int l = length;
		//string zero("0");
		while(array[i] == 0)
		{
			i++;
		}
		return i;
		
		//if(a.length() == 0)
		//{
		//	a = zero;
		//}
	}
      
	/*int * div_by_two(int *array1,int index)
	{
		int a_length =index;
		int i = 0, digit = 0, carry = 0;
		static int c[1001] = {0}; //The result is stored in this new string c
		for(i = 0; i < a_length; i++)
		{
			digit = array1[i];
			c[i] =( digit + carry )/2; //Each digit is divided by 2
			if ( digit%2 == 1) // If the digit was odd it will have a carry over to the next digit
				carry = 10;
			else
				carry = 0;
		}
		unpad_zeroes(c,a_length);
		//return c;
	return c;
		for(i=0;i<index;i++)
		{
			printf("%d",c[i]);
		}
	printf("\n");
	}*/
	/*int * div_by_two(int *array1,int index)
	{
		int i=0;
		int *divide;
		divide=(int *)malloc(sizeof(int)*index);
		for(i=0;i<index;i++)
		{
			if(array1[i]%2==0)
			{	
				divide[i]=array1[i]/2;
				array1[i+1]=(array1[i]%2)*10 + array1[i+1];
			}
			else
			{
				divide[i]=array1[i]/2;
				array1[i+1]=(array1[i]%2)*10+array1[i+1];
			}


		for(i=0;i<index;i++)
		{
			printf("%d",divide[i]);
		}
	printf("\n");
	}
		return divide;
	}*/
	int div_by_two(int * array,int i,int length,int remain)
	{
		
		if(i==length)
			return remain;
		array[i]=(remain*10)+array[i];
		remain=array[i]%2;
		array[i]=array[i]/2;
		div_by_two(array,i+1,length,remain);
		
				

	}

	
	
	void pad(int *array1,int l)
	{
		while(l--)
		{
			int i=1;
			array1[i] = 0;
			i++;
		}
	}

	


	int * sub(int *array1,int *array2,int index)
	{
		int a_length = index, b_length = 1, borrow_from, i, j;
		static int c[1001] = {0}; 
		if(a_length > b_length)
		{
			pad(array2, a_length - b_length);
			j = b_length - 1;
			i = a_length - 1;
		}
		else if(a_length < b_length)
		{
			pad(array1 , b_length - a_length);
			j = a_length - 1;
			i = b_length - 1;
		}
		else
		{
			j = a_length - 1;
			i = j;
		}

		/*
		This method to compare strings works accurately only if they are of equal length.
		Hence we are padding them with zeroes if they are of unequal length
		*/
		//printf("%d\n",j);
		//printf("%d\n",i);
		//printf("%d\n",array1[1000]);
		//for(i=0;i<1000;i++)
		//{
		//	printf("%d",array2[i]);
		//}
		//printf("\n");
		//printf("\n");
		//i=0;
		unpad_zeroes(array1,index);
		unpad_zeroes(array2,1);
		for(j; j >= 0; j--)
		{
			if(array2[j] <= array1[i])
			{
				//This is the case where we dont have to borrow from the next digits
				c[j] = array1[i] - array2[j] ;
				//printf("%d\n",c[j]);
			}	
			else
			{
				//In this case we have to borrow
				borrow_from = i - 1;
				while(array1[borrow_from] == 0)
				{	
					//This loop gives us the first index from where we can borrow a digit
					borrow_from--;
				}
				array1[borrow_from++]--;
				printf("%d\n",borrow_from);
				while(borrow_from < i) array1[borrow_from++] = 9;
				c[j] = array1[i] - array2[j]; // After succesfully borrowing, we can now subtract the numbers
			}
			i--;
		}
		//printf("%d\n",i);
		if(i >= 0)
		{
			//In case the string a has more digits than b, then the remaining digits are appended in this loop
			while(i>=0)
			{
				c[i] = array1[i];
				i--;
			}
		}
	unpad_zeroes(c,index);
	/*for(i=0;i<index;i++)
		{
			printf("%d",c[i]);
		}
	printf("\n");*/
	
	return c;
	}

//sub(number,array1,index);
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
	
	
			l=div_by_two(number,0,index,0);
			printf("%d ",l);
			m=unpad_zeroes(number,index);
			printf("%d ",m);
			n=unpad_zeroes1(number,index);
			for(i=0;i<(index-m);i++)
			{
				printf("%d",n[i]);
			}
			printf("\n");
			index=index-m;		
	 		//n=div_by_two(n,index);
		      //n=n/2;
			
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
			//d=sub(n,array1,index);
			//for(i=0;i<1;i++)
			//	printf("%d",d[i]);
			//printf("\n");
	            matpow(Z,n,result,M,index);
	      	fib=(result[2][0]*values[2] + result[2][1]*values[1] + result[2][2]*values[0])%1000;    
	    	}	
	    	
	      
	         
	      return fib;
	}
	long long x;
	//scanf("%lld",&x);
	//for(i=0;i<index;i++)
	//{
	//	printf("%d",number[i]);
	//}
	//printf("\n");
	printf("%lld\n",findFibonacci(number,1000,index));
	return 0;
}
			
