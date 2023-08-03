#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node * left;
    struct Node * right;
    int lbit,rbit;
};

// type of tree - inorder threaded binary tree

struct Node * inorder_succ(struct Node * p)
{
    if(p->rbit==0) return p->right;
    p = p->right;
    while(p->lbit==1)
    {
        p=p->left;
        return p;
    }
}

void inorder(struct Node * p)
{
    struct Node * head;
    head = p;
    p = p->left;
    while(p->lbit ==1) p = p->left;
    while(p!=head)
    {
        printf("%d ",p->data);
        p = inorder_succ(p);
    }
}

struct Node * insert(int num, struct Node * root,struct Node * head)
{
    if(root==NULL)
    {
        
        root->data = num;
        root->lbit=root->rbit=0;
        root->left=root->right=head;
        return root;
    }
    else if(num<root->data)
    {
        if(root->lbit==0)
        {
            
        }
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
    head->lbit=head->rbit = 1;
    head->left = NULL;
    head->right = head;

    struct Node * root = NULL;
    root = insert(10,root,head);
    head->left = root;

    insert(15,root,head);
    insert(11,root,head);
    insert(3,root,head);
    // preorder(root);
    // inorder(root);

    return 0;
}