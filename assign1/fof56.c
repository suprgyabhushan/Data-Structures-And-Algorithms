#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct node
{
	int id;
	struct node *next;
} node;

int ids(node **head,int id)
{
	node *temp = malloc(sizeof(node));
	if(temp == 0)
    		return -1;
  	temp->id = id;
  	temp->next = *head;
  	*head = temp;
 	return 0;
}

void print(node *head)
{
	while(head !=NULL)
	{
		printf("%d ",head->id);
		head=head->next;
	}
}

int search(int *a, int id)
{
	int i;
	for(i=0;a[i]!=0;++i)
		if(a[i]==id)
			return 1;
	return 0;
}



int friends(struct node **f, int pers, int *refarray,int x)
{
	struct node *temp;
	int i=0,k=0,size_of_refarray=0;
	int flag=0;
	int count=0;
	temp=f[pers];
	while(temp!=NULL)
	{
		refarray[i++]=temp->id;
		temp=temp->next;
	}
	refarray[i]=0;
	k=0;
	temp = f[pers];
	while(refarray[k]!=0)
	{
		node *t = f[refarray[k]-1];
		while(t!=NULL)
		{
			flag = 0;
			if(!search(refarray,t->id))
			//if(t->id != pers+1)
			{
				refarray[i++] = t->id;
				flag = 1;
			}
			t = t->next;
			if(flag == 0)
			continue;
		}
		k++;
	}
	k=0;
	if(refarray[k]==0)
	{
		refarray[k]=pers+1;
	}
	return 0;
}

int main(int argc,char *argv[])
{
	FILE *f;
  	int i, j,n,num;
	int p,q=0;
	p=0;	
  	int rows,mostInts;

	int GetLinesOfFile(char *path)
	{
    		FILE *fp = fopen(argv[1], "r");
    		int spaces=0, lines=0, sK=0;
    		char *line;  
    		char *buf;
    		line = malloc(1000);
    		line = fgets(line, 1000, fp);
   		while(line)
    		{
			lines++;
        		line = fgets(line, 1000, fp);
		}
		fclose(fp);
    		free(line);
  		return lines;
	}
	rows = GetLinesOfFile(argv[1]);

	int val;
	f = fopen(argv[1], "r");
	fscanf(f,"%d",&n);
	
	node *pointers[n];
	for(i=0;i<n;i++)
	{		
		pointers[i]=NULL;
	}
	val=fgetc(f);
	for(i=0;i<n;i++)
	{	
		for(j=0;;j++)
		{
			val=fgetc(f);
			if(val!=' ')
			{
				if(val=='\n')
				{
					break;
				}
				else
				{
					fseek(f,-1,SEEK_CUR);
					fscanf(f,"%d",&num);
					ids(&pointers[i],num);
				}
			}		
		}
	}
								
		
	fclose(f);

	/*for(i=0;i<n;i++)
	{		

		print(pointers[i]);	
		printf("\n");
	}*/
	
	//int number= atoi(argv[2])-1;
	int *array=calloc(rows,sizeof(int));
	
	
	int ref=0;
	for(j=0;j<rows-1;j++)
	{
		friends(pointers,j,array,rows-1);
		for(i=0;i<rows-1;i++)
		{
			if(array[i]==0)
				break;
        		ref++;
			printf("%d ",array[i]);
		}
		printf("\n");
		array=calloc(rows,sizeof(int));
	}

   
    
	
	return 0;
	
}




