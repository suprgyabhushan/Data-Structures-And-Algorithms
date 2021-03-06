#include<stdio.h>
#define MAXSIZE 1000000     

long A[MAXSIZE];
long seg[MAXSIZE];
     

void build(int t,int i,int j)
{
    
    if(i==j)
    {
    	seg[t] = A[i];
    	return;
    }
    
    int left = t<<1,right=left|1,mid=(i+j)>>1;	
   
    build(left,i,mid);    
    build(right,mid+1,j);
    
    seg[t]=seg[left]+seg[right];
}
     

void update(int t,int i,int j,int k,long x)
{
    
    if(i==j)
    {
    	if(i==k)
    		seg[t] = x;
      return;
    }
    int left = t<<1,right=left|1,mid=(i+j)>>1;
    
    if(k<=mid)
    	update(left,i,mid,k,x);
    
    else
    	update(right,mid+1,j,k,x);
    
    seg[t]=seg[left]+seg[right];
}
     

long query(int t,int i,int j,int ri,int rj)
{
   
    if(j<ri || i>rj)
    	return 0;
   
    if(ri<=i && rj>=j)
    	return seg[t];

    int left = t<<1,right=left|1,mid=(i+j)>>1;
    
    return query(left,i,mid,ri,rj) + query(right,mid+1,j,ri,rj);
}

     
int main(int argc,char *argv[]) 
{
    int N,Q,L,R,k,O,i,j;
    
    FILE *input;
    input=fopen(argv[1],"r");
    long x;
    fscanf(input,"%d",&N);
    fscanf(input,"%d",&Q);
    for(i=1;i<=N;i++)
    {
    	fscanf(input,"%d",&j);
    	fscanf(input,"%ld",&A[i]);	
    }
  
    build(1,1,N);
   
    while(Q>0)
    {    	
	fscanf(input,"%d",&O);
    	if(O==1)
	{
    		fscanf(input,"%d%d",&L,&R);    		
    		printf("%ld\n",query(1,1,N,L+1,R+1));
    	}
    	else if(O==0)
	{
	      fscanf(input,"%d%ld",&k,&x);            
            update(1,1,N,k+1,x);
      }
	Q=Q-1;
    }
    return 0;
}
