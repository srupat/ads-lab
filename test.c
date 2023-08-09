#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node * left;
    struct Node * right;
    int lbit,rbit;
};

// type of tree - inorder threaded binary tree

struct Node * inorder_succ(struct Node * p) {
    if (p->rbit == 0) return p->right;
    p = p->right;
    while (p->lbit == 1) {
        p = p->left;
    }
    return p;
}


void inorder(struct Node * p) {
    struct Node * head = p;
    p = p->left;
    while (p->lbit == 1) p = p->left;
    
    while (p != head) {
        printf("%d ", p->data);
        p = inorder_succ(p);
    }

    // Print the last node
    printf("%d ", p->data);

    printf("\n");
}


struct Node * insert(int val, struct Node * root)
{
    if (root == NULL)
    {
        struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = val;
        temp->left = temp->right = temp;
        temp->lbit = temp->rbit = 0;
        return temp;
    }

    if (root->data > val)
    {
        if (root->lbit == 1)
        {
            root->left = insert(val, root->left);
        }
        else
        {
            struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
            temp->data = val;
            temp->left = root->left;
            temp->right = root;
            temp->lbit = temp->rbit = 1; 
            root->left = temp;
            root->lbit = 0; 
        }
    }
    else if (root->data < val) 
    {
        if (root->rbit == 1)
        {
            root->right = insert(val, root->right);
        }
        else
        {
            struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
            temp->data = val;
            temp->right = root->right;
            temp->left = root;
            temp->lbit = temp->rbit = 1; 
            root->right = temp;
            root->rbit = 0; 
        }
    }
    
    return root;
}


int main()
{
    struct Node * head = (struct Node *)malloc(sizeof(struct Node));
    head->lbit=head->rbit = 1;
    head->left = NULL;
    head->right = head;

    struct Node * root = NULL;
    root = insert(10,root);
    head->left = root;

    insert(15,root);
    insert(11,root);
    insert(3,root);
    
    inorder(root);

    return 0;
}