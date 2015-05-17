#include<stdio.h>
#include<stdlib.h>
 
// An AVL tree node
struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
};
 
int max(int a, int b);
 
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
struct node* newNode(int key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
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
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
struct node* insert(struct node* node, int key)
{

    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
    node->height = max(height(node->left), height(node->right)) + 1;
 
    int balance = getBalance(node);
 
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
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
 
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
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
//        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
 void inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
//        printf("%d ", root->key);
        inOrder(root->right);
    }
}
void postOrder(struct node *root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
//        printf("%d ", root->key);
    }
}
int search(struct node *root,int k)
{

	if(root->key == k)
	{	return 1;
	}
	else if(k < root->key)
		{
		if(root->left==NULL)return 0;
		 return search(root->left,k);
		}
	else if(k > root->key)
		{
		if(root->right==NULL)return 0;
		return search(root->right,k);
		}
	return 0;

}
struct node * odd(struct node *root,struct node *k)
{
    if(k->right != NULL)
        {
        k=minValueNode(k->right);
        if((k->key)%2!=0)    
            printf("%d ",k->key);
        else
             printf("0");
        }
    struct node *p= k->parent;
    while(p !=NULL && k == p-> right)
        {
        k=p;
        p=p->parent;
        }
    if((p->key)%2 != 0)
        printf("%d ",p->key);
    else
        {
        p=p->parent;
        while((p->key)%2 ==0)
            {
            p=p->parent;
            }
        printf("%d ",p->key);    
        }
}
int main(int argc, char* arg[])
{
  struct node *root = NULL;
  struct node *temp;
FILE*in = fopen(arg[1],"r");
int option,data,N,search_result;
 fscanf(in,"%d\n",&N);
    while(!feof(in))
{
fscanf(in,"%d %d\n",&option,&data);
if(option==0)

{
	if(search(root,data)==1)
	printf("key = %d  FOUND\n",data);
	else 
    printf("key = %d  NOT FOUND\n",data);
}
else if(option==1)
{

    root = insert(root, data);
 }
else if(option==2)
{
    root = deleteNode(root, data);
}
else if(option==3)
{
    temp->key=data;
    root= odd(root,temp);
}
}
}
