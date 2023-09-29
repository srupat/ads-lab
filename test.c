#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    int weight;
    struct Node* next;
};

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
    int num,weight;
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

            printf("Enter the weight between %d and %d\n",i,num);
            scanf("%d",&weight);

            struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
            struct Node* temp = A[i]->next;

            ptr->data = num;
            ptr->weight = weight;
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

void createAdjMatrix(int** G, int n)
{
    int bit;
    int weight;
    for(int j = 0;j<n;j++)
    {
        for(int k=j;k<n;k++)
        {
            printf("Enter 1 if there exists an edge between %d and %d\t",j,k);
            scanf("%d",&bit);
            if(bit==1) 
            {
                printf("Enter the weight of the edge between %d and %d\t",j,k);
                scanf("%d",&weight);
                G[j][k] = G[k][j] = weight;
            }
            else G[j][k] = G[k][j] = 99;            
        }
    }
    displayAdjMatrix(G,n);
}

int original_parent(int i, int * parent)
{
    while(parent[i])
    {
        i = parent[i];
    }
    if(parent[i]==0) i = 0;
    return i;
}

int whether_original_parent_equal(int i, int j, int * parent)
{
    if(i!=j)
    {
        parent[j] = i;
        return 0;
    }
    return 1;
}

void Kruskal_adj_mat(int **G, int n) {
    int *parent = (int *)malloc(n*sizeof(int)); 
    int * visited = (int*)malloc(n*sizeof(int)); 

    for (int i = 0; i < n; i++) {
        parent[i] = -1; 
        visited[i] = 0; 
    }

    int ne = 0; 
    int mincost = 0; 

    while (ne < n - 1) {
        int min = 999;
        int u = -1, v = -1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (G[i][j] < min && !visited[j]) {
                    min = G[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        u = original_parent(u, parent);
        v = original_parent(v, parent);

        if (!whether_original_parent_equal(u, v, parent)) {
            printf("%d edge (%d, %d) = %d\n", ++ne, u, v, min);
            mincost += min;
            visited[v] = 1;
        }

        G[u][v] = G[v][u] = 99;
    }

    printf("The cost of MST is %d\n", mincost);
}

int main()
{
    int n,ch;
    printf("Enter the number of vertices\n");
    scanf("%d", &n);
    //struct Node** A = (struct Node**)malloc(sizeof(struct Node*) * n);
    //createAdjList(A, n);
    
    int ** G;
    G = (int **)calloc(n, sizeof(int *));
    for(int i=0;i<n;i++)
    {
        G[i] = (int*)calloc(n, sizeof(int));
    }
    createAdjMatrix(G,n);

    // struct Node** A = (struct Node**)malloc(sizeof(struct Node*) * n);
    // createAdjList(A, n);

    printf("The minimum cost spanning tree using Kruskals algorithm and adjancency matrix is \n");
    Kruskal_adj_mat(G,n);
}