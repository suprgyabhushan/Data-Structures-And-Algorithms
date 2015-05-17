#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<limits.h>


int maxVal(int x, int y)
{
	if(x<y)
		return x;
	else
		return y;
}


int getMid(int s, int e) {  return s + (e-s)/2;  }
   
* A recursive function to update the nodes which have the given index in
   their range. The following are parameters
    st, index, ss and se are same as getSumUtil()
    i    --> index of the element to be updated. This index is in input array.
   diff --> Value to be added to all nodes which have i in range 
void updateValueUtil(int *st, int ss, int se, int i, int diff, int index)
{
    // Base Case: If the input index lies outside the range of this segment
    if (i < ss || i > se)
        return;
 
    // If the input index is in range of this node, then update the value
    // of the node and its children
    
int RMQUtil(int *st, int ss, int se, int qs, int qe, int index)
{
    if (qs <= ss && qe >= se)
        return st[index];
 
   
    if (se < qs || ss > qe)
        return INT_MAX;
 
    int mid = getMid(ss, se);
    return maxVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1),
                  RMQUtil(st, mid+1, se, qs, qe, 2*index+2));
}


int RMQ(int *st, int n, int qs, int qe)
{
    
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }
 
    return RMQUtil(st, 0, n-1, qs, qe, 0);
}


int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }
 
    int mid = getMid(ss, se);
    st[si] =  maxVal(constructSTUtil(arr, ss, mid, st, si*2+1),
                     constructSTUtil(arr, mid+1, se, st, si*2+2));
    return st[si];
}

   
int *constructST(int arr[], int n)
{
    int x = (int)(ceil(log2(n))); 
    int max_size = 2*(int)pow(2, x) - 1;
    int *st = (int*)malloc(sizeof(int)*max_size);
 
    
    constructSTUtil(arr, 0, n-1, st, 0);
 
    return st;
}
 
 
int main()
{
    int arr[] = {1,3, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
	
    
    int *st = constructST(arr, n);
 
    int qs = 0;  
    int qe = 2;  
 
    
    printf("Maximum of values in range [%d, %d] is = %d\n",
                           qs, qe, RMQ(st, n, qs, qe));
 
    return 0;
}

