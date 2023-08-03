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
        struct Node * temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = num;
        temp->left = NULL;
        temp->right = NULL;
        root = temp;
        return root;
    }
    else if(num>root->data)
    {
        root->right = insert(num,root->right);
    }
    else if (num<root->data)
    {
        root->left = insert(num,root->left);
    }
     return root;
}

struct Node * findMax(struct Node * t)
{
    while(t->right!=NULL)
       { t = t->right;}

    return t;
}

struct Node * delete(struct Node * root, int val)
{
    struct Node * temp;
    if(root == NULL) printf("value not present");
    
    else if(val<root->data) root->left = delete(root->left,val);
    
    else if(val>root->data) root->right = delete(root->right,val);

    else
    {
        if(root->right!=NULL && root->left!=NULL)
        {
            temp = findMax(root->left);
            root->data = temp->data;
            root->left = delete(root->left,temp->data);
        }
        else{
            temp = root;
            if(root->left == NULL) root = root->right;
            if(root->right == NULL) root = root->left;
            free(temp);
        }
    }
    return root;
}  


void preorder(struct Node * root)
{
    // printf("! ");
    if(root == NULL)return;
    
    printf("%d  ", root->data);
    preorder(root->left);
    preorder(root->right);
    
}

void postorder(struct Node * root)
{
    if(root == NULL)return;
    
    preorder(root->left);
    preorder(root->right);
    printf("%d  ", root->data);
    
}

void inorder(struct Node * root)
{
    // printf("! ");
    if(root == NULL)return;
    
    preorder(root->left);
    printf(" %d  ", root->data);
    preorder(root->right);
    
}

int search(struct Node * root, int val)
{
    if(root == NULL)return 0;
    if(root->data==val)return 1;
    if(root->data<val)return search(root->right,val);
    if(root->data>val)return search(root->left,val);
}

int main()
{
    int ch,num;
    struct Node * root = NULL;
    printf("Enter the data of root node\n");
    scanf("%d",&num);
    root = insert(num,root);
    while(1){
    printf("Enter 1 to insert\n2 to display(preorder)\n3 to display(inorder)\n4 to display(postorder)\n5 to search\n6 to delete\n7 to exit\n\n");
    scanf("%d",&ch);
    switch (ch)
        {
        case 1:
            printf("Enter data of the node to be inserted\n");
            scanf("%d",&num);
            insert(num,root);
            break;
        case 2:
            preorder(root);
            printf("\n\n");
            break;
        case 3:
            inorder(root);
            printf("\n\n");
            break;
        case 4:
            postorder(root);
            printf("\n\n");
            break;
        case 5:
            printf("Enter the data to be searched\n");
            scanf("%d",&num);
            if(search(root,num)==1) printf("Present\n");
            else printf("Not Present\n");
            break;
        case 6:
            printf("Enter the data to be deleted\n");
            scanf("%d",&num);
            delete(root,num);
            break;
        case 7:
            exit(1);
            break;
        default:
            printf("Invalid\n");
            break;
        }
    }
    
    // root = insert(10,root);
    // insert(7,root);
    // insert(8,root);
    // insert(15,root);

    // preorder(root);
    // postorder(root);
    // inorder(root);
    // printf("%d",search(root,8));

    return 0;
}