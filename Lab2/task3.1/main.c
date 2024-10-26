#include "options.h"


int main(){
    answer* result = NULL;
    int amount = 0;
    switch(substrings_function(&result, &amount, "1\n1", 3, "test1.txt", "test2.txt", "test3.txt")){
        case string_ok:
            for(int i = 0; i < amount; i++){
                printf("File: %s   String: %d   Symbol: %d\n", result[i].file, result[i].string, result[i].symbol);
            }
            free(result);
            return 0;
        case string_allocation_error:
            printf("Allocation error");
            free(result);
            return -1;
    }
}
