#include<stdio.h>
#define MAXSIZE 100000000     

long A[MAXSIZE];
long segtree[MAXSIZE];
     
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
    
    if(i==j)
    {
    	segtree[t] = A[i];
    	return;
    }
    
    int left = t<<1,right=left|1,mid=(i+j)>>1;	
   
    build(left,i,mid);
    
    build(right,mid+1,j);
    
    segtree[t]=min(segtree[left],segtree[right]);
}
     

void update(int t,int i,int j,int k,long x)
{
    
    if(i==j)
    {
    	if(i==k)
    		segtree[t] = x;
      return;
    }
    int left = t<<1,right=left|1,mid=(i+j)>>1;
    
    if(k<=mid)
    	update(left,i,mid,k,x);
    
    else
    	update(right,mid+1,j,k,x);
    
    segtree[t]=min(segtree[left],segtree[right]);
}
     

long query(int t,int i,int j,int ri,int rj)
{
   
    if(j<ri || i>rj)
    	return 0;
   
    if(ri<=i && rj>=j)
    	return segtree[t];
    int left = t<<1,right=left|1,mid=(i+j)>>1;
    
    return min(query(left,i,mid,ri,rj), query(right,mid+1,j,ri,rj));
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
    		
    		printf("%ld\n",query(1,1,N,L,R));
    	}
    	else if(O==0)
	{
	      fscanf(input,"%d%ld",&k,&x);
            
            update(1,1,N,k,x);
      }
	Q=Q-1;
    }
    return 0;
}
