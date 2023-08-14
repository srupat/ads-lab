#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node * top = NULL;

struct queue
{
    int size;
    int f;
    int r;
    int * arr;
};

int isFullq(struct queue * q)
{
    if(q->r == q->size - 1)
    {
        return 1;
    }
    return 0;
}
int isEmptyq(struct queue * q)
{
    if(q->r == q->f)
    {
        return 1;
    }
    return 0;
}
void enqueue(struct queue * q,int val)
{
    if(isFullq(q))
    {
        printf("This queue is full\n");
    }
    else{
        q->r++;
        q->arr[q->r] = val;
    }
}
int dequeue(struct queue * q)
{
    int a=-1;
    if(isEmptyq(q))
    {
        printf("Cannot dequeue, queue is empty\n");
    }
    else{
        q->f ++;
        a = q->arr[q->f];
    }
    return a;
}

int isEmpty() {
    if (top == NULL) {
        return 1;
    }
    return 0;
}

int isFull() {
    struct Node *p = (struct Node *)malloc(sizeof(struct Node));
    if (p == NULL) {
        return 1;
    } else {
        free(p); // Release the allocated memory
        return 0;
    }
}

void displayAdjMatrix(int ** G, int n)
{
    printf("The matrix is as follows\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d  ",G[i][j]);
        }
        printf("\n");
    }
}

void displayAdjList(struct Node * A[],int n)
{
    printf("The adjacency list is as follows\n");
    for(int i=0;i<n;i++)
    {
        struct Node * temp = A[i];
        while(temp!=NULL)
        {
            printf("%d | ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void createAdjList(struct Node* A[], int n) 
{
    char ch;
    int num;
    for (int i = 0; i < n; i++) {
        A[i] = (struct Node*)malloc(sizeof(struct Node));
        A[i]->data = i;  
        A[i]->next = NULL;
    }
    for (int i = 0; i < n; i++) 
    {
        printf("Is there any node connected to node %d [y/n]\n", i);
        scanf(" %c", &ch);
        while (ch == 'y') 
        {
            printf("Enter the connected node (vertex number)\n");
            scanf("%d", &num);

            struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
            struct Node* temp = A[i]->next;

            ptr->data = num;
            ptr->next = NULL;

            if (A[i]->next == NULL) 
            {
                A[i]->next = ptr;
            } 
            else 
            {
                while (temp->next != NULL) 
                {
                    temp = temp->next;
                }

                temp->next = ptr;
            }
            printf("Do you wish to continue?[y/n]\n");
            scanf(" %c", &ch);
        }
    }
    displayAdjList(A,n);
}

struct Node * push(struct Node * top,int x)
{
    if(isFull(top)){
        printf("Stack overflow\n");
    }
    else
    {
        struct Node * n = (struct Node *)malloc(sizeof(struct Node));
        n->next = top;
        n->data = x;
        top = n;
        return top;
    }
}

int pop(struct Node* tp)
{
    if(isEmpty(tp))
    {
        printf("Stack Underflow\n");
    }
    else{
        struct Node* n = tp;
        top = (tp)->next;
        int x = n->data;
        free(n);
        return x; 
    }
}

int stackTop()
{
    return top->data;
}


void createAdjMatrix(int** G, int n)
{
    int bit;
    
    for(int j = 0;j<n;j++)
    {
        for(int k=0;k<n;k++)
        {
            printf("Enter 1 if there exists an edge between %d and %d\t",j,k);
            scanf("%d",&bit);
            G[j][k] = bit;
        }
    }
    displayAdjMatrix(G,n);
}


void dfs_adj_mat_rec(int ** G, int i, int n, int * visited)
{
    printf("%d ", i);    
    visited[i]=1;
    for (int j = 0; j < n; j++)
    {
        if(G[i][j]==1 && visited[j]==0)
        {
            dfs_adj_mat_rec(G,j,n,visited);
        }
    }
    
}

void dfs_adj_list_rec(struct Node * A[], int n, int i, int * visited)
{
    printf("%d ", i);
    visited[i] = 1;
    
    struct Node * temp = A[i]->next; 

    while (temp != NULL)
    {
        int j = temp->data;
        if (visited[j] == 0)
        {
            dfs_adj_list_rec(A, n, j, visited);
        }
        temp = temp->next;
    }
}


void dfs_adj_list_non_rec(struct Node *A[], int n) {
    int start;
    printf("Enter the start vertex\n");
    scanf("%d", &start);
    int *visited = (int *)calloc(n, sizeof(int));
    visited[start] = 1;
    top = push(top, start); 

    printf("DFS traversal order: ");
    while (!isEmpty()) {
        int x = pop(top); 
        printf("%d ", x);

        struct Node *temp = A[x];
        while (temp->next != NULL) 
        {
            temp = temp->next;
            if (visited[temp->data] == 0) 
            {
                visited[temp->data] = 1;
                top = push(top, temp->data);
            }
        }
    }
    printf("\n");
}

void dfs_adj_mat_non_rec(int **G, int n) {
    int start;
    printf("Enter the start vertex\n");
    scanf("%d", &start);
    int *visited = (int *)calloc(n, sizeof(int));
    visited[start] = 1;
    top = push(top, start);

    printf("DFS traversal order: ");
    while (!isEmpty()) {
        int x = pop(top);
        printf("%d ", x);

        for (int i = 0; i < n; i++) {
            if (G[x][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                top = push(top, i);
            }
        }
    }
    printf("\n");
}

void bfs_adj_list_non_rec(struct Node * A[], int n)
{
    int start;
    printf("Enter the start vertex\n");
    scanf("%d", &start);
    
    int *visited = (int *)calloc(n, sizeof(int));
    visited[start] = 1;

    struct queue q;
    q.size = n;
    q.f = q.r = -1;
    q.arr = (int *)malloc(n * sizeof(int));
    
    enqueue(&q, start);

    while (!isEmptyq(&q))
    {
        int current = dequeue(&q);
        printf("%d ", current);

        struct Node *temp = A[current]->next; 

        while (temp != NULL)
        {
            if (visited[temp->data] == 0)
            {
                visited[temp->data] = 1;
                enqueue(&q, temp->data);
            }
            temp = temp->next; 
        }
    }
    printf("\n");

    free(visited);
    free(q.arr);
}

void bfs_adj_mat_non_rec(int **G, int n)
{
    int start;
    printf("Enter the start vertex\n");
    scanf("%d", &start);
    
    int *visited = (int *)calloc(n, sizeof(int));
    visited[start] = 1;

    struct queue q;
    q.size = n;
    q.f = q.r = -1;
    q.arr = (int *)malloc(n * sizeof(int));
    
    enqueue(&q, start);

    while (!isEmptyq(&q))
    {
        int x = dequeue(&q);
        printf("%d ", x);

        for (int i = 0; i < n; i++) {
            if (G[x][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
        
    }
    printf("\n");

    free(visited);
    free(q.arr);
}

int isBipartite(int **G, int n) {
    int *colour = (int *)calloc(n, sizeof(int)); 
    struct queue q;
    q.size = n;
    q.f = q.r = -1;
    q.arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (colour[i] == 0) 
        {
        colour[i] = 1; 
        enqueue(&q, i);

        while (!isEmptyq(&q)) 
        {
        int current = dequeue(&q);

        for (int j = 0; j < n; j++) {
        if (G[current][j] == 1) 
        {
            if (colour[j] == 0) 
            {
                colour[j] = -colour[current]; // -1 represents the opposite set
                enqueue(&q, j);
            } 
            else if (colour[j] == colour[current]) 
            {
                free(q.arr);
                free(colour);
                return 0; 
            }
        }
    }
        }
        }
    }

    free(q.arr);
    free(colour);
    return 1; 
}

int main() {
    int n,ch;
    printf("Enter the number of vertices\n");
    scanf("%d", &n);
    struct Node** A = (struct Node**)malloc(sizeof(struct Node*) * n);
    createAdjList(A, n);
    
    int ** G;
    G = (int **)calloc(n, sizeof(int *));
    for(int i=0;i<n;i++)
    {
        G[i] = (int*)calloc(n, sizeof(int));
    }
    createAdjMatrix(G,n);

    int *visited = (int *)calloc(n, sizeof(int));

    while(1){
    printf("Enter 1 dfs + adjacency list + recursive\n2 dfs + adjacency list + non-recursive\n3 dfs + adjacency matrix + recursive\n4 dfs + adjacency matrix + non-recursive\n5 bfs + adjacency list + non-recursive\n6 bfs + adjacency matrix + non-recursive \n7 check if graph is bipartite or not\n8 to exit\n\n");
    scanf("%d",&ch);
    switch (ch)
        {
        case 1:
            dfs_adj_list_rec(A,n,0,visited);
            break;
        case 2:
            dfs_adj_list_non_rec(A,n);
            break;
        case 3:
            dfs_adj_mat_rec(G,0,n,visited);
            break;
        case 4:
            dfs_adj_mat_non_rec(G,n);
            break;
        case 5:
            bfs_adj_list_non_rec(A,n);
            break;
        case 6:
            bfs_adj_mat_non_rec(G,n);
            break;
        case 7:
            if(isBipartite(G,n)) printf("the inputted graph is bipartite\n");
            else printf("The inputted graph is not bipartite\n");
            break;
        case 8:
            exit(1);
            break;
        default:
            printf("Invalid\n");
            break;
        }
    }

    
    for (int i = 0; i < n; i++) {
        free(G[i]);
    }
    free(G);
    free(A);
    return 0;
}
