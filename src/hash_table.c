#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_KEY_LENGTH 256
#define DEFAULT_VALUE 0

// Chaining collision resolution
typedef struct Node {
    char key[MAX_KEY_LENGTH];
    int value;
    struct Node* next;
} Node;

// Hash table structure
typedef struct {
    Node** buckets;
    int size;
} HashTable;

// Initialize the hash table
HashTable* hash_table_init() {
    HashTable* table = malloc(sizeof(HashTable));
    table->buckets = calloc(TABLE_SIZE, sizeof(Node*));
    table->size = TABLE_SIZE;
    return table;
}

// Hash function (simple modulo)
int hash_function(const char* key) {
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

// Insert a key-value pair into the hash table
int hash_table_insert(HashTable* table, const char* key, int value) {
    int index = hash_function(key);
    Node* node = &table->buckets[index][0];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            // Key already exists, update value
            node->value = value;
            return 1;
        }
        if (node->next == NULL) {
            break;
        }
        node = node->next;
    }
    // Create a new node and add it to the bucket
    node = malloc(sizeof(Node));
    strcpy(node->key, key);
    node->value = value;
    node->next = table->buckets[index];
    table->buckets[index] = node;
    return 0;
}

// Search for a key in the hash table
int* hash_table_search(HashTable* table, const char* key) {
    int index = hash_function(key);
    Node* node = table->buckets[index];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return &node->value;
        }
        node = node->next;
    }
    return NULL;
}

// Delete a key from the hash table
int hash_table_delete(HashTable* table, const char* key) {
    int index = hash_function(key);
    Node** node_ptr = &table->buckets[index];
    Node* node = *node_ptr;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            // Key found, update the bucket pointer
            *node_ptr = node->next;
            free(node);
            return 0;
        }
        node_ptr = &node->next;
        node = node->next;
    }
    return 1; // Key not found
}

// Print the hash table contents
void hash_table_print(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = table->buckets[i];
        printf("Bucket %d: ", i);
        while (node != NULL) {
            printf("%s -> %d, ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
}

// Free the hash table resources
void hash_table_free(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = table->buckets[i];
        while (node != NULL) {
            Node* next = node->next;
            free(node);
            node = next;
        }
    }
    free(table->buckets);
    free(table);
}

int main() {
    HashTable* table = hash_table_init();
    hash_table_insert(table, "key1", 10);
    hash_table_insert(table, "key2", 20);
    hash_table_print(table);
    int* value = hash_table_search(table, "key1");
    if (value != NULL) {
        printf("Value: %d\n", *value);
    }
    hash_table_delete(table, "key1");
    hash_table_print(table);
    hash_table_free(table);
    return 0;
}