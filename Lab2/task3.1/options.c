#include "options.h"

status substrings_function(answer** result, int* substrings_amount, const char* substring, const int file_amount, ...){
    *substrings_amount = 0;
    int answer_array_realloc = 2;
    *result = (answer*)malloc(sizeof(answer) * answer_array_realloc);
    if (!(*result)) return string_allocation_error;
    va_list filenames;
    va_start(filenames, file_amount);
    for (int i = 0; i < file_amount; i++){
        char* filename = va_arg(filenames, char*);
        FILE* file = fopen(filename, "task4");
        if (!file) continue;
        int current_string = 1;
        int current_symbol = 0;
        char symbol;
        const int substring_length = strlen(substring);
        int substring_index = 0;
        do {
            symbol = fgetc(file);
            if (symbol == '\n' && substring_index == 0 && substring[substring_index] != '\n'){
                current_string++;
                current_symbol = -1;
            }
            if (symbol == substring[substring_index]){
                substring_index++;
                if (substring_index == substring_length){
                    if ((*substrings_amount) == answer_array_realloc) {
                        answer_array_realloc *= 2;
                        answer* ptr = realloc(*result, sizeof(answer)* answer_array_realloc);
                        if (!ptr) return string_allocation_error;
                        *result = ptr;
                    }
                    fseek(file, -substring_index + 1, SEEK_CUR);
                    substring_index = 0;
                    answer current;
                    current.file = filename;
                    current.string = current_string;
                    current.symbol = current_symbol;
                    if (substring[0] == '\n') {
                        current_string++;
                        current_symbol = -1;
                    }
                    (*result)[*substrings_amount] = current;
                    (*substrings_amount)++;
                    current_symbol++;
                }
            } else {
                if(substring[0] == '\n' && substring_index != 0){
                    current_string++;
                    current_symbol = -1;
                }
                fseek(file, -substring_index, SEEK_CUR);
                substring_index = 0;
                current_symbol++;
            }
        } while (symbol != EOF);
    }
    va_end(filenames);
    return string_ok;
}