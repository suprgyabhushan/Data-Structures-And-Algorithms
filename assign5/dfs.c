#include<stdio.h>
#include<stdlib.h>

#include<string.h> 


#define MAX 1000
#define RED 0
#define YELLOW 1
#define BLUE 2
#define EDGE 1 

int i , j , m , n ;
int M , N ;

 
int graph[MAX ][MAX ];
int color[MAX ];
int dist[MAX];
int finish[MAX];
int Q[MAX];
int parent[MAX ] ;


int top, status;
 

void push (int stack[], int item)
{   if (top == (MAX-1))
	status = 0;
    else
    {   status = 1;
	++top;
	stack [top] = item;
    }
}
 

int pop (int stack[])
{  
    int ret;
    if (top == -1)
    {   ret = 0;
	status = 0;
    }
    else
    {   status = 1;
	ret = stack [top];
	--top;
    }
return ret;
}

int empty(int stack[])
{
if(top==0)
 return 1;
else
 return 0;
}

void printPath(int start , int end )
{
 if( start == end )
  printf("%d ",start);

 else if( parent[ end ] == -1 )
  printf("No path from %d to %d\n",start,end);

 else
 {
  printPath( start , parent[end ] );

  printf("-> %d ",end ); 
 }  
}

void Dfs( int s )
{
 int u ;
      /** INITIALIZATION **/
 for(i = 1 ; i <= N ; i++)
 {
  color[ i ] = RED ;

  dist[i ]   = -1 ;
  parent[ i] = -1 ;
 }
 color[ s ] = YELLOW ;

 dist[s ] = 0 ;   /**INITIALIZE DISTANCE OF SOURCE TO ZERO**/

 parent[s ] = -1 ;

 push(Q,s) ;  

 while( empty(Q)!=1 )       
 {
    int x;
x = pop(Q);

    

    for( i=1 ; i<= N; i++)
    {  
  if(( color[i ] == RED) && (graph[x][i] == 1 ))
  {
   color[i ] = YELLOW ;
 
     dist[i ] = dist[x] + 1 ;
    
   parent[ i] = x ;
      
   push(Q,i); /** PUSH INTO STACK **/
  }
    }
    color[x ] = BLUE ;
 }
}








int main(int argc,char *argv[])
{
// freopen("t.in","r",stdin);
// freopen("t.out","w",stdout);
 
 int a, b ;
FILE *f;
f=fopen(argv[1],"r");

 fscanf(f,"%d",&N);         /**Verticess (N) ******/

while( 1 )         /** INPUT EDGES ****/
 {
  fscanf(f,"%d %d",&a,&b);

  if( a== 0 && b==0 )
   break ;

  graph[a][b] = 1 ;  
 }
 while( fscanf(f,"%d",&a) != EOF )       /* ENTER START AND END */
 {
  fscanf(f,"%d",&b);
           Dfs(a);    /** EXPLORE ALL NODE FROM START TO END **/
       

  printf(" Source: %d , Destination: %d\t",a,b);

  printPath(a,b);     

  printf(" End of Path\n\n");
 }
 return 0 ;
}

