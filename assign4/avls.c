#include<stdio.h>
#include<stdlib.h>
struct node
	{
    	long long int key;
   	struct node *left;
    	struct node *right;
    	long long int height;
	};
long long int max(long long int a, long long int b);
long long int height(struct node *N)
	{
    	if (N == NULL)
        	return -1;
    	return N->height;
	}
long long int max(long long int a, long long int b)
	{
    	if(a > b)
		return a;
	else 
		return b;
	}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node* newNode(long long int key)
	{
   	struct node* node = (struct node*)malloc(sizeof(struct node));
    	node->key   = key;
   	node->left   = NULL;
    	node->right  = NULL;
    	node->height = 0;  // new node is initially added at leaf
    	return(node);
	}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
	{
    	struct node *x = y->left;
    	struct node *T2 = x->right;
 
    	// Perform rotation
    	x->right = y;
    	y->left = T2;
 
    	// Update heights
    	y->height = max(height(y->left), height(y->right))+1;
    	x->height = max(height(x->left), height(x->right))+1;
 
    	// Return new root
    	return x;
	}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
	{
    	struct node *y = x->right;
    	struct node *T2 = y->left;
 
    	// Perform rotation
    	y->left = x;
    	x->right = T2;
 	
    	//  Update heights
    	x->height = max(height(x->left), height(x->right))+1;
    	y->height = max(height(y->left), height(y->right))+1;
 
    	// Return new root
    	return y;
	}
 
// Get Balance factor of node N
long long int getBalance(struct node *N)
	{
    	if (N == NULL)
        	return 0;
    	return height(N->left) - height(N->right);
	}
 
struct node* insert(struct node* node, long long int key)
	{
    	/* 1.  Perform the normal BST rotation */
    	if (node == NULL)
        	return(newNode(key));
 
    	if (key < node->key)
        	node->left  = insert(node->left, key);
    	else
        	node->right = insert(node->right, key);
 
    	/* 2. Update height of this ancestor node */
    	node->height = max(height(node->left), height(node->right)) + 1;
 
    	/* 3. Get the balance factor of this ancestor node to check whether
       		this node became unbalanced */
    	long long int balance = getBalance(node);
 
    	// If this node becomes unbalanced, then there are 4 cases
 
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
 	
    	/* return the (unchanged) node pointer */
    	return node;
	}
 
/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node)
	{
    	struct node* current = node;
 
    	/* loop down to find the leftmost leaf */
    	while (current->left != NULL)
        	current = current->left;
 	return current;
	}
struct node * maxValueNode(struct node * node)
	{
	struct node * current;
	current=node;
	while(current->right != NULL)
		current = current->right;
	return current;
	}
struct node* deleteNode(struct node* root, long long int key)
	{
    	// STEP 1: PERFORM STANDARD BST DELETE
 
    	if (root == NULL)
        	return root;
 	// If the key to be deleted is smaller than the root's key,
    	// then it lies in left subtree
    	if ( key < root->key )
        	root->left = deleteNode(root->left, key);
 
    	// If the key to be deleted is greater than the root's key,
    	// then it lies in right subtree
    	else if( key > root->key )
        	root->right = deleteNode(root->right, key);
 
    	// if key is same as root's key, then This is the node
    	// to be deleted
    	else
    		{
        	// node with only one child or no child
        	if( (root->left == NULL) || (root->right == NULL) )
        		{
            		struct node *temp = root->left ? root->left : root->right;
 
            		// No child case
            		if(temp == NULL)
            			{
                		temp = root;
                		root = NULL;
            			}
            		else // One child case
             		*root = *temp; // Copy the contents of the non-empty child
 			free(temp);
        	}
        	else
        		{
            		// node with two children: Get the inorder successor (smallest
            		// in the right subtree)
            		struct node* temp = minValueNode(root->right);
 
            		// Copy the inorder successor's data to this node
            		root->key = temp->key;
 
            		// Delete the inorder successor
            		root->right = deleteNode(root->right, temp->key);
        		}
    		}
 
    	// If the tree had only one node then return
    	if (root == NULL)
      		return root;
 
    	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    	root->height = max(height(root->left), height(root->right)) + 1;
 
    	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    	//  this node became unbalanced)
    	long long int balance = getBalance(root);
 
    	// If this node becomes unbalanced, then there are 4 cases
 
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
        	printf("%lld ", root->key);
        	preOrder(root->left);
        	preOrder(root->right);
    		}
	}
long long int search(struct node *temp,long long int value)
	{
	if(temp==NULL)
		return 0;
	if(value==temp->key)
		{
		printf("true\n");
		return 0;
		}
	if(value<temp->key)
		{
		return search(temp->left,value);
		}
	if(value>temp->key)
		{
		return search(temp->right,value);
		}
	return 0;
	}
struct node * trav(struct node *temp,long long int value)
	{
	if(temp==NULL)
		return NULL;
	if(value==temp->key)
	 	{
		return temp;
		}
	
	if(value>temp->key)
		{
		return trav(temp->right,value);
		}
	if(value<temp->key)
		{
		return trav(temp->left,value);
		}	
	}
long long int oddtrav(struct node *temp,long long int value)
    {
    if(temp==NULL)
        return -1;
    long long int ref=temp->key;
    while(temp->left!=NULL)
        {
        temp=temp->left;
        if((temp->key)%2!=0)
            {
            ref=temp->key;
            }
        }
    return ref;
    }
    
long long int oddsuccessor(struct node *temp,long long int value)
    {
    struct node *n;
    long long int number=0;
    n=(struct node *)malloc(sizeof(struct node));
    n=trav(temp,value);
    if(n==NULL)
        {
        printf("does not exist\n");
        return 0;
        }
    else
        {
        number=oddtrav(n->right,value);
        if(number==-1)
            printf("minodd successor does not exist\n");
	  printf("%lld\n",number);
        }
    return 0;
    }
int main(int argc,char *argv[]) 
	{
  	struct node *root = NULL;
 	FILE *in;
	long long int ref=0;
	long long int number=0;
	in=fopen(argv[1],"r");
    fscanf(in,"%lld\n",&ref);
	while(!feof(in))
		{
		fscanf(in,"%lld",&ref);
		if(ref==0)
			{
			fscanf(in,"%lld\n",&number);
			search(root,number);
			}
		if(ref==1)
			{
			fscanf(in,"%lld\n",&number);
            root=insert(root,number);
			}
		if(ref==2)
			{
			fscanf(in,"%lld\n",&number);
			root=deleteNode(root,number);
			}
        if(ref==3)
            {
            fscanf(in,"%lld\n",&number);
            oddsuccessor(root,number);
            }
        }
 	return 0;
	}
