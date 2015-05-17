#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
#include<string.h> 

#define MAX 600
#define RED 0
#define YELLOW 1
#define BLUE 2
#define EDGE 1 

int i , j , m , n ;
int M , N ;
int head=0;
int tail=0;
 
int graph[MAX][MAX];
int color[MAX];
int dist[MAX];
int finish[MAX];
int Q[MAX];
int parent[MAX ] ;

void Enqueue(int q[],int x)
{	
	if (tail==MAX && head==0)
	{
		printf("queue is full");
	}
	else
	{
		q[tail]=x;
	}
	tail++;
}

int Dequeue1(int q[])
{
	int no;
	no=q[head];
	head++;
	return no;
}

void Dequeue2(int q[])
{
	int no;
	no=q[head];
	head++;
}

int isEmpty()
{
	if(head==tail)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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

void Bfs( int s )
{
int u;
 
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

 Enqueue(Q,s) ;  

 while( isEmpty()!=1 )       // LOOP UNTIL QUEUE(Q) IS EMPTY 
 {

   
u= Dequeue1(Q);
//Dequeue2(Q);

    

    for( i=1 ; i<= N; i++)
    {  
  if(( color[i ] == RED) && (graph[u][i] == 1 ))
  {
   color[i ] = YELLOW ;
 
     dist[i ] = dist[u] + 1 ;
    
   parent[ i] = u;
      
   Enqueue(Q,i); /** PUSH INTO QUEUE **/
  }
//Dequeue2(Q);
    }
    color[u ] = BLUE ;
 }
}








int main(int argc,char *argv[])
{

 
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
 while( fscanf(f,"%d",&a) != EOF )       
 {
  fscanf(f,"%d",&b);
           Bfs(a);    
  printf(" Source: %d , Destination: %d\t",a,b);

  printPath(a,b);      
  printf(" End of Path\n\n");
 }
 return 0 ;
fclose(f);
}



