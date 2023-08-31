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
            
        }
    }
    displayAdjMatrix(G,n);
}

int all_are_visited(int * visited, int n)
{
    int i = 1;
    for(int i = 0;i<n;i++)
    {
        if (visited[i] == 0)
        {
            i=0;
            break;
        } 
    }
    return i;
}

int minKey(int * visited, int* distance, int n)
{
    int min = 99, index;
    for(int i=0;i<n;i++)
    {
        if(visited[i]==0 && distance[i]<min)
        {
            min = distance[i];
            index = i;
        }
    }
    return index;
}

void displayMST(int * parent,int n)
{
    printf("Edge\n");
    for(int i=1;i<n;i++)
    {
        printf("%d - %d\n",parent[i],i);
    }
}

void PrimsAlgorithm_adj_mat(int ** G, int n)
{
    int * parent = (int *)calloc(n,sizeof(int));    
    int * visited = (int *)calloc(n,sizeof(int));
    int * distance = (int *)calloc(n,sizeof(int));

    for(int k =1;k<n;k++)
    {
        distance[k] = 99;
    }

    int u;
    
    distance[0] = 0;
    parent[0] = -1;

    for(int i=0;i<n-1;i++)
    {
        u = minKey(visited,distance,n);
        visited[u] = 1;
        for(int j=0;j<n;j++)
        {
            if(G[u][j]!=0 && visited[j]==0 && G[u][j]<distance[j])
            {
                parent[j] = u;
                distance[j] = G[u][j];
            }
        }
        
    }
    displayMST(parent,n);
}

void PrimsAlgorithm_adj_list(struct Node * A[], int n)
{
    int * parent = (int *)calloc(n, sizeof(int));    
    int * visited = (int *)calloc(n, sizeof(int));
    int * distance = (int *)calloc(n, sizeof(int));
    int * weight = (int *)calloc(n, sizeof(int)); // Added weight array

    for(int k = 1; k < n; k++)
    {
        distance[k] = 99;
    }

    int u;
    
    distance[0] = 0;
    parent[0] = -1;

    for(int i = 0; i < n - 1; i++)
    {
        u = minKey(visited, distance, n);
        visited[u] = 1;
        struct Node * temp = A[u]->next; // Start from the adjacency list of u
        while(temp != NULL)
        {
            int v = temp->data;
            if(visited[v] == 0 && temp->weight < distance[v])
            {
                parent[v] = u;
                distance[v] = temp->weight;
                weight[v] = temp->weight; // Store weight
            }
            temp = temp->next;
        }
    }
    displayMST(parent, n);
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

    struct Node** A = (struct Node**)malloc(sizeof(struct Node*) * n);
    createAdjList(A, n);

    printf("The minimum spanning tree using Adjacency Matrix is:\n");
    PrimsAlgorithm_adj_mat(G,n);
    printf("The minimum spanning tree using Adjacency List is:\n");
    PrimsAlgorithm_adj_list(A,n);
}