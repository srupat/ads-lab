#include<stdio.h>
#include<stdlib.h>

// let us first try to implement preorder, postorder and inorder traversals with a binary tree
struct Node{
    struct Node *left;
    struct Node *right;
    int data;
};

struct queue{
    struct Node * data;
    struct queue * next;
};

struct queue *f = NULL;
struct queue *r = NULL;

struct queue * createQueueNode(struct Node * t)
{
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    q->data = t;
    q->next = NULL;
    return q;
}

struct Node * createNode(int val)
{
    struct Node * newNode= (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void enqueue(struct queue *f, struct queue* r, int val)
{
    // when the rear is equal to the size, the queue is full
    if(r->next == NULL)
    {
        printf("queue is full\n");
        return;
    }
    // we are maintaining a queue of all struct Nodes according to position
    struct Node * node = createNode(val);
    struct queue* qnode = createQueueNode(node);
    r->next = qnode;
}

struct Node * dequeue(struct queue* f, struct queue* r)
{
    if(f==r) return NULL;
    struct queue* temp = f->next;
    f->next = temp->next;
    return temp->data;
}

struct Node * insert(struct Node *root, int data)
{
    if(root==NULL)
    {
        root = createNode(data);
        return root;
    }

    if (root->left== NULL)
    {
        root->left = insert(root->left, data);
        enqueue(f,r,data);
    }
     
    else if (root->right== NULL)
    {
        root->right = insert(root->right, data);
        enqueue(f,r,data);
    }
    return root;
}

void displayqueue(struct queue * f, struct queue * r)
{
    struct queue * temp = f;
    while(temp != NULL)
    {
        printf("%d ", temp->data->data);
        temp = temp->next;
    }
}

int main()
{
    struct queue * q = (struct queue*)malloc(sizeof(struct queue));
    //f = q;
    //r = q;
    struct Node * root = NULL;
    root = insert(root, 12);
    root = insert(root, 56);
    root = insert(root, 11);
    root = insert(root, 29);
    root = insert(root, 7);
    root = insert(root, 9);
    root = insert(root, 20);
    displayqueue(f,r);

    return 0;
}