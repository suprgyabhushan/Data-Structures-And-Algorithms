#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int countitems(char * s)
{
	int i;
	for (i=0; *s; i++)
	{
		while(*s && isblank(*s++));
    		while(*s && !isblank(*s++));    
  	}
  	return(i);
}

char * nextitem(char *s)
{
	while (*s && !isblank(*s)) s++;
  	while (*s && isblank(*s)) s++;
  	return (s);
}

char * skipblanks(char *s)
{
	while (*s && isblank(*s)) s++;
	return (s);
}



int main(int argc,char *argv[])
{
	FILE *f;
  	int i, j,k;
	int p,q;
	p=0;

  	char s[100];
  	char * ss;
	int rows,mostInts;
  	f = fopen(argv[1], "r");
  	i = 0;
  	while (!feof(f))
	{
    		fgets(s, 99, f);
    		j = countitems(s);
		//printf("%d\n",j);
    		if (j>i) i = j;
  	}
  	printf("you need %d columns\n", i);
  	// allocate matrix
	fclose(f);

	int GetParamsOfFile(char *path, int *numInts)
	{
    		FILE *fp = fopen(argv[1], "r");
    		int spaces=0, lines=0, sK=0;
    		char *line;  //choose big here
    		char *buf;
    		line = malloc(1000);
    		line = fgets(line, 1000, fp);
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
			//printf("%s",line);
	    	}
		//printf("\n");
            *numInts = sK;
    		fclose(fp);
    		free(line);
  		return lines;
	}
	rows = GetParamsOfFile(argv[1], &mostInts);
	printf("%d\n",rows);
  
	int array[rows-1][i-1];
	f=fopen(argv[1],"r");
	while(!feof(f))
	{
    		fgets(s, 99, f);
    		ss = skipblanks(s);
    		array[p][q]=*ss;
		
  	}
  	fclose(f);
}


