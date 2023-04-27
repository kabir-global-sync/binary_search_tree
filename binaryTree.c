#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}
Node *insert(Node *node, int key)
{
    if (node == NULL)
    {
        return newNode(key);
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    return node;
}

Node *search(Node *node, int key)
{
    if (node == NULL || node->key == key)
    {
        return node;
    }
    if (key < node->key)
    {
        return search(node->left, key);
    }
    else
    {
        return search(node->right, key);
    }
}

void traverse(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    traverse(node->left);
    printf("%d ", node->key);
    traverse(node->right);
    printf("\n");
}

// Function to delete a node from the binary search tree
Node *delete(Node *node, int key)
{
    if (node == NULL)
    {
        return node;
    }
    if (key < node->key)
    {
        node->left = delete (node->left, key);
    }
    else if (key > node->key)
    {
        node->right = delete (node->right, key);
    }
    else
    {
        // Node to be deleted has no children or only one child
        if (node->left == NULL)
        {
            Node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            Node *temp = node->left;
            free(node);
            return temp;
        }
        Node *temp = node->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        node->key = temp->key;
        node->right = delete (node->right, temp->key);
    }
    return node;
}

int main()
{
    Node *root = NULL;
    int choice, key;

    do
    {
        printf("1.INSERT\n2.SEARCH\n3.DELETE\n4.TRAVERSE\n5.EXIT\nINPUT HERE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;
        case 2:
            printf("Enter key to search: ");
            scanf("%d", &key);
            if (search(root, key) == NULL)
            {
                printf("Key not found!\n");
            }
            else
            {
                printf("Key found!\n");
            }
            break;
        case 3:
            printf("Enter the key to delete: ");
            scanf("%d", &key);
            root = delete (root, key);
            break;
        case 4:
            traverse(root);
            break;
        }
    }while(choice!=5);
    return 0;
}