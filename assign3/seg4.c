#include<stdio.h>
#define MAXSIZE 1000000     

long A[MAXSIZE];
long segtree[MAXSIZE];
     

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
    
    segtree[t]=segtree[left]+segtree[right];
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
    
    segtree[t]=segtree[left]+segtree[right];
}
     

long query(int t,int i,int j,int ri,int rj)
{
   
    if(j<ri || i>rj)
    	return 0;
   
    if(ri<=i && rj>=j)
    	return segtree[t];

    int left = t<<1,right=left|1,mid=(i+j)>>1;
    
    return query(left,i,mid,ri,rj) + query(right,mid+1,j,ri,rj);
}

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

void build1(int t,int i,int j)
{
    if(i>j) return;
    
    if(i==j)
    {
    	segtree[t] = A[i];
    	return;
    }
    
    int left = t<<1,right=left|1,mid=(i+j)>>1;
   
    build1(left,i,mid);    
    build1(right,mid+1,j);
    
    segtree[t]=min(segtree[left],segtree[right]);
}
     

void update1(int t,int i,int j,int k,long x)
{
    
    if(i==j)
    {
    	if(i==k)
    		segtree[t] = x;
      return;
    }
    int left = t<<1,right=left|1,mid=(i+j)>>1;
    
    if(k<=mid)
    	update1(left,i,mid,k,x);
    
    else
    	update1(right,mid+1,j,k,x);
    
    segtree[t]=min(segtree[left],segtree[right]);
}
     

long query1(int t,int i,int j,int ri,int rj)
{
   
    if(i>j || i>rj || j<ri)
    	return 2000000000;
   
    if(ri<=i && rj>=j)
    	return segtree[t];

    int left = t<<1,right=left|1,mid=(i+j)>>1;

    int q1 = query1(left,i,mid,ri,rj);
    int q2 = query1(right,mid+1,j,ri,rj);

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
    if(atoi(argv[2])==0)
    {	
  
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
    }
    else if(atoi(argv[2])==1)
    {
	 build1(1,1,N);
    
       while(Q>0)
    	 {
    	
		fscanf(input,"%d",&O);
    		if(O==1)
		{
    			fscanf(input,"%d%d",&L,&R);
    		
    			printf("%ld\n",query1(1,1,N,L+1,R+1));
    		}
    		else if(O==0)
		{
		      fscanf(input,"%d%ld",&k,&x);
      	      
      	      update1(1,1,N,k+1,x);
      	}
		Q=Q-1;
    	}
    }
    return 0;
}
