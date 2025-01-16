#include <stdio.h>
#include <stdlib.h>

// โครงสร้างข้อมูล Node
typedef struct Node{
    int data;           // เก็บค่าข้อมูลของโหนด
    struct Node *left;  // ตัวซี้ไปยังโหนดลูกทางซ้าย
    struct Node *right; // ตัวซี้ไปยังโหนดลูกทางขวา
} Node;

// ฟังก์ชันสร้างโหนด
Node *createNode(int data){
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode){
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
Node *insertNode(Node *root, int data){
    if (root == NULL){
        printf("Node %d inserted successfully.\n", data);
        root = createNode(data);
        return root;
    }
    if (data < root->data){
        // ถ้าข้อมูลน้อยกว่า root, แทรกในลูกซ้าย
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data){
        // ถ้าข้อมูลมากกว่า root, แทรกในลูกขวา
        root->right = insertNode(root->right, data);
    }else{
        // ถ้าข้อมูลมีอยู่แล้ว
        printf("Node %d already exists in the BST.\n", data);
    }
    return root;
}

// ฟังก์ชันหาค่าน้อยที่สุด
Node *findMin(Node *root){
    // วนลูปไปทางซ้ายสุดของ BST เพื่อหาค่าน้อยที่สุด
    while (root->left != NULL){
        root = root->left;
    }
    return root;
}

// ฟังก์ชันลบข้อมูล: ใช้การเรียกซ้ำ (Recursive) เพื่อค้นหาและลบโหนดที่ต้องการ โดยรักษาคุณสมบัติของ BST ไว้ตลอดกระบวนการลบ
Node *deleteNode(Node *root, int data){
    // ถ้า root เป็น NULL (ไม่มีโหนด), ส่งคืน root
    if (root == NULL) return root;

    if (data < root->data){
        // ถ้าข้อมูลน้อยกว่า root, ลบในลูกซ้าย
        root->left = deleteNode(root->left, data);
    }else if (data > root->data){
        // ถ้าข้อมูลมากกว่า root, ลบในลูกขวา
        root->right = deleteNode(root->right, data);
    }else{
        // พบโหนดที่ต้องการลบ (ข้อมูลเท่ากับ root)

        // กรณีที่โหนดไม่มีลูกหรือมีลูกเดียว:
        if (root->left == NULL){
            // ถ้าไม่มีลูกซ้าย, ให้ลูกขวาแทนที่โหนดปัจจุบัน
            Node *temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL){
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
    // ส่งคืนค่าโหนด root ที่อาจถูกปรับเปลี่ยน
    return root;
}

// ฟังก์ชันค้นหาข้อมูล
Node *searchNode(Node *root, int data){
    // ถ้า root เป็น NULL หรือพบข้อมูลที่ต้องการ, ส่งคืน root
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data){
        // ถ้าข้อมูลน้อยกว่า root, ค้นหาในลูกซ้าย
        return searchNode(root->left, data);
    }else{
        // ถ้าข้อมูลมากกว่า root, ค้นหาในลูกขวา
        return searchNode(root->right, data);
    }
}

// ฟังก์ชันการท่องใน BST แบบ in-order (ซ้าย-ราก-ขวา)
void inorderTraversal(Node *root){
    if (root == NULL) return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// ฟังก์ชันการท่องใน BST แบบ pre-order (ราก-ซ้าย-ขวา)
void preorderTraversal(Node *root){
    if (root == NULL) return;

    // แสดงค่าของโหนดปัจจุบันก่อน แล้วจึงท่องไปยังลูกซ้ายและลูกขวาตามลำดับ
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// ฟังก์ชันการท่องใน BST แบบ post-order (ซ้าย-ขวา-ราก)
void postorderTraversal(Node *root){
    if (root == NULL)
        return;

    // ท่องไปยังลูกซ้ายและลูกขวาก่อน แล้วจึงแสดงค่าของโหนดปัจจุบัน
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

int main(){
    Node *root = NULL;
    int choice, data;

    while (1){
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Search for a node\n");
        printf("4. In-order traversal\n");
        printf("5. Pre-order traversal\n");
        printf("6. Post-order traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("----------------------------------------------\n");

        switch (choice){
        case 1:
            int cntNum;
            printf("How many nodes do you want to insert? ");
            scanf("%d", &cntNum);
            for(int i = 0; i < cntNum; i++){
                printf("Enter data to insert node %d : ", i+1);
                scanf("%d", &data);
                root = insertNode(root, data);
            }
            break;
        case 2:
            printf("Enter data to delete: ");
            scanf("%d", &data);
            if (searchNode(root, data) == NULL){
                printf("Node %d not found in the BST.\n", data);
            }else{
                root = deleteNode(root, data);
                printf("Node %d deleted successfully.\n", data);
            }

            break;
        case 3:
            printf("Enter data to search: ");
            scanf("%d", &data);
            if (searchNode(root, data) != NULL){
                printf("Node %d found in the BST.\n", data);
            }else{
                printf("Node %d not found in the BST.\n", data);
            }
            break;
        case 4:
            printf("In-order traversal: ");
            inorderTraversal(root);
            printf("\n");
            break;
        case 5:
            printf("Pre-order traversal: ");
            preorderTraversal(root);
            printf("\n");
            break;
        case 6:
            printf("Post-order traversal: ");
            postorderTraversal(root);
            printf("\n");
            break;
        case 7:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
