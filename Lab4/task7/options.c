#include "options.h"

status_code create_storage(Storage** st) {
    if (!st) return code_invalid_parameter;

    *st = (Storage*)malloc(sizeof(Storage));
    if (!(*st)) return code_error_alloc;

    (*st)->capacity = MIN_SIZE;
    (*st)->size = 0;
    (*st)->data = (MemoryCell*)malloc(sizeof(MemoryCell) * MIN_SIZE);
    if (!(*st)->data) {
        free(*st);
        *st = NULL;
        return code_error_alloc;
    }

    for (int i = 0; i < MIN_SIZE; i++) {
        (*st)->data[i].var = NULL;
        (*st)->data[i].value = 0;
    }

    return code_success;
}

status_code resize_storage(Storage** st) {
    if (!st || !(*st)) return code_invalid_parameter;

    size_t new_capacity = (*st)->capacity * 2;
    MemoryCell* tmp = realloc((*st)->data, sizeof(MemoryCell) * new_capacity);
    if (!tmp) {
        return code_error_alloc;
    }

    (*st)->data = tmp;
    (*st)->capacity = new_capacity;

    for (int i = (*st)->size; i < (*st)->capacity; i++) {
        (*st)->data[i].var = NULL;
        (*st)->data[i].value = 0;
    }

    return code_success;
}

void free_cell(MemoryCell* cell) {
    if (cell && cell->var) {
        free(cell->var);
        cell->var = NULL;
    }
}

void free_storage(Storage* st) {
    if (!st) return;

    if (st->data) {
        for (int i = 0; i < st->size; i++) {
            free_cell(&st->data[i]);
        }
        free(st->data);
        st->data = NULL;
    }

    free(st);
}


status_code create_cell(MemoryCell** cell, char* name, int val) {
    if (!cell || !name) return code_invalid_parameter;

    *cell = (MemoryCell*)malloc(sizeof(MemoryCell));
    if (!(*cell)) return code_error_alloc;

    (*cell)->var = strdup(name);
    if (!(*cell)->var) {
        free(*cell);
        *cell = NULL;
        return code_error_alloc;
    }

    (*cell)->value = val;
    return code_success;
}

int compare_cells(const void* a, const void* b) {
    return strcmp(((MemoryCell*)a)->var, ((MemoryCell*)b)->var);
}

int get_value_index(Storage* st, int index) {
    if (!st) return -1;
    return st->data[index].value;
}

int binary_search(Storage* st, char* key) {
    int left = 0;
    int right = st->size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (strcmp(st->data[mid].var, key) < 0) {
            left = mid + 1;
        } else if (strcmp(st->data[mid].var, key) > 0) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

status_code add_cell(Storage** st, char* name, int value) {
    if (!st || !(*st) || !name) return code_invalid_parameter;

    status_code st_act;
    MemoryCell new_cell;
    new_cell.var = strdup(name);
    if (!new_cell.var) return code_error_alloc;

    new_cell.value = value;

    if ((*st)->size == (*st)->capacity) {
        st_act = resize_storage(st);
        if (st_act != code_success) {
            free(new_cell.var);
            return st_act;
        }
    }

    (*st)->data[(*st)->size] = new_cell;
    (*st)->size++;
    qsort((*st)->data, (*st)->size, sizeof(MemoryCell), compare_cells);

    return code_success;
}


status_code edit_var(Storage* st, char* name, int new_val) {
    //printf("suka upper %s\n", name);
    int index = binary_search(st, name);
    if (index == -1) {
        return add_cell(&st, name, new_val);
    } else {
        st->data[index].value = new_val;
    }
    return code_success;
}

void print_storage(Storage* st) {
    if (!st) return;
    int size = st->size;
    for (int i = 0; i < size; i++) {
        printf("Key: %s, Value: %d\n", st->data[i].var, st->data[i].value);
    }
}

void print(Storage* st, char* name) {
    if (strcmp(name, "\0")) {
        int index = binary_search(st, name);
        //printf("%d---------------------------\n", index);
        if (index == -1) {
            return;
        }
        printf("Key: %s, Value: %d\n", st->data[index].var, st->data[index].value);
    } else {
        print_storage(st);
    }
}

Operator get_op(char symb) {
    switch (symb) {
        case '+': 
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return MULT;
        case '^':
            return POW;
        case '%':
            return MOD;    
        case '/':
            return DIV;  
        default:
            return INVALID;
    }
}

bool is_number_str(char* str) {
    if (!str) return false;
    int size = strlen(str);

    for (int i = 0; i < size; i++) {
        if (!isdigit(str[i]) && str[i] != '\0') {
            return false;
        }
    }
    return true;
}

status_code process_line(char* line, Storage* st) {
    if (!line) return code_success;

    int size = strlen(line);
    int index = 0;  
    char* cmd = (char*)malloc(sizeof(char) * size);
    if (!cmd) return code_error_alloc;

    char* arg_one = (char*)malloc(sizeof(char) * size);
    if (!arg_one) {
        free(cmd);
        return code_error_alloc;
    }

    char* arg_two = (char*)malloc(sizeof(char) * size);
    if (!arg_two) {
        free(cmd);
        free(arg_one);
        return code_error_alloc;
    }
    char c;
    bool is_read_first = false;
    bool is_read_second = false;
    bool is_read_third = false;
    Operator action;
    status_code st_act;
    for (int i = 0; i < size; i++) {
        c = line[i];
        if (!isspace(c) && c != '\n' && c != '\r' && c != ';') {
            Operator op = get_op(c);
            if (!is_read_first) {
                if (c == '=') {
                    cmd[index] = '\0';
                    index = 0;
                    is_read_first = true;
                } else {
                    cmd[index] = c;
                    index++;
                }
            } 
            else if (is_read_first && !is_read_second) {
                if (c == '=') continue;
                if (op == INVALID) {
                    arg_one[index] = c;
                    index++;
                } else {
                    action = op;
                    arg_one[index] = '\0';
                    index = 0;
                    is_read_second = true;
                }
            }
            else if (is_read_first && is_read_second) {
                if (op == INVALID) {
                    arg_two[index] = c;
                    index++;
                } else {
                    arg_two[index] = '\0';
                    index = 0;
                    is_read_third = true;
                }
            }
        } else if (isspace(c) && c != '\n' && c != '\r') {
            if (!is_read_first) {
                cmd[index] = '\0';
                index = 0;
                is_read_first = true;
            } 
        }
    }
    if (!is_read_first) {
        cmd[index] = '\0';
        index = 0;
    }
    if (!is_read_second) {
        arg_one[index] = '\0';
        index = 0;
    }
    if (!is_read_third) arg_two[index] = '\0';
    if (!strcmp(cmd, "print")) {
        print(st, arg_one);
    } else {
        if (!strcmp(arg_two, "\0")) {
            int _value;
            if (is_number_str(arg_one)) {
                _value = atof(arg_one);
                st_act = edit_var(st, cmd, _value);
                if (st_act != code_success) {
                    free(cmd);
                    free(arg_one);
                    free(arg_two);
                    return st_act;
                }
            } else {
                int index = binary_search(st, arg_one);
                if (index == -1) {
                    free(cmd);
                    free(arg_one);
                    free(arg_two);
                    return code_invalid_parameter;
                }

                _value = get_value_index(st, index);
                st_act = edit_var(st, cmd, _value);
                if (st_act != code_success) {
                    free(cmd);
                    free(arg_one);
                    free(arg_two);
                    return st_act;
                }
            }
        } else {
            int _value1, _value2;
            if (is_number_str(arg_one)) {
                _value1 = atof(arg_one);
            } else {
                int index_find = binary_search(st, arg_one);
                if (index_find == -1) {
                    free(cmd);
                    free(arg_one);
                    free(arg_two);
                    return code_invalid_parameter;
                }
                _value1 = get_value_index(st, index_find);
            }
            if (is_number_str(arg_two)) {
                _value2 = atof(arg_two);
            } else {
                int index_find = binary_search(st, arg_two);
                if (index_find == -1) {
                    free(cmd);
                    free(arg_one);
                    free(arg_two);
                    return code_invalid_parameter;
                }
                _value2 = get_value_index(st, index_find);
            }
            int result;
            st_act = solve_equation(action, _value1, _value2, &result);
            if (st_act != code_success) {
                free(cmd);
                free(arg_one);
                free(arg_two);
                return st_act;
            }
            printf("Result: %d\n", result);
            st_act = edit_var(st, cmd, result);
            if (st_act != code_success) {
                free(cmd);
                free(arg_one);
                free(arg_two);
                return st_act;
            }
        }
    }
    free(cmd);
    free(arg_one);
    free(arg_two);
    return code_success;
}

status_code solve_equation(Operator op, int a, int b, int* result) {
    if ((op == DIV || op == MOD) && b == 0) {
        return code_invalid_parameter;
    }
    if (op == PLUS) {
        *result = a + b;
    } else if (op == MINUS) {
        *result = a - b;
    } else if (op == MULT) {
        *result = a * b;
    } else if (op == DIV) {
        *result = a / b;
    } else if (op == POW) {
        if (a == 0 && b == 0) return code_invalid_parameter;
        *result = pow(a, b);
    } else if (op == MOD) {
        *result = a % b;
    } else {
        return code_invalid_parameter;
    }
    return code_success;
}

void print_error(status_code st) {
    switch (st) {
        case code_invalid_parameter:
            printf("Invalid parameter detected!!!\n");
            break;
        case code_error_alloc:
            printf("Error alloc detected!!!\n");
            break;
        case code_error_oppening:
            printf("Can`t open file!!!\n");
            break;
        default:
            break;
    }
}

status_code process_file(const char* filename) {
    if (!filename) return code_invalid_parameter;
    FILE* file = fopen(filename, "r");
    if (!file) {
        return code_error_oppening;
    }
    char* line = NULL;
    size_t len = 0;
    size_t read;
    status_code st_act;
    Storage* st = NULL;
    st_act = create_storage(&st);
    if (st_act != code_success) {
        fclose(file);
        return st_act;
    }

    while ((read = getline(&line, &len, file)) != -1) {
        st_act = process_line(line, st);
        free(line);
        line = NULL;
        if (st_act != code_success) {
            fclose(file);
            free_storage(st);
            return st_act;
        }
    }
    free(line);
    fclose(file);
    free_storage(st);
    return code_success;
}