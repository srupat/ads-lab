#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node * left;
    struct Node * right;
    int lbit,rbit;
};

struct Node * insert(int num, struct Node * root)
{
    if(root==NULL)
    {
        struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
        root = temp;
        root->data = num;
        root->lbit,root->rbit=0;
        root->left,root->right=NULL;
        return root;
    }
    else if(num<root->data)
    {
        root->lbit = 1;
        root->left = insert(num, root->left);
    }
    else if(num>root->data)
    {
        root->rbit = 1;
        root->right = insert(num, root->right);
    }
}

int main()
{
    
    struct Node * head = (struct Node *)malloc(sizeof(struct Node));
    head->lbit, head->rbit = 1;
    struct Node * root = insert(10,root);
    head->left = root;
    head->right = head;


    return 0;
}