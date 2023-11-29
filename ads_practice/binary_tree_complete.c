#include<stdio.h>
#include<stdlib.h>

struct Node 
{
    int data;
    struct Node * left;
    struct Node * right;
};

struct stack
{
    int size;
    int top;
    struct Node ** arr;
};

struct Node * newNode(int data)
{
    struct Node * n = (struct Node *)malloc(sizeof(struct Node));
    if(n == NULL)
    {
        return n;
    }
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void insert(struct Node * root, int val)
{
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node) * 100);
    int front = -1;
    int rear = -1;

    if(root== NULL)
    {
        root = newNode(val);
        return;
    }

    queue[rear++] = root;

    while(front<rear)
    {
        struct Node * temp = queue[front++];
        if(temp->left == NULL)
        {
            temp->left = newNode(val);
            break;
        }

        else queue[rear++] = temp->left;

        if(temp->right == NULL)
        {
            temp->right = newNode(val);
            break;
        }

        else queue[rear++] = temp->right;
    }
    free(queue);
}

int printLevelOrder(struct Node * root)
{
    struct Node ** queue = (struct Node**)malloc(sizeof(struct Node) * 100);
    int front = -1;
    int rear = -1;
    int count = -1;

    queue[rear++] = root;

    while(front<rear)
    {
        struct Node * temp = queue[front++];
        printf("%d  ", temp->data);

        if(temp->left)
            queue[rear++] = temp->left;

        if(temp->right)
            queue[rear++] = temp->right;

        else {
            count++;
            continue;
        }
    }

    free(queue);
    return count;
}

void push(struct stack *s, struct Node * temp)
{
    if(s->top == s->size -1) return;
    s->arr[s->top ++] = temp;
}

struct Node* pop(struct stack* s)
{
    if(s->top == -1) return NULL;
    struct Node * a = s->arr[s->top -1 ];
    s->top --;
    return a;
}

int isEmpty(struct stack * s)
{
    if(s->top == -1) return 1;
    return 0;
}

void preorder(struct Node* root)
{
    struct Node * temp = root;
    struct Node * prev = NULL;
    struct stack * s = (struct stack*)malloc(sizeof(struct stack)*50);

    s->top = -1;
    s->size = 30;

    s->arr = (struct Node **)malloc(sizeof(struct Node)*s->size);

    s->arr[++s->top] = temp;
    while(!isEmpty(s) || temp != NULL)
    {
        if(temp != NULL)
        {
            printf("%d  ", temp->data);
            if(temp->right != NULL)
                push(s, temp->right);
            temp = temp->left;        
        }
        else
        {
            if (s->top > 0)
                temp = s->arr[s->top - 1];
            pop(s);
        }
    }


}

void inorder(struct Node* root)
{
    if (root == NULL) return;
    struct Node * temp = root;
    struct Node * prev = NULL;
    struct stack * s = (struct stack*)malloc(sizeof(struct stack)*50);

    s->top = -1;
    s->size = 30;

    s->arr = (struct Node **)malloc(sizeof(struct Node)*s->size);

    s->arr[++s->top] = temp;
    while(!isEmpty(s) || temp != NULL)
    {
        while(temp != NULL)
        {
            push(s, temp);
            temp = temp->left;        
        }
    
        temp = pop(s);
        printf("%d ", temp->data);
        temp = temp->right;       
    }


}

int main()
{
    struct Node * root = newNode(12);
    insert(root, 56);
    insert(root, 11);
    insert(root, 29);
    insert(root, 7);
    insert(root, 9);
    insert(root, 20);

    printf("The level order traversal is \n");
    printf("%d ", printLevelOrder(root));

    printf("\nPreorder traversal\n");
    preorder(root);

    printf("\nInorder traversal\n");
    inorder(root);

    return 0;
}