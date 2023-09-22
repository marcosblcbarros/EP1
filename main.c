#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STRING_LENGTH 100


typedef struct {
    int key;
    char value[MAX_STRING_LENGTH];
} Tuple;


typedef struct Node {
    Tuple data;
    struct Node* prev;
    struct Node* next;
} Node;


#define MEMORY_POOL_SIZE 1000
static char memory_pool[MEMORY_POOL_SIZE];
static size_t used_memory = 0;


void* aloca(size_t size) {
    if (used_memory + size > MEMORY_POOL_SIZE) {
        return NULL; 
    }
    
    void* ptr = &memory_pool[used_memory];
    used_memory += size;
    return ptr;
}


void libera(void* ptr) {
    
}


Node* createNode(int key, const char* value) {
    Node* newNode = (Node*)aloca(sizeof(Node));
    if (newNode) {
        newNode->data.key = key;
        strncpy(newNode->data.value, value, MAX_STRING_LENGTH);
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    return newNode;
}


void insertNodeAtBeginning(Node** head, int key, const char* value) {
    Node* newNode = createNode(key, value);
    if (newNode) {
        newNode->next = *head;
        if (*head) {
            (*head)->prev = newNode;
        }
        *head = newNode;
    }
}


void printList(const Node* head) {
    const Node* current = head;
    while (current) {
        printf("Key: %d, Value: %s\n", current->data.key, current->data.value);
        current = current->next;
    }
}

int main(void) {
    Node* listHead = NULL;

   
    insertNodeAtBeginning(&listHead, 1, "Hello");
    insertNodeAtBeginning(&listHead, 2, "World,");
    insertNodeAtBeginning(&listHead, 3, "Marcos!");

   
    printf("Lista após inserções:\n");
    printList(listHead);



    return 0;
}
