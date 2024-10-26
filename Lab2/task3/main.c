#include "options.h"


int main() {
    char *substring = "111";
    char *answer = NULL;
    int result = findSubstringInFiles(substring, &answer, 3, "test1.txt", "test2.txt", "test3.txt");
    if (result == no_memory) {
        printError(result);
        return result;
    }
    if (result == file_error) {
        printError(result);
        return result;
    }

    printf("%s\n", answer);
    free(answer);
    answer = NULL;

    printf("\nThe program has finished correctly.\n");
    return success;
}