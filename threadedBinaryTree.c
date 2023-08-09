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
    }
    return p;
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
    printf("\n");
}


struct Node * insert(int val, struct Node * root, struct Node * head)
{
    
    if (root == NULL)
    {
        struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = val;
        temp->left = temp->right = head;
        temp->lbit = temp->rbit = 0;
        return temp;
    }

    if (root->data > val)
    {
        if (root->lbit == 1)
        {
            root->left = insert(val, root->left, head);
        }
        else
        {
            struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
            temp->data = val;
            temp->left = root->left;
            temp->right = root;
            temp->lbit = temp->rbit = 0; 
            root->left = temp;
            root->lbit = 1;
        }
    }
    if (root->data < val) 
    {
        if (root->rbit == 1)
        {
            root->right = insert(val, root->right, head);
        }
        else
        {
            struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
            temp->data = val;
            temp->right = root->right;
            temp->left = root;
            temp->lbit = temp->rbit = 0; 
            root->right = temp;
            root->rbit = 1; 
        }
    }
    
    return root;
}

struct Node * findMax(struct Node * t,struct Node * head)
{
    while(t->right!=head)
       { t = t->right;}

    return t;
}

struct Node * delete(struct Node * head,struct Node * root, int val)
{
    
    struct Node * temp;
    if(root == NULL) printf("value not present");
    
    else if(val<root->data) root->left = delete(head, root->left, val);
    
    else if(val>root->data) root->right = delete(head, root->right, val);

    else
    {
        if(root->rbit!=0 && root->lbit!=0)
        {
            temp = findMax(root->left,head);
            root->data = temp->data;
            root->left = delete(head,root->left,temp->data);
        }
        else{
            temp = root;
            if(root->lbit == 0)
            {
                root = root->right;
                root->left = temp->left;
            }
            if(root->rbit == 0) 
            {
                root = root->left;
                root->right = temp->right;
            }
            free(temp);
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
    int num,ch;
    struct Node * root = NULL;
    printf("Enter the data of root node\n");
    scanf("%d",&num);
    root = insert(num,root, head);
    head->left = root;

    while(1){
    printf("Enter 1 to insert\n2 to display(inorder)\n3 to delete particular node\n4 to exit\n\n");
    scanf("%d",&ch);
    switch (ch)
        {
        case 1:
            printf("Enter data of the node to be inserted\n");
            scanf("%d",&num);
            insert(num,root,head);
            break;
        case 2:
            inorder(head);
            break;
        case 3:
            printf("Enter the data of the node to be deleted\n");
            scanf("%d",&num);
            delete(head,root,num);
            break;
        case 4:
            exit(1);
            break;        
        default:
            printf("Invalid\n");
            break;
        }
    }
    
    return 0;
}