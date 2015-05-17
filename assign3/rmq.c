#include<stdio.h>
#define MAXSIZE 1000000     

long A[MAXSIZE];
long seg[MAXSIZE];
     
int min(int i,int j)
{
	if(i<j)
	{
		return i;
	}
	else
	{
		return j;
	}
}

void build(int t,int i,int j)
{
    if(i>j) return;
    
    if(i==j)
    {
    	seg[t] = A[i];
    	return;
    }
    
    int left = t<<1,right=left|1,mid=(i+j)>>1;
   
    build(left,i,mid);    
    build(right,mid+1,j);
    
    seg[t]=min(seg[left],seg[right]);
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
    
    seg[t]=min(seg[left],seg[right]);
}
     

long query(int t,int i,int j,int ri,int rj)
{
   
    if(i>j || i>rj || j<ri)
    	return 2000000000;
   
    if(ri<=i && rj>=j)
    	return seg[t];

    int left = t<<1,right=left|1,mid=(i+j)>>1;

    int q1 = query(left,i,mid,ri,rj);
    int q2 = query(right,mid+1,j,ri,rj);

    int res = min(q1,q2);
    return res; 
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
	for(i=1;i<=N;i++)
	{
		printf("%ld\n",A[i]);
	}
    return 0;
}
