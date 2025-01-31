#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head = temp->next;  
        free(temp);          
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key not found in the list.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Function to print the list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Function to add a node at the beginning of the list
void push(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
}

// Main function
int main() {
    struct Node* head = NULL;

    // Adding elements to the list
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);

    printf("Initial list: ");
    printList(head);

    printf("Deleting node with key 3...\n");
    deleteNode(&head, 3);
    printList(head);

    printf("Deleting node with key 1...\n");
    deleteNode(&head, 1);
    printList(head);

    printf("Deleting node with key 5 (non-existent)...\n");
    deleteNode(&head, 5);
    printList(head);

    return 0;
}
