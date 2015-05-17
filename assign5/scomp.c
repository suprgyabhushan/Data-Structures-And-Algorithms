#include<stdio.h>
#include<stdlib.h>
struct node
        {
        int key;
        struct node *next;
        };
void add_at_end(struct node** head_ref, int new_data)
	{
    	/* 1. allocate node */
    	struct node* temp = (struct node*) malloc(sizeof(struct node));
 
    	struct node *last = *head_ref;  /* used in step 5*/
  
    	/* 2. put in the data  */
    	temp->key  = new_data;
 
    	/* 3. This new node is going to be the last node, so make next of it as NULL*/
    	temp->next = NULL;
 
    	/* 4. If the Linked List is empty, then make the new node as head */
    	if (*head_ref == NULL)
    		{
       		*head_ref = temp;
       		return;
    		}	  
      
    	/* 5. Else traverse till the last node */
    	while (last->next != NULL)
        	last = last->next;
  
    	/* 6. Change the next of last node */
    	last->next = temp;
    	return;    
	}
/*struct node
	{
	int key;
	struct node *next;
	};*/
void print(struct node *n)
	{
	struct node *temp;
	temp=n;
	while(temp!=NULL)
		{
		printf("%d ",temp->key);
		temp=temp->next;
		}
	printf("\n");
	return;
	}
int dequeue(struct node **q)
	{
	int vertex=0;
	vertex=(*q)->key;
	(*q)=(*q)->next;
	return vertex;
	}
int bfsvisit(struct node **pointerarray,int current,char *colourarray)
	{
	struct node *queue=NULL;
	add_at_end(&queue,current);
	int i = 0;
	while(queue!=NULL)
		{
		i++;
		current=dequeue(&queue);
		printf("%d\n",current);
		colourarray[current-1]='b';
		struct node *temp=(struct node *)malloc(sizeof(struct node));
		temp=pointerarray[current-1];
		temp=temp->next;
		while(temp!=NULL)
			{
			if(colourarray[(temp->key)-1]=='r')
				{
				colourarray[temp->key-1] = 'y';
				add_at_end(&queue,temp->key);
				}
			temp=temp->next;
			}
		}
	return 0;
	}
int dfsvisit(struct node **pointerarray,int current,char *colourarray,int *delay,int *finish,int *counter,int *finalarray,int *index)
	{
	colourarray[current-1]='b';
	printf("%d\n",current);
    (*counter)=(*counter)+1;
    finalarray[(*index)]=current;
    (*index)=(*index)+1;
    //printf(" rrr %d\n",*counter);
    delay[current-1]=(*counter);
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp=pointerarray[current-1];
	temp=temp->next;
	while(temp!=NULL)
		{
		if(colourarray[(temp->key-1)]=='r')
			{
			dfsvisit(pointerarray,temp->key,&colourarray[0],&delay[0],&finish[0],counter,&finalarray[0],index);
			}
		temp=temp->next;
		}
    *counter=(*counter)+1;
    finish[current-1]=(*counter);
	return 0;
	}
int main(int argc,char *argv[])
	{
	FILE *in;
	int no_elements,i;
	in=fopen(argv[1],"r");
	fscanf(in,"%d\n",&no_elements);
	char *colour_array;
	colour_array=(char *)malloc(sizeof(char)*no_elements);
	for(i=0;i<no_elements;i++)
		{
		colour_array[i]='r';
		}
	struct node **pointerarray;
	pointerarray=(struct node**)malloc(sizeof(struct node *)*no_elements);
	for(i=0;i<no_elements;i++)
		{
		pointerarray[i]=(struct node *)malloc(sizeof(struct node )*1);
		pointerarray[i]->key=i+1;
		pointerarray[i]->next=NULL;
		}
	int parent_present,child;
	while(!feof(in))
		{
		//int parent_present,child;
		fscanf(in,"%d %d\n",&parent_present,&child);
		add_at_end(&pointerarray[parent_present-1],child);
		}
	/*for(i=0;i<no_elements;i++)
		{
		//printf("ggg\n");
		if(colour_array[i]=='r')
			{
			bfsvisit(pointerarray,i+1,&colour_array[0]);
			}
		}*/
    int *delay,*finish,*finalarray;
    int counter=0,index=0;
    delay=(int *)calloc(sizeof(int),no_elements);
    finish=(int *)calloc(sizeof(int),no_elements);
    finalarray=(int *)calloc(sizeof(int),no_elements);
	for(i=0;i<no_elements;i++)
		{
		if(colour_array[i]=='r')
			{
			dfsvisit(pointerarray,i+1,&colour_array[0],&delay[0],&finish[0],&counter,&finalarray[0],&index);
			}
		}
    /*for(i=0;i<no_elements;i++)
        {
        printf("%d ",delay[i]);
        }
    printf("\n");
    for(i=0;i<no_elements;i++)
        {
        printf("%d ",finish[i]);
        }*/
    for(i=0;i<no_elements;i++)
        {
        printf("%d %d\n",finalarray[i],finish[finalarray[i]-1]);
        }
    printf("\n");
	return 0;
	}

