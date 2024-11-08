#include "options.h"


int main(int argc, char* argv[]){
    if (argc != 3) {
        printf("Wrong arguments amount");
        return -1;
    }
    FILE* in = fopen(argv[1], "r");
    if (!in){
        printf("Wrong filename");
        return -2;
    }
    FILE* out = fopen(argv[2], "w");
    if (!out){
        printf("Wrong filename");
        return -2;
    }
    status status_code = ok;
    char* string = NULL;
    Node* tree = NULL;
    while(status_code == ok){
        status_code = get_string(in, &string);
        if (status_code == allocation_error) {
            free(string);
            break;
        }
        if (tree_from_expression(string, &tree) != ok) {
            free_tree(tree);
            free(string);
            printf("Allocation error");
            fclose(in);
            fclose(out);
            return -3;
        }
        print_tree(out, tree, 0);
        fprintf(out, "\n---------------------------\n");
        free_tree(tree);
        string = NULL;
    }
    if (status_code == allocation_error){
        printf("Allocation error");
        fclose(in);
        fclose(out);
        return -2;
    }
    fclose(in);
    fclose(out);
    return 0;
}