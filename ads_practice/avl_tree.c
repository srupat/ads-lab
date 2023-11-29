#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node* right;
    int height;
};

int maxi(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

struct Node * create(int data)
{
    struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int height(struct Node * root)
{
    if (root == NULL)
        return 0;

    int left = height(root->left);
    int right = height(root->right);

    int height = maxi(left, right) + 1;

    return height;
}

int balanceFactor(struct Node *root)
{
    if (root==NULL) return 0;
    return height(root->left) - height(root->right);
}

struct Node * rightRotate(struct Node * y)
{
    struct Node * x = y->left;
    struct Node * T2 = x->right;

    x->right = y;
    y->left = T2;

    
    y->height = maxi(height(y->left), height(y->right)) + 1;
    x->height = maxi(height(x->left), height(x->right)) + 1;

    // return new root
    return x;
}

struct Node * leftRotate(struct Node * x)
{
    struct Node * y = x->right;
    struct Node * T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = maxi(height(y->left), height(y->right)) + 1;
    x->height = maxi(height(x->left), height(x->right)) + 1;

    return y;
}

struct Node * insert(struct Node * root, int val)
{
    if(root== NULL)
    {
        root = create(val);
        return root;
    }

    else if (val<root->data)
        insert(root->left, val);

    else if(val>root->data)
        insert(root->right, val);

    else 
        return root;

    root->height = maxi(height(root->left), height(root->right)) + 1;

    int bf = balanceFactor(root);

    if(bf>1 && val<root->left->data)
        return rightRotate(root);

    if(bf>1 && val>root->left->data)
    {
        root->left = leftRotate(root);
        return rightRotate(root);
    }

    if(bf<-1 && val>root->right->data)
            return leftRotate(root);

    if(bf<-1 && val<root->right->data)
    {
        root->right = rightRotate(root);
        return leftRotate(root);
    }

    return root;

}

void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->data); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 


int main() 
{ 
    struct Node *root = NULL; 
    
    
    root = insert(root, 10); 
    root = insert(root, 20); 
    root = insert(root, 30); 
    root = insert(root, 40); 
    root = insert(root, 50); 
    root = insert(root, 25); 
        
    printf("Preorder traversal of the constructed AVL tree is \n"); 
    preOrder(root); 
    
    return 0; 
} 