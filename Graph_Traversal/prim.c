
C program to find Minimum Spanning tree PRIM’s Algorithm
Mr Coder February 18, 2013 2

    Tweet
    inShare



C program to find Minimum Spanning tree PRIM’s Algorithm : Prim’s algorithm is a greedy algorithm that finds a minimum spanning tree for a connected weighted undirected graph. This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized.

General apporach for writing a C Code to Find Minimum Spanning tree using PRIM’s Algorithm :

        create a tree containing a single vertex, chosen arbitrarily from the graph

        create a set containing all the edges in the graph

        loop until every edge in the set connects two vertices in the tree

            remove from the set an edge with minimum weight that connects a vertex in the tree with a vertex not in the tree

            add that edge to the tree

Let’s see how to write a C program of PRIM’s Algorithm to find Minimum Spanning tree.
C program to find Minimum Spanning tree using PRIM’s Algorithm :

 

#include<stdio.h>
#define INF 1000
int vertex[10];
int wght[10][10];
int new_wght[10][10];
int closed[10];
int n;
int inclose(int i,int n1)
{
/*chk for the ith vertex presence in closed*/
int j;
for(j=0;j<=n1;j++)
if(closed[j]==i)
return 1;
return 0;
}
void buildtree()
{
int i=0,j,count=0;
int min,k,v1=0,v2=0;
closed[0]=0;
while(count<n-1)
{
min=INF;
for(i=0;i<=count;i++)
for(j=0;j<n;j++)
if(wght[closed[i]][j]<min && !inclose(j,count))
{
min=wght[closed[i]][j];
v1=closed[i];
v2=j;
}
new_wght[v1][v2]=new_wght[v2][v1]=min;
count++;
closed[count]=v2;
printf("\nScan : %d %d---------%d wght = %d \n",count,v1+1,v2+1,min);
getch();
}
}
void main()
{
int i,j,ed,sum=0;
clrscr();
printf("\n\n\tPRIM'S ALGORITHM TO FIND SPANNING TREE\n\n");
printf("\n\tEnter the No. of Nodes : ");
scanf("%d",&n);
for(i=0;i<n;i++)
{
vertex[i]=i+1;
for(j=0;j<n;j++)
{
wght[i][j]=INF;
new_wght[i][j]=INF;
}
}
printf("\n\nGetting Weight.\n");
printf("\n\tEnter 0 if path doesn't exist between {v1,v2} else enter the wght\n");
for(i=0;i<n;i++)
for(j=i+1;j<n;j++)
{
printf("\n\t%d -------- %d : ",vertex[i],vertex[j]);
scanf("%d",&ed);
if(ed>=1)
wght[i][j]=wght[j][i]=ed;
}
getch();
clrscr();
printf("\n\n\t\tNODES CURRENTLY ADDED TO SPANNING TREE\n\n");
buildtree();
printf("\n\tNEW GRAPH WEIGHT MATRIX\n\n");
printf("\n\tweight matrix\n\n\t");
for(i=0;i<n;i++,printf("\n\t"))
for(j=0;j<n;j++,printf("\t"))
printf("%d",new_wght[i][j]);
printf("\n\n\t\tMINIMUM SPANNING TREE\n\n");
printf("\n\t\tLIST OF EDGES\n\n");
for(i=0;i<n;i++)
for(j=i+1;j<n;j++)
if(new_wght[i][j]!=INF)
{
printf("\n\t\t%d ------ %d = %d ",vertex[i],vertex[j],new_wght[i][j]);
sum+=new_wght[i][j];
}
printf("\n\n\t Total Weight : %d ",sum);
getch();
}


Read original Article: C program to find Minimum Spanning tree PRIM’s Algorithm | Learn C Programming | C Language | C programs

