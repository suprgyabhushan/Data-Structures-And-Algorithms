#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main(int argc,char *argv[])
{

	int GetParamsOfFile(char *path, int *numInts)
	{
    		FILE *fp = fopen(argv[1], "r");
    		int spaces=0, lines=0, sK=0;
    		char *line;  //choose big here
    		char *buf;
    		line = malloc(1000);
    		line = fgets(line, 1000, fp);
		printf("%s\n",line);
    		while(line)
    		{
			//printf("%d\n",lines);
        		lines++;
        		spaces = 0;
        		buf = strtok(line, " ");
        		while(buf)
        		{
            		spaces++;
            		buf = strtok(NULL, " ");
        		}
        		(spaces > sK)?(sK = spaces):(sK==sK);
        		line = fgets(line, 1000, fp);
			printf("%s",line);
	    	}
		printf("\n");
            *numInts = sK;
    		fclose(fp);
    		free(line);
  		return lines;
	}

	int **Create2D(int **arr, int rows, int cols)
	{   
		int space = cols*rows; 
    		int y;
    		arr = calloc(space, sizeof(int));
    		for(y=0;y<rows;y++)
    		{
        		arr[y] = calloc(cols, sizeof(int)); 
    		}
    		return arr;
	}
	void free2DInt(int **arr, int rows)
	{
    		int i;
    		for(i=0;i<rows; i++)
        	if(arr[i]) free(arr[i]);
    		free(arr);  
	}

	int i,j;
    	int lines,start;
    	int mostInts;
    	int **array;
    	lines = GetParamsOfFile(argv[1], &mostInts);
	printf("%d\n",mostInts);
	printf("%d\n",lines);
    	array = Create2D(array,lines,mostInts);//creates array with correct number of rows and columms;
    	//Here is where you would re-read your file, this time, populating your new array.  
    	//I will leave this part to you...
	char buf[128];
 FILE *fp;
  fp = fopen(argv[1], "r");
  if(fp == NULL)
  {
    puts("Cannot open file for reading");
    exit(EXIT_FAILURE);
  }
 for(i=0;i<lines;i++)
 {
	for(j=0;j<mostInts;j++)
	{	
  		fgets(buf, sizeof(buf), fp);
  		sscanf(buf, "%d %d", &array[i][j], &array[i][j+1]);
  	      } 
  fclose(fp);
 
  printf("Set 1 - 1st: %d, 2nd: %d\n", array1[0], array1[1]);
  printf("Set 2 - 1st: %d, 2nd: %d\n", array2[0], array2[1]);
 
  
    	free(line);
	
	
 
      //free2DInt(array, mostInts);

	//for(j=0;j<
    	return 0;
}





