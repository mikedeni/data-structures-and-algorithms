#include <stdio.h>
#include <stdlib.h>

typedef struct nd {
    int c;
    struct nd *next;
} node;

node *head = NULL;
node *tail = NULL;
int count = 0;

void append_beforeTail(int ch) {
    node *n = malloc(sizeof(node));
    n->c = ch;

    if (head == NULL) {
        head = n;
        tail = n;
        tail->next = NULL;
    } else if (head == tail) {
        n->next = tail;
        head = n;
    } else if (count == 2) {
        n->next = tail;
        head->next = n;
    } else {
        node *temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        n->next = head;
        temp->next = n;
    }

    count++;
}