#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


// Structure used to define the graph nodes


int main(int argc,char *argv[])
{
FILE *f;
int num,num1,num2,num3;
int total;
f=fopen(argv[1],"r");
fscanf(f,"%d",&num);
int GraphNodes[num];			// Array of nodes in the graph
int AdjMatrix[num][num];	// Matrix to define the graph links
	
	
int i, j, idx, numLinks, link;


// Initialize Adjacency Matrix to all 0s
for(i=0; i<num; i++)
	for(j=0; j<num; j++)
		AdjMatrix[i][j] = 0;


// Read all the graph data and build the adjacency matrix
while(!feof(f))
{
	// Read the graph ID and use this as it's index in the graph
	fscanf(f,"%d",&num1);
	GraphNodes[num1-1] = num1-1;

	// Read all links and set the marker in the adjacency matrix
	fscanf(f,"%d",&num2);
	fscanf(f,"%d",&num3);
	AdjMatrix[num1-1][num2-1] = num3;		// Set the link
	
}
printf("%d\n",AdjMatrix[0][2]);
fclose(f);
return 0;
}
