#include<stdio.h>
#include<string.h>
#include<math.h>
 


long arr[4*100000];
long tree[4*100000];
long lazy[4*100000];
 
/**
* Build and init tree
*/
void build_tree(int node, int a,int b)
{
	if(a > b) return; // Out of range
	if(a == b)
	{
		// Leaf node
		tree[node] = arr[a]; // Init value
		return;
	}
	build_tree(node*2, a, (a+b)/2); // Init left child
	build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
	tree[node] = tree[node*2]+ tree[node*2+1]; // Init root value
}
 
/**
* Increment elements within range [i, j] with value value
*/
void update_tree(int node, int a, int b, int i, int j, int value)
{
	if(lazy[node] != 0)
	{
		// This node needs to be updated
		tree[node] += lazy[node]; // Update it
 
		if(a != b)
		{
			lazy[node*2] += lazy[node]; // Mark child as lazy
			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}
 
		lazy[node] = 0; // Reset it
	}
	if(a > j || b < i) return; // Current segment is not within range [i, j]
		return 0;
	if(a >= i && b <= j)
	{
		// Segment is fully within range
		tree[node] += value;
 
		if(a != b)
		{
			// Not leaf node
			lazy[node*2] += value;
			lazy[node*2+1] += value;
		}
 
		return;
	}

	update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
	update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child
 
	tree[node] = tree[node*2]+ tree[node*2+1];
}
 

long query_tree(int node, int a, int b, int i, int j)
{
	if(a > j || b < i) return 0 ; // Out of range
 
	if(lazy[node] != 0)
	{ // This node needs to be updated
		tree[node] += lazy[node]; // Update it
 
		if(a != b)
		{
			lazy[node*2] += lazy[node]; // Mark child as lazy
			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}
 
		lazy[node] = 0; // Reset it	
	}
 
	if(a >= i && b <= j) // Current segment is totally within range [i, j]
		return tree[node];
 
	int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
	int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child
 
	int res = q1+q2; // Return final result
	return res;
}
 
int main(int argc,char *argv[])
{

int N,C;
int op,p,q,v;
FILE *f;
f=fopen(argv[1],"r");

fscanf(f,"%d %d",&N,&C);
int i;
for( i = 0; i < N; i++) arr[i] = 0;
 
build_tree(1, 0, N-1);
 
memset(lazy, 0, sizeof lazy);






int j;
for( j = 0;j< C;++j)
{
fscanf(f,"%d",&op);
if(op == 0)
{
fscanf(f,"%d %d %d",&p,&q,&v);
update_tree(1, 0, N-1,p,q,v);
}
else
{
fscanf(f,"%d %d",&p,&q);
printf("%ld\n",query_tree(1, 0, N-1,p,q));
}
}

return 0;
}

 
/*update_tree(1, 0, N-1, 0, 6, 5); // Increment range [0, 6] by 5. here 0, N-1 represent the current range.
update_tree(1, 0, N-1, 7, 10, 12); // Incremenet range [7, 10] by 12. here 0, N-1 represent the current range.
update_tree(1, 0, N-1, 10, N-1, 100); // Increment range [10, N-1] by 100. here 0, N-1 represent the current range.
 
cout << query_tree(1, 0, N-1, 0, N-1) << endl; // Get max element in range [0, N-1] */
