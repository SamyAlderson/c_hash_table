#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "utils.h"

#define MAX_TABLE_SIZE 1024
#define MAX_KEY_SIZE 256

int main() {
    // Create a hash table with chaining collision resolution
    HashTable* table = create_hash_table(MAX_TABLE_SIZE, CHAINING);

    // Insert some key-value pairs
    insert(table, "key1", "value1");
    insert(table, "key2", "value2");
    insert(table, "key3", "value3");

    // Search for some keys
    char* value1 = search(table, "key1");
    char* value2 = search(table, "key2");
    char* value3 = search(table, "key4"); // should return NULL

    printf("Value for key 'key1': %s\n", value1);
    printf("Value for key 'key2': %s\n", value2);
    printf("Value for key 'key4': %s\n", value3);

    // Delete some keys
    delete(table, "key1");
    delete(table, "key2");

    // Search for deleted keys
    value1 = search(table, "key1");
    value2 = search(table, "key2");

    printf("Value for key 'key1': %s\n", value1);
    printf("Value for key 'key2': %s\n", value2);

    // Cleanup
    free_table(table);

    return 0;
}
```

```c
// src/utils.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

void print_error(const char* message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

// ... other utility functions ...
```

```c
// src/hash_table.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// ... hash table implementation ...
```

```c
// src/hash_table.h

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct HashTable {
    int size;
    int type;
    int* slots;
    char** keys;
    char** values;
} HashTable;

HashTable* create_hash_table(int size, int type);
void free_table(HashTable* table);
void insert(HashTable* table, char* key, char* value);
char* search(HashTable* table, char* key);
void delete(HashTable* table, char* key);

#endif