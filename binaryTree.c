#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    int data;
    struct Node * left;
    struct Node * right;
};
struct queueNode
{
    struct Node * data;
    struct queueNode * next;
};
struct queue{
    struct queueNode * f;
    struct queueNode * r;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

struct queueNode * createQueueNode(struct Node * data)
{
    struct queueNode * newNode = (struct queueNode *)malloc(sizeof(struct queueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct queue * createQueue()
{
    struct queue * queue = (struct queue*)malloc(sizeof(struct queue));

    queue->f = NULL;
    queue->r = NULL;

    return queue;
}

int isEmpty(struct queue * queue)
{
    if(queue->f == NULL) return 1;
    return 0;
}

void enqueue(struct queue * queue, struct Node* data) {
    struct queueNode* newNode = createQueueNode(data);
    if (queue->r == NULL) // if its the first ever node to be enqueued 
    {
        queue->f = newNode;
        queue->r = newNode;
    } else {
        queue->r->next = newNode;
        queue->r = newNode;
    }
}

struct Node* dequeue(struct queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }

    struct queueNode* temp = queue->f;
    struct Node* data = temp->data;
    queue->f = queue->f->next;

    if (queue->f == NULL) {
        queue->r = NULL;
    }

    free(temp);
    return data;
}

int compute_height(struct Node * root)
{
    if(root==NULL) return 0;
    
    int left = compute_height(root->left);
    int right = compute_height(root->right);

    int height = (left > right ? left : right);

    return height+1;
}


void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct queue* queue = createQueue();
    enqueue(queue, root);

    while (!isEmpty(queue)) {
        struct Node* current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }

    free(queue);
}

bool areMirrorImages(struct Node * left, struct Node * right)
{
    if(left==NULL && right==NULL) return true;
    if(left==NULL || right==NULL || left->data!=right->data) return false;
    return areMirrorImages(left->left,left->right) && areMirrorImages(right->left,right->right);
}

bool hasMirrorImage(struct Node * root)
{
    if(root==NULL)return false;
    return areMirrorImages(root->left,root->right);
}

struct Node* insert(int parent, struct Node* root, int data, int choice) {
    if (root == NULL) {
        return createNode(data); 
    }

    if (root->data == parent) {
        if (choice == 0) {
            root->left = insert(parent, root->left, data, choice); 
        } else if (choice == 1) {
            root->right = insert(parent, root->right, data, choice); 
        }
    } else {
        if(choice==0){
            root->left = insert(parent, root->left, data, choice);}
        else if(choice ==1){    
            root->right = insert(parent, root->right, data, choice);}
     }

    return root;
}

void printLeafNodes(struct Node * root)
{
    // printf("! ");
    if(root == NULL)return;
    
    printLeafNodes(root->left);
    if(root->left==NULL && root->right==NULL) printf("%d  ", root->data);        
    printLeafNodes(root->right);
    
}

void mirror(struct Node* root)
{
    if (root == NULL)
        return;
    else {
        struct Node* temp;
 
        
        mirror(root->left);
        mirror(root->right);
 
        
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}
int main()
{
    int ch,num,parent,choice;
    struct Node * root = NULL;

    root = insert(0,root,15,0);
    // insert(15,root,13,0);
    // insert(15,root,16,1);
    // insert(13,root,3,1);

    // printLeafNodes(root);
    // levelOrderTraversal(root);
    // mirror(root);
    // compute_height(root);

    while(1){
    printf("Enter 1 to insert\n2 to compute height\n3 to display level-order traversal\n4 to detect whether given tree has mirror image or not\n5 to print all leaf nodes recursively\n6 to construct mirror image of given binary tree\n7 to exit\n\n");
    scanf("%d",&ch);
    switch (ch)
        {
        case 1:
            printf("Enter data of the node to be inserted\n");
            scanf("%d",&num);
            printf("Enter the parent\n");
            scanf("%d",&parent);
            printf("Enter 0 to insert to the left and 1 to insert to the right\n");
            scanf("%d",&choice);
            insert(parent,root,num,choice);
            break;
        case 2:
            printf("%d",compute_height(root));
            break;
        case 3:
            levelOrderTraversal(root);
            printf("\n\n");
            break;
        case 4:
            if(hasMirrorImage) printf("the given tree has a mirror image\n");
            else printf("the given tree does not have a mirror image\n");
            break;
        case 5:
            printLeafNodes(root);
            break;
        case 6:
            mirror(root);
            break;
        case 7:
            exit(1);
            break;
        default:
            printf("Invalid\n");
            break;
        }
    }
    return 0;
}