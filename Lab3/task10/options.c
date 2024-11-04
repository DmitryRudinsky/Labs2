#include "options.h"

status new_son(Node* node, char key){
    Node* son = (Node*)malloc(sizeof(Node));
    if (!son) return allocation_error;
    son->key = key;
    son->parent = node;
    son->brother = NULL;
    son->son = NULL;
    node->son = son;
    return ok;
}

status new_brother(Node* node, char key){
    Node* brother = (Node*)malloc(sizeof(Node));
    if (!brother) return allocation_error;
    brother->key = key;
    brother->parent = node->parent;
    brother->brother = NULL;
    brother->son = NULL;
    node->brother = brother;
    return ok;
}

void skip_delimiter(char** ptr){
    while (**ptr == ' ' || **ptr == '\t') {
        (*ptr)++;
    }
}

status tree_from_expression(char* expression, Node** tree){
    char* ptr = expression;
    *tree = (Node*)malloc(sizeof(Node));
    if (!(*tree)) return allocation_error;
    Node* current = (*tree);
    skip_delimiter(&ptr);
    (*tree)->key = *ptr;
    (*tree)->brother = NULL;
    (*tree)->parent = NULL;
    (*tree)->son = NULL;
    ptr++;
    while (*ptr){
        switch (*ptr){
            case ' ':
                skip_delimiter(&ptr);
                break;
            case '(':
                ++ptr;
                skip_delimiter(&ptr);
                new_son(current, *ptr);
                if (!current->son) return allocation_error;
                current = current->son;
                ++ptr;
                break;
            case ',':
                ++ptr;
                skip_delimiter(&ptr);
                new_brother(current, *ptr);
                if (!current->brother) return allocation_error;
                current = current->brother;
                ++ptr;
                break;
            case ')':
                current = current->parent;
                ++ptr;
                break;
        }
    }
    return ok;
}

void free_tree(Node* node){
    if (!node) return;
    free_tree(node->son);
    free_tree(node->brother);
    free(node);
}

void print_tree(FILE*const file, Node* node, int level){
    if (!node) return;
    for (int i = 0; i < level; i++) fprintf(file, "\t");
    fprintf(file, "%c\n", node->key);
    print_tree(file, node->son, level+1);
    print_tree(file, node->brother, level);
    return;
}

status get_string(FILE* in, char** string){
    char symbol = fgetc(in);
    int capacity = 2;
    int length = 0;
    *string = (char*)malloc(sizeof(char) * capacity);
    if (!(*string)) return allocation_error;
    while (symbol != '\n' && symbol != EOF){
        (*string)[length] = symbol;
        length++;
        if (length == capacity){
            capacity *= 2;
            char* ptr = realloc(*string, capacity);
            if (!ptr) {
                free(*string);
                return allocation_error;
            }
            *string = ptr;
        }
        symbol = fgetc(in);
    }
    (*string)[length] = 0;
    if (symbol == EOF) return end;
    return ok;
}