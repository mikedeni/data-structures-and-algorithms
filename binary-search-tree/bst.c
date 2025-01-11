#include <stdio.h>
#include <stdlib.h>

// โครงสร้างข้อมูล Node
typedef struct Node
{
    int data;           // เก็บค่าข้อมูลของโหนด
    struct Node *left;  // ตัวซี้ไปยังโหนดลูกทางซ้าย
    struct Node *right; // ตัวซี้ไปยังโหนดลูกทางขวา
} Node;

// ฟังก์ชันสร้างโหนด
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        // ตรวจสอบว่าการจัดสรรหน่วยความจำสำเร็จหรือไม่
        printf("Memory error\n");
        return NULL;
    }
    // กำหนดค่าข้อมูลและตั้งค่าลูกซ้ายและขวาเป็น NULL
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ฟังก์ชันแทรกข้อมูล
Node *insertNode(Node *root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
        return root;
    }

    if (data < root->data)
    {
        // ถ้าข้อมูลน้อยกว่า root, แทรกในลูกซ้าย
        root->left = insertNode(root->left, data);
    }
    else
    {
        // ถ้าข้อมูลมากกว่าหรือเท่ากับ root, แทรกในลูกขวา
        root->right = insertNode(root->right, data);
    }

    return root;
}

// ฟังก์ชันหาค่าน้อยที่สุด
Node *findMin(Node *root)
{
    // วนลูปไปทางซ้ายสุดของ BST เพื่อหาค่าน้อยที่สุด
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// ฟังก์ชันลบข้อมูล: ใช้การเรียกซ้ำ (Recursive) เพื่อค้นหาและลบโหนดที่ต้องการ โดยรักษาคุณสมบัติของ BST ไว้ตลอดกระบวนการลบ
Node *deleteNode(Node *root, int data)
{
    // ถ้า root เป็น NULL (ไม่มีโหนด), ส่งคืน root
    if (root == NULL)
        return root;

    if (data < root->data)
    {
        // ถ้าข้อมูลน้อยกว่า root, ลบในลูกซ้าย
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        // ถ้าข้อมูลมากกว่า root, ลบในลูกขวา
        root->right = deleteNode(root->right, data);
    }
    else
    {
        // พบโหนดที่ต้องการลบ (ข้อมูลเท่ากับ root)

        // กรณีที่โหนดไม่มีลูกหรือมีลูกเดียว:
        if (root->left == NULL)
        {
            // ถ้าไม่มีลูกซ้าย, ให้ลูกขวาแทนที่โหนดปัจจุบัน
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            // ถ้าไม่มีลูกขวา, ให้ลูกซ้ายแทนที่โหนดปัจจุบัน
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // กรณีโหนดมีสองลูก: หาค่าน้อยที่สุดในลูกขวา, แทนที่ข้อมูลในโหนดปัจจุบัน, และลบโหนดลูกขวานั้นออกไป
        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// ฟังก์ชันค้นหาข้อมูล
Node *searchNode(Node *root, int data)
{
    // ถ้า root เป็น NULL หรือพบข้อมูลที่ต้องการ, ส่งคืน root
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
    {
        // ถ้าข้อมูลน้อยกว่า root, ค้นหาในลูกซ้าย
        return searchNode(root->left, data);
    }
    else
    {
        // ถ้าข้อมูลมากกว่า root, ค้นหาในลูกขวา
        return searchNode(root->right, data);
    }
}

// ฟังก์ชันการท่องใน BST แบบ in-order (ซ้าย-ราก-ขวา)
void inorderTraversal(Node *root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// ฟังก์ชันการท่องใน BST แบบ pre-order (ราก-ซ้าย-ขวา)
void preorderTraversal(Node *root)
{
    if (root == NULL)
        return;

    // แสดงค่าของโหนดปัจจุบันก่อน แล้วจึงท่องไปยังลูกซ้ายและลูกขวาตามลำดับ
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// ฟังก์ชันการท่องใน BST แบบ post-order (ซ้าย-ขวา-ราก)
void postorderTraversal(Node *root)
{
    if (root == NULL)
        return;

    // ท่องไปยังลูกซ้ายและลูกขวาก่อน แล้วจึงแสดงค่าของโหนดปัจจุบัน
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

int main()
{
    // สร้าง Binary Search Tree
    Node *root = NULL;
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);

    // ท่องใน BST แบบ in-order
    printf("In-order traversal of the BST: ");
    inorderTraversal(root);
    printf("\n\n");

    // ท่องใน BST แบบ pre-order
    printf("Pre-order traversal of the BST: ");
    ;
    preorderTraversal(root);
    printf("\n\n");

    // ท่องใน BST แบบ post-order
    printf("Post-order traversal of the BST: ");
    postorderTraversal(root);
    printf("\n\n");

    // ลบโหนดใน BST
    printf("Deleting node 20...\n");
    root = deleteNode(root, 20);
    printf("In-order traversal after deletion: ");
    inorderTraversal(root);
    printf("\n\n");

    // ค้นหาข้อมูลใน BST
    Node *searchedNode = searchNode(root, 40);
    if (searchNode != NULL)
    {
        printf("Node 40 found in the BST.\n");
    }
    else
    {
        printf("Node 40 not found in the BST.\n");
    }

    return 0;
}