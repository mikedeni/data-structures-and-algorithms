#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// โครงสร้างของโหนดใน BST
typedef struct Zoo
{
    int animalTag;
    char animalName[100];
    double wight;
    struct Zoo *left;
    struct Zoo *right;
} Zoo;

// ฟังก์ชันสร้างโหนดใหม่
Zoo *createNode(int animalTag, char animalName[], double wight)
{
    Zoo *newNode = (Zoo *)malloc(sizeof(Zoo));
    if (!newNode)
    {
        printf("Memory error\n");
        return NULL;
    }
    newNode->animalTag = animalTag;
    strcpy(newNode->animalName, animalName);
    newNode->wight = wight;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ฟังก์ชันแทรกข้อมูล
Zoo *insertNode(Zoo *root, int animalTag, char animalName[], double wight)
{
    if (root == NULL)
    {
        printf("Animal Tag: %d added successfully.\n", animalTag);
        return createNode(animalTag, animalName, wight);
    }
    if (animalTag < root->animalTag)
    {
        root->left = insertNode(root->left, animalTag, animalName, wight);
    }
    else if (animalTag > root->animalTag)
    {
        root->right = insertNode(root->right, animalTag, animalName, wight);
    }
    else
    {
        printf("Animal Tag: %d already exists.\n", animalTag);
    }
    return root;
}

// ฟังก์ชันหาค่าต่ำสุด
Zoo *findMin(Zoo *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// ฟังก์ชันลบข้อมูล
Zoo *deleteNode(Zoo *root, int animalTag)
{
    if (root == NULL)
    {
        return root;
    }
    if (animalTag < root->animalTag)
    {
        root->left = deleteNode(root->left, animalTag);
    }
    else if (animalTag > root->animalTag)
    {
        root->right = deleteNode(root->right, animalTag);
    }
    else
    {
        if (root->left == NULL)
        {
            Zoo *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Zoo *temp = root->left;
            free(root);
            return temp;
        }
        Zoo *temp = findMin(root->right);
        root->animalTag = temp->animalTag;
        strcpy(root->animalName, temp->animalName);
        root->wight = temp->wight;
        root->right = deleteNode(root->right, temp->animalTag);
    }
    return root;
}

// ฟังก์ชันค้นหา
Zoo *searchNode(Zoo *root, int animalTag)
{
    if (root == NULL || root->animalTag == animalTag)
    {
        return root;
    }
    if (animalTag < root->animalTag)
    {
        return searchNode(root->left, animalTag);
    }
    else
    {
        return searchNode(root->right, animalTag);
    }
}

// ฟังก์ชันการท่องใน in-order
void inorderTraversal(Zoo *root)
{
    if (root == NULL)
    {
        return;
    }
    inorderTraversal(root->left);
    printf("Animal Tag: %d, Name: %s, Wight: %.2f\n", root->animalTag, root->animalName, root->wight);
    inorderTraversal(root->right);
}

// ฟังก์ชันการท่องใน BST แบบ pre-order (ราก-ซ้าย-ขวา)
void preorderTraversal(Zoo *root)
{
    if (root == NULL)
        return;

    printf("Animal Tag: %d, Name: %s, Wight: %.2f\n", root->animalTag, root->animalName, root->wight);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// ฟังก์ชันการท่องใน BST แบบ post-order (ซ้าย-ขวา-ราก)
void postorderTraversal(Zoo *root)
{
    if (root == NULL)
    {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("Animal Tag: %d, Name: %s, Wight: %.2f\n", root->animalTag, root->animalName, root->wight);
}

int main()
{
    Zoo *root = NULL;
    int choice, animalTag;
    char animalName[100];
    double wight;

    while (1)
    {
        printf("Management Operations:\n");
        printf("1. Add a animal\n");
        printf("2. Delete a animal\n");
        printf("3. Search for a animal\n");
        printf("4. Display animals(sorted by ID)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter animal tag: ");
            scanf("%d", &animalTag);
            printf("Enter name: ");
            scanf(" %s", &animalName);
            printf("Enter wight: ");
            scanf("%lf", &wight);
            root = insertNode(root, animalTag, animalName, wight);
            break;
        case 2:
            printf("Enter animal tag to delete: ");
            scanf("%d", &animalTag);
            if (searchNode(root, animalTag) != NULL)
            {
                root = deleteNode(root, animalTag);
                printf("Animal tag %d deleted successfully.\n", animalTag);
            }
            else
            {
                printf("Animal tag %d not found.\n", animalTag);
            }
            break;
        case 3:
            printf("Enter animal tag to search: ");
            scanf("%d", &animalTag);
            Zoo *result = searchNode(root, animalTag);
            if (searchNode(result, animalTag) != NULL)
            {
                printf("Animal Tag: %d, Name: %s, Wight: %.2lf\n", result->animalTag, result->animalName, result->wight);
            }
            else
            {
                printf("Animal tag %d not found.\n", animalTag);
            }
            break;
        case 4:
            printf("Animal List:\n");
            inorderTraversal(root);
            break;
        case 5:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
    printf("\n");
    return 0;
}