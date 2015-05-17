#include<stdio.h>
#include<stdlib.h>
struct node
	{
	int data;
	struct node *next;
	};
struct node *createnode(struct node *n)
	{
	struct node *temp;
	temp=(struct node *)malloc(sizeof(struct node));
	temp->next=n;
	return temp;
	}
int search(int *a, int value)
	{
	int i;
	for(i=0;a[i]!=0;++i)
		if(a[i]==value)
			return 1;

	return 0;
	}
int function(struct node **n,int no_,int *refarray,int x)
	{
	struct node *temp;
	int i=0,k=0,size_of_refarray=0;
	int flag=0;
	temp=n[no_];
	while(temp!=NULL)
		{
		refarray[i++]=temp->data;
		temp=temp->next;
		}	
    //refarray[i]=no_+1;
	k=0;
	temp = n[no_];
	while(refarray[k]!=0)
		{
		struct node *t = n[refarray[k]-1];
		while(t!=NULL)
			{
			flag = 0;
			if(!search(refarray,t->data))
			if(t->data != no_+1){
				refarray[i++] = t->data;
				flag = 1;
			}
			t = t->next;
			if(flag == 0)
				continue;
		}
		k++;
	}
	return 0;
	}
int main(int argc,char *argv[])
	{
	FILE *in;
	int *friends;
	int i=0,j=0,count,flag=0;
	char ch;
	char *str;
	in=fopen(argv[1],"r");
	fscanf(in,"%d\n",&count);
	friends=(int *)malloc(sizeof(int)*count);
	str=(char *)malloc(sizeof(char)*2*count);
	int ref=0;
	while(!feof(in))
		{
		fscanf(in,"%c",&ch);
		if(ch==10)
			{
			friends[i]=flag;
			ref++;
			flag=0;
			i++;
			}
		if(ch==' '&&ref==count-1)
			{
			fseek(in,-2,SEEK_CUR);
			fscanf(in,"%[^\n]",str);
			flag=0;
			for(j=0;j<2*count;j++)
				{
				if(str[j]=='\0')
					break;
				if(str[j]!=' ')
					{
					flag++;
					}
				}
			friends[i]=flag;
			break;
			}
		else if(ch==' ')
			{
			flag++;
			}
		}
	free(str);
	fclose(in);
	in=fopen(argv[1],"r");
	fscanf(in,"%d\n",&count);
	struct node **pointerarray;
	pointerarray=(struct node **)malloc(sizeof(struct node *)*(count));
	for(i=0;i<count;i++)
		{
		pointerarray[i]=(struct node *)malloc(sizeof(struct node));
		}
	i=0;
	while(1)
		{
		struct node *n;
		n=(struct node *)malloc(sizeof(struct node));
		n=NULL;
		if(i==count)
			break;
		if(friends[i]==0)
			{
			pointerarray[i]=n;
			i++;
			}
		if(friends[i]!=0)
			{
			for(j=0;j<friends[i];j++)
				{
				fscanf(in,"%d\n",&ref);
				struct node *temp;
				temp=createnode(n);
				temp->data=ref;
				n=temp;
				}
			pointerarray[i]=n;
			i++;
			}
		}
	int number=atoi(argv[2])-1;
	int *array;
	array=(int *)calloc(sizeof(int),count);
	function(pointerarray,number,&array[0],count);
    ref=0;
	for(i=0;i<count;i++)
		{
		if(array[i]==0)
			break;
        ref++;
		printf("%d ",array[i]);
		}
    array[ref]=number+1;
    printf("%d",array[ref]);
	printf("\n");
    /*
    j=0;
    int k=0;
    int *array1;
    array1=(int *)calloc(sizeof(int),count);
    j=0;
    flag=0;
    for(i=0;i<count;i++)
        {
        for(j=0;j<ref;j++)
            {
            if(array[j]==i+1)
                {
                flag=1;
                break;
                }
            }
        if(flag==0)
            {
            function(pointerarray,i,&array1[0],count);
            for(k=0;k<count;k++)
                {
                if(array1[k]==0)
                    break;
                array[ref]=array1[k];
                printf("%d ",array1[k]);
                ref=ref+1;
                }
            printf("\n");
            }
        flag=0;
        }*/
    flag=0;
    int k=0,l=0;
    int *array1;
    array1=(int *)calloc(sizeof(int),count);
    for(i=1;i<count;i++)
        {
        function(pointerarray,i,&array1[0],count);
        for(l=0;l<count;l++)
            {
            if(array1[l]==0)
                break;
            for(k=0;k<ref;k++)
                {
                if(array[k]==array1[l])
                    {
                    flag=1;
                    break;
                    }
                }
            if(flag==1)
                break;
            }
        if(flag==0)
            {
            //if(array1[0]==0)
                //break;
            printf("%d ",i+1);
            array[ref]=i+1;
            ref=ref+1;
            for(j=0;j<count;j++)
                {
                if(array1[j]==0)
                    break;
                printf("%d ",array1[j]);
                //free(array1);
                }
            free(array1);
            int *array1;
            array1=(int *)calloc(sizeof(int),count);
            printf("\n");
            }
        }
	fclose(in);
	return 0;
	}
