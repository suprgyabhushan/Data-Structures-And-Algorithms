#include<stdio.h>
#include<stdlib.h>
struct node
	{
    	long long int key;
    	struct node *left;
    	struct node *right;
    	long long int height;
	};

long long int height(struct node *N)
	{
    	if (N == NULL)
        	return 0;
    	return N->height;
	}

long long int max(long long int a, long long int b)
	{
	if(a>b) return a;
	else return b;
	}

struct node* newNode(long long int key)
	{
    	struct node* node = (struct node*)malloc(sizeof(struct node));
    	node->key   = key;
    	node->left   = NULL;
    	node->right  = NULL;
    	node->height = 1;  
    	return(node);
	}

struct node *rightRotate(struct node *y)
	{
    	struct node *x = y->left;
    	struct node *T2 = x->right;
    	x->right = y;
    	y->left = T2;
    	y->height = max(height(y->left), height(y->right))+1;
    	x->height = max(height(x->left), height(x->right))+1;
    	return x;
	}

struct node *leftRotate(struct node *x)
	{
	struct node *y = x->right;
	struct node *T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;
	return y;
	}

long long int getBalance(struct node *N)
	{
    	if (N == NULL) return 0;
    	return height(N->left) - height(N->right);
	}
struct node * search(struct node* node, long long int key)
	{
	if(node == NULL ) return NULL;
	else if(key < node->key)  return search(node->left,key);
	else if(key > node->key)  return search(node->right,key);
	else return node;
	}

struct node* insert(struct node* node, long long int key)
	{
    	if (node == NULL) return(newNode(key)); 
    	if (key < node->key)
        	node->left  = insert(node->left, key);
    	else
        	node->right = insert(node->right, key);
    	node->height = max(height(node->left), height(node->right)) + 1;
    	long long int balance = getBalance(node);
    	if (balance > 1 && key < node->left->key)
        	return rightRotate(node);
    	if (balance < -1 && key > node->right->key)
        	return leftRotate(node);
    	if (balance > 1 && key > node->left->key)
    		{
        	node->left =  leftRotate(node->left);
        	return rightRotate(node);
    		}
    	if (balance < -1 && key < node->right->key)
    		{
        	node->right = rightRotate(node->right);
        	return leftRotate(node);
    		}
    	return node;
	}

struct node * minValueNode(struct node* node)
	{
    	struct node* current = node;
    	while (current->left != NULL)
        	current = current->left; 
    	return current;
	}
struct node* deleteNode(struct node* root, long long int key)
	{
    	if (root == NULL)
        	return root;
    	if ( key < root->key )
        	root->left = deleteNode(root->left, key);
    	else if( key > root->key )
        	root->right = deleteNode(root->right, key);
    	else
    		{
        	if( (root->left == NULL) || (root->right == NULL) )
        		{
            		struct node *temp = root->left ? root->left : root->right;
            		if(temp == NULL)
            			{
                		temp = root;
                		root = NULL;
            			}
            		else 
             			*root = *temp; 
            		free(temp);
        		}
        	else
        		{
            		struct node* temp = minValueNode(root->right);
            		root->key = temp->key;
            		root->right = deleteNode(root->right, temp->key);
        		}
    		}
    	if (root == NULL)
      		return root;
    	root->height = max(height(root->left), height(root->right)) + 1;
    	long long int balance = getBalance(root);
    	if (balance > 1 && getBalance(root->left) >= 0)
        	return rightRotate(root);
    	if (balance > 1 && getBalance(root->left) < 0)
    		{
        	root->left =  leftRotate(root->left);
        	return rightRotate(root);
    		}
    	if (balance < -1 && getBalance(root->right) <= 0)
        	return leftRotate(root);
    	if (balance < -1 && getBalance(root->right) > 0)
    		{
        	root->right = rightRotate(root->right);
        	return leftRotate(root);
    		}
 	return root;
	}

void preOrder(struct node *root)
	{
    	if(root != NULL)
    		{
        	printf("%lld ", root->key);
        	preOrder(root->left);
        	preOrder(root->right);
    		}
	}
long long int trav(struct node *root,long long int val,long long int *max)
	{
	struct node *temp=root;
	if(root==NULL)
		return 0;
	else if(root->key>(*max) && ((root->key)%2)!=0 && root->key>val)
		{
		(*max)=root->key;
		}
	trav(temp->left,val,&(*max));
	trav(temp->right,val,&(*max));
	}
int main(long long int argc,char*argv[])
        {
        struct node *root = NULL;
        long long int total,oper,key,i,max=0;
        FILE *inp=fopen(argv[1],"r");
        fscanf(inp,"%lld",&total);
        for(i=0;i<total;i++)
                {
                fscanf(inp, "%lld %lld" ,&oper,&key);
                if(oper==0)
                        {
			struct node *hi = (struct node*)malloc(sizeof(struct node));
                        hi = search(root,key);
			if(search(root,key)==NULL) printf("False\n");
			else printf("True\n");
                        }
         	 if(oper==1)
                        {
                        root = insert(root,key);
                        }
                if(oper==2)
                        {
                        root = deleteNode(root,key);
                        }
		if(oper==3)
			{
			trav(root,key,&max);
			if(max!=0)
				printf("odd successor is %lld\n",max);
			else
				printf("no\n");	
			max=0;		
			}
                }
	//preOrder(root);
        }
                         
