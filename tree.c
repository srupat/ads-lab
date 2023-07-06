#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *right,*left;
};

struct Node * insert(int num,struct Node * root)
{
    // printf("! ");
    
    if(root == NULL)
    {
        struct Node * root = (struct Node *)malloc(sizeof(struct Node));
        root->data = num;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if(num>root->data)
    {
        root->right = insert(num,root->right);
    }
    else
    {
        root->left = insert(num,root->left);
    }
    
}
    
void preorder(struct Node * root)
{
    if(root == NULL)return;
    
    printf("%d  ", root->data);
    preorder(root->left);
    preorder(root->right);
    
}

int search(struct Node * root, int val)
{
    if(root == NULL)return 0;
    if(root->data==val)return 1;
    if(root->data>val)return search(root->right,val);
    if(root->data<val)return search(root->left,val);
}

int main()
{
    int ch;
    struct Node * root = NULL;
    
    insert(10,root);
    insert(7,root);
    insert(8,root);
    insert(15,root);

    preorder(root);

    return 0;
}