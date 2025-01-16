#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// โครงสร้างข้อมูล Node สำหรับนักเรียน
typedef struct Node {
    int rollNo;              // เลขที่ของนักเรียน
    char name[50];           // ชื่อนักเรียน
    float score;             // คะแนนของนักเรียน
    struct Node *left;       // ตัวชี้ไปยังโหนดลูกซ้าย
    struct Node *right;      // ตัวชี้ไปยังโหนดลูกขวา
} Node;

// ฟังก์ชันสร้างโหนดใหม่
Node *createNode(int rollNo, char *name, float score) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->rollNo = rollNo;
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ฟังก์ชันแทรกข้อมูล
Node *insertNode(Node *root, int rollNo, char *name, float score) {
    if (root == NULL) {
        printf("Student with roll number %d inserted successfully.\n", rollNo);
        return createNode(rollNo, name, score);
    }

    if (rollNo < root->rollNo) {
        root->left = insertNode(root->left, rollNo, name, score);
    } else if (rollNo > root->rollNo) {
        root->right = insertNode(root->right, rollNo, name, score);
    } else {
        printf("Student with roll number %d already exists.\n", rollNo);
    }
    return root;
}

// ฟังก์ชันค้นหานักเรียน
Node *searchNode(Node *root, int rollNo) {
    if (root == NULL || root->rollNo == rollNo)
        return root;

    if (rollNo < root->rollNo)
        return searchNode(root->left, rollNo);
    else
        return searchNode(root->right, rollNo);
}

// ฟังก์ชันแสดงข้อมูลนักเรียนแบบ in-order
void inorderTraversal(Node *root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("Roll No: %d, Name: %s, Score: %.2f\n", root->rollNo, root->name, root->score);
    inorderTraversal(root->right);
}

// ฟังก์ชันหลัก
int main() {
    Node *root = NULL;
    int choice, rollNo;
    char name[50];
    float score;

    while (1) {
        printf("\nStudent Record System:\n");
        printf("1. Insert a student\n");
        printf("2. Search for a student\n");
        printf("3. Display all students (In-order traversal)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Roll Number: ");
            scanf("%d", &rollNo);
            printf("Enter Name: ");
            scanf(" %[^\n]", name); // รับชื่อพร้อมช่องว่าง
            printf("Enter Score: ");
            scanf("%f", &score);
            root = insertNode(root, rollNo, name, score);
            break;

        case 2:
            printf("Enter Roll Number to search: ");
            scanf("%d", &rollNo);
            Node *foundNode = searchNode(root, rollNo);
            if (foundNode) {
                printf("Found: Roll No: %d, Name: %s, Score: %.2f\n", foundNode->rollNo, foundNode->name, foundNode->score);
            } else {
                printf("Student with Roll Number %d not found.\n", rollNo);
            }
            break;

        case 3:
            printf("Student Records (In-order Traversal):\n");
            inorderTraversal(root);
            break;

        case 4:
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
