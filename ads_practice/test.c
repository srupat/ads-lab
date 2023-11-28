#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertLevelOrder(struct Node* root, int data) {
    // Create a queue for level order traversal
    struct Node** queue = (struct Node**)malloc(100 * sizeof(struct Node*));
    int front = 0;
    int rear = 0;

    // If the tree is empty, assign the data to the root
    if (root == NULL) {
        root = createNode(data);
        return;
    }

    // Enqueue the root node
    queue[rear++] = root;

    // Iterate through the tree using level order traversal
    while (front < rear) {
        struct Node* tempNode = queue[front++];

        // If the left child is empty, create a new node and assign the data
        if (tempNode->left == NULL) {
            tempNode->left = createNode(data);
            break;
        }
        // If the left child is not empty, enqueue it
        else {
            queue[rear++] = tempNode->left;
        }

        // If the right child is empty, create a new node and assign the data
        if (tempNode->right == NULL) {
            tempNode->right = createNode(data);
            break;
        }
        // If the right child is not empty, enqueue it
        else {
            queue[rear++] = tempNode->right;
        }
    }

    free(queue);
}

void levelOrderTraversal(struct Node* root) {
    // Create a queue for level order traversal
    struct Node** queue = (struct Node**)malloc(100 * sizeof(struct Node*));
    int front = 0;
    int rear = 0;

    // Enqueue the root node
    queue[rear++] = root;

    // Iterate through the tree using level order traversal
    while (front < rear) {
        struct Node* tempNode = queue[front++];
        printf("%d ", tempNode->data);

        // Enqueue the left child if it exists
        if (tempNode->left != NULL) {
            queue[rear++] = tempNode->left;
        }

        // Enqueue the right child if it exists
        if (tempNode->right != NULL) {
            queue[rear++] = tempNode->right;
        }
    }

    free(queue);
}

int main() {
    // Create the root node
    struct Node* root = createNode(1);

    // Perform insertions using level order traversal
    insertLevelOrder(root, 2);
    insertLevelOrder(root, 3);
    insertLevelOrder(root, 4);
    insertLevelOrder(root, 5);

    // Print the level order traversal
    printf("Level Order Traversal: ");
    levelOrderTraversal(root);

    return 0;
}