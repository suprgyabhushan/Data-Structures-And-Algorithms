#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
if(a>b) return a;
else return b;
}

struct node* newNode(int key)
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

int getBalance(struct node *N)
{
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}
struct node * search(struct node* node, int key)
{
if(node == NULL ) return NULL;
else if(key < node->key)  return search(node->left,key);
else if(key > node->key)  return search(node->right,key);
else return node;
}

struct node* insert(struct node* node, int key)
{
    if (node == NULL) return(newNode(key)); 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);
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
struct node* deleteNode(struct node* root, int key)
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
    int balance = getBalance(root);
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
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int getsmallestoddtoright(struct node *root, int key);
int getsmallestoddtoleft(struct node *root, int key)
{
	int odd1 = 100000;
	struct node *ptr;
	ptr = root->left;
	
	if((ptr->key)/2 == 1)
	{
		if(ptr->key <= odd1)
		{
			
			odd1 = ptr->key;
			if(ptr->left == NULL)	return odd1;
			ptr = ptr->left;
			odd1 = getsmallestoddtoleft(ptr, key);
		}
		else
		{
			if(ptr->left == NULL)	return odd1;
			odd1 = getsmallestoddtoleft(ptr, key);
		}
			
	}
	else
	{
		if(ptr->key > key)
		{
			if(ptr->left == NULL)	return odd1;
			odd1 = getsmallestoddtoleft(ptr, key);
		}
		else
		{
			if(ptr->right == NULL)	return odd1;
			odd1 = getsmallestoddtoright(ptr, key);
		}
	}
	
	printf("Odd in function %d\n", odd1);
	return odd1;
}




int getsmallestoddtoright(struct node *root, int key)
{
	int odd1 = 100000;
	struct node *ptr;
	ptr = root->right;
	
	if((ptr->key)/2 == 1)
	{
		if(ptr->key <= odd1)
		{
			
			odd1 = ptr->key;
			if(ptr->left == NULL)	return odd1;
			ptr = ptr->left;
			odd1 = getsmallestoddtoleft(ptr, key);
		}
		else
		{
			if(ptr->left == NULL)	return odd1;
			odd1 = getsmallestoddtoleft(ptr, key);
		}
			
	}
	else
	{
		if(ptr->key > key)
		{
			if(ptr->left == NULL && ptr->right == NULL)	return ptr->key;
			if(ptr->left == NULL)	return ptr->key;
			else
				odd1 = getsmallestoddtoleft(ptr, key);
		}
		else
		{
			if(ptr->right == NULL)	return odd1;
			odd1 = getsmallestoddtoright(ptr, key);
		}
	}
	
	printf("Odd in second function %d\n", odd1);
	return odd1;
}





int main(int argc,char*argv[])
{
	struct node *root = NULL;
    int total,oper,key,i;
    int odd1 = 100000, odd2 = 100000;
    int array[10000], j = 0;
    FILE *inp=fopen(argv[1],"r");
    fscanf(inp,"%d",&total);
    for(i=0;i<total;i++)
    {
        fscanf(inp, "%d %d" ,&oper,&key);
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
        if(oper == 3)
        {
        	if(root->key > key)
        	{
        		odd1 = getsmallestoddtoleft(root, key);
        		odd2 = getsmallestoddtoright(root, key);
        		printf("odd1 %d odd2 %d\n", odd1, odd2);
        		if(odd1 < odd2)
        			array[j] = odd1;
        		else
        			array[j] = odd2;
        		j++;
        	}
        	else
        	{
        		odd1 = getsmallestoddtoright(root, key);
        		printf("odd1 %d\n", odd1);
          		array[j] = odd1;
        		j++;
        	}
        }
    }
	
	int k;
	printf("%d %d",array[0],array[1]);
}
                         
