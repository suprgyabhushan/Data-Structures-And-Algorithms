#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
	{
	int num;
	int array[5000];
	struct node *next;
	};
void print(struct node *head,int *matrix,int x,int *farray,int *l)
	{
	int k=0;
	while(head!=NULL)
		{
		if(head->num==x)
			{
			while(k<matrix[x])
				{
				farray[(*l)]=head->array[k];
				(*l)=(*l)+1;
				k++;
				}
			}
		head=head->next;
		}

	}
void rmdup(int *karray,int *l)
	{
	int i=0,j=0,k=0;
	for(i=0;i<(*l);i++)
		{
		for(j=i+1;j<(*l);j++)
			{
			if(i==j)
				continue;
			else if(karray[i]==karray[j])
				{
				k=j;
				(*l)=(*l)-1;
				while(k<(*l))
					{
					karray[k]=karray[k+1];
					k++;
					}
				j=0;
				}
			}
		}
	}
	
int main(int argc,char*argv[])
	{
	FILE *in;
	in=fopen(argv[1],"r");
	int frnds=0,i=0,j=0;
	fscanf(in,"%d",&frnds);
	char str[500];
	int *matrix=malloc(sizeof(int)*(frnds+1));
	char *t1=NULL;
	while(i<=frnds)
		{
		fgets(str,200,in);
		j=0;
		for(t1=strtok(str," ");t1!=NULL;t1=strtok(NULL," "))
			{
			j++;
			}
		matrix[i]=j-1;
		i++;
		}
	i=0;
	rewind(in);
	struct node *input,*new;
	input=malloc(sizeof(struct node));
	input=NULL;
	j=0;
	fscanf(in,"%d",&frnds);
	while(i<=frnds)
		{
		new=malloc(sizeof(struct node));
		while(new!=NULL)
			{
			new->num=i;
			j=0;
			if(matrix[i]==0)
				{
				new->array[j]=0;
				j++;
				}
			while(j<matrix[i])
				{
				fscanf(in,"%d",&new->array[j]);
				j++;
				}
			break;
			}
		new->next=input;
		input=new;
		i++;
		}	
	new=input;
	int k=atoi(argv[2]);
	i=0;
	j=0;
	int *farray=malloc(sizeof(int)*matrix[k]);
	int *karray=malloc(sizeof(int)*10000);
 	int l=0;	
	int n=0,m=0,h=0;
		print(input,matrix,k,farray,&l);
		karray=farray;
	while(j<frnds)
		{
		m=0;
		while(m<h)
			{
			print(input,matrix,farray[i],karray,&l);	
			i++;
			m++;
			}
		rmdup(karray,&l);
		farray=karray;
		h=l-i;
		k=farray[i];
		j++;
		}
	j=0;
	while(j<l)
		{
		if(atoi(argv[2])!=karray[j])
			{
			printf("%d ",karray[j]);
			}
			j++;
		}
	printf("\n");
	}

