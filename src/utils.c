#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new hash table with a specified size
void* ht_create(int size) {
    // Allocate memory for the hash table structure
    void* ht = malloc(sizeof(struct ht));
    if (ht == NULL) {
        fprintf(stderr, "Error: Out of memory\n");
        exit(1);
    }

    // Allocate memory for the array of buckets
    ht->buckets = malloc(size * sizeof(void*));
    if (ht->buckets == NULL) {
        fprintf(stderr, "Error: Out of memory\n");
        exit(1);
    }

    // Initialize the size of the hash table
    ht->size = size;

    return ht;
}

// Function to free memory allocated for a hash table
void ht_free(void* ht) {
    // Free memory allocated for the array of buckets
    free(ht->buckets);
    // Free memory allocated for the hash table structure
    free(ht);
}

// Function to hash a key
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    int c;

    // Djb2 hashing algorithm
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

// Function to insert a key-value pair into the hash table
void ht_insert(void* ht, const char* key, void* value) {
    // Get the index of the bucket where the key-value pair should be stored
    unsigned int index = hash(key) % ((struct ht*)ht)->size;

    // If the bucket is empty, create a new node
    if (((struct ht*)ht)->buckets[index] == NULL) {
        ((struct ht*)ht)->buckets[index] = malloc(sizeof(struct node));
        if (((struct ht*)ht)->buckets[index] == NULL) {
            fprintf(stderr, "Error: Out of memory\n");
            exit(1);
        }
        ((struct ht*)ht)->buckets[index]->key = malloc(strlen(key) + 1);
        if (((struct ht*)ht)->buckets[index]->key == NULL) {
            fprintf(stderr, "Error: Out of memory\n");
            exit(1);
        }
        strcpy(((struct ht*)ht)->buckets[index]->key, key);
        ((struct ht*)ht)->buckets[index]->value = value;
    }
    // If the bucket is not empty, add the key-value pair to the end of the linked list
    else {
        struct node* current = ((struct ht*)ht)->buckets[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(struct node));
        if (current->next == NULL) {
            fprintf(stderr, "Error: Out of memory\n");
            exit(1);
        }
        ((struct ht*)ht)->buckets[index]->next = current->next;
        current->next->key = malloc(strlen(key) + 1);
        if (current->next->key == NULL) {
            fprintf(stderr, "Error: Out of memory\n");
            exit(1);
        }
        strcpy(current->next->key, key);
        current->next->value = value;
    }
}

// Function to search for a key-value pair in the hash table
void* ht_search(void* ht, const char* key) {
    // Get the index of the bucket where the key should be stored
    unsigned int index = hash(key) % ((struct ht*)ht)->size;

    // Traverse the linked list of the bucket to find the key-value pair
    struct node* current = ((struct ht*)ht)->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    // If the key is not found, return NULL
    return NULL;
}

// Function to delete a key-value pair from the hash table
void ht_delete(void* ht, const char* key) {
    // Get the index of the bucket where the key should be stored
    unsigned int index = hash(key) % ((struct ht*)ht)->size;

    // Traverse the linked list of the bucket to find the key-value pair
    struct node* current = ((struct ht*)ht)->buckets[index];
    struct node* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // If the key-value pair is the head of the linked list, update the head
            if (previous == NULL) {
                ((struct ht*)ht)->buckets[index] = current->next;
            }
            // If the key-value pair is in the middle or at the end of the linked list, remove it
            else {
                previous->next = current->next;
            }
            // Free memory allocated for the key-value pair
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Node structure for linked lists
struct node {
    char* key;
    void* value;
    struct node* next;
};