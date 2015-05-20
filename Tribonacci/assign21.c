#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{

	int index,k,string_length,Product,New_product,i,j;
	int number[1001]={0};
	char string_digit[200];
	int a;
	FILE *f_read;
    
    	index=0;
    	f_read=fopen(argv[1],"r");
	for(i=0;i<3;i++)
	{
		fscanf(f_read,"%d",&a);
		printf("%d\n",a);
	}

    	while (fscanf(f_read,"%s",string_digit)==1)
	{
		string_length=strlen(string_digit);
      	for(k=0;k<string_length;k++)    {   number[index]=string_digit[k]-48;index++;   }
    	}
    	fclose(f_read);

    /*for(i=0;i<=995;i++){
        New_product=1;
        for(j=i;j<=i+4;j++) New_product=New_product*number[j];
        if(New_product>=Product)  Product=New_product;
    }
    printf("%d\n",Product);*/



	for(i=0;i<index;i++)
	{
		printf("%d",number[i]);
	}
	printf("\n");
    	return 0;
}

