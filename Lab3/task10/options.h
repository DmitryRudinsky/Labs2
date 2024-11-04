#include <stdio.h>
#include <stdlib.h>

#ifndef LAB3_OPTIONS_H
#define LAB3_OPTIONS_H

typedef enum {
    ok,
    allocation_error,
    end
} status;

typedef struct Node{
    char key;
    struct Node* parent;
    struct Node* brother;
    struct Node* son;
} Node;

status new_son(Node* node, char key);
status new_brother(Node* node, char key);
void skip_delimiter(char** ptr);
status tree_from_expression(char* expression, Node** tree);
void free_tree(Node* node);
void print_tree(FILE*const file, Node* node, int level);
status get_string(FILE* in, char** string);


#endif //LAB3_OPTIONS_H
